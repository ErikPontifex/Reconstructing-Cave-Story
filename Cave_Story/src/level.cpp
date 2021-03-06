//
//  level.cpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-22.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#include "level.hpp"
#include "graphics.hpp"
#include "util.hpp"

#include "tinyxml2.h"
#include <SDL2/SDL.h>

#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace tinyxml2;

Level::Level() {}

Level::Level(string mapName, Vector2 spawnPoint, Graphics &graphics) :
    _mapName(mapName),
    _spawnPoint(spawnPoint),
    _size(Vector2(0, 0))
{
    loadMap(mapName, graphics);
}

Level::~Level() {
    
}

void Level::loadMap(string mapName, Graphics &graphics) {
    // Parse the .tmx file
    
    // Represents entire XML document
    XMLDocument doc;
    stringstream ss;
    ss << "content/maps/" << mapName << ".tmx";
    
    doc.LoadFile(ss.str().c_str());
    
    XMLElement* mapNode = doc.FirstChildElement("map");
    
    // Get width and height of map and store it in _size
    
    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    _size = Vector2(width, height);
    
    // Get width and height of tiles and store it in _tileSize
    
    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);
    _tileSize = Vector2(tileWidth, tileHeight);
    
    // Load tilesets
    
    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if (pTileset != NULL) {
        while (pTileset) {
            int firstgid;
            
            const char* source = pTileset->Attribute("source"); //
            
            stringstream ss;
            ss << source;
            
            pTileset->QueryIntAttribute("firstgid", &firstgid);
            
            SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
            
            if (tex == NULL) cout << "tex is null\n";
            else cout << "tex is NOT null\n";
            
            _tilesets.push_back(Tileset(tex, firstgid));
            
            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }
    
    // Load layers
    
    XMLElement* pLayer = mapNode->FirstChildElement("layer");
    if (pLayer != NULL) {
        while (pLayer) {
            
            XMLElement* pData = pLayer->FirstChildElement("data");
            if (pData != NULL) {
                while (pData) {
                    
                    XMLElement* pTile = pData->FirstChildElement("tile");
                    if (pTile != NULL) {
                        int tileCounter = 0;
                        while (pTile) {
                            // Build each individual tile here
                            // If gid is 0, no tile should be drawn

                            if (pTile->IntAttribute("gid") == 0) {
//                                cout << "No attribute\n";
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile")) {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                }
                                else {
                                    break;
                                }
                            }
                            
                            // Get tileset for this gid
                            
                            int gid = pTile->IntAttribute("gid");
//                            cout << "gid = " << gid << "\n";
                            Tileset tls;
                            
                            for (int i = 0; i < _tilesets.size(); i++) {
                                if (_tilesets[i].FirstGid <= gid) {
                                    tls = _tilesets.at(i);
                                    break;
                                }
                            }
                            
                            if (tls.FirstGid == -1) {
                                // No tileset found for gid
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile")) {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                }
                                else {
                                    break;
                                }
                            }
                            
                            // Get position of tile in level
                            int xx = 0;
                            int yy = 0;
                            
                            xx = tileCounter % width;
                            xx *= tileWidth;
                            yy += tileHeight * (tileCounter / width);
                            
                            Vector2 finalTilePosition = Vector2(xx, yy);
                            
                            // Calculate the position of the tile in the tileset
                            
                            int tilesetWidth, tilesetHeight;
                            SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
                            
                            int tsxx = gid % (tilesetWidth / tileWidth) - 1;
                            tsxx *= tileWidth;
                            
                            int tsyy = 0;
                            int amt = (gid / (tilesetWidth / tileWidth));
                            tsyy = tileHeight * amt;
                            
                            Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);
                            
//                            cout << "tilecounter " << tileCounter << "\n";
//                            cout << "xx = " << xx << "\n";
//                            cout << "yy = " << yy << "\n";
//                            cout << "tsxx = " << tsxx << "\n";
//                            cout << "tsyy = " << tsyy << "\n";
                            
                            Tile tile(tls.Texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
                            
                            _tileList.push_back(tile);
                            tileCounter++;
                            
                            pTile = pTile->NextSiblingElement("tile");
                        }
                    }
                    
                    pData = pData->NextSiblingElement("data");
                }
            }
            
            pLayer = pLayer->NextSiblingElement("layer");
        }
    }
    
    // parse out the collisions
    XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if (pObjectGroup != NULL) {
        while (pObjectGroup) {
            const char* name = pObjectGroup->Attribute("name");
            stringstream ss;
            ss << name;
            
            if (ss.str() == "collisions") {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        float x, y, width, height;
                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        width = pObject->FloatAttribute("width");
                        height = pObject->FloatAttribute("height");
                        
                        cout << "\nx = " << x * kScale;
                        cout << "\ny = " << y * kScale;
                        cout << "\nwidth = " << width * kScale;
                        cout << "\nheight = " << height * kScale;
                        
                        _collisionRects.push_back(Rectangle(
                                                            ceil(x) * kScale,
                                                            ceil(y) * kScale,
                                                            ceil(width) * kScale,
                                                            ceil(height)  * kScale));
                        
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            
            else if (ss.str() == "slopes") {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        vector<Vector2> points;
                        Vector2 p1;
                        p1 = Vector2(ceil(pObject->FloatAttribute("x")), ceil(pObject->FloatAttribute("y")));
                        
                        XMLElement* pPolyline = pObject->FirstChildElement("polyline");
                        if (pPolyline != NULL) {
                            vector<string> pairs;
                            const char* pointString = pPolyline->Attribute("points");
                            
                            stringstream ss;
                            ss << pointString;
                            
                            Utils::split(ss.str(), pairs, ' ');
                            
                            // Loop through pairs and split them into Vector2s and store them in points vector
                            
                            for (int i = 0; i < pairs.size(); i++) {
                                vector<string> ps;
                                Utils::split(pairs.at(i), ps, ',');
                                points.push_back(Vector2(
                                                        stoi(ps.at(0)),
                                                        stoi(ps.at(1))));
                            }

                        }
                        
                        for (int i = 0; i < points.size(); i += 2) {
                            _slopes.push_back(Slope(
                                                    Vector2((p1.x + points.at(i < 2 ? i : i - 1).x) * kScale,
                                                            (p1.y + points.at(i < 2 ? i : i - 1).y) * kScale),
                                                    Vector2((p1.x + points.at(i < 2 ? i + 1 : i).x) * kScale,
                                                            (p1.y + points.at(i < 2 ? i + 1 : i).y) * kScale)));
                        }
                    
                    pObject = pObject->NextSiblingElement("object");
                        
                    }
                }
            }
            
            else if (ss.str() == "spawn points") {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        
                        const char* name = pObject->Attribute("name");
                        stringstream ss;
                        ss << name;
                        if (ss.str() == "player") {
                            _spawnPoint = Vector2(ceil(x) * kScale, ceil(y) * kScale);
                        }
                        
                        pObject = pObject->NextSiblingElement("object");
                        
                    }
                }
            }
            

            
            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
    
    
}

void Level::update(int elapsedTime) {
    
}

void Level::draw(Graphics &graphics) {
//    cout << "_tilelist.size() = " << _tileList.size() << "\n";
    for (int i = 0; i < _tileList.size(); i++) {
        _tileList.at(i).draw(graphics);
    }
}

vector<Rectangle> Level::checkTileCollisions(const Rectangle &other) {
    vector<Rectangle> others;
    for (int i = 0; i < _collisionRects.size(); i++) {
        if (_collisionRects.at(i).collidesWith(other)) {
            others.push_back(_collisionRects.at(i));
        }
    }
    return others;
}

vector<Slope> Level::checkSlopeCollisions(const Rectangle &other) {
    vector<Slope> others;
    for (int i = 0; i < _slopes.size(); i++) {
        if (_slopes.at(i).collidesWith(other)) {
            others.push_back(_slopes.at(i));
        }
    }
    return others;
    
}

const Vector2 Level::getPlayerSpawnPoint() const {
    return _spawnPoint;
}

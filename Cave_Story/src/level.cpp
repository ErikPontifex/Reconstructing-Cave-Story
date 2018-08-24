//
//  level.cpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-22.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#include "level.hpp"
#include "graphics.hpp"

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
    
    
}

void Level::update(int elapsedTime) {
    
}

void Level::draw(Graphics &graphics) {
//    cout << "_tilelist.size() = " << _tileList.size() << "\n";
    for (int i = 0; i < _tileList.size(); i++) {
        _tileList.at(i).draw(graphics);
    }
}

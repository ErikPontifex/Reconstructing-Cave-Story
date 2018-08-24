//
//  level.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-22.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef level_hpp
#define level_hpp

#include "globals.h"
#include "tile.hpp"
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;
using namespace globals;

class Graphics;
struct SDL_Texture;
struct Tileset;

class Level {
public:
    Level();
    Level(string mapName, Vector2 spawnPoint, Graphics &graphics);
    ~Level();
    
    void update(int elapsedTime);
    void draw(Graphics & graphics);
    
private:
    string _mapName;
    Vector2 _spawnPoint;
    
    // Width and height of entire map
    
    Vector2 _size;
    Vector2 _tileSize;
    
    SDL_Texture* _backgroundTexture;
    
    vector<Tile> _tileList;
    vector<Tileset> _tilesets;
    
    // Load map
    
    void loadMap(string mapName, Graphics &graphics);
};

// Tileset struct

struct Tileset {
    SDL_Texture* Texture;
    int FirstGid;
    
    Tileset() {
        FirstGid = -1;
    }
    
    Tileset(SDL_Texture* texture, int firstGid) {
        Texture = texture;
        FirstGid = firstGid;
    }
};

#endif /* level_hpp */

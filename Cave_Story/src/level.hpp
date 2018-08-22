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
#include <stdio.h>
#include <string>
using namespace std;
using namespace globals;

class Graphics;
struct SDL_Texture;

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
    
    SDL_Texture* _backgroundTexture;
    
    // Load map
    
    void loadMap(string mapName, Graphics &graphics);
};

#endif /* level_hpp */

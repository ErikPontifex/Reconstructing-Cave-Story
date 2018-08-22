//
//  level.cpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-22.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#include "level.hpp"
#include "graphics.hpp"
#include <SDL2/SDL.h>

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
    _backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
                                                      graphics.loadImage("content/backgrounds/bkBlue.png"));
    _size = Vector2(1280, 960);
}

void Level::update(int elapsedTime) {
    
}

void Level::draw(Graphics &graphics) {
    SDL_Rect sourceRect = { 0, 0, 64, 64 };
    SDL_Rect destRect;
    
    for (int x = 0; x < _size.x/64; x++) {
        for (int y = 0; y < _size.y/64; y++) {
            destRect.x = x * 64;
            destRect.y = y * 64;
            destRect.w = 64;
            destRect.h = 64;
            graphics.blitSurface(_backgroundTexture, &sourceRect, &destRect);
        }
    }
}

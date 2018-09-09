//
//  tile.cpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-24.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#include "tile.hpp"
#include "graphics.hpp"

#include <SDL2/SDL.h>

Tile::Tile() {}

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) :
    _tileset(tileset),
    _size(size),
    _tilesetPosition(tilesetPosition),
    _position(Vector2(position.x * kScale, position.y * kScale))
{}

void Tile::update(int elapsedTime) {
    
}

void Tile::draw(Graphics &graphics) {
    SDL_Rect destRect = {
                        _position.x,
                        _position.y,
                        _size.x * kScale,
                        _size.y * kScale
    };
    
    SDL_Rect sourceRect = {
        _tilesetPosition.x,
        _tilesetPosition.y,
        _size.x,
        _size.y
    };
    
    graphics.blitSurface(_tileset, &sourceRect, &destRect);
}

Tile::~Tile() {
    
}

//
//  sprite.cpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-20.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#include "sprite.hpp"
#include "graphics.hpp"
#include "globals.h"
using namespace globals;

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics,
               const std::string &filepath,
               int sourceX,
               int sourceY,
               int width,
               int height,
               float posX,
               float posY) :
                        _x(posX),
                        _y(posY)
{
    _sourceRect.x = sourceX;
    _sourceRect.y = sourceY;
    _sourceRect.w = width;
    _sourceRect.h = height;
    
    _spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(),
                                                graphics.loadImage(filepath));
    
    if (_spriteSheet == NULL) {
        printf("\nError: Unable to load image\n");
    }
    
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
    SDL_Rect destinationRectangle = {x, y, _sourceRect.w, _sourceRect.h};
    graphics.blitSurface(_spriteSheet, &_sourceRect, &destinationRectangle);
}

void Sprite::update() {}

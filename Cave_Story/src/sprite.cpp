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
    
    _boundingBox = Rectangle(_x, _y, width * kScale, height * kScale);
    
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
    SDL_Rect destinationRectangle = {x, y, _sourceRect.w * kScale, _sourceRect.h * kScale};
    graphics.blitSurface(_spriteSheet, &_sourceRect, &destinationRectangle);
}

void Sprite::update() {
    _boundingBox = Rectangle(_x, _y, _sourceRect.w * kScale, _sourceRect.h * kScale);
}

const Rectangle Sprite::getBoundingBox() const {
    return _boundingBox;
}

const sides::Side Sprite::getCollisionSide(Rectangle &other) const {
    int amtRight, amtLeft, amtTop, amtBottom;
    
    amtRight = getBoundingBox().getRight() - other.getLeft();
    amtLeft = other.getRight() - getBoundingBox().getLeft();
    amtTop = other.getBottom() - getBoundingBox().getTop();
    amtBottom = getBoundingBox().getBottom() - other.getTop();
    
    int vals[4] = {abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom)};
    int lowest = vals[0];
    for (int i = 0; i < 4; i++) {
        if (vals[i] < lowest) {
            lowest = vals[i];
        }
    }
    
    return
            lowest == abs(amtRight)  ? sides::RIGHT :
            lowest == abs(amtLeft)   ? sides::LEFT :
            lowest == abs(amtTop)    ? sides::TOP :
            lowest == abs(amtBottom) ? sides::BOTTOM :
            sides::NONE;
}

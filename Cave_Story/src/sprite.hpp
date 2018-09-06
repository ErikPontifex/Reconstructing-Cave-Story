//
//  sprite.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-20.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef sprite_hpp
#define sprite_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include "rectangle.hpp"
#include "globals.h"
using namespace globals;

struct Graphics;

class Sprite {

public:
    Sprite();
    Sprite(Graphics &graphics,
           const std::string &filepath,
           int sourceX,
           int sourceY,
           int width,
           int height,
           float posX,
           float posY);
    
    virtual ~Sprite();
    virtual void update();
    void draw(Graphics &graphics, int x, int y);
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;
    float _x, _y;
    
    const Rectangle getBoundingBox() const;
    
    // Determine which side collision happened on
    const sides::Side getCollisionSide(Rectangle &other) const;
    
private:
    
protected:
    Rectangle _boundingBox;
    
};

#endif /* sprite_hpp */

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

struct Graphics;

struct Sprite {
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
    
private:
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;
    
    float _x, _y;
};

#endif /* sprite_hpp */

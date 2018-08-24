//
//  graphics.cpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-20.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#include "graphics.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "globals.h"
#include <iostream>
using namespace globals;

Graphics::Graphics() {
    SDL_CreateWindowAndRenderer(kScreenWidth,
                                kScreenHeight,
                                0,
//                                SDL_WINDOW_FULLSCREEN_DESKTOP,
                                &_window,
                                &_renderer);
    SDL_SetWindowTitle(_window, "Cave Story");
    
}

Graphics::~Graphics() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
    std::cout << "filePath = " << filePath << "\n";
    
    if (_spriteSheets.count(filePath) == 0) {
        std::cout << "loading image\n";
        _spriteSheets[filePath] = IMG_Load(filePath.c_str());
        if (_spriteSheets[filePath] == NULL) {
            std::cout << "file failed to load\n";
        }
    }
    
    return _spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture,
                           SDL_Rect* source_rectangle,
                           SDL_Rect* destination_rectangle) {
    SDL_RenderCopy(_renderer, texture, source_rectangle, destination_rectangle);
}

void Graphics::flip() {
    SDL_RenderPresent(_renderer);
}

void Graphics::clear() {
    SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
    return _renderer;
}

//
//  graphics.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-20.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef graphics_hpp
#define graphics_hpp

#include <stdio.h>
#include <map>
#include <string>
#include "SDL2/SDL.h"

struct SDL_Window;
struct SDL_Renderer;

struct Graphics {
    Graphics();
    ~Graphics();
    
    void blitSurface(SDL_Surface* source,
                     SDL_Rect* source_rectangle,
                     SDL_Rect* destination_rectangle);
    
    // SDL_Surface* loadImage
    // load image into _spriteSheets map if it doesn't already exist
    // As a result, each image will only be loaded once
    // Returns the image from the map regardless of whether it was just loaded
    
    SDL_Surface* loadImage(const std::string &filePath);
    
    // void blitSurface
    // Draws a texture to a certain part of the screen
    
    void blitSurface(SDL_Texture* source,
                     SDL_Rect* sourceRectangle,
                     SDL_Rect* destinationRectangle);
    
    // void flip
    // Renders everything to the screen
    
    void flip();
    
    // void clear
    // Clears the screen
    
    void clear();
    
    // SDL_Renderer* getRenderer
    // Return renderer
    
    SDL_Renderer* getRenderer() const;
    
private:
    SDL_Window*     _window;
    SDL_Renderer*   _renderer;
    std::map<std::string, SDL_Surface*> _spriteSheets;
};



#endif /* graphics_hpp */

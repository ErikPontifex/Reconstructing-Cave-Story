//
//  input.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-20.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef input_hpp
#define input_hpp

#include <map>
#include <SDL2/SDL.h>

struct Input {
    void beginNewFrame();
    void keyUpEvent(const SDL_Event& event);
    void keyDownEvent(const SDL_Event& event);
    
    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);
private:
    
    // Keys held during current frame
    
    std::map<SDL_Scancode, bool> _heldKeys;
    
    // Keys pressed during current frame
    
    std::map<SDL_Scancode, bool> _pressedKeys;
    
    // Keys released during current frame
    
    std::map<SDL_Scancode, bool> _releasedKeys;
};

#endif /* input_hpp */

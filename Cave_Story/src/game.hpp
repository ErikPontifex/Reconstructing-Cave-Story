//
//  game.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-19.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>

struct SDL_Window;

struct Game {
    Game();
    ~Game();
    
private:

    void eventLoop();
    void update();
    void draw();
    SDL_Window* screen_;
};

#endif /* game_hpp */

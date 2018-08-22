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
#include "animatedSprite.hpp"

class Graphics;

struct Game {
    Game();
    ~Game();
    
private:

    void eventLoop();
    void update(float elapsedTime);
    void draw(Graphics &graphics);
    void printFps(int start_time_ms);
    
    AnimatedSprite _player;
};

#endif /* game_hpp */

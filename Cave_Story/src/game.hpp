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
#include "player.hpp"
#include "level.hpp"

class Graphics;

struct Game {
    Game();
    ~Game();
    
private:

    void eventLoop();
    void update(float elapsedTime);
    void draw(Graphics &graphics);
    void printFps(int start_time_ms);
    
    Player _player;
    Level _level;
};

#endif /* game_hpp */

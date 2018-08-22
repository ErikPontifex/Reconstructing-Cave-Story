//
//  player.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-21.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include "globals.h"
#include "animatedSprite.hpp"
using namespace std;
using namespace globals;

class Graphics;

class Player : public AnimatedSprite {
public:
    Player();
    Player(Graphics &graphics, float x, float y);
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    
    // Move player left by -dx
    
    void moveLeft();
    
    // Move player right by dx
    
    void moveRight();
    
    // Stop moving player
    // Play idle animation
    
    void stopMoving();
    
    virtual void animationDone(string currentAnimation);
    virtual void setupAnimations();
    
private:
    float _dx, _dy;
    
    Direction _facing;
};

#endif /* player_hpp */

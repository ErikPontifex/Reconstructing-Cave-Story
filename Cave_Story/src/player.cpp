//
//  player.cpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-21.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#include "player.hpp"
#include "graphics.hpp"

namespace player_constants {
    const float kWalkSpeed = 0.2f;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y) :
    AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100)
{
    graphics.loadImage("content/sprites/MyChar.png");
    
    setupAnimations();
    playAnimation("RunRight");
}

void Player::setupAnimations() {
        addAnimation(1, 0, 0,  "IdleLeft",  16, 16, Vector2(0, 0));
        addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
        addAnimation(3, 0, 0,  "RunLeft",   16, 16, Vector2(0, 0));
        addAnimation(3, 0, 16, "RunRight",  16, 16, Vector2(0, 0));
    
}

void Player::animationDone(string currentAnimation) {
    
}

void Player::moveLeft() {
    _dx = -player_constants::kWalkSpeed;
    playAnimation("RunLeft");
    _facing = LEFT;
}

void Player::moveRight() {
    _dx = player_constants::kWalkSpeed;
    playAnimation("RunRight");
    _facing = RIGHT;
}

void Player::stopMoving() {
    _dx = 0.0f;
    playAnimation(_facing == RIGHT ? "IdleRight" : "IdleLeft");
}


void Player::update(float elapsedTime) {
    // Move by dx
    _x += _dx * elapsedTime;
    
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
    AnimatedSprite::draw(graphics, _x, _y);
}

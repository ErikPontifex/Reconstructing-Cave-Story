//
//  player.cpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-21.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#include "player.hpp"
#include "graphics.hpp"
#include <cmath>

namespace player_constants {
    const float kWalkSpeed              = 0.2f;
    const float kWalkingAcceleration    = 0.0012f;
    const float kMaxSpeedX              = 0.325f;
    const float kSlowdownFactor         = 0.96f;
    const float kGravity                = 0.002f;
    const float kGravityCap             = 0.8f;
    const float kJumpSpeed              = 0.7f;
    
}

Player::Player() {}

Player::Player(Graphics &graphics, Vector2 spawnPoint) :
    AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
    _acceleration_x(0.0f),
    _velocity_x(0.0f),
    _dx(0),
    _dy(0),
    _facing(Direction::RIGHT),
    _grounded(false)
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

const float Player::getX() const {
    return _x;
}

const float Player::getY() const {
    return _y;
}

void Player::moveLeft() {
    _acceleration_x = -player_constants::kWalkingAcceleration;
    _dx = -player_constants::kWalkSpeed;
    playAnimation("RunLeft");
    _facing = Direction::LEFT;
}

void Player::moveRight() {
    _acceleration_x = player_constants::kWalkingAcceleration;
    _dx = player_constants::kWalkSpeed;
    playAnimation("RunRight");
    _facing = Direction::RIGHT;
}

void Player::stopMoving() {
    _acceleration_x = 0.0f;
    playAnimation(_facing == Direction::RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::jump() {
    if (_grounded) {
        _dy = 0;
        _dy -= player_constants::kJumpSpeed;
        _grounded = false;
    }
}

void Player::handleTileCollisions(std::vector<Rectangle> &others) {
    // Figure out side collision happened on and move player accordingly
    
    for (int i = 0; i < others.size(); i++) {
        sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
        if (collisionSide != sides::NONE) {
            switch (collisionSide) {
                case sides::TOP:
                    _dy = 0.0f;
                    _y = others.at(i).getBottom() + 1;
                    if (_grounded) {
                        _velocity_x = 0;
                        _x -= _facing == Direction::RIGHT ? 0.5f : -0.5f;
                    }
                    break;
                case sides::BOTTOM:
                    cout << "\ncolliding with the top of a rectangle";
                    cout << "\nother rectangle top = " << others.at(i).getTop();
                    cout << "\nthis bottom = " << getBoundingBox().getBottom();
                    this->_y = others.at(i).getTop() - this->_boundingBox.getHeight() - 1;
                    _dy = 0;
                    _grounded = true;
                    break;
                case sides::LEFT:
                    cout << "\ncolliding with the right side of a rectangle";
                    cout << "\nother rectangle right = " << others.at(i).getRight();
                    cout << "\nthis left = " << getBoundingBox().getLeft();
                    _x = others.at(i).getRight() + 1;
                    _velocity_x = 0;
                    break;
                case sides::RIGHT:
                    cout << "\ncolliding with the left side of a rectangle";
                    cout << "\nother rectangle left = " << others.at(i).getLeft();
                    cout << "\nthis right = " << getBoundingBox().getRight();
                    _x = others.at(i).getLeft() - _boundingBox.getWidth() - 1;
                    _velocity_x = 0;
                    break;
                default:
                    break;
            }
        }
    }
}

void Player::handleSlopeCollisions(std::vector<Slope> &others) {
    for (int i = 0; i < others.size(); i++) {
        // calculate where on slope the player's bottom center is touching
        // use y=mx+b to figure out the y position to place him at
        // first calculate "b" (slope intercept) using one of the points
        int b = (others.at(i).getP1().y - (others.at(i).getSlope() * fabs(others.at(i).getP1().x)));
        
        // get player's center x
        int centerX = _boundingBox.getCenterX();
        
        // pass centerX into the equation y = mx + b (using our newly found b and x) to get the new y position
        
        int newY = (others.at(i).getSlope() * centerX) + b - 8;
        
        if (_grounded) {
            _y = newY - _boundingBox.getHeight();
            _grounded = true;
        }
    }
    
}


void Player::update(float elapsedTime) {
    
    if (_dy <= player_constants::kGravityCap) {
        _dy += player_constants::kGravity * elapsedTime;
    }
    
    // Move by dy
    
    _y += _dy * elapsedTime;
    
    // Move by dx
    _x += _velocity_x * elapsedTime;
    _velocity_x += _acceleration_x * elapsedTime;
    
    if (_acceleration_x < 0.0f) {
        _velocity_x = std::max(_velocity_x, -player_constants::kMaxSpeedX);
    }
    else if (_acceleration_x > 0.0f) {
        _velocity_x = std::min(_velocity_x, player_constants::kMaxSpeedX);
    }
    else { // _acceleration_x == 0.0f
        _velocity_x *= player_constants::kSlowdownFactor;
    }
//    
//    cout << "\nplayer x = " << _x;
//    cout << "\nplayer y = " << _y;
    
//    cout << "\nplayer velocity x = " << _velocity_x;
//    cout << "\nplayer dy = " << _dy;
    
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
    AnimatedSprite::draw(graphics, _x, _y);
}

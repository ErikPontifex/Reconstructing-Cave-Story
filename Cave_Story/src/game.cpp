//
//  game.cpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-19.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#include "game.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
using namespace std;

namespace  {
    const int kFps = 50;
    const int kMaxFrameTime = 5 * 1000 / kFps;
}

/* Game Class
 *  Holds all inofrmation for our main game loop
 */

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(SDL_DISABLE);

    eventLoop();

}

Game::~Game() {
    cout << "Destroying\n";
    
    SDL_Quit();
}

void Game::eventLoop() {
    Graphics graphics;
    SDL_Event event;
    Input input;
    
    _level = Level("cave2", Vector2(100, 100), graphics);
    _player = Player(graphics, _level.getPlayerSpawnPoint());
    
    bool running = true;
    
    int last_update_time_ms = SDL_GetTicks();
    
    while (running) {
        input.beginNewFrame();
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.repeat == 0) {
                        input.keyDownEvent(event);
                    }
                    break;
                case SDL_KEYUP:
                    input.keyUpEvent(event);
                    break;
                default:
                    break;
            }
            if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
                running = false;
            }
            else if (input.isKeyHeld(SDL_SCANCODE_LEFT) && input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
                _player.stopMoving();
            }
            else if (input.isKeyHeld(SDL_SCANCODE_LEFT)) {
                _player.moveLeft();
            }
            else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
                _player.moveRight();
            }
            
            if (input.wasKeyPressed(SDL_SCANCODE_Z)) {
                _player.jump();
            }
            
            if (!input.isKeyHeld(SDL_SCANCODE_LEFT) &&
                !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
                _player.stopMoving();
            }
            
        }
        
        // This loop lasts 1/50th of a second
        //                 1000/50th ms
        
        const int current_time_ms = SDL_GetTicks();
        int elapsed_time_ms = current_time_ms - last_update_time_ms;
        update(std::min(elapsed_time_ms, kMaxFrameTime));
        
        last_update_time_ms = current_time_ms;
        
        draw(graphics);
        
    }
    
    cout << "Exiting loop\n";
}

void Game::update(float elapsedTime) {
    _player.update(elapsedTime);
    _level.update(elapsedTime);
    
    // Check collisions
    
    Rectangle pBB = _player.getBoundingBox();
//    
//    cout << "\nplayer BoundingBox right = " << pBB.getRight();
//    cout << "\nplayer BoundingBox left = " << pBB.getLeft();
//    cout << "\nplayer BoundingBox top = " << pBB.getTop();
//    cout << "\nplayer BoundingBox bottom = " << pBB.getBottom();
    
    
    vector<Rectangle> others = _level.checkTileCollisions(pBB);
    if (others.size() > 0) {
        // Player collided with at least one tile
//        cout << "collisions are occuring\n";
        
        _player.handleTileCollisions(others);
    }
    
    vector<Slope> otherSlopes = _level.checkSlopeCollisions(_player.getBoundingBox());
    if (otherSlopes.size()) {
        _player.handleSlopeCollisions(otherSlopes);
    }
}

void Game::draw(Graphics &graphics) {
    graphics.clear();
    
    _level.draw(graphics);
    _player.draw(graphics);
    graphics.flip();
    
}

void Game::printFps(int start_time_ms) {
    const float seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;
    const float fps = 1 / (seconds_per_frame);
    printf("fps=%f\n", fps);
    
}

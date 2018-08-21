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
    const int kFps = 60;
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
    
    _player = Sprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, 100, 100);
    
    bool running = true;
    
    while (running) {
        input.beginNewFrame();
        
        const int start_time_ms = SDL_GetTicks();
        
        while (SDL_PollEvent(&event)) {
            cout << event.type << "\n";
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    cout << event.key.keysym.sym;
                    if (event.key.repeat == 0) {
                        input.keyDownEvent(event);
                    }
                case SDL_KEYUP:
                    input.keyUpEvent(event);
                    break;
                default:
                    break;
            }
            if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
                running = false;
            }
        }
        
        // This loop lasts 1/60th of a second
        //                 1000/60th ms
        
        const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        if (1000/kFps - elapsed_time_ms > 0) {
            SDL_Delay(1000/kFps - elapsed_time_ms);
        }
        
        update(std::min(elapsed_time_ms, kMaxFrameTime));
        draw(graphics);
        printFps(start_time_ms);
    }
    
    cout << "Exiting loop\n";
}

void Game::update(float elapsedTime) {
    
}

void Game::draw(Graphics &graphics) {
    graphics.clear();
    
    _player.draw(graphics, 100, 100);
    graphics.flip();
    
}

void Game::printFps(int start_time_ms) {
    const float seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;
    const float fps = 1 / (seconds_per_frame);
    printf("fps=%f\n", fps);
    
}

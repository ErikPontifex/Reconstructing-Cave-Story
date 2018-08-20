//
//  game.cpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-19.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#include "game.hpp"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
using namespace std;

namespace  {
    const int kScreenWidth = 640;
    const int kScreenHeight = 480;
    const int kFps = 60;
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(SDL_DISABLE);
    screen_ = SDL_CreateWindow("Cave Story",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               kScreenWidth,
                               kScreenHeight,
                               SDL_WINDOW_FULLSCREEN_DESKTOP);
    eventLoop();

}

Game::~Game() {
    cout << "Destroying\n";
    SDL_DestroyWindow(screen_);
    SDL_Quit();
}

void Game::eventLoop() {
    
    bool running = true;
    SDL_Event event;
    
    while (running) {
        
        const int start_time_ms = SDL_GetTicks();
//        cout << "running" << "\n";
        
        while (SDL_PollEvent(&event)) {
            cout << event.type << "\n";
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    cout << event.key.keysym.sym;
                    if (event.key.keysym.sym == 27) {
                        cout << "Ending\n";
                        running = false;
                    }
                    break;
                default:
                    break;
            }
        }
 
        update();
        draw();
        
        // This loop lasts 1/60th of a second
        //                 1000/60th ms
        
        const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        if (1000/kFps - elapsed_time_ms > 0) {
            SDL_Delay(1000/kFps - elapsed_time_ms);
        }
        
        const float seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;
        const float fps = 1 / (seconds_per_frame);
        printf("fps=%f\n", fps);
        
    }
    
    cout << "Exiting loop\n";
}

void Game::update() {
    
}

void Game::draw() {
    
}

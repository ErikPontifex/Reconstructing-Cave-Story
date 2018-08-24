//
//  tile.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-24.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef tile_hpp
#define tile_hpp

#include <stdio.h>
#include "globals.h"
using namespace globals;

struct SDL_Texture;
class Graphics;

class Tile {
    
public:
    Tile();
    Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
    ~Tile();
    
    void update(int elapsedTime);
    void draw(Graphics & graphics);

private:
    SDL_Texture* _tileset;
    Vector2 _size;
    Vector2 _tilesetPosition;
    Vector2 _position;
};

#endif /* tile_hpp */

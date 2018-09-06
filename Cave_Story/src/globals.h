//
//  globals.h
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-20.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef globals_h
#define globals_h

namespace globals {
    const int kScreenWidth      = 640;
    const int kScreenHeight     = 480;
    
    const int kScale            = 1;
}

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

namespace sides {
    enum Side {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE
    };
    
    // return side opposite to whatever side was passed in
    
    inline Side getOppositeSide(Side side) {
        return
        side == TOP ? BOTTOM :
        side == BOTTOM ? TOP :
        side == LEFT ? RIGHT :
        side == RIGHT ? LEFT :
        NONE;
    }
    
}

struct Vector2 {
    
    int x, y;
    
    Vector2() :
        x(0), y(0)
    {}
    
    Vector2(int x, int y) :
        x(x), y(y)
    {}
    
    Vector2 zero() {
        return Vector2(0, 0);
    }
};


#endif /* globals_h */

//
//  slope.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-09-13.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef slope_hpp
#define slope_hpp

#include <stdio.h>
#include <math.h>
#include "globals.h"
#include "rectangle.hpp"

class Slope {
    
public:
    Slope() {}
    Slope(Vector2 p1, Vector2 p2) :
        _p1(p1),
        _p2(p2)
    {
        if ((p2.x - p1.x) != 0) {
            _slope = (fabs(p2.y) - fabs(p1.y)) / (fabs(p2.x) - fabs(p1.x));
        }
    }

    const inline float getSlope() const {
        return _slope;
    }
    
    const inline Vector2 getP1() const {
        return _p1;
    }
    
    const inline Vector2 getP2() const {
        return _p2;
    }
    
    const bool collidesWith(const Rectangle &other) const {
        return (other.getRight() >= _p2.x &&
                other.getLeft() <= _p1.x &&
                other.getTop() <= _p2.y &&
                other.getBottom() >= _p1.y) ||
        
                (other.getRight() >= _p1.x &&
                 other.getLeft() <= _p2.x &&
                 other.getTop() <= _p1.y &&
                 other.getBottom() >= _p2.y) ||
        
                (other.getRight() >= _p2.x &&
                 other.getLeft() <= _p1.x &&
                 other.getTop() <= _p1.y &&
                 other.getBottom() >= _p2.y) ||
        
                (other.getRight() >= _p1.x &&
                  other.getLeft() <= _p2.x &&
                  other.getTop() <= _p2.y &&
                 other.getBottom() >= _p1.y);
    }
    
    
    
private:
    Vector2 _p1, _p2;
    float _slope;
};

#endif /* slope_hpp */

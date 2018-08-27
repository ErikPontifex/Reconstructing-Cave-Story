//
//  rectangle.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-26.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include <stdio.h>
#include "globals.h"
using namespace sides;

class Rectangle {

public:
    Rectangle() {}
    
    Rectangle(int x, int y, int width, int height) :
        _x(x),
        _y(y),
        _width(width),
        _height(height)
    {}
    
    const int getCenterX() const {
        return _x + _width / 2;
    }
    
    const int getCenterY() const {
        return _y + _height / 2;
    }
    
    const int getLeft() const  {
        return _x;
    }
    
    const int getRight() const  {
        return _x + _width;
    }
    
    const int getTop() const  {
        return _y;
    }
    
    const int getBottom() const  {
        return _y + _height;
    }
    
    const int getWidth() const {
        return _width;
    }
    
    const int getHeight() const {
        return _height;
    }
    
    const int getSide(const Side side) const {
        return
            side == sides::LEFT     ? getLeft() :
            side == sides::RIGHT    ? getRight() :
            side == sides::TOP      ? getTop() :
            side == sides::BOTTOM   ? getBottom() :
            NONE;
    }
    
    const bool collidesWith(const Rectangle &other) const {
        return
            getRight() >= other.getLeft() &&
            getLeft() <= other.getRight() &&
            getTop() <= other.getBottom() &&
            getBottom() >= other.getTop();
    }
    
    const bool isValidRectangle() const {
        return (_x >= 0 && _y >= 0 && _width >= 0 && _height >= 0);
    }
    
private:
    int _x, _y, _width, _height;
};

#endif /* rectangle_hpp */

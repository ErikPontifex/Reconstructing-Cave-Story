//
//  animatedSprite.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-08-21.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef animatedSprite_hpp
#define animatedSprite_hpp

#include <stdio.h>
#include "globals.h"
#include "sprite.hpp"
#include <map>
#include <string>
#include <vector>
using namespace std;
using namespace globals;

struct Graphics;

// AnimatedSprite
// Holds logic for animating sprites

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite();
    AnimatedSprite(Graphics &graphics,
                   const string &filePath,
                   int sourceX,
                   int sourceY,
                   int width,
                   int height,
                   float posX,
                   float posY,
                   float timeToUpdate);
    
    // Play animation if not already playing
    // once is optional
    void playAnimation(string animation, bool once = false);
    
    // Update animated sprite
    void update(int elapsedTime);
    
    // Draw sprite to screen
    void draw(Graphics &graphics, int x, int y);
  
    // Sets up all animations for sprite
    // Required function
    
    virtual void setupAnimations();
    
protected:
    
    // Amount of time between frames
    
    double _timeToUpdate;
    
    // Should animation only be played once
    
    bool _currentAnimationOnce;
    
    // Name of current animation
    
    string _currentAnimation;
    
    // Add animation to map of animations for sprite
    
    void addAnimation(int frames, int x, int y, string name, int width, int height, Vector2 offset);
    
    // Clear animations for sprite
    
    void resetAnimations();
    
    // Stop animation
    
    void stopAnimation();
    
    // Change visiblity of animated sprite
    
    void setVisible(bool visible);
    
    // Logic that occurs when an animation ends
    
    virtual void animationDone(string currentAnimation);
    
    
private:
    
    // A map of animations
    
    map<string, vector<SDL_Rect> > _animations;
    
    map<string, Vector2> _offsets;
    
    // Which frame in the animation we are at
    
    int _frameIndex;
    
    double _timeElapsed = 0.0;
    
    // Is the animation visible
    
    bool _visible;
    
    
};


#endif /* animatedSprite_hpp */

#pragma once

#include <raylib.h>
#include <iostream>

#include "gameVars.hpp"

class Character{
private: 
    GameVars gv;
    Vector2 i_position = gv.characterInitialPosition;
    float i_speed = gv.characterInitialSpeed; 
    int i_radius = gv.characterInitialRadius; 
    
    int* frame; 
    
    void handleBoundaries(Vector2 _direction);
    
public: 
    int numberOfFlowers = 0; 
    Vector2 getPosition(){ return i_position; }
    
    void init(int *_frame);
    void draw(); 
    void updatePosition(Vector2 _direction); 

}; 
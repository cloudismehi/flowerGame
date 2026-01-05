#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>

#include "gameVars.hpp"

class Character{
private: 
    GameVars gv;
    Vector2 i_position = gv.characterInitialPosition;
    float i_speed = gv.characterInitialSpeed; 
    int i_radius = gv.characterInitialRadius; 
    
    int* frame; 
    std::vector<Vector2> roomCoordinates; 
    
    void handleBoundaries(Vector2 _direction);
    bool checkBuiltRoom(Vector2 _coord);
    
public: 
    int numberOfFlowers = 0; 
    Vector2 room = {0.f, 0.f}; 
    Vector2 getPosition(){ return i_position; }
    
    void init(int *_frame, std::vector<Vector2> _roomCoords);
    void draw(); 
    void drawStats(); 
    void updatePosition(Vector2 _direction); 

}; 
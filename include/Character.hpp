#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>

#include "gameVars.hpp"

class Character{
private: 
    GameVars gv;
    
    int* frame; 
    std::vector<Vector2> roomCoordinates; 
    
public: 
    Vector2 i_position = gv.characterInitialPosition;
    float i_speed = gv.characterInitialSpeed; 
    int i_radius = gv.characterInitialRadius; 
    int numberOfFlowers = 0; 
    Vector2 room = {0.f, 0.f}; 

    //if true, the player can see a map of the world if they press M, unlocked by the second flower captured
    bool hasUnlockedMap = false; 


    Vector2 getPosition(){ return i_position; }
    
    void init(int *_frame, std::vector<Vector2> _roomCoords);
    void draw(); 
    void drawStats(); 
    void drawMap(); 
    
    // calculate new character position, returns new value we can use to evaluate edge conditions on the game logic
    Vector2 updatePosition(Vector2 _direction); 

    // returns a vector of all the edge rooms (top, bottom, right, and left most)
    std::vector<Vector2> findRoomEdges(); 

}; 
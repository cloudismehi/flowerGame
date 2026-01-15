#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>

#include "gameVars.hpp"
#include "Room.hpp"

class Character{
private: 
    GameVars gv;
    
    int* frame; 
    std::vector<Vector2> roomCoordinates; 
    
public: 
    Room currentRoom; 

    Vector2 position = gv.characterInitialPosition;
    float speed = gv.characterInitialSpeed; 
    int radius = gv.characterInitialRadius; 
    int numberOfFlowers = 0; 
    Vector2 room = {0.f, 0.f}; 

    //if true, the player can see a map of the world if they press M, unlocked by the second flower captured
    bool hasUnlockedMap = false; 


    Vector2 getPosition(){ return position; }
    
    void init(int *_frame, std::vector<Vector2> _roomCoords, Room _curRoom);
    void draw(); 
    void drawStats(); 
    void drawMap(); 
    
    // calculate new character position, returns new value we can use to evaluate edge conditions on the game logic
    Vector2 updatePosition(Vector2 _direction); 

    // returns a vector of all the edge rooms (top, bottom, right, and left most)
    std::vector<Vector2> findRoomEdges(); 

}; 
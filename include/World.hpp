#pragma once

#include <raylib.h>
#include <raymath.h>
#include <iostream> 
#include <vector> 
#include <ctime> 
#include <cmath> 


#include "gameVars.hpp"
#include "Flowers.hpp"
#include "Room.hpp"


class World {  
private:

    void drawBackground(); //def 
    void initFlowerPositions(Vector2 _playerPos); // def
    GameVars gv; 
    float randomNumber(int _min = 0, int _max = 1); // def
    void printAllRooms(); //def

public: 
    
    int flowerEngaged = -1; 

    std::vector<Vector2> allRoomCoords; 
    std::vector<Room> worldRooms; 

    Vector2 flowerPositions[5]; 
    Vector2 flowerRooms[5]; 

    BabysBreath babysBreath;
    Orchid orchid; 
    Rose rose; 
    Sunflower sunflower; 
    Lily lily;

    // class constructor, sets random seed, generates rooms and inits the flower positions
    World(); 

    // holds logic for procedural world generation
    void createWorld();

    // iterates through all rooms and builds new ones when posible, if a room has been built it returns true,
    // else it returns false. used pseudo-recursively in the createWorld
    bool makeRoom(); 

    // returns true if there is a room built in the given room coordinate
    bool checkBuiltRoom(Vector2 _coord); 

    // returns a vector of all the edge rooms (top, bottom, right, and left most)
    std::vector<Vector2> findRoomEdges(); 


    void draw(Vector2 _room); 

    Room findRoom(int _roomCoord_X, int _roomCoord_Y); 
    int findRoomIndex(int _roomCoord_x, int _roomCoord_y); 
}; 


#pragma once

#include <raylib.h>
#include <iostream> 
#include <vector> 
#include <ctime> 
#include <cmath> 


#include "gameVars.hpp"
#include "Flowers.hpp"

struct Room{
    Vector2 coordinate; //coordinates of the current room
    float weights[4]; //north, east, south, west -> these are the odds of a room generated on all direction of the current room 
    bool roomAdjacent[4]; //is there a room adjacent on all directions of the current room

    Room(Vector2 _coord, const float _weights[4], const bool _adjacent[4]){
        for (int i = 0; i < 4; i++){
            weights[i] = _weights[i]; 
            roomAdjacent[i] = _adjacent[i];
        }
        coordinate = _coord;
    }

    Room(){}

    void printStatus(){
        printf("Room (%0.f, %0.f):\n", coordinate.x, coordinate.y); 
        printf("    north: %d (%0.2f), east: %d (%0.2f), south: %d (%0.2f), west: %d (%0.2f)\n", 
            roomAdjacent[0], weights[0], roomAdjacent[1], weights[1], roomAdjacent[2], weights[2], roomAdjacent[3], weights[3]); 
    }
}; 

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
    BabysBreath babysBreath;
    Orchid orchid; 
    Rose rose; 
    Sunflower sunflower; 
    Lily lily;

    World(); // def
    void createWorld(); // def
    bool makeRoom(); // def
    bool checkBuiltRoom(Vector2 _coord); //


    void draw(); 

}; 


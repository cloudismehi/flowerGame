#include <iostream> 
#include <raylib.h> 
#include <raymath.h> 

class Room{
    public:
    Vector2 coordinate; //coordinates of the current room
    float weights[4]; //north, east, south, west -> these are the odds of a room generated on all direction of the current room 
    bool roomAdjacent[4]; //is there a room adjacent on all directions of the current room

    Room(Vector2 _coord, const float _weights[4], const bool _adjacent[4]);
    Room(){}
    void printStatus();      
}; 
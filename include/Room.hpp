#pragma once

#include <iostream> 
#include <ctime>

#include <raylib.h> 
#include <raymath.h> 

#include "gameVars.hpp"

class Room{
    GameVars gv; 

    static const int roomSize_x = 800; 
    static const int roomSize_y = 600; 

    // generates random number from min to max using rand, to set a seed use srand(std::time(0))
    float randomNumber(int _min = 0, int _max = 1);  

    public:
    
    // coordinates of the current room
    Vector2 coordinate; 

    // north, east, south, west -> these are the odds of a room generated on all direction of the current room 
    float weights[4]; 

    // is there a room adjacent on all directions of the current room
    bool roomAdjacent[4]; 

    // * information about room contents
    static const int subdivSize = 20; 
    static const int noSubdivs_x =  roomSize_x / subdivSize; 
    static const int noSubdivs_y =  roomSize_y / subdivSize; 
    
    int cellStates[noSubdivs_x][noSubdivs_y] = { 0 }; 

    
    // copies down weights, roomAdjacent, and coordinates into class info
    Room(Vector2 _coord, const float _weights[4], const bool _adjacent[4], 
         int _roomSize_x, int _roomSize_y);
    // doesn't do anything 
    Room(){}

    // generates the random walls and smooths them (amount of smoothing passes set in gameVars)
    void init(); 

    // print room coordinates, and existance + odds of rooms generated on all four directions 
    // (mostly used in troubleshooting room generation, leaving it here if needed) 
    void printStatus();      

    // generates random tiles on the world, then smooths them out using cell automata
    void generateObjects(); 

    // draw grid of cells, with the walls being any cell with value one 
    void drawRoom(); 

    // using concepts from cellular automata, this block of code looks at neighboring cells and makes decisions on the state
    // of the current cell
    void smooth(); 

    // clear way in the center of the room, the direction states which way the paths should lead but they all connect to the center 
    // of the room in one way or another - only when this direction is (0, 0) do we have paths connecting in all directions, this is used in the 
    // center room. every other use will likely be for flower rooms
    void clearSpace(Vector2 _dir = (Vector2){0.f, 0.f}); 
}; 
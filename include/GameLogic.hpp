#pragma once

#include <raylib.h>
#include <raymath.h> 
#include <iostream> 

#include "Character.hpp"
#include "World.hpp"
#include "gameVars.hpp"

class GameLogic{
private:
    // monitors all game input 
    void input(); 
    // handles all game mechanic updates
    void gameUpdate(); 
    // handles all drawing functions
    void sceneUpdate(); 

    // update characters position
    void moveCharacter(); 
    // handle boundary conditions
    void handleCharBoundaries(Vector2 _newPosition); 

    GameVars gv; 

    World world;        // world is generated before character
    bool drawMap = false; 
    Character ro;       // character initialized

public: 
    int* frame; 

    GameLogic(int* _frame); 
    void update(); 
    
    int checkCollisions(); 

}; 

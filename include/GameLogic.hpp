#pragma once

#include <raylib.h>
#include <raymath.h> 
#include <iostream> 

#include "Character.hpp"
#include "World.hpp"
#include "gameVars.hpp"

class GameLogic{
private:
    
    void input(); 
    void gameUpdate(); 
    void sceneUpdate(); 

    void moveCharacter(); 

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

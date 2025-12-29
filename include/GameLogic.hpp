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

    GameVars gv; 

    World world; 
    Character ro; 

public: 
    int* frame; 

    GameLogic(int* _frame); 
    void update(); 
    
    int checkCollisions(); 

}; 

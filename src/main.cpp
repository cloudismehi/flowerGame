#include <iostream> 
#include <raylib.h>

#include "GameLogic.hpp"
#include "gameVars.hpp"


int frame = 0; 

int main(){
    GameVars gv; 
    GameLogic gameLogic(&frame);
    InitWindow(gv.worldSize.x, gv.worldSize.y, "gamey");

    SetRandomSeed(time(NULL)); 

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        if ((++frame) > 60) frame = 0;  
        BeginDrawing();
        gameLogic.update(); 
        EndDrawing();
        
    }

    CloseWindow();        
    
    
    return 0; 
}


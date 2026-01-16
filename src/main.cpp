#include <iostream> 
#include <raylib.h>

#include "GameLogic.hpp"
#include "gameVars.hpp"


int frame = 0; 

int main(){
    std::cout << "[GAMEY] game starting!\n"; 
    
    GameVars gv; 
    GameLogic gameLogic(&frame);
    InitWindow(gv.windowSize.x, gv.windowSize.y, "gamey");

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


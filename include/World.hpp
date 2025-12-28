#pragma once

#include <raylib.h>
#include <iostream> 

#include "gameVars.hpp"
#include "Flowers.hpp"

class World {  
private:

    void drawBackground();
    void initFlowerPositions(); 
    GameVars gv; 

public: 

    Vector2 flowerPositions[5]; 
    BabysBreath babysBreath;
    Orchid orchid; 
    Rose rose; 
    Sunflower sunflower; 
    Lily lily;

    World(); 
    void draw(); 

}; 


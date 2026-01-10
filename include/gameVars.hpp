#pragma once

#include "raylib.h"

enum Flowers{
    BABYS_BREATH, 
    ORCHID, 
    ROSE, 
    SUNFLOWER, 
    LILY
}; 

class GameVars{
public: 
    // world properties
    const Vector2 worldSize = {800.f, 500.f};
    const Vector2 windowSize = {800.f, 500.f}; 

    // colors
    const Color backgroundColor = {114, 189, 163, 255}; // muted teal, light green 
    const Color defaultCharacterColor = {220, 107, 173, 255}; // petal pink, soft magenta
    const Color defaultFlowerColor = YELLOW; 

    // character init properties
    const float characterInitialSpeed = 5.f;
    const Vector2 characterInitialPosition = {400.0f, 400.f};
    const int characterInitialRadius = 20;

    // flower properties
    const float flowerDefaultSize = 10.f;

    int minRoomsGen = 8;  
    int maxRoomsGen = 15; 

}; 
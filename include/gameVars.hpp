#pragma once

#include "raylib.h"

class GameVars{
public: 
    // world properties
    const Vector2 worldSize = {800.f, 500.f};

    // colors
    const Color backgroundColor = {114, 189, 163, 255}; // muted teal, light green 
    const Color defaultCharacterColor = {220, 107, 173, 255}; // petal pink, soft magenta
    const Color defaultFlowerColor = YELLOW; 

    // character init properties
    const float characterInitialSpeed = 2.f;
    const Vector2 characterInitialPosition = {400.0f, 250.0f};
    const int characterInitialRadius = 20;

    // flower properties
    const float flowerDefaultSize = 10.f;

}; 
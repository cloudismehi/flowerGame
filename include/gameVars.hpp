#pragma once

#include <iostream>
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
    // * world properties

    // both are used interchangeably, probably not a good thing. the room class has a static const of these so if they change
    // make sure to change them in there as well @.@
    Vector2 worldSize = {800.f, 600.f};
    Vector2 windowSize = {800.f, 600.f}; 

    // * colors
    Color backgroundColor = {114, 189, 163, 255}; // muted teal, light green 
    Color defaultCharacterColor = {220, 107, 173, 255}; // petal pink, soft magenta
    Color defaultFlowerColor = YELLOW; 
    Color miniMapBackgroundColor = {211, 211, 211, 200}; 
    Color miniMapRoomDefaultColor = BLACK; 
    Color miniMapRoomZero = RED; 
    Color miniMapActiveRoom = ORANGE; 
    Color wallColor = BLACK; 

    // * character init properties
    float characterInitialSpeed = 5.f;
    Vector2 characterInitialPosition = {400.0f, 400.f};
    int characterInitialRadius = 10;
    
    // * mini-map properties
    Vector2 miniMapSize = {150, 100}; 
    Vector2 miniMapPos = {worldSize.x - miniMapSize.x - 10, 10}; 
    int miniMapRoomSize = 5; 
    int miniMapRoomBuffer = 15; 

    // * room properties
    int amountOfSmoothing = 5; 
    // * there is additional information on the room generation (namely, the cell size) in the room class itself. it needs to be there
    // * because of some silliness with the consts in this class and the static consts in Room. 

    // * flower properties
    float flowerDefaultSize = 10.f;

    int minRoomsGen = 8;  
    int maxRoomsGen = 15; 
 
}; 
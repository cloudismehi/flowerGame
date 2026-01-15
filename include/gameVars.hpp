#pragma once

#include "raylib.h"

/* //TODO:

- rooms seem to repeat a lot which implies that either the room generation or the room drawing software have issues
- room drawing happens in the character drawing function and i don't want that 

*/

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
    const Vector2 worldSize = {800.f, 600.f};
    const Vector2 windowSize = {800.f, 600.f}; 

    // * colors
    const Color backgroundColor = {114, 189, 163, 255}; // muted teal, light green 
    const Color defaultCharacterColor = {220, 107, 173, 255}; // petal pink, soft magenta
    const Color defaultFlowerColor = YELLOW; 
    const Color miniMapBackgroundColor = {211, 211, 211, 200}; 
    const Color miniMapRoomDefaultColor = BLACK; 
    const Color miniMapRoomZero = RED; 
    const Color miniMapActiveRoom = ORANGE; 

    // * character init properties
    const float characterInitialSpeed = 5.f;
    const Vector2 characterInitialPosition = {400.0f, 400.f};
    const int characterInitialRadius = 20;
    
    // * mini-map properties
    const Vector2 miniMapSize = {150, 100}; 
    const Vector2 miniMapPos = {worldSize.x - miniMapSize.x - 10, 10}; 
    const int miniMapRoomSize = 5; 
    const int miniMapRoomBuffer = 15; 



    // * flower properties
    const float flowerDefaultSize = 10.f;

    const int minRoomsGen = 8;  
    const int maxRoomsGen = 15; 

}; 
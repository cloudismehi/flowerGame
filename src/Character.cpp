#include "Character.hpp"

void Character::handleBoundaries(Vector2 _newPosition){
    if ((_newPosition.x <= 0) and (checkBuiltRoom({room.x-1, room.y}))){
        
        // going to the room to the left
        i_position = {gv.windowSize.x - 15, _newPosition.y}; 
        room.x -= 1; 

    } else if ((_newPosition.x >= gv.windowSize.x) and (checkBuiltRoom({room.x + 1, room.y}))){
        
       // going to the room to the right
       i_position = {15, _newPosition.y}; 
       room.x += 1; 
        

    } else if ((_newPosition.y >= gv.windowSize.y) and (checkBuiltRoom({room.x, room.y - 1}))){

        //going to the room down 
        i_position = {_newPosition.x, 15}; 
        room.y -= 1; 


    } else if ((_newPosition.y <= 0) and (checkBuiltRoom({room.x, room.y + 1}))){

        //going to the room up
        i_position = {_newPosition.x, gv.windowSize.y - 15}; 
        room.y += 1; 

    } else {
        if ((_newPosition.x > 0) and (_newPosition.x < 800)){
            if ((_newPosition.y > 0) and (_newPosition.y < 500)){
                i_position = _newPosition; 
            }
        }
    }
}

bool Character::checkBuiltRoom(Vector2 _coord){
    for (auto coord : roomCoordinates){
        if ((_coord.x == coord.x) and (_coord.y == coord.y)){
            return true; 
        }
    }
    return false; 
}

void Character::init(int *_frame, std::vector<Vector2> _roomCoords){
    frame = _frame; 
    roomCoordinates = _roomCoords; 
}

void Character::draw(){
    // placeholder for character drawing
    DrawCircle(i_position.x, i_position.y, i_radius, gv.defaultCharacterColor);   

    DrawText(TextFormat("in room (%0.f, %0.f)", room.x, room.y), gv.windowSize.x - 180, gv.windowSize.y - 30, 20, BLACK); 
}

void Character::drawStats(){
    //report number of flowers collected
    if (numberOfFlowers == 1){
        DrawText("you have collected 1 flower!", 10, 10, 20, WHITE);
    } else{
        DrawText(TextFormat("you have collected %d flowers!", numberOfFlowers), 10, 10, 20, WHITE);
    }
}

void Character::updatePosition(Vector2 _direction){
    // placeholder for position update logic
    Vector2 newPosition = i_position; 

    newPosition.x += (_direction.x * i_speed); 
    newPosition.y += (_direction.y * i_speed); 

    handleBoundaries(newPosition);
}


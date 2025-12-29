#include "Character.hpp"

void Character::handleBoundaries(Vector2 _newPosition){
    // placeholder for boundary conditions

    if ((_newPosition.x > 0) and (_newPosition.x < 800)){
        if ((_newPosition.y > 0) and (_newPosition.y < 500)){
            i_position = _newPosition; 
        }
    }
}

void Character::init(int *_frame){
    frame = _frame; 
}

void Character::draw(){
    // placeholder for character drawing
    DrawCircle(i_position.x, i_position.y, i_radius, gv.defaultCharacterColor);   
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


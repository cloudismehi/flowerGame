#include "GameLogic.hpp"

void GameLogic::input(){
    // input handling
    
    Vector2 movementDirection = {0.f, 0.f}; 

    if (IsKeyDown(KEY_UP)){
        movementDirection.y += -1.f;
    }
    if (IsKeyDown(KEY_DOWN)){
        movementDirection.y += 1.f;
    }
    if (IsKeyDown(KEY_LEFT)){
        movementDirection.x += -1.f; 
    }
    if (IsKeyDown(KEY_RIGHT)){
        movementDirection.x += 1.f; 
    }
    
    movementDirection = Vector2Normalize(movementDirection);

    ro.updatePosition(movementDirection);
}

void GameLogic::gameUpdate(){
    // internal game logic update
    
    if (world.flowerEngaged == -1){
        int collision = checkCollisions(); 
        if (collision != -1){
            std::cout << "detected collision with flower " << collision << '\n'; 
            world.flowerEngaged = collision; 
        }
    }
}

void GameLogic::sceneUpdate(){
    // scene update, visuals

    // world rendering    
    world.draw(); 

    // character rendering
    ro.draw(); 
}


GameLogic::GameLogic(int* _frame){
    frame = _frame; 

    ro.init(frame); 
}

void GameLogic::update(){
    input(); //handle input first
    gameUpdate();  //change game state
    sceneUpdate(); // update visuals accordingly
}


int GameLogic::checkCollisions(){
    for (int i = 0; i < 5; i++){
        Rectangle flowerRec = {world.flowerPositions[i].x, world.flowerPositions[i].y, gv.flowerDefaultSize, gv.flowerDefaultSize}; 
        if (CheckCollisionCircleRec(ro.getPosition(), gv.characterInitialRadius, flowerRec)){
            return i; 
        }
    }
    return -1; 
}
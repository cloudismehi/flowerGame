#include "GameLogic.hpp"

void GameLogic::input(){
    // input handling
    switch (world.flowerEngaged){
        case BABYS_BREATH: 
            world.babysBreath.input();
            break; 
        case ORCHID: 
            world.orchid.input();
            break; 
        case ROSE: 
            world.rose.input();
            break; 
        case SUNFLOWER: 
            world.sunflower.input();
            break; 
        case LILY: 
            world.lily.input();
            break; 
        default: 
            moveCharacter(); 
            break; 
    }

    if (IsKeyDown(KEY_M)) drawMap = true; 
    else drawMap = false; 
}

void GameLogic::gameUpdate(){
    // internal game logic update
    
    // check if a flower is engaged, if it is check if it has been beaten to reset or run flower's logic function 
    switch (world.flowerEngaged){
        case BABYS_BREATH: 
            if (world.babysBreath.flowerBeat){
                world.flowerPositions[BABYS_BREATH] = {-1000.f, -1000.f}; //move offscreen
                world.flowerEngaged = -1; 
                ro.numberOfFlowers += 1; 
                
                if (ro.numberOfFlowers >= 2) ro.hasUnlockedMap = true; 
            }
            world.babysBreath.logic();
            break; 
        case ORCHID: 
            if (world.orchid.flowerBeat){
                world.flowerPositions[ORCHID] = {-1000.f, -1000.f}; //move offscreen
                world.flowerEngaged = -1; 
                ro.numberOfFlowers += 1; 

                if (ro.numberOfFlowers >= 2) ro.hasUnlockedMap = true; 
            }
            world.orchid.logic();
            break; 
        case ROSE: 
            if (world.rose.flowerBeat){
                world.flowerPositions[ROSE] = {-1000.f, -1000.f}; //move offscreen
                world.flowerEngaged = -1; 
                ro.numberOfFlowers += 1; 

                if (ro.numberOfFlowers >= 2) ro.hasUnlockedMap = true; 
            }
            world.rose.logic();
            break; 
        case SUNFLOWER: 
            if (world.sunflower.flowerBeat){
                world.flowerPositions[SUNFLOWER] = {-1000.f, -1000.f}; //move offscreen
                world.flowerEngaged = -1; 
                ro.numberOfFlowers += 1; 

                if (ro.numberOfFlowers >= 2) ro.hasUnlockedMap = true; 
            }
            world.sunflower.logic();
            break; 
        case LILY: 
            if (world.lily.flowerBeat){
                world.flowerPositions[LILY] = {-1000.f, -1000.f}; //move offscreen
                world.flowerEngaged = -1; 
                ro.numberOfFlowers += 1; 

                if (ro.numberOfFlowers >= 2) ro.hasUnlockedMap = true; 
            }
            world.lily.logic();
            break; 
        default: 
            int collision = checkCollisions(); 
            if (collision != -1){
                std::cout << "detected collision with flower " << collision << '\n'; 
                world.flowerEngaged = collision; 
            }
            break; 
    }

}

void GameLogic::sceneUpdate(){
    // scene update, visuals

    // world rendering    
    world.draw(ro.room); 

    // character rendering
    switch(world.flowerEngaged){
        case BABYS_BREATH: 
            break; 
        case ORCHID: 
            break; 
        case ROSE: 
            break; 
        case SUNFLOWER: 
            break; 
        case LILY:
            break; 
        default: 
            ro.draw(); 
            ro.drawStats();
            if (drawMap) ro.drawMap(); 
            break; 

    }
}

void GameLogic::moveCharacter(){
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


GameLogic::GameLogic(int* _frame){
    frame = _frame; 

    ro.init(frame, world.allRoomCoords); 
}

void GameLogic::update(){
    input(); //handle input first
    gameUpdate();  //change game state
    sceneUpdate(); // update visuals accordingly
}


int GameLogic::checkCollisions(){
    for (int i = 0; i < 5; i++){
        Rectangle flowerRec = {world.flowerPositions[i].x, world.flowerPositions[i].y, gv.flowerDefaultSize, gv.flowerDefaultSize}; 
        if (CheckCollisionCircleRec(ro.getPosition(), gv.characterInitialRadius, flowerRec) and (ro.room == world.flowerRooms[i])){
            return i; 
        }
    }
    return -1; 
}
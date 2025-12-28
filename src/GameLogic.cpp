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

    for (int i = 0; i < 5; i++){
        Rectangle flowerRec = {world.flowerPositions[i].x, world.flowerPositions[i].y, gv.flowerDefaultSize, gv.flowerDefaultSize}; 
        if (CheckCollisionCircleRec(ro.getPosition(), gv.characterInitialRadius, flowerRec)){
            switch(i){
                case 0 : // baby's breath
                    world.babysBreath.flowerBeat = true; // this won't be automatically set in the future

                    if (world.babysBreath.flowerBeat){
                        std::cout << "collected the baby's breath!\n"; 
                        world.flowerPositions[i] = {-20.f, -20.f}; 
                        ro.numberOfFlowers++; 
                    }
                break; 

                case 1 : // orchid
                    world.orchid.flowerBeat = true; // this won't be automatically set in the future

                    if (world.orchid.flowerBeat){
                        std::cout << "collected the orchid!\n"; 
                        world.flowerPositions[i] = {-20.f, -20.f}; 
                        ro.numberOfFlowers++; 
                    }
                break; 

                case 2: // rose
                    world.rose.flowerBeat = true; // this won't be automatically set in the future

                    if (world.rose.flowerBeat){
                        std::cout << "collected the rose!\n"; 
                        world.flowerPositions[i] = {-20.f, -20.f}; 
                        ro.numberOfFlowers++; 
                    }
                break; 

                case 3: // sunflower
                    world.sunflower.flowerBeat = true; // this won't be automatically set in the future

                    if (world.sunflower.flowerBeat){
                        std::cout << "collected the sunflower!\n"; 
                        world.flowerPositions[i] = {-20.f, -20.f}; 
                        ro.numberOfFlowers++; 
                    }
                break; 

                case 4: // lily
                    world.lily.flowerBeat = true; // this won't be automatically set in the future

                    if (world.lily.flowerBeat){
                        std::cout << "collected the lily!\n"; 
                        world.flowerPositions[i] = {-20.f, -20.f}; 
                        ro.numberOfFlowers++; 
                    }
                break; 
            }
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


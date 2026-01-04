#include "World.hpp"

void World::drawBackground(){
    ClearBackground(gv.backgroundColor); 
}

void World::initFlowerPositions(Vector2 _playerPos){
    // make random positions for each flower, making sure they don't land where the player's default position is
    // i don't know that the flower positions will be generated randomly in the future but for now it works

    Rectangle f_flowerRectangle = {0, 0, gv.flowerDefaultSize, gv.flowerDefaultSize}; 
    
    // babys breath
    do {
        flowerPositions[BABYS_BREATH] = { (float) GetRandomValue(30, (int)gv.windowSize.x - 30), (float) GetRandomValue(30, (int)gv.windowSize.y - 30) };
        f_flowerRectangle.x = flowerPositions[BABYS_BREATH].x; 
        f_flowerRectangle.y = flowerPositions[BABYS_BREATH].y; 
    } while (CheckCollisionCircleRec(_playerPos, gv.characterInitialRadius, f_flowerRectangle)); 
    babysBreath.init(flowerPositions[0]);

    // orchid
    do {
        flowerPositions[ORCHID] = { (float) GetRandomValue(30, (int)gv.windowSize.x - 30), (float) GetRandomValue(30, (int)gv.windowSize.y - 30) };
        f_flowerRectangle.x = flowerPositions[ORCHID].x; 
        f_flowerRectangle.y = flowerPositions[ORCHID].y; 
    }  while (CheckCollisionCircleRec(_playerPos, gv.characterInitialRadius, f_flowerRectangle)); 
    orchid.init(flowerPositions[1]);

    // rose
    do {
        flowerPositions[ROSE] = { (float) GetRandomValue(30, (int)gv.windowSize.x - 30), (float) GetRandomValue(30, (int)gv.windowSize.y - 30) };
        f_flowerRectangle.x = flowerPositions[ROSE].x; 
        f_flowerRectangle.y = flowerPositions[ROSE].y; 
    } while (CheckCollisionCircleRec(_playerPos, gv.characterInitialRadius, f_flowerRectangle)); 
    rose.init(flowerPositions[2]);

    // sunflower
    do {
        flowerPositions[SUNFLOWER] = { (float) GetRandomValue(30, (int)gv.windowSize.x - 30), (float) GetRandomValue(30, (int)gv.windowSize.y - 30) };
        f_flowerRectangle.x = flowerPositions[SUNFLOWER].x; 
        f_flowerRectangle.y = flowerPositions[SUNFLOWER].y; 
    }  while (CheckCollisionCircleRec(_playerPos, gv.characterInitialRadius, f_flowerRectangle));
    sunflower.init(flowerPositions[3]);

    // lily 
    do {
        flowerPositions[LILY] = { (float) GetRandomValue(30, (int)gv.windowSize.x - 30), (float) GetRandomValue(30, (int)gv.windowSize.y - 30) };
        f_flowerRectangle.x = flowerPositions[LILY].x; 
        f_flowerRectangle.y = flowerPositions[LILY].y; 
    }  while (CheckCollisionCircleRec(_playerPos, gv.characterInitialRadius, f_flowerRectangle)); 
    lily.init(flowerPositions[4]);

    // for (int i = 0; i < 5; i++){
    //     std::cout << "flower " << i << " position: (" << flowerPositions[i].x << ", " << flowerPositions[i].y << ")\n"; 
    // }
}

World::World(){
    //initialize world
    
    initFlowerPositions(gv.characterInitialPosition); 
}

void World::draw(){
    drawBackground(); 
    // draw either each flower's fight sceen if enganged or all unbeaten flowers ortherwise
    switch (flowerEngaged){
        case BABYS_BREATH:    
            babysBreath.drawScreen(); 
            break; 

        case ORCHID: 
            orchid.drawScreen(); 
            break; 

        case ROSE:
            rose.drawScreen(); 
            break;

        case SUNFLOWER: 
            sunflower.drawScreen(); 
            break;
        
        case LILY:
            lily.drawScreen(); 
            break;

        default: 
            if (!babysBreath.flowerBeat) babysBreath.drawFlower();
            if (!orchid.flowerBeat) orchid.drawFlower();
            if (!rose.flowerBeat) rose.drawFlower();
            if (!sunflower.flowerBeat) sunflower.drawFlower();
            if (!lily.flowerBeat) lily.drawFlower();
            break;
    }   
}
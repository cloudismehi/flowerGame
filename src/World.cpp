#include "World.hpp"

void World::drawBackground(){
    ClearBackground(gv.backgroundColor); 
}

void World::initFlowerPositions(){
    // babys breath
    flowerPositions[0] = { (float) GetRandomValue(30, (int)gv.worldSize.x - 30), (float) GetRandomValue(30, (int)gv.worldSize.y - 30) };
    babysBreath.init(flowerPositions[0]);

    // orchid
    flowerPositions[1] = { (float) GetRandomValue(30, (int)gv.worldSize.x - 30), (float) GetRandomValue(30, (int)gv.worldSize.y - 30) };
    orchid.init(flowerPositions[1]);

    // rose
    flowerPositions[2] = { (float) GetRandomValue(30, (int)gv.worldSize.x - 30), (float) GetRandomValue(30, (int)gv.worldSize.y - 30) };
    rose.init(flowerPositions[2]);

    // sunflower
    flowerPositions[3] = { (float) GetRandomValue(30, (int)gv.worldSize.x - 30), (float) GetRandomValue(30, (int)gv.worldSize.y - 30) };
    sunflower.init(flowerPositions[3]);

    // lily 
    flowerPositions[4] = { (float) GetRandomValue(30, (int)gv.worldSize.x - 30), (float) GetRandomValue(30, (int)gv.worldSize.y - 30) };
    lily.init(flowerPositions[4]);

    for (int i = 0; i < 5; i++){
        std::cout << "flower " << i << " position: (" << flowerPositions[i].x << ", " << flowerPositions[i].y << ")\n"; 
    }
}

World::World(){
    //initialize world
    
    initFlowerPositions(); 
}

void World::draw(){
    drawBackground(); 

    //draw flowers
    if (!babysBreath.flowerBeat)
        babysBreath.drawFlower();

    if (!orchid.flowerBeat)
        orchid.drawFlower();
    
    if (!rose.flowerBeat)
        rose.drawFlower();

    if (!sunflower.flowerBeat)
        sunflower.drawFlower();

    if (!lily.flowerBeat)
        lily.drawFlower();
}
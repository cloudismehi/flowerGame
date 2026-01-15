#include "World.hpp"

void World::drawBackground(){
    ClearBackground(gv.backgroundColor); 
}

void World::initFlowerPositions(Vector2 _playerPos){
    /*
    flowers will generally be generated in the furthestmost point north, south, east, and west from room (0,0)
    one of them, the rose, will be generated IN room (0,0) and will be a sort of tutorial flower for how the capturing works. 

    the flower will be placed in the center of each room
    */

    auto roomEdges = findRoomEdges(); 

    Rectangle f_flowerRectangle = {0, 0, gv.flowerDefaultSize, gv.flowerDefaultSize}; 
    
    // rose
    flowerPositions[ROSE] = { (gv.windowSize.x / 2), (gv.windowSize.y / 2) };
    rose.init(flowerPositions[ROSE]);
    rose.p_room = {0.f, 0.f}; 
    flowerRooms[ROSE] = rose.p_room; 

    printf("[WORLD GEN] rose placed at (%0.f, %0.f)\n", rose.p_room.x, rose.p_room.y); 

    // babys breath, placed north-most 
    flowerPositions[BABYS_BREATH] = { (gv.windowSize.x / 2), (gv.windowSize.y / 2) };
    babysBreath.init(flowerPositions[BABYS_BREATH]);
    babysBreath.p_room = roomEdges[0];
    flowerRooms[BABYS_BREATH] = babysBreath.p_room; 

    printf("[WORLD GEN] baby's breath placed at (%0.f, %0.f)\n", babysBreath.p_room.x, babysBreath.p_room.y); 


    // orchid, placed south-most
    flowerPositions[ORCHID] = { (gv.windowSize.x / 2), (gv.windowSize.y / 2) };
    orchid.init(flowerPositions[ORCHID]);
    orchid.p_room = roomEdges[1]; 
    flowerRooms[ORCHID] = orchid.p_room; 
    
    printf("[WORLD GEN] orchid placed at (%0.f, %0.f)\n", orchid.p_room.x, orchid.p_room.y); 


    // sunflower, placed east-most
    flowerPositions[SUNFLOWER] = { (gv.windowSize.x / 2), (gv.windowSize.y / 2) };
    sunflower.init(flowerPositions[SUNFLOWER]);
    sunflower.p_room = roomEdges[2]; 
    flowerRooms[SUNFLOWER] = sunflower.p_room; 

    printf("[WORLD GEN] sunflower placed at (%0.f, %0.f)\n", sunflower.p_room.x, sunflower.p_room.y); 


    // lily, placed west-most
    flowerPositions[LILY] = { (gv.windowSize.x / 2), (gv.windowSize.y / 2) };
    lily.init(flowerPositions[LILY]);
    lily.p_room = roomEdges[3]; 
    flowerRooms[LILY] = lily.p_room; 
    
    printf("[WORLD GEN] lily placed at (%0.f, %0.f)\n", lily.p_room.x, lily.p_room.y); 
}

// little helper function to generate random numbers
float World::randomNumber(int _min, int _max){
    float randNum = (float)std::rand() / RAND_MAX; 

    randNum *= (_max - _min); 
    randNum += _min; 

    return randNum; 
}

void World::printAllRooms(){
    for (auto room : worldRooms){
        room.printStatus(); 
    }
}

World::World(){
    //initialize world
    std::srand(std::time(0)); 

    // ensure we generate between min and max rooms per iteration (the min and max are set in project params file), 
    // if not -> reset and try again. 
    do { 
        allRoomCoords.clear(); 
        worldRooms.clear(); 
        createWorld(); 
    } while ((worldRooms.size() < gv.minRoomsGen) or (worldRooms.size() > gv.maxRoomsGen)); 
    printf("\na total of %d rooms were generated\n", (int) allRoomCoords.size()); 

    initFlowerPositions(gv.characterInitialPosition); 
}

void World::createWorld(){
    // make starting position, the first room with coordinates (0, 0) and full chances of rooms generated around it 
    float startWeights[4] = {0.8, 0.8, 0.8, 0.8}; // there is an 80% chance of rooms being adjacent to this one in all directions
    bool startAdjacent[4] = {false, false, false, false}; // nothing is adjacent to this room as of right now, in all directions

    Room _room((Vector2){0, 0}, startWeights, startAdjacent, gv.worldSize.x, gv.worldSize.y);   // add room 
    worldRooms.push_back(_room); 
    allRoomCoords.push_back(_room.coordinate); 

    // this is a recursive function to continue to generate all other rooms around it, returning false if no other rooms are generating
    while(makeRoom()); 
}

// generates rooms depending on the odds of each room to have subsequent rooms next to it, it returns true if any new rooms have been made and false if not
bool World::makeRoom(){
    bool addedNewRoom = false; 
    std::vector<Room> newRooms = worldRooms; 
    std::vector<Vector2> newRoomCoords = allRoomCoords; 

    for (auto& room : worldRooms){
        for (int i = 0; i < 4; i++){
            if (randomNumber() < room.weights[i]){
                room.weights[i] = 0; 

                Vector2 _newCoord; 
                int prevDir; 
                switch (i){
                    case 0: 
                        _newCoord = {room.coordinate.x, room.coordinate.y + 1}; 
                        prevDir = 2; 
                        break; 
                    case 1: 
                        _newCoord = {room.coordinate.x + 1, room.coordinate.y}; 
                        prevDir = 3; 
                        break; 
                    case 2: 
                        _newCoord = {room.coordinate.x, room.coordinate.y - 1}; 
                        prevDir = 0; 
                        break; 
                    case 3: 
                        _newCoord = {room.coordinate.x - 1, room.coordinate.y}; 
                        prevDir = 1; 
                        break; 
                }
                
                if (!checkBuiltRoom(_newCoord) and !((std::abs(_newCoord.x) > 2) or (std::abs(_newCoord.y) > 2))){
                    // the odds of each room having subsequent rooms is given by this function made such that no rooms three or more units 
                    // away from the origin can be generated 
                    float newWeight = std::abs(-(std::abs(_newCoord.x + _newCoord.y) / 2) + 0.7); 
                    newWeight /= 1.6; 

                    float newWeights[4] = {newWeight, newWeight, newWeight, newWeight};
                    bool newAdjacent[4] = {false, false, false, false};
                    Room _newRoom(_newCoord, newWeights, newAdjacent, gv.worldSize.x, gv.worldSize.y); 

                    _newRoom.weights[prevDir] = 0; 
                    room.weights[i] = 0; 

                    newRooms.push_back(_newRoom); 
                    newRoomCoords.push_back(_newCoord); 
                    addedNewRoom = true; 
                }
            }
        }
    }
    worldRooms = newRooms; 
    allRoomCoords = newRoomCoords; 

    return addedNewRoom; 
}

// check if there are any rooms at the given coordinate
bool World::checkBuiltRoom(Vector2 _coord){
    for (auto coord : allRoomCoords){
        if ((_coord.x == coord.x) and (_coord.y == coord.y)){
            return true; 
        }
    }
    return false; 
}

std::vector<Vector2> World::findRoomEdges(){
    Vector2 maxY = {0, -999}; 
    Vector2 minY = {0, 999}; 
    Vector2 maxX = {-999, 0}; 
    Vector2 minX = {999, 0}; 

    for (auto room : worldRooms){
        if (room.coordinate.y > maxY.y) maxY = room.coordinate; 
        if (room.coordinate.y < minY.y) minY = room.coordinate; 
        if (room.coordinate.x > maxX.x) maxX = room.coordinate; 
        if (room.coordinate.x < minX.x) minX = room.coordinate; 
    }

    std::vector<Vector2> edges = {maxY, minY, maxX, minX}; 
    return edges; 
}

void World::draw(Vector2 _room){
    
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
            if ((!babysBreath.flowerBeat) and (babysBreath.p_room == _room)) babysBreath.drawFlower();
            if ((!orchid.flowerBeat) and (orchid.p_room == _room)) orchid.drawFlower();
            if ((!rose.flowerBeat) and (rose.p_room == _room)) rose.drawFlower();
            if ((!sunflower.flowerBeat) and (sunflower.p_room == _room)) sunflower.drawFlower();
            if ((!lily.flowerBeat) and (lily.p_room == _room)) lily.drawFlower();
            break;
    }   
}
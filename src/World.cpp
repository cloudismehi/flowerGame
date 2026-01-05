#include "World.hpp"

void World::drawBackground(){
    ClearBackground(gv.backgroundColor); 
}

void World::initFlowerPositions(Vector2 _playerPos){
    // make random positions for each flower, making sure they don't land where the player's default position is
    // i don't know that the flower positions will be generated randomly in the future but for now it works

    //! need to allocate some room for each flower 

    Rectangle f_flowerRectangle = {0, 0, gv.flowerDefaultSize, gv.flowerDefaultSize}; 
    
    // babys breath
    do {
        flowerPositions[BABYS_BREATH] = { (float) GetRandomValue(30, (int)gv.windowSize.x - 30), (float) GetRandomValue(30, (int)gv.windowSize.y - 30) };
        f_flowerRectangle.x = flowerPositions[BABYS_BREATH].x; 
        f_flowerRectangle.y = flowerPositions[BABYS_BREATH].y; 
    } while (CheckCollisionCircleRec(_playerPos, gv.characterInitialRadius, f_flowerRectangle)); 
    babysBreath.init(flowerPositions[0]);
    babysBreath.p_room = {0.f, 0.f}; 
    flowerRooms[0] = {0.f, 0.f}; 


    // orchid
    do {
        flowerPositions[ORCHID] = { (float) GetRandomValue(30, (int)gv.windowSize.x - 30), (float) GetRandomValue(30, (int)gv.windowSize.y - 30) };
        f_flowerRectangle.x = flowerPositions[ORCHID].x; 
        f_flowerRectangle.y = flowerPositions[ORCHID].y; 
    }  while (CheckCollisionCircleRec(_playerPos, gv.characterInitialRadius, f_flowerRectangle)); 
    orchid.init(flowerPositions[1]);
    orchid.p_room = {1.f, 0.f}; 
    flowerRooms[1] = {1.f, 0.f}; 

    // rose
    do {
        flowerPositions[ROSE] = { (float) GetRandomValue(30, (int)gv.windowSize.x - 30), (float) GetRandomValue(30, (int)gv.windowSize.y - 30) };
        f_flowerRectangle.x = flowerPositions[ROSE].x; 
        f_flowerRectangle.y = flowerPositions[ROSE].y; 
    } while (CheckCollisionCircleRec(_playerPos, gv.characterInitialRadius, f_flowerRectangle)); 
    rose.init(flowerPositions[2]);
    rose.p_room = {0.f, 1.f}; 
    flowerRooms[2] = {0.f, 1.f}; 

    // sunflower
    do {
        flowerPositions[SUNFLOWER] = { (float) GetRandomValue(30, (int)gv.windowSize.x - 30), (float) GetRandomValue(30, (int)gv.windowSize.y - 30) };
        f_flowerRectangle.x = flowerPositions[SUNFLOWER].x; 
        f_flowerRectangle.y = flowerPositions[SUNFLOWER].y; 
    }  while (CheckCollisionCircleRec(_playerPos, gv.characterInitialRadius, f_flowerRectangle));
    sunflower.init(flowerPositions[3]);
    sunflower.p_room = {-1.f, 0.f}; 
    flowerRooms[3] = {-1.f, 0.f}; 

    // lily 
    do {
        flowerPositions[LILY] = { (float) GetRandomValue(30, (int)gv.windowSize.x - 30), (float) GetRandomValue(30, (int)gv.windowSize.y - 30) };
        f_flowerRectangle.x = flowerPositions[LILY].x; 
        f_flowerRectangle.y = flowerPositions[LILY].y; 
    }  while (CheckCollisionCircleRec(_playerPos, gv.characterInitialRadius, f_flowerRectangle)); 
    lily.init(flowerPositions[4]);
    lily.p_room = {0.f, -1.f}; 
    flowerRooms[4] = {0.f, -1.f}; 
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

    Room _room((Vector2){0, 0}, startWeights, startAdjacent);   // add room 
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
                    Room _newRoom(_newCoord, newWeights, newAdjacent); 

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
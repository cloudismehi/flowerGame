#include <iostream> 
#include <raylib.h>
#include <vector> 
#include <ctime> 
#include <cmath>

#include <raylib.h> 

class World{
    private: 
    void genWorld(); 
    bool makeRoom(); 
    bool checkBuiltRoom(Vector2 _coord); 

    float randomNumber(int _min = 0, int _max = 1);  
    std::vector<Vector2> allRoomCoords; 
    public: 

    struct Room{
        Vector2 coordinate; //coordinates of the current room
        float weights[4]; //north, east, south, west -> these are the odds of a room generated on all direction of the current room 
        bool roomAdjacent[4]; //is there a room adjacent on all directions of the current room

        Room(Vector2 _coord, const float _weights[4], const bool _adjacent[4]){
            for (int i = 0; i < 4; i++){
                weights[i] = _weights[i]; 
                roomAdjacent[i] = _adjacent[i];
            }
            coordinate = _coord;
        }

        Room(){}

        void printStatus(){
            printf("Room (%0.f, %0.f):\n", coordinate.x, coordinate.y); 
            printf("    north: %d (%0.2f), east: %d (%0.2f), south: %d (%0.2f), west: %d (%0.2f)\n", 
                roomAdjacent[0], weights[0], roomAdjacent[1], weights[1], roomAdjacent[2], weights[2], roomAdjacent[3], weights[3]); 
        }
    }; 


    std::vector<Room> worldRooms; 

    void printAllRooms(); 

    World(); 
    ~World(){
        allRoomCoords.clear(); 
        worldRooms.clear();
    }
}; 

int main(){
    World world; 

    InitWindow(800, 800, "world gen test"); 

    while(!WindowShouldClose()){
        BeginDrawing(); 
        ClearBackground(RAYWHITE); 
        
        for (auto room : world.worldRooms){
            DrawCircle(200 + (room.coordinate.x * 20), 200 + (room.coordinate.y * 20), 5, BLACK); 
        }

        EndDrawing(); 
    }

    CloseWindow(); 

    std::cout << "program finished!\n"; 
    return 0; 
}

void World::genWorld(){
    // make starting position, the first room with coordinates (0, 0) and full chances of rooms generated around it 
    float startWeights[4] = {0.8, 0.8, 0.8, 0.8};
    bool startAdjacent[4] = {false, false, false, false};
    Room _room((Vector2){0, 0}, startWeights, startAdjacent); 
    worldRooms.push_back(_room); 
    allRoomCoords.push_back(_room.coordinate); 

    // this is a recursive function to continue to generate all other rooms
    while(makeRoom()); 
}

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


bool World::checkBuiltRoom(Vector2 _coord){
    for (auto coord : allRoomCoords){
        if ((_coord.x == coord.x) and (_coord.y == coord.y)){
            return true; 
        }
    }
    return false; 
}

float World::randomNumber(int _min, int _max){
    float randNum = (float)std::rand() / (RAND_MAX); 
    
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
    std::srand(std::time(0));
    
    do {
        allRoomCoords.clear(); 
        worldRooms.clear(); 
        genWorld();
    } while ((worldRooms.size() < 6) or (worldRooms.size() > 20)); 


    printf("\na total of %d rooms were generated\n", (int) allRoomCoords.size()); 
}


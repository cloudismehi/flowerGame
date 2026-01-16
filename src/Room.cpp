#include "Room.hpp"

float Room::randomNumber(int _min, int _max){
    float randNum = (float)std::rand() / (RAND_MAX); 
    
    randNum *= (_max - _min); 
    randNum += _min; 

    return randNum; 
}

Room::Room(Vector2 _coord, const float _weights[4], const bool _adjacent[4], int _roomSize_x, int _roomSize_y){
    std::srand(std::time(0)); // set the seed for the random number generator using the current time

    randomNumber(); // to make sure the random number generator actually works we need to run it one time, idk why 
    for (int i = 0; i < 4; i++){
        weights[i] = _weights[i]; 
        roomAdjacent[i] = _adjacent[i];
    }
    coordinate = _coord;
}

void Room::init(){
    // generate random states for the cells in the room
    generateObjects(); 

    int noWalls = 0; 
    for (int x = 0; x < noSubdivs_x; x++){
        for (int y = 0; y < noSubdivs_y; y++){
            if (cellStates[x][y]) noWalls++; 
        }
    }
    std::cout << "[ROOM GEN] room (" << coordinate.x << ", " << coordinate.y << ") has " << noWalls << " walls\n"; 

    // run cell automata smoothing five times
    for (int i = 0; i < gv.amountOfSmoothing; i++){ smooth(); } 
}

void Room::printStatus(){
    printf("Room (%0.f, %0.f):\n", coordinate.x, coordinate.y); 
    printf("    north: %d (%0.2f), east: %d (%0.2f), south: %d (%0.2f), west: %d (%0.2f)\n", 
        roomAdjacent[0], weights[0], roomAdjacent[1], weights[1], roomAdjacent[2], weights[2], roomAdjacent[3], weights[3]); 
}

void Room::generateObjects(){
    for (int x = 0; x < noSubdivs_x; x++){
        for (int y = 0; y < noSubdivs_y; y++){
            if (randomNumber(1, 10) > 5.5) cellStates[x][y] = 1; // generate random weights
        }
    }   
}

void Room::drawRoom(){
    for (int x = 0; x < noSubdivs_x; x++){
        for (int y = 0; y < noSubdivs_y;y++){
            Color cellColor = (cellStates[x][y] == 1) ? gv.wallColor : (Color){0, 0, 0, 0}; 
            DrawRectangle(x * subdivSize, y * subdivSize, subdivSize, subdivSize, cellColor); 
        }
    }
}

void Room::smooth(){
    for (int x = 0; x < noSubdivs_x; x++){
        for (int y = 0; y < noSubdivs_y; y++){
            int counter = 0; 
            int neighborhoodSize = 1; 
        
            for (int subX = x - neighborhoodSize; subX <= x + neighborhoodSize; subX++){
                for (int subY = y - neighborhoodSize; subY <= y + neighborhoodSize; subY++){
                    if ((subX < 0) or (subX >= noSubdivs_x) or (subY < 0) or (subY >= noSubdivs_y)) continue; 
        
                    if (cellStates[subX][subY] == 1) counter++; 
                }
            }
            if (counter < 4) cellStates[x][y] = 0; 
            // else cellStates[x][y] = 0; 

            if ((x < 2) or (x > noSubdivs_x - 3) or (y < 2) or (y > noSubdivs_y - 3)) cellStates[x][y] = 0; 
        }
    }
}

void Room::clearSpace(Vector2 _dir){
    // clear in all directions
    if (_dir == (Vector2){0.f, 0.f}){
        std::cout << "[ROOM] clearing all directions\n"; 
        for (int x = (noSubdivs_x / 2) - 2; x < ((noSubdivs_x / 2) + 2); x++){
            for (int y = 0; y < noSubdivs_y; y++){
                cellStates[x][y] = 0; 
            }
        }
        for (int y = (noSubdivs_y / 2) - 2; y < ((noSubdivs_y / 2) + 2); y++){
            for (int x = 0; x < noSubdivs_x; x++){
                cellStates[x][y] = 0; 
            }
        }
    }

    // clear under
    if (_dir == (Vector2){0.f, -1.f}){
        std::cout << "[ROOM] clearing under\n"; 
        for (int x = (noSubdivs_x / 2) - 2; x < ((noSubdivs_x / 2) + 2); x++){
            for (int y = (noSubdivs_y / 2) - 2; y < noSubdivs_y; y++){
                cellStates[x][y] = 0; 
            }
        }
    }

    // clear over
    if (_dir == (Vector2){0.f, 1.f}){
        std::cout << "[ROOM] clearing over\n"; 
        for (int x = (noSubdivs_x / 2) - 2; x < ((noSubdivs_x / 2) + 2); x++){
            for (int y = 0; y < (noSubdivs_y/2) + 2; y++){
                cellStates[x][y] = 0; 
            }
        }
    }

    // clear left
    if (_dir == (Vector2){-1.f, 0.f}){
        std::cout << "[ROOM] clearing left\n"; 
        for (int x = 0; x < ((noSubdivs_x / 2) + 2); x++){
            for (int y = (noSubdivs_y / 2) - 2; y < ((noSubdivs_y / 2) + 2); y++){
                cellStates[x][y] = 0; 
            }
        }
    }

    // clear right
    if (_dir == (Vector2){1.f, 0.f}){
        std::cout << "[ROOM] clearing right\n"; 
        for (int x = (noSubdivs_x / 2) - 2; x < noSubdivs_x; x++){
            for (int y = (noSubdivs_y / 2) - 2; y < ((noSubdivs_y / 2) + 2); y++){
                cellStates[x][y] = 0; 
            }
        }
    }
}

Vector2 Room::loc2Coord(Vector2 _loc){
    Vector2 retVal = {0.f, 0.f}; 

    retVal.x = floor(_loc.x / subdivSize); 
    retVal.y = floor(_loc.y / subdivSize); 
    
    return retVal; 
}
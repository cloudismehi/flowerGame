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

    // generate random states for the cells in the room
    generateObjects(); 

    // run cell automata smoothing five times
    for (int i = 0; i < 5; i++){ smooth(); } 
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
            Color cellColor = (cellStates[x][y] == 1) ? BLACK : (Color){0, 0, 0, 0}; 
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

            if ((x == 0) or (x == noSubdivs_x - 1) or (y == 0) or (y == noSubdivs_y - 1)) cellStates[x][y] = 0; 
        }
    }
}


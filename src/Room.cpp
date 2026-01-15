#include "Room.hpp"

Room::Room(Vector2 _coord, const float _weights[4], const bool _adjacent[4]){
    for (int i = 0; i < 4; i++){
        weights[i] = _weights[i]; 
        roomAdjacent[i] = _adjacent[i];
    }
    coordinate = _coord;
}

void Room::printStatus(){
    printf("Room (%0.f, %0.f):\n", coordinate.x, coordinate.y); 
    printf("    north: %d (%0.2f), east: %d (%0.2f), south: %d (%0.2f), west: %d (%0.2f)\n", 
        roomAdjacent[0], weights[0], roomAdjacent[1], weights[1], roomAdjacent[2], weights[2], roomAdjacent[3], weights[3]); 
}
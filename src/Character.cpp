#include "Character.hpp"

void Character::init(int *_frame, std::vector<Vector2> _roomCoords, Room _curRoom){
    frame = _frame; 
    roomCoordinates = _roomCoords; 
    currentRoom = _curRoom; 
    std::cout << "[CHARACTER] character initialized in room " << currentRoom.coordinate.x << ", " << currentRoom.coordinate.y << '\n'; 
}

void Character::draw(){
    // currentRoom.drawRoom(); 
    // placeholder for character drawing
    DrawCircle(position.x, position.y, radius, gv.defaultCharacterColor);   

    DrawRectangle(gv.windowSize.x - 190, gv.windowSize.y - 40, 190, 40, RAYWHITE); 
    DrawText(TextFormat("in room (%0.f, %0.f)", room.x, room.y), gv.windowSize.x - 180, gv.windowSize.y - 30, 20, BLACK); 
}

void Character::drawStats(){
    //report number of flowers collected
    if (numberOfFlowers == 1){
        DrawText("you have collected 1 flower!", 10, 10, 20, WHITE);
    } else{
        DrawText(TextFormat("you have collected %d flowers!", numberOfFlowers), 10, 10, 20, WHITE);
    }
}

void Character::drawMap(){
    if (hasUnlockedMap){
        DrawRectangle(gv.miniMapPos.x, gv.miniMapPos.y, gv.miniMapSize.x, gv.miniMapSize.y, gv.miniMapBackgroundColor); 

        for (auto _room : roomCoordinates){
            Color roomColor; 
            if ((_room.x == room.x) and (_room.y == room.y)){
                roomColor = gv.miniMapActiveRoom; 
            } else if ((_room.x == 0) and (_room.y == 0)){
                roomColor = gv.miniMapRoomZero; 
            } else roomColor = BLACK; 

            DrawCircle(gv.miniMapPos.x + (gv.miniMapSize.x / 2) + (_room.x * gv.miniMapRoomBuffer), 
                (gv.miniMapPos.y + (gv.miniMapSize.y / 2) - (_room.y * gv.miniMapRoomBuffer)), gv.miniMapRoomSize, roomColor); 
        }
    }
}

Vector2 Character::updatePosition(Vector2 _direction){
    // placeholder for position update logic
    Vector2 newPosition = position; 

    newPosition.x += (_direction.x * speed); 
    newPosition.y += (_direction.y * speed); 

    return newPosition; 
    // handleBoundaries(newPosition);
}

std::vector<Vector2> Character::findRoomEdges(){
    Vector2 maxY = {0, -999}; 
    Vector2 minY = {0, 999}; 
    Vector2 maxX = {-999, 0}; 
    Vector2 minX = {999, 0}; 

    for (auto room : roomCoordinates){
        if (room.y > maxY.y) maxY = room; 
        if (room.y < minY.y) minY = room; 
        if (room.x > maxX.x) maxX = room; 
        if (room.x < minX.x) minX = room; 
    }

    std::vector<Vector2> edges = {maxY, minY, maxX, minX}; 
    return edges; 
}
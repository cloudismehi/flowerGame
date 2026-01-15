#include <iostream> 
#include <vector> 
#include <ctime> 

#include <raylib.h> 
#include <raymath.h> 
#include <rlgl.h>

class Room{
private: 
    Vector2 p_roomSize = {800, 600}; 
    
public:
    static const int subdivSize = 20;
    static const int noSubdivs_x =  800 / subdivSize; 
    static const int noSubdivs_y =  600 / subdivSize; 

    
    int cellStates[noSubdivs_x][noSubdivs_y] = { 0 }; 

    // draws arbitrary polygons from an array of coordinates, the points must be given in counter-clockwise order
    // if _connect is set to true, the last and first points will connect
    void drawArbPolygon(Vector2 *_coords, int _noPoints, bool _connect = false); 

    // generates random number from min to max using rand, to set a seed use srand(std::time(0))
    float randomNumber(int _min = 0, int _max = 1);  

    // generates random tiles on the world, then smooths them out using cell automata
    void generateObjects(); 

    // draw grid of cells, with the walls being any cell with value one 
    void drawRoom(); 

    // using concepts from cellular automata, this block of code looks at neighboring cells and makes decisions on the state
    // of the current cell
    void smooth(); 

    //room initializer, right now it just sets the seed and runs generate object function
    Room();
}; 

int main(){
    Room room1; 
    InitWindow(800, 600, "polygons"); 

    while (!WindowShouldClose()){
        BeginDrawing(); 
        ClearBackground({70, 156, 90, 255}); 
        
        room1.drawRoom(); 

        EndDrawing(); 
    }
    CloseWindow(); 
}

void Room::drawArbPolygon(Vector2 *_coords, int _noPoints, bool _connect){
    rlBegin(RL_TRIANGLES); 

    for (int i = 1; i < _noPoints - 1; i++){
        rlColor4ub(0, 0, 0, 255); 
        rlVertex2f(_coords[i - 1].x, _coords[i - 1].y); 
        rlVertex2f(_coords[i].x, _coords[i].y); 
        rlVertex2f(_coords[i + 1].x, _coords[i + 1].y); 
    }
    if (_connect){
        rlVertex2f(_coords[_noPoints - 2].x, _coords[_noPoints - 2].y);
        rlVertex2f(_coords[_noPoints - 1].x, _coords[_noPoints - 1].y);
        rlVertex2f(_coords[0].x, _coords[0].y);
    }

    rlEnd(); 
}

float Room::randomNumber(int _min, int _max){
    float randNum = (float)std::rand() / (RAND_MAX); 
    
    randNum *= (_max - _min); 
    randNum += _min; 

    return randNum; 
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

Room::Room(){
    std::srand(std::time(0)); 
    
    // generates a random number to kick things off, the first number generated doesn't seem to be random at all,
    // don't know why
    randomNumber(); 
    generateObjects(); 

    for (int i = 0; i < 5; i++){
        smooth(); 
    }
}
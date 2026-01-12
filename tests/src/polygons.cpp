#include <raylib.h> 
#include <iostream> 

#include <raymath.h> 
#include <rlgl.h>

// draws arbitrary polygons from an array of coordinates, the points must be given in counter-clockwise order
// if _connect is set to true, the last and first points will connect
void drawArbPolygon(Vector2 *_coords, int _noPoints, bool _connect = false); 

int main(){
    InitWindow(800, 600, "polygons"); 

    Vector2 points[4] = {
        (Vector2){100, 200}, 
        (Vector2){200, 200}, 
        (Vector2){200, 100}, 
        (Vector2){100, 100}
    };

    Vector2 points2[4] = {
        (Vector2){300, 200}, 
        (Vector2){500, 200}, 
        (Vector2){500, 100}, 
        (Vector2){300, 100}
    }; 

    while (!WindowShouldClose()){
        BeginDrawing(); 
        ClearBackground({70, 156, 90, 255}); 
        
        drawArbPolygon(points, 4, true); 
        drawArbPolygon(points2, 4); 

        EndDrawing(); 
    }
}

void drawArbPolygon(Vector2 *_coords, int _noPoints, bool _connect){
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
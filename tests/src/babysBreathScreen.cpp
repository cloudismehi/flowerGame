#include <iostream>
#include <raylib.h>
#include <raymath.h>

class Room{
private: 
    Vector2 p_roomSize = {800, 600}; 
    
public:
    static const int subdivSize = 20;
    static const int noSubdivs_x =  800 / subdivSize; 
    static const int noSubdivs_y =  600 / subdivSize; 

    bool drawX = false; //debugging tool to keep track of x coordinate of cell on the screen
    bool drawY = false; //debugging tool to keep track of y coordinate of cell on the screen

    
    int cellStates[noSubdivs_x][noSubdivs_y] = { 0 }; 

    // generates random number from min to max using rand, to set a seed use srand(std::time(0))
    float randomNumber(int _min = 0, int _max = 1);  

    // generates random tiles on the world, then smooths them out using cell automata
    void generateObjects(); 

    // draw grid of cells, with the walls being any cell with value one 
    void drawRoom(); 


    //room initializer, right now it just sets the seed and runs generate object function
    Room();

    Vector2 loc2Coord(Vector2 _loc); 
}; 

class Character{
public:
    int speed = 5; 
    int radius = 10; 
    Vector2 position = {400, 570}; 
    Room currentRoom; 
    Color color = {220, 107, 173, 255}; 

    void drawCharacter(); 
    void moveCharacter(); 
    
    Character(Room _room){ currentRoom = _room; }
}; 

class Flower{
private: 
    public: 
    // the p_ here means these are properties of the parent class
    Vector2 p_position; 
    Vector2 p_internalPos; 
    float p_size; 
    Color p_color = YELLOW; 
    Vector2 p_room = {0.f, 0.f}; 
    bool flowerBeat = false; 

    virtual void init(Vector2 _position); 
    virtual void drawFlower(); 
    virtual void drawScreen(); 
    virtual void input(); 
    virtual Character logic(Character _player); 
}; 

class BabysBreath : public Flower{
private:
    // specific properties 
    
public: 
    //init baby's breath with specific color
    BabysBreath(){ p_color = {255, 255, 255, 200}; } // soft white, room right of origin
    void drawScreen() override; 
};

int main(){
    Room room; 
    Character ro(room);
    BabysBreath babysBreath; 

    InitWindow(800, 600, "enemy"); 

    SetTargetFPS(60); 

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground((Color){114, 189, 163, 255});
        
        babysBreath.input(); 
        ro = babysBreath.logic(ro); 

        babysBreath.drawScreen();
        babysBreath.drawFlower();  

        ro.drawCharacter(); 
        
        if (babysBreath.flowerBeat){
            EndDrawing(); 
            return 0; 
        }

        EndDrawing(); 
    }

    return 0; 
}

void Character::drawCharacter(){
    DrawCircle(position.x, position.y, radius, color); 
}

void Character::moveCharacter(){
    Vector2 movementDirection = {0.f, 0.f}; 

    if (IsKeyDown(KEY_UP)){
        movementDirection.y += -1.f;
    }
    if (IsKeyDown(KEY_DOWN)){
        movementDirection.y += 1.f;
    }
    if (IsKeyDown(KEY_LEFT)){
        movementDirection.x += -1.f; 
    }
    if (IsKeyDown(KEY_RIGHT)){
        movementDirection.x += 1.f; 
    }
    
    movementDirection = Vector2Normalize(movementDirection);
    
    Vector2 _newPosition = position; 

    _newPosition.x += (movementDirection.x * speed); 
    _newPosition.y += (movementDirection.y * speed); 

    if ((_newPosition.x > 0) and (_newPosition.x < 800)){
        if ((_newPosition.y > 0) and (_newPosition.y < 600)){
            //check if there is any walls in the new position by checking the state of the cell where the new position is
            Vector2 convCoord = currentRoom.loc2Coord(_newPosition); 

            if (!currentRoom.cellStates[(int)convCoord.x][(int)convCoord.y]){
                position = _newPosition; 
            }
        }
    }
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
            cellStates[x][y] = 0; 
        }
    }   
}

void Room::drawRoom(){
    for (int x = 0; x < noSubdivs_x; x++){
        for (int y = 0; y < noSubdivs_y;y++){
            Color cellColor = (cellStates[x][y] == 1) ? BLACK : (Color){0, 0, 0, 0}; 
            DrawRectangle(x * subdivSize, y * subdivSize, subdivSize, subdivSize, cellColor); 
            
            if (drawX){
                DrawText(TextFormat("%d", x), (x*subdivSize) + 2, (y*subdivSize)+2, 15, DARKGRAY); 
            } else if (drawY){
                DrawText(TextFormat("%d", y), (x*subdivSize) + 2, (y*subdivSize)+2, 15, DARKGRAY); 
            } 
        }
    }
}

Room::Room(){
    std::srand(std::time(0)); 
    
    // generates a random number to kick things off, the first number generated doesn't seem to be random at all,
    // don't know why
    randomNumber(); 
    generateObjects(); 
    
}

Vector2 Room::loc2Coord(Vector2 _loc){
    Vector2 retVal = {0.f, 0.f}; 

    retVal.x = floor(_loc.x / subdivSize); 
    retVal.y = floor(_loc.y / subdivSize); 
    
    return retVal; 
}

void Flower::init(Vector2 _position){
    p_position = _position; 
    p_internalPos = _position; 
    p_size = 10; 
}

void Flower::drawFlower(){
    DrawRectangleV(p_position, {p_size, p_size}, p_color);
}

void Flower::drawScreen(){
    DrawText("you're in the general flower fight screen!", 10, 10, 20, WHITE); 
}

void Flower::input(){
    if (IsKeyPressed(KEY_ENTER)){
        flowerBeat = true; 
    }
}

Character Flower::logic(Character _player){
    // placeholder for flower logic
    Character player = _player; 
    player.moveCharacter(); 
    
    return player; 
}

void BabysBreath::drawScreen(){
    DrawText("you're in the baby's breath fight screen!", 10, 10, 20, WHITE); 
}
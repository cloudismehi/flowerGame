#include "Flowers.hpp"

void Flower::init(Vector2 _position){
    p_position = _position; 
    p_size = gv.flowerDefaultSize; 
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

void Flower::logic(){
    // placeholder for flower logic
}

void BabysBreath::drawScreen(){
    DrawText("you're in the baby's breath fight screen!", 10, 10, 20, WHITE); 
}
void Orchid::drawScreen(){
    DrawText("you're in the orchid fight screen!", 10, 10, 20, WHITE); 
}
void Rose::drawScreen(){
    DrawText("you're in the rose fight screen!", 10, 10, 20, WHITE); 
}
void Sunflower::drawScreen(){
    DrawText("you're in the sunflower fight screen!", 10, 10, 20, WHITE); 
}
void Lily::drawScreen(){
    DrawText("you're in the lily fight screen!", 10, 10, 20, WHITE); 
}
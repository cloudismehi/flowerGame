#include "Flowers.hpp"

void Flower::init(Vector2 _position){
    p_position = _position; 
    p_size = gv.flowerDefaultSize; 
}

void Flower::drawFlower(){
    DrawRectangleV(p_position, {p_size, p_size}, p_color);
}


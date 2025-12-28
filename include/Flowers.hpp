#pragma once

#include <raylib.h>

#include "gameVars.hpp"

/* 
as of right now, for every flower type, the only difference is the color which is updated in each flowers constructor
potentially in the future, each flower type could have its own unique properties and methods
*/

class Flower{
private: 
    GameVars gv;
    public: 
    // the p_ here means these are properties of the parent class
    Vector2 p_position; 
    float p_size; 
    Color p_color = gv.defaultFlowerColor; 
    bool flowerBeat = false; 

    virtual void init(Vector2 _position); 
    virtual void drawFlower(); 
    
}; 

class BabysBreath : public Flower{
private:
    // specific properties 
    
public: 
    //init baby's breath with specific color
    BabysBreath(){ p_color = {255, 255, 255, 200}; } // soft white
    
};

class Orchid : public Flower{
private:
    // specific properties 
    
public: 
    Orchid(){ p_color = {200, 100, 250, 200}; } // light purple
};

class Rose : public Flower{
private:
    // specific properties 
    
public: 
    Rose(){ p_color = {255, 0, 0, 200}; } // soft red
};

class Sunflower : public Flower{
private:
    // specific properties 

public: 
    Sunflower(){ p_color = {255, 223, 0, 200}; } // sunflower yellow
};

class Lily : public Flower{
private:
    // specific properties
    
public: 
    Lily(){ p_color = {241, 127, 41, 200}; } // mauve pink
};
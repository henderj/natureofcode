#pragma once

#include <SDL2/SDL.h>

class Liquid
{
private:
public:
    float x, y, w, h;
    float c;
    Liquid(float _x, float _y, float _w, float _h, float _c);
    ~Liquid();
    void display(SDL_Renderer *rend);
};
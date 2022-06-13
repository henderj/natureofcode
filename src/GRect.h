#pragma once

// #include <SDL2/SDL.h>

class GRect
{
private:
public:
    float x, y, w, h;
    GRect();
    GRect(float _x, float _y, float _w, float _h);
    ~GRect();

    operator SDL_Rect();
    operator SDL_FRect();
};

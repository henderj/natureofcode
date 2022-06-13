#include "GRect.h"
#include <SDL2/SDL.h>

GRect::GRect() : x(0), y(0), w(0), h(0) {}
GRect::GRect(float _x, float _y, float _w, float _h) : x(_x), y(_y), w(_w), h(_h) {}
GRect::~GRect() {}

// GRect::operator SDL_Rect()
// {
//     SDL_Rect rect;
//     rect.x = (int)x;
//     rect.y = (int)y;
//     rect.w = (int)w;
//     rect.h = (int)h;
//     return rect;
// }

// GRect::operator SDL_FRect()
// {
//     SDL_FRect rect;
//     rect.x = x;
//     rect.y = y;
//     rect.w = w;
//     rect.h = h;
//     return rect;
// }
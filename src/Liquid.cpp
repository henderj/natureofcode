#include "Liquid.h"
#include <SDL2/SDL.h>

Liquid::Liquid(float _x, float _y, float _w, float _h, float _c)
    : x(_x), y(_y), w(_w), h(_h), c(_c)
{
}
Liquid::~Liquid() {}
void Liquid::display(SDL_Renderer *rend)
{
    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_SetRenderDrawColor(rend, 66, 245, 215, 255);
    SDL_RenderFillRectF(rend, &rect);
}
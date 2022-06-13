#pragma once

#include "GVector.h"
#include <SDL2/SDL.h>

class Mover
{
public:
    GVector location;
    GVector velocity;
    GVector acceleration;
    float mass;
    Mover();
    Mover(float m, float x, float y);
    void applyForce(const GVector &force, bool isGravity = false);
    void update();
    void checkEdges();
    void display(SDL_Renderer *rend);
};
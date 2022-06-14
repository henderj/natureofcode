#pragma once

#include <SDL2/SDL.h>
#include "GVector.h"
#include "Liquid.h"

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
    bool isInside(Liquid &l);
    void drag(Liquid &l);
    GVector attract(Mover &m);
};
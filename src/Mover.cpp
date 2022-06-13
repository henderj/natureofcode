#include "Mover.h"

#include "config.h"
#include "GVector.h"
#include "Primitives.h"
#include <SDL2/SDL.h>

Mover::Mover()
{
    location = GVector(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    velocity = GVector(0, 0);
    acceleration = GVector(0, 0);
    mass = 1;
}
Mover::Mover(float m, float x, float y)
    : mass(m), location(GVector(x, y)), velocity(GVector(0, 0)), acceleration(GVector(0, 0)) {}
void Mover::applyForce(const GVector &force, bool isGravity)
{
    if (isGravity)
    {
        acceleration.add(force);
        return;
    }
    acceleration.add(force / mass);
}
void Mover::update()
{
    velocity.add(acceleration);
    // velocity.limit(topSpeed);
    location.add(velocity);
    acceleration.mult(0);
}
void Mover::checkEdges()
{
    if (location.x > SCREEN_WIDTH)
    {
        location.x = SCREEN_WIDTH;
        velocity.x *= -1;
    }
    else if (location.x < 0)
    {
        location.x = 0;
        velocity.x *= -1;
    }

    if (location.y > SCREEN_HEIGHT)
    {
        location.y = SCREEN_HEIGHT;
        velocity.y *= -1;
    }
}
void Mover::display(SDL_Renderer *rend)
{
    SDL_SetRenderDrawColor(rend, 81, 148, 219, 175);
    SDL_RenderFillCircle(rend, location.x, location.y, mass * 16);
}

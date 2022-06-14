#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "config.h"
#include "Primitives.h"
#include "GVector.h"
#include "Mover.h"
#include "Liquid.h"

GVector mousePos;

void PlayGame(SDL_Renderer *rend);
void setup();
void draw(SDL_Renderer *rend);
float randomFloat(float a, float b)
{
    return a + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (b - a)));
}
float constrain(float f, float min, float max)
{
    if (f < min)
        f = min;
    else if (f > max)
        f = max;
    return f;
}

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window *win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    PlayGame(rend);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

void PlayGame(SDL_Renderer *rend)
{
    // SDL_Surface *temp;
    // temp = IMG_Load("colored-transparent.png");
    // SDL_Texture *spritesheet = SDL_CreateTextureFromSurface(rend, temp);

    // SDL_FreeSurface(temp);

    int close = 0;
    int speed = 8;
    int lastFrameTimeStamp = 0;
    int deltaTime = 0;
    int mouseX, mouseY;

    setup();

    while (!close)
    {
        deltaTime = SDL_GetTicks() - lastFrameTimeStamp;
        lastFrameTimeStamp = SDL_GetTicks();
        SDL_Event event;
        int totalFrames = 8;
        int delayPerFrame = 100;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                close = 1;
                break;
            default:
                break;
            }
        }

        SDL_GetMouseState(&mouseX, &mouseY);
        mousePos.x = mouseX;
        mousePos.y = mouseY;

        SDL_SetRenderDrawColor(rend, 71, 45, 60, 255);
        SDL_RenderClear(rend);

        draw(rend);

        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 60);
    }
}

class Attractor
{
private:
public:
    float mass;
    GVector location;
    float G;
    Attractor();
    ~Attractor();
    void display(SDL_Renderer *rend);
    GVector attract(Mover &m);
};

Attractor::Attractor() : mass(500), location(GVector(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)), G(0.4) {}
Attractor::~Attractor() {}
void Attractor::display(SDL_Renderer *rend)
{
    SDL_SetRenderDrawColor(rend, 169, 90, 191, 255);
    SDL_RenderFillCircle(rend, location.x, location.y, 25);
}
GVector Attractor::attract(Mover &m)
{
    GVector force = location - m.location;
    float dist = force.mag();
    dist = constrain(dist, 5, 25);
    force.normalize();
    float strength = (G * mass * m.mass) / (dist * dist);
    force.mult(strength);
    return force;
}

Mover movers[30];
// GVector wind = GVector(0.01, 0);
// GVector gravity = GVector(0, 0.1);
// float c = 0.01;

// Mover m;
Attractor a;
Liquid l = Liquid(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.001);
bool attract;

void setup()
{
    std::srand((unsigned)std::time(0));
    attract = randomFloat(0, 1) > 0.5;
    for (auto i = 0; i < sizeof(movers) / sizeof(Mover); i++)
    {
        movers[i] = Mover(randomFloat(1, 10), randomFloat(0, SCREEN_WIDTH), randomFloat(0, SCREEN_HEIGHT));
        // movers[i].velocity = GVector(1, 0);
    }
}

void draw(SDL_Renderer *rend)
{
    a.location = mousePos;
    // a.display(rend);
    for (auto i = 0; i < sizeof(movers) / sizeof(Mover); i++)
    {
        for (auto j = 0; j < sizeof(movers) / sizeof(Mover); j++)
        {
            if (i == j)
                continue;
            GVector force = movers[j].attract(movers[i]);
            // movers[i].applyForce(force);
            force = movers[i].collision(movers[j]);
            movers[i].applyForce(force);
            movers[i].drag(l);
        }
        GVector edgeForce = movers[i].checkEdgesForce();
        movers[i].applyForce(edgeForce);

        GVector mouseForce = a.attract(movers[i]);
        if (!attract)
            mouseForce.mult(-1);
        movers[i].applyForce(mouseForce);

        movers[i].update();
        movers[i].display(rend);
    }
    // m.update();
    // m.display(rend);
}
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Primitives.h"
#include "GVector.h"
#include "config.h"
#include "Mover.h"

GVector mousePos;

void PlayGame(SDL_Renderer *rend);
void setup();
void draw(SDL_Renderer *rend);
float randomFloat(float a, float b)
{
    return a + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (b - a)));
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
    SDL_RenderDrawRectF(rend, &rect);
}

Mover movers[20];
GVector wind = GVector(0.01, 0);
GVector gravity = GVector(0, 0.1);
float c = 0.01;

Liquid liquid = Liquid(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0.1);

void setup()
{
    std::srand((unsigned)std::time(0));

    for (auto i = 0; i < sizeof(movers) / sizeof(Mover); i++)
    {
        movers[i] = Mover(randomFloat(0.1, 5), 0, 0);
    }
}

void draw(SDL_Renderer *rend)
{
    for (auto i = 0; i < sizeof(movers) / sizeof(Mover); i++)
    {
        GVector friction = GVector(movers[i].velocity);
        friction.mult(-1);
        friction.normalize();
        friction.mult(c);

        movers[i].applyForce(wind);
        movers[i].applyForce(gravity, true);
        movers[i].applyForce(friction);

        movers[i].update();
        movers[i].checkEdges();
        movers[i].display(rend);
    }
}
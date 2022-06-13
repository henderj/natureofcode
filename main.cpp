#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Primitives.h"
#include "GVector.h"
#include "GRect.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 360;
GVector mousePos;

void PlayGame(SDL_Renderer *rend);
void draw(SDL_Renderer *rend);

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

GVector location;
GVector dif;
GVector center = GVector(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

void draw(SDL_Renderer *rend)
{

    dif = mousePos - center;
    dif.normalize();
    dif.mult(50);
    location = center + dif;
    SDL_SetRenderDrawColor(rend, 81, 148, 219, 255);
    // SDL_RenderFillCircle(rend, location.x, location.y, 16);
    // GRect rect = GRect(0, 0, dif.mag(), 10);
    // SDL_FRect frect = rect;
    SDL_FRect frect;
    frect.x = 0;
    frect.y = 0;
    frect.w = dif.mag();
    frect.h = 10;
    SDL_RenderFillRectF(rend, &frect);
    SDL_RenderDrawLineF(rend, center.x, center.y, location.x, location.y);
}
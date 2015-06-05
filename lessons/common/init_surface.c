#include "init.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *init(SDL_Surface **screen) {
    SDL_Window *gWindow = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow != NULL) {
            //Get window surface
            *screen = SDL_GetWindowSurface(gWindow);
            //printf("init: screen pointer values: %p\n", *screen);
        }
        else {
            printf("SDL_Init failed ON WINDOW: %s\n", SDL_GetError());
        }
    }
    else {
        printf("SDL init: unable to start: %s\n", SDL_GetError());
    }

    return gWindow;
}


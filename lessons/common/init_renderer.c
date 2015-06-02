#include "init_renderer.h"

SDL_Renderer *_init_renderer(SDL_Window *gWindow, struct renderer_RGBA *colours) {
    SDL_Renderer *gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    
    if (gRenderer != NULL) {
        //Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, colours->r, colours->b, colours->g, colours-a);
    }

    return gRenderer;
}
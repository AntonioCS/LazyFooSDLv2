#include "init_sdlimage.h"

SDL_Window *init_sdlimage(SDL_Surface **screen) {
    SDL_Window *w = init(&(*screen));

    if (w != NULL) {
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            SDL_DestroyWindow(w);
            w = NULL;
        }
    }

    return w;
}

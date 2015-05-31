#include "loadmedia.h"

SDL_Surface *loadMedia(char *path) {
    char *full_path = resource_path(path);

    if (full_path != NULL) {
        SDL_Surface *image = SDL_LoadBMP(full_path);
        
        free(full_path);
        full_path = NULL;

        return image;
    }

    return NULL;
}
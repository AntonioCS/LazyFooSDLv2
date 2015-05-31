
#include "loadmedia_sdlimage.h"


SDL_Surface *loadMedia_sdlimage(char *path) {
    char *full_path = resource_path(path);

    if (full_path != NULL) {
        SDL_Surface *image = IMG_Load(full_path);

        free(full_path);
        full_path = NULL;

        return image;
    }

    return NULL;
}
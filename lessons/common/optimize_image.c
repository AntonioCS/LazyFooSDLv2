
#include "optimize_image.h"

SDL_Surface *optimize_image(SDL_Surface *image, SDL_Surface *main_surface) {

    if (image != NULL) {
        //The final optimized image
        SDL_Surface *optimizedSurface = SDL_ConvertSurface(image, main_surface->format, 0);

        if (optimizedSurface != NULL) {            
            return optimizedSurface;
        }
    }

    return NULL;
}

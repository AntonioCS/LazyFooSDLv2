#include "loadtexture.h"

SDL_Texture *loadTexture(SDL_Surface **loadedSurface, SDL_Renderer *renderer) {
    //The final texture
    SDL_Texture *newTexture = NULL;

    if (*loadedSurface != NULL) {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, *loadedSurface);
        
        if (newTexture != NULL) {
            //Get rid of old loaded surface
            SDL_FreeSurface(*loadedSurface);
        }

    }

    return newTexture;
}

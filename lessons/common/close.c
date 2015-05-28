
#include "close.h"

void close(SDL_Surface **gImage, SDL_Window **gWindow) {
    //Deallocate surface
    SDL_FreeSurface(*gImage);
    *gImage = NULL;

    //Destroy window
    SDL_DestroyWindow(*gWindow);
    *gWindow = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
}


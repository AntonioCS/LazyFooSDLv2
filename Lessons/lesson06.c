#include "../SDL_Helper.h"

static bool loadMediaLocal();
static SDL_Surface* loadSurface(char *);

//Current displayed PNG image
static SDL_Surface *gPNGSurface = NULL;

static bool loadMediaLocal() {
    //Loading success flag
    bool success = true;

    //Load PNG surface
    gPNGSurface = loadSurface(resources_path("images/lesson06/loaded.png"));
    if (gPNGSurface == NULL) {
        printf("Failed to load PNG image!\n");
        success = false;
    }

    return success;
}

SDL_Surface* loadSurface(char *path) {
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path); //<--------- NOTE: Different from lesson 05
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    else {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, sdl_unused_flags);
        if (optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

void lesson06() {
    //Start up SDL and create window
    if (!init_with_image()) {
        printf("Failed to initialize!\n");
    }
    else {
        //Load media
        if (!loadMediaLocal()) {
            printf("Failed to load media!\n");
        }
        else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                //Apply the PNG image
                SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    //Free resources and close SDL
    close();
}
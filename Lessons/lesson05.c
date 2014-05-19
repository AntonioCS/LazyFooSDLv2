#include "../SDL_Helper.h"

static bool loadMediaLocal();
static SDL_Surface *loadSurface(char *);

//Current displayed image
static SDL_Surface* gStretchedSurface = NULL;

bool loadMediaLocal() {
    //Loading success flag
    bool success = true;

    //Load stretching surface
    gStretchedSurface = loadSurface(resources_path("images/lesson05/stretch.bmp"));
    if (gStretchedSurface == NULL) {
        printf("Failed to load stretching image!\n");
        success = false;
    }

    return success;
}

SDL_Surface *loadSurface(char *path) {
    //The final optimized image
    SDL_Surface *optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = SDL_LoadBMP(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
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


void lesson05() {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        //Load media
        if (!loadMediaLocal()) { //internal to this file
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

                //Apply the image stretched
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;
                SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    //Free loaded image
	SDL_FreeSurface(gStretchedSurface);
	gStretchedSurface = NULL;
    close();
}
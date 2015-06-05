/* 
 * File:   lesson05.c
 * Author: antoniocs
 *
 * Created on 30 de Maio de 2015, 12:26
 */

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init_surface.h"
#include "common/loadmedia.h"
#include "common/optimize_image.h"
#include "common/close.h"

/*
 * 
 */
int main(int argc, char** argv) {

    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;

    SDL_Surface *image = NULL;

    gWindow = init_surface(&gScreenSurface);

    //a bit of duplication
    int SCREEN_WIDTH = 640;
    int SCREEN_HEIGHT = 480;

    if (gWindow) {
        image = optimize_image(loadMedia("images/lesson05/stretch.bmp"), gScreenSurface);

        if (image) {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Apply the image stretched
            SDL_Rect stretchRect;

            stretchRect.x = 0;
            stretchRect.y = 0;
            stretchRect.w = SCREEN_WIDTH;
            stretchRect.h = SCREEN_HEIGHT;

            SDL_BlitScaled(image, NULL, gScreenSurface, &stretchRect);

            //Update the surface
            SDL_UpdateWindowSurface(gWindow);

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
            }
        }

        SDL_FreeSurface(image);
    }

    //Free resources and close SDL
    close(&gScreenSurface, &gWindow);

    return (EXIT_SUCCESS);
}


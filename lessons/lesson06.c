/* 
 * File:   lesson06.c
 * Author: antoniocs
 *
 * Created on 31 de Maio de 2015, 17:18
 */

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init_surface.h"
#include "common/init_only_sdlimage.h"
#include "common/optimize_image.h"
#include "common/loadmedia_sdlimage.h"
#include "common/close.h"

/*
 * 
 */
int main(int argc, char** argv) {

    //The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;

    //The window we'll be rendering to
    SDL_Window *gWindow = init_surface(&gScreenSurface);
    //SDL_Window *gWindow = init_sdlimage(&gScreenSurface);

    SDL_Surface *image = NULL;

    if (gWindow != NULL && init_sdlimage()) {
        image = optimize_image(loadMedia_sdlimage("images/lesson06/loaded.png"), gScreenSurface);

        if (image != NULL) {
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
                SDL_BlitSurface(image, NULL, gScreenSurface, NULL);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }

        IMG_Quit();
    }

    close(&gScreenSurface, &gWindow);

    return (EXIT_SUCCESS);
}


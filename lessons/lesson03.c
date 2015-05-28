/* 
 * File:   lesson03.c
 * Author: antoniocs
 *
 * Created on 28 de Maio de 2015, 23:38
 */

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init.h"
#include "common/loadmedia.h"
#include "common/close.h"

/*
 * 
 */
int main(int argc, char** argv) {
    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;

    //The image we will load and show on the screen
    SDL_Surface *gImage = NULL;


    gWindow = init(&gScreenSurface);
    //Start up SDL and create window
    if (gWindow) {
        
        gImage = loadMedia("images/x.bmp");
        
        if (gImage) {            
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Apply the image
            SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    else {
        printf("Failed to create window: %s\n", SDL_GetError());
    }

    //Free resources and close SDL
    close(&gImage, &gWindow);

    return (EXIT_SUCCESS);
}


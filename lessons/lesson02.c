/* 
 * File:   lesson02.c
 * Author: antoniocs
 *
 * Created on 27 de Maio de 2015, 19:47
 */

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "common/init_surface.h"
#include "common/loadmedia.h"
#include "common/close.h"

int main(int argc, char** argv) {
    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;

    //The image we will load and show on the screen
    SDL_Surface *gHelloWorld = NULL;


    gWindow = init_surface(&gScreenSurface);

    if (gWindow) {
        gHelloWorld = loadMedia("images/hello_world.bmp");

        if (gHelloWorld) {
            //Apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            //Update the surface
            SDL_UpdateWindowSurface(gWindow);

            //Wait two seconds
            SDL_Delay(2000);           
        }
        else {
            printf("Falha ao carregar imagem\n");
            printf("SDL_Init failed: %s\n", SDL_GetError());
        }
    }
    else {
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }

    close(&gHelloWorld, &gWindow);


    return (EXIT_SUCCESS);
}


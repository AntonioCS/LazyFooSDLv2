/* 
 * File:   lesson01.c
 * Author: antoniocs
 *
 * Created on 27 de Maio de 2015, 19:32
 */

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "common/init.h"

//Screen dimension constants
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    //The window we'll be rendering to
    SDL_Window *window = NULL;

    //The surface contained by the window
    SDL_Surface *screenSurface = NULL;
    ///*
    window = init(&screenSurface);
    printf("window pointer values: %p\n", window);
    if (window) {
        printf("lesson init: screen pointer values: %p\n", screenSurface);
        //Fill the surface white
        //SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 238, 118, 33));

        //Update the surface
        SDL_UpdateWindowSurface(window);

        //Wait two seconds
        SDL_Delay(2000);
    } else {
        printf("Falha ao criar window\n");
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }
    //*/
    /*
        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        } else {
            //Create window
            window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (window == NULL) {
                printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            } else {
                //Get window surface
                screenSurface = SDL_GetWindowSurface(window);

                //Fill the surface white
                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

                //Update the surface
                SDL_UpdateWindowSurface(window);

                //Wait two seconds
                SDL_Delay(2000);
            }
        }
     //*/
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return EXIT_SUCCESS;
}

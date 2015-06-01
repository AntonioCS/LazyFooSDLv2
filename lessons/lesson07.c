/* 
 * File:   lesson07.c
 * Author: antoniocs
 *
 * Created on 01 June 2015, 09:53
 */

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init.h"
#include "common/init_sdlimage.h"
#include "common/optimize_image.h"
#include "common/loadmedia_sdlimage.h"
#include "common/close.h"
#include "common/loadtexture.h"

/*
 * 
 */
int main(int argc, char** argv) {

    //The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;

    //The window we'll be rendering to
    SDL_Window *gWindow = init_sdlimage(&gScreenSurface);

    SDL_Surface *image = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;

    if (gWindow != NULL) {

        //Create renderer for window
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer != NULL) {
            image = optimize_image(loadMedia_sdlimage("images/lesson07/texture.png"), gScreenSurface);

            if (image != NULL) {
                gTexture = loadTexture(&image, gRenderer);

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

                }
            }
        }

        IMG_Quit();
    }

    close(&gScreenSurface, &gWindow);

    return (EXIT_SUCCESS);
}


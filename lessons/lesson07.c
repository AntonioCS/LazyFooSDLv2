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
#include "common/init_surface.h"
#include "common/init_only_sdlimage.h"
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
    SDL_Window *gWindow = init_surface(&gScreenSurface);
   

    SDL_Surface *image = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;

    if (gWindow != NULL && init_sdlimage()) {

        //Create renderer for window
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer != NULL) {
            //Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

            image = optimize_image(loadMedia_sdlimage("images/lesson07/texture.png"), gScreenSurface);

            if (image != NULL) {
                gTexture = loadTexture(&image, gRenderer);

                if (gTexture == NULL) {
                    printf("Unable to load texture: %s\n", SDL_GetError());
                    exit(EXIT_FAILURE);
                }

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

                    //Clear screen
                    SDL_RenderClear(gRenderer);

                    //Render texture to screen
                    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                    //Update screen
                    SDL_RenderPresent(gRenderer);
                }

                //Free loaded image
                SDL_DestroyTexture(gTexture);
                gTexture = NULL;

                //Destroy renderer
                SDL_DestroyRenderer(gRenderer);
            }
        }

        IMG_Quit();
    }

    close(&gScreenSurface, &gWindow);

    return (EXIT_SUCCESS);
}


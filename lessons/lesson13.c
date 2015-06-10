/* 
 * File:   lesson13.c
 * Author: antoniocs
 *
 * Created on 09 June 2015, 13:09
 */

#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init_renderer.h"
#include "common/init_only_sdlimage.h"
#include "common/resource_path.h"
#include "class/LTexture.class.h"

static void handle_alpha_change(SDL_Keycode, Uint8 *);

int main(int argc, char** argv) {

    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);

    if (gWindow != NULL && init_sdlimage()) {
        bool quit = false;

        //Event handler
        SDL_Event e;

        //Scene textures
        LTexture *gModulatedTexture = LTexture_Init(gRenderer);
        LTexture *gBackgroundTexture = LTexture_Init(gRenderer);

        if ((gModulatedTexture == NULL ||
                !gModulatedTexture->loadFromFile(gModulatedTexture, resource_path("images/lesson13/fadeout.png")))
                ||
                (gBackgroundTexture == NULL ||
                !gBackgroundTexture->loadFromFile(gBackgroundTexture, resource_path("images/lesson13/fadein.png")))
                ) {
            printf("Unable to allocate ltexture or image\n");

        } else {

            //Modulation component
            Uint8 a = 255;

            gModulatedTexture->setBlendMode(gModulatedTexture, SDL_BLENDMODE_BLEND);

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit ----------- Quit also with ESCAPE key pressed
                    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        handle_alpha_change(e.key.keysym.sym, &a);
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render background
                gBackgroundTexture->render(gBackgroundTexture, 0, 0, NULL);

                //Render front blended
                gModulatedTexture->setAlpha(gModulatedTexture, a);
                gModulatedTexture->render(gModulatedTexture, 0, 0, NULL);

                //Update screen
                SDL_RenderPresent(gRenderer);

                //So its not super cpu intensive
                SDL_Delay(1);
            }

            gBackgroundTexture->free(gBackgroundTexture);
            gModulatedTexture->free(gModulatedTexture);
        }
    } else {
        printf("Something wrong with the window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

    exit(EXIT_SUCCESS);
}

void handle_alpha_change(SDL_Keycode k, Uint8 *a) {
    switch (k) {
        case SDLK_w: //Increase alpha on w
        {         
            //Cap if over 255
            if (*a + 32 > 255) {
                *a = 255;
            }//Increment otherwise
            else {
                *a += 32;
            }
        }
            break;
        case SDLK_s: //Decrease alpha on s
        {            
            //Cap if below 0
            if (*a - 32 < 0) {
                *a = 0;
            }//Decrement otherwise
            else {
                *a -= 32;
            }
        }
            break;
    }
}
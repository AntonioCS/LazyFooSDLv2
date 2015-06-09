/* 
 * File:   lesson12.c
 * Author: antoniocs
 *
 * Created on 9 de Junho de 2015, 8:06
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


static void change_rgb_values(SDL_Keycode, Uint8 *, Uint8 *, Uint8 *);

int main(int argc, char** argv) {
    //const int SCREEN_WIDTH = 640;
    //const int SCREEN_HEIGHT = 480;

    //SDL_Surface *image = NULL;
    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);

    if (gWindow != NULL && init_sdlimage()) {
        bool quit = false;

        //Event handler
        SDL_Event e;

        //Scene texture
        LTexture *gModulatedTexture = lt_init(gRenderer);

        if (gModulatedTexture == NULL ||
                !gModulatedTexture->load_from_file(gModulatedTexture, resource_path("images/lesson12/colors.png"))) {
            printf("Unable to allocate ltexture or image\n");

        } else {

            //Modulation components
            Uint8 r = 255;
            Uint8 g = 255;
            Uint8 b = 255;


            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit ----------- Quit also with ESCAPE key pressed
                    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        change_rgb_values(e.key.keysym.sym, &r, &g, &b);
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Modulate and render texture
                gModulatedTexture->set_color(gModulatedTexture, r, g, b);
                gModulatedTexture->render(gModulatedTexture, 0, 0, NULL);


                //Update screen
                SDL_RenderPresent(gRenderer);

                //So its not super cpu intensive
                SDL_Delay(1);
            }
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

void change_rgb_values(SDL_Keycode k_pressed, Uint8 *r, Uint8 *g, Uint8 *b) {
    //On keypress change rgb values
    switch (k_pressed) {
            //Increase red
        case SDLK_q:
            *r += 32;
            break;

            //Increase green
        case SDLK_w:
            *g += 32;
            break;

            //Increase blue
        case SDLK_e:
            *b += 32;
            break;

            //Decrease red
        case SDLK_a:
            *r -= 32;
            break;

            //Decrease green
        case SDLK_s:
            *g -= 32;
            break;

            //Decrease blue
        case SDLK_d:
            *b -= 32;
            break;
    }
}
/* 
 * File:   lesson11.c
 * Author: antoniocs
 *
 * Created on 7 de Junho de 2015, 19:51
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

void initialize_sprit_coords(SDL_Rect *);

int main(int argc, char** argv) {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Surface *image = NULL;
    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);

    if (gWindow != NULL && init_sdlimage()) {
        bool quit = false;

        //Event handler
        SDL_Event e;

        //Scene sprites
        SDL_Rect gSpriteClips[4];
        LTexture *gSpriteSheetTexture = lt_init(gRenderer);

        if (gSpriteSheetTexture == NULL ||
                ! gSpriteSheetTexture->load_from_file(gSpriteSheetTexture, resource_path("images/lesson11/dots.png"))) {
            printf("Unable to allocate ltexture or image\n");

        } else {

            initialize_sprit_coords(gSpriteClips);

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit ----------- Quit also with ESCAPE key pressed
                    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                        quit = true;
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render top left sprite
                gSpriteSheetTexture->render(gSpriteSheetTexture, 0, 0, &gSpriteClips[0]);

                //Render top right sprite
                gSpriteSheetTexture->render(gSpriteSheetTexture, SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ]);

                //Render bottom left sprite
                gSpriteSheetTexture->render(gSpriteSheetTexture, 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ]);

                //Render bottom right sprite
                gSpriteSheetTexture->render(gSpriteSheetTexture, SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ]);

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

void initialize_sprit_coords(SDL_Rect *clips) {
    //Set top left sprite
    clips[0].x = 0;
    clips[0].y = 0;
    clips[0].w = 100;
    clips[0].h = 100;

    //Set top right sprite
    clips[1].x = 100;
    clips[1].y = 0;
    clips[1].w = 100;
    clips[1].h = 100;

    //Set bottom left sprite
    clips[2].x = 0;
    clips[2].y = 100;
    clips[2].w = 100;
    clips[2].h = 100;

    //Set bottom right sprite
    clips[3].x = 100;
    clips[3].y = 100;
    clips[3].w = 100;
    clips[3].h = 100;
}
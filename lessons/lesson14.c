/* 
 * File:   lesson14.c
 * Author: antoniocs
 *
 * Created on 9 de Junho de 2015, 18:48
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

void setup_sprite_clips(SDL_Rect []);

int main(int argc, char** argv) {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    //SDL_Surface *image = NULL;
    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);

    if (gWindow != NULL && init_sdlimage()) {

        //Walking animation
        const int WALKING_ANIMATION_FRAMES = 4;
        SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
        LTexture *gSpriteSheetTexture = LTexture_Init(gRenderer);

        if (gSpriteSheetTexture == NULL ||
                !gSpriteSheetTexture->loadFromFile(gSpriteSheetTexture, resource_path("images/lesson14/foo.png"))) {
            printf("Unable to allocate ltexture or image\n");

        } else {

            setup_sprite_clips(gSpriteClips);

            //Current animation frame
            int frame = 0;

            bool quit = false;

            //Event handler
            SDL_Event e;

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

                //printf("Frame: %d - Divided by 4: %d\n", frame, frame / 4);

                //Render current frame
                SDL_Rect *currentClip = &gSpriteClips[frame / 4];
                gSpriteSheetTexture->render(gSpriteSheetTexture, (SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);

                //Update screen
                SDL_RenderPresent(gRenderer);

                //Go to next frame
                ++frame;

                //Cycle animation
                if (frame / 4 >= WALKING_ANIMATION_FRAMES) {
                    frame = 0;
                }

                //So its not super cpu intensive
                //This delay has to be here otherwise the images are switched too fast
                //SDL_Delay(50);

                //Using SDL_RENDERER_PRESENTVSYNC in the init function as I should have used the image
                //doesn't go too fast so there is no need for a big delay
            }

            gSpriteSheetTexture->free(gSpriteSheetTexture);
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

void setup_sprite_clips(SDL_Rect gSpriteClips[]) {

    //Set sprite clips
    gSpriteClips[ 0 ].x = 0;
    gSpriteClips[ 0 ].y = 0;
    gSpriteClips[ 0 ].w = 64;
    gSpriteClips[ 0 ].h = 205;

    gSpriteClips[ 1 ].x = 64;
    gSpriteClips[ 1 ].y = 0;
    gSpriteClips[ 1 ].w = 64;
    gSpriteClips[ 1 ].h = 205;

    gSpriteClips[ 2 ].x = 128;
    gSpriteClips[ 2 ].y = 0;
    gSpriteClips[ 2 ].w = 64;
    gSpriteClips[ 2 ].h = 205;

    gSpriteClips[ 3 ].x = 196;
    gSpriteClips[ 3 ].y = 0;
    gSpriteClips[ 3 ].w = 64;
    gSpriteClips[ 3 ].h = 205;
}
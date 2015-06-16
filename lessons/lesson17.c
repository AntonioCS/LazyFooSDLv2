/* 
 * File:   lesson17.c
 * Author: antoniocs
 *
 * Created on 13 de Junho de 2015, 23:19
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
#include "class/LButton.class.h"

int main(int argc, char** argv) {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    //Button constants
    const int BUTTON_WIDTH = 300;
    const int BUTTON_HEIGHT = 200;
    const int TOTAL_BUTTONS = 4;

    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);

    if (gWindow != NULL && init_sdlimage()) {
        bool quit = false;

        LTexture *gButtonSpriteSheetTexture = LTexture_Init(gRenderer);


        if (gButtonSpriteSheetTexture &&
                gButtonSpriteSheetTexture->loadFromFile(gButtonSpriteSheetTexture, resource_path("images/lesson17/button.png"))) {

            //Mouse button sprites
            SDL_Rect gSpriteClips[LButton_TotalSpriteButtons()];

            //Buttons objects
            LButton * gButtons[TOTAL_BUTTONS];

            //Set sprites
            for (int i = 0; i < TOTAL_BUTTONS; ++i) {
                gSpriteClips[i].x = 0;
                gSpriteClips[i].y = i * 200;
                gSpriteClips[i].w = BUTTON_WIDTH;
                gSpriteClips[i].h = BUTTON_HEIGHT;
            }

            //So that we already have all the gSpriteClips initialized
            for (int i = 0; i < TOTAL_BUTTONS; i++) {
                gButtons[i] = LButton_Init(gButtonSpriteSheetTexture, gSpriteClips);

                if (gButtons[i] == NULL) {
                    printf("Error allocating LButton\n");
                    goto terminate;
                }
            }

            //Set buttons in corners
            gButtons[0]->setPosition(gButtons[0], 0, 0);
            gButtons[1]->setPosition(gButtons[1], SCREEN_WIDTH - BUTTON_WIDTH, 0);
            gButtons[2]->setPosition(gButtons[2], 0, SCREEN_HEIGHT - BUTTON_HEIGHT);
            gButtons[3]->setPosition(gButtons[3], SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);

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

                    //Handle button events
                    for (int i = 0; i < TOTAL_BUTTONS; ++i) {
                        gButtons[i]->handleEvent(gButtons[i], &e);
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render buttons
                for (int i = 0; i < TOTAL_BUTTONS; ++i) {
                    gButtons[i]->render(gButtons[i]);
                }

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

terminate:
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
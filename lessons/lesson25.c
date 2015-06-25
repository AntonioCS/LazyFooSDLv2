/* 
 * File:   lesson25.c
 * Author: antoniocs
 *
 * Created on 24 de Junho de 2015, 8:27
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init_renderer.h"
#include "common/init_only_sdlimage.h"
#include "common/resource_path.h"
#include "class/LTexture.class.h"
#include "class/LTimer.class.h"

#define TIMESTRBUFFERSIZE 100

int main(int argc, char** argv) {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int SCREEN_FPS = 60;
    const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);

    //Initialize TTF directly here (no external function)
    if (gWindow != NULL && init_sdlimage() && TTF_Init() == 0) {
        //Destroy window
	SDL_DestroyRenderer( gRenderer );

        //////////////////////////////////////////////////
        //Create renderer for window --- Disable Vsync
        //////////////////////////////////////////////////
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

        //Scene textures
        LTexture *gFPSTextTexture = LTexture_Init(gRenderer);

        //Open the font
        TTF_Font *gFont = TTF_OpenFont(resource_path("fonts/lazy.ttf"), 28);

        if (gFont == NULL) {
            printf("Unable to load font - %s\n", TTF_GetError());
            goto terminate;
        }


        bool quit = false;

        //Event handler
        SDL_Event e;


        //Set text color as black
        SDL_Color textColor = {0, 0, 0, 255};

        //The frames per second timer
        LTimer *fpsTimer = LTimer_Init();

        //The frames per second cap timer
        LTimer *capTimer = LTimer_Init();

        //Start counting frames per second
        int countedFrames = 0;
        fpsTimer->start(fpsTimer);

        //In memory text stream
        char timeText[TIMESTRBUFFERSIZE] = {0};

        //While application is running
        while (!quit) {
            //Start cap timer
            capTimer->start(capTimer);

            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User requests quit ----------- Quit also with ESCAPE key pressed
                if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                    quit = true;
                }
            }

            //Calculate and correct fps
            float avgFPS = countedFrames / (fpsTimer->getTicks(fpsTimer) / 1000.f);
            if (avgFPS > 2000000) {
                avgFPS = 0;
            }

            //clear time string
            memset(timeText, 0, TIMESTRBUFFERSIZE);
            //snprintf(timeText, TIMESTRBUFFERSIZE, "Milliseconds since start time %u", (timer->getTicks(timer) / 1000.f));
            snprintf(timeText, TIMESTRBUFFERSIZE, "Average Frames Per Second %f", avgFPS);

            //Set the time text
            gFPSTextTexture->loadFromRenderedText(gFPSTextTexture, timeText, gFont, textColor);


            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            gFPSTextTexture->render(gFPSTextTexture,
                    (SCREEN_WIDTH - gFPSTextTexture->getWidth(gFPSTextTexture)) / 2,
                    (SCREEN_HEIGHT - gFPSTextTexture->getHeight(gFPSTextTexture)) / 2,
                    NULL);

            //Update screen
            SDL_RenderPresent(gRenderer);

            ++countedFrames;

            //If frame finished early
            int frameTicks = capTimer->getTicks(capTimer);
            if (frameTicks < SCREEN_TICK_PER_FRAME) {
                //Wait remaining time
                SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
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
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    exit(EXIT_SUCCESS);
}


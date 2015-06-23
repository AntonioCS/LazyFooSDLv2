/* 
 * File:   lesson24.c
 * Author: antoniocs
 *
 * Created on 23 de Junho de 2015, 21:40
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
    
    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);

    //Initialize TTF directly here (no external function)
    if (gWindow != NULL && init_sdlimage() && TTF_Init() == 0) {
        bool quit = false;

        //Event handler
        SDL_Event e;

        //Scene textures
        LTexture *gFPSTextTexture = LTexture_Init(gRenderer);

        //Open the font
        TTF_Font *gFont = TTF_OpenFont(resource_path("fonts/lazy.ttf"), 28);

        if (gFont == NULL) {
            printf("Unable to load font - %s\n", TTF_GetError());
            goto terminate;
        }

        //Set text color as black
        SDL_Color textColor = {0, 0, 0, 255};

        //The application timer
        LTimer *fpsTimer = LTimer_Init();

        char timeText[TIMESTRBUFFERSIZE] = {0};

        //Start counting frames per second
        int countedFrames = 0;
        fpsTimer->start(fpsTimer);

        //While application is running
        while (!quit) {
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
                    (SCREEN_WIDTH - gFPSTextTexture->getWidth(gFPSTextTexture) ) / 2,
                    (SCREEN_HEIGHT - gFPSTextTexture->getHeight(gFPSTextTexture) ) / 2,
                    NULL);

            //Update screen
            SDL_RenderPresent(gRenderer);

            ++countedFrames;
            //So its not super cpu intensive
            SDL_Delay(1);
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



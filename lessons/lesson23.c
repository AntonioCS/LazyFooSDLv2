/* 
 * File:   lesson23.c
 * Author: antoniocs
 *
 * Created on 23 de Junho de 2015, 8:24
 */

/*
 * File:   lesson22.c
 * Author: antoniocs
 *
 * Created on 21 de Junho de 2015, 19:30
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> //memset
#include <inttypes.h> //%"PRIu32" -- http://stackoverflow.com/questions/3168275/printf-format-specifiers-for-uint32-t-and-size-t
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

        //Scene textures
        LTexture *gTimeTextTexture = LTexture_Init(gRenderer);
        LTexture *gPromptTextTexture = LTexture_Init(gRenderer);

        //Open the font
        TTF_Font *gFont = TTF_OpenFont(resource_path("fonts/lazy.ttf"), 28);

        if (gFont == NULL) {
            printf("Unable to load font - %s\n", TTF_GetError());
            goto terminate;
        }

        //Set text color as black
        SDL_Color textColor = {0, 0, 0, 255};

        //The application timer
        LTimer *timer = LTimer_Init();

        //Load prompt texture
        if (!gPromptTextTexture->loadFromRenderedText(gPromptTextTexture, "Press S to Start or Stop the Timer", gFont, textColor)) {
            printf("Unable to render prompt texture!\n");
            goto terminate;
        }

        char timeText[TIMESTRBUFFERSIZE] = {0};

        //Event handler
        SDL_Event e;  

        //While application is running
        while (!quit) {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User requests quit ----------- Quit also with ESCAPE key pressed
                if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                    quit = true;
                }//Reset start time on return keypress
                    //Reset start time on return keypress
                else if (e.type == SDL_KEYDOWN) {
                    //Start/stop
                    if (e.key.keysym.sym == SDLK_s) {
                        if (timer->isStarted(timer)) {
                            timer->stop(timer);
                        } else {
                            timer->start(timer);
                        }
                    }                        //Pause/unpause
                    else if (e.key.keysym.sym == SDLK_p) {
                        if (timer->isPaused(timer)) {
                            timer->unpause(timer);
                        } else {
                            timer->pause(timer);
                        }
                    }
                }
            }

            //clear time string
            memset(timeText, 0, TIMESTRBUFFERSIZE);
            //snprintf(timeText, TIMESTRBUFFERSIZE, "Milliseconds since start time %u", (timer->getTicks(timer) / 1000.f));
            snprintf(timeText, TIMESTRBUFFERSIZE, "Milliseconds since start time %u", timer->getTicks(timer) / 1000);

            //Set the time text
            gTimeTextTexture->loadFromRenderedText(gTimeTextTexture, timeText, gFont, textColor);

            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            //Render textures
            gPromptTextTexture->render(gPromptTextTexture,
                    (SCREEN_WIDTH - gPromptTextTexture->getWidth(gPromptTextTexture)) / 2, 0, NULL);
            gTimeTextTexture->render(gTimeTextTexture,
                    (SCREEN_WIDTH - gPromptTextTexture->getWidth(gPromptTextTexture)) / 2,
                    (SCREEN_HEIGHT - gPromptTextTexture->getHeight(gPromptTextTexture)) / 2, NULL);

            //Update screen
            SDL_RenderPresent(gRenderer);

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




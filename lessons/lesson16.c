/* 
 * File:   lesson16.c
 * Author: antoniocs
 *
 * Created on 12 de Junho de 2015, 8:12
 */

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init_renderer.h"
#include "common/init_only_sdlimage.h"
#include "common/resource_path.h"
#include "class/LTexture.class.h"

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

        TTF_Font *gFont = NULL;

        //Rendered texture
        LTexture *gTextTexture = LTexture_Init(gRenderer);

        //Open the font
        gFont = TTF_OpenFont(resource_path("fonts/lesson16/lazy.ttf"), 28);


        if (gTextTexture != NULL && gFont != NULL) {

            SDL_Color textColor = { 0, 0, 0 };
            if( !gTextTexture->loadFromRenderedText(gTextTexture, "The quick brown fox jumps over the lazy dog", gFont, textColor ) ) {
                printf( "Failed to render text texture!\n" );
                goto end; //too many nested ifs
            }

            //int y = 0;

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

                //Render current frame
                gTextTexture->render(
                            gTextTexture,
                            (SCREEN_WIDTH - gTextTexture->getWidth(gTextTexture)) / 2,
                            //(SCREEN_HEIGHT - gTextTexture->getHeight(gTextTexture)) / 2 - (y++ / 4),
                            (SCREEN_HEIGHT - gTextTexture->getHeight(gTextTexture)) / 2,
                            NULL
                );

                //Update screen
                SDL_RenderPresent(gRenderer);

                //So its not super cpu intensive
                SDL_Delay(1);
            }
            //Free font
            TTF_CloseFont(gFont);
            gFont = NULL;
        } else {
            printf("Something went wrong with creating the LTexture or loading the font\n");
        }
    } else {
        printf("Something wrong with the window: %s\n", SDL_GetError());        
    }

    end:
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


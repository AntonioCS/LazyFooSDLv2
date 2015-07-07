/* 
 * File:   lesson27.c
 * Author: antoniocs
 *
 * Created on 2 de Julho de 2015, 8:09
 */

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init_renderer.h"
#include "common/init_only_sdlimage.h"
#include "common/resource_path.h"
#include "class/LTexture.class.h"
#include "class/Dot.class.h"

int main(int argc, char** argv) {
    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);

    if (gWindow != NULL && init_sdlimage()) {
        bool quit = false;

        //Event handler
        SDL_Event e;

        //Scene textures
        LTexture *gDotTexture = LTexture_Init(gRenderer);

        //Load prompt texture
        if (!gDotTexture->loadFromFile(gDotTexture, resource_path("images/dot.bmp"))) {
            printf("Unable to load dot texture!\n");
            goto terminate;
        }

        Dot *dot = Dot_Init(gDotTexture);

        //Set the wall
        SDL_Rect wall;
        wall.x = 300;
        wall.y = 40;
        wall.w = 40;
        wall.h = 400;

        //While application is running
        while (!quit) {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User requests quit ----------- Quit also with ESCAPE key pressed
                if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                    quit = true;
                }
                dot->handleEvent(dot, &e);
            }

            dot->move(dot, &wall);
            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            //Render wall
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderDrawRect(gRenderer, &wall);

            //Render objects
            dot->render(dot);

            //Update screen
            SDL_RenderPresent(gRenderer);

            //So its not super cpu intensive
            //SDL_Delay(1);
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
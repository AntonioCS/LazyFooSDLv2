/* 
 * File:   lesson15.c
 * Author: antoniocs
 *
 * Created on 10 de Junho de 2015, 21:49
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

int main(int argc, char** argv) {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);

    if (gWindow != NULL && init_sdlimage()) {
        bool quit = false;

        //Event handler
        SDL_Event e;

        //Scene texture
        LTexture *gArrowTexture = LTexture_Init(gRenderer);

        if (gArrowTexture == NULL ||
                !gArrowTexture->loadFromFile(gArrowTexture, resource_path("images/lesson15/arrow.png"))) {
            printf("Unable to allocate ltexture or image\n");

        } else {

            //Angle of rotation
            double degrees = 0;

            //Flip type
            SDL_RendererFlip flipType = SDL_FLIP_NONE;

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit ----------- Quit also with ESCAPE key pressed
                    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_a:
                                degrees -= 60;
                                break;

                            case SDLK_d:
                                degrees += 60;
                                break;

                            case SDLK_q:
                                flipType = SDL_FLIP_HORIZONTAL;
                                break;

                            case SDLK_w:
                                flipType = SDL_FLIP_NONE;
                                break;

                            case SDLK_e:
                                flipType = SDL_FLIP_VERTICAL;
                                break;
                        }
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render arrow
                gArrowTexture->renderAngle(gArrowTexture, (SCREEN_WIDTH - gArrowTexture->getWidth(gArrowTexture)) / 2, (SCREEN_HEIGHT - gArrowTexture->getHeight(gArrowTexture)) / 2, NULL, degrees, NULL, flipType);

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



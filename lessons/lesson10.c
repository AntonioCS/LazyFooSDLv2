/* 
 * File:   lesson10.c
 * Author: antoniocs
 *
 * Created on 6 de Junho de 2015, 19:29
 */

#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init_renderer.h"
#include "common/init_only_sdlimage.h"
#include "class/LTexture.class.h"
#include "common/resource_path.h"

int main(int argc, char** argv) {
    //const int SCREEN_WIDTH = 640;
    //const int SCREEN_HEIGHT = 480;

    //SDL_Surface *image = NULL;
    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);


    if (gWindow != NULL && init_sdlimage()) {
        LTexture *gFooTexture = lt_init(gRenderer);
        LTexture *gBackgroundTexture = lt_init(gRenderer);

        if (gFooTexture == NULL || gBackgroundTexture == NULL) {
            printf("Unable to allocate space for LTextures\n");
            exit(EXIT_FAILURE);
        }

        if (gFooTexture->load_from_file(gFooTexture, resource_path("images/lesson10/foo.png")) &&
                gBackgroundTexture->load_from_file(gBackgroundTexture, resource_path("images/lesson10/background.png"))) {

            bool quit = false;
            SDL_Event e;
            int x = 240;
            int y = 190;
            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit ----------- Quit also with ESCAPE key pressed
                    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                        quit = true;
                    }


                    //To handle more than one key: http://stackoverflow.com/questions/1252976/how-to-handle-multiple-keypresses-at-once-with-sdl
                    //SDL_GetKeyboardState kills the program
                    if (e.type == SDL_KEYDOWN) {                        
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                            case SDLK_w:
                                y-= 10;
                                break;

                            case SDLK_DOWN:
                            case SDLK_s:
                                y+= 10;
                                break;

                            case SDLK_LEFT:
                            case SDLK_a:
                                x-= 10;
                                break;

                            case SDLK_RIGHT:
                            case SDLK_d:
                                x+= 10;
                                break;
                        }               
                    }

                    if (x < 0) {
                        x = 0;
                    }

                    if (y < 0) {
                        y = 0;
                    }

                }
/*
                const Uint8 *keystate = SDL_GetKeyboardState(NULL);
                if (keystate[SDLK_UP] || keystate[SDLK_w]) {
                    y -= 10;
                }
                if (keystate[SDLK_DOWN] || keystate[SDLK_s]) {
                    y += 10;
                }
                if (keystate[SDLK_LEFT] || keystate[SDLK_a]) {
                    x -= 10;
                }
                if (keystate[SDLK_RIGHT] || keystate[SDLK_d]) {
                    x += 10;
                }
*/

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render background texture to screen
                gBackgroundTexture->render(gBackgroundTexture, 0, 0);

                //Render Foo' to the screen
                gFooTexture->render(gFooTexture, x, y);

                //Update screen
                SDL_RenderPresent(gRenderer);

                SDL_Delay(1);
            }


            gBackgroundTexture->free(gBackgroundTexture);
            gFooTexture->free(gFooTexture);
        }
    }
    else {
        printf("Something wrong with the window: %s\n", SDL_GetError());
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


#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init_renderer.h"
#include "common/init_only_sdlimage.h"
#include "common/loadmedia_sdlimage.h"
#include "common/loadtexture.h"



bool createAndRenderViewPort(SDL_Renderer *, SDL_Rect *, SDL_Texture *);

int main(int argc, char** argv) {

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Surface *image = NULL;
    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);


    if (gWindow != NULL && init_sdlimage()) {
        image = loadMedia_sdlimage("images/lesson09/viewport.png");

        if (image) {
            SDL_Texture *gTexture = loadTexture(&image, gRenderer);
            if (gTexture) {
                bool quit = false;

                //Event handler
                SDL_Event e;

                //Top left corner viewport
                SDL_Rect topLeftViewport;
                topLeftViewport.x = 0;
                topLeftViewport.y = 0;
                topLeftViewport.w = SCREEN_WIDTH / 2;
                topLeftViewport.h = SCREEN_HEIGHT / 2;

                //Top right viewport
                SDL_Rect topRightViewport;
                topRightViewport.x = SCREEN_WIDTH / 2;
                topRightViewport.y = 0;
                topRightViewport.w = SCREEN_WIDTH / 2;
                topRightViewport.h = SCREEN_HEIGHT / 2;

                //Bottom viewport
                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y = SCREEN_HEIGHT / 2;
                bottomViewport.w = SCREEN_WIDTH;
                bottomViewport.h = SCREEN_HEIGHT / 2;

                //While application is running
                while (!quit) {
                    //Handle events on queue
                    while (SDL_PollEvent(&e) != 0) {
                        //User requests quit
                        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                            quit = true;
                            continue;
                        }

                        //Clear screen
                        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        SDL_RenderClear(gRenderer);

                        //Top left corner viewport                  
                        //SDL_RenderSetViewport(gRenderer, &topLeftViewport);
                        //Render texture to screen
                        //SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                        createAndRenderViewPort(gRenderer, &topLeftViewport, gTexture);


                        //Top right viewport                        
                        //SDL_RenderSetViewport(gRenderer, &topRightViewport);
                        //Render texture to screen
                        //SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                        createAndRenderViewPort(gRenderer, &topRightViewport, gTexture);


                        //Bottom viewport
                        //SDL_RenderSetViewport(gRenderer, &bottomViewport);
                        //Render texture to screen
                        //SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                        createAndRenderViewPort(gRenderer, &bottomViewport, gTexture);

                        //Update screen
                        SDL_RenderPresent(gRenderer);
                    }
                }
            }
        }
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

bool createAndRenderViewPort(SDL_Renderer *gRender, SDL_Rect *rect, SDL_Texture *text) {
    return (SDL_RenderSetViewport(gRender, rect) == 0 && SDL_RenderCopy(gRender, text, NULL, NULL) == 0);
}
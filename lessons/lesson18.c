/*
 * File:   lesson04.c
 * Author: antoniocs
 *
 * Created on 29 de Maio de 2015, 8:04
 */

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init_surface.h"
#include "common/loadmedia.h"
#include "common/close.h"

#define IMAGE_PATH_SIZE 25

static bool load_all_images(SDL_Surface **, char **, int);

int main(int argc, char** argv) {
    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;

    //The image we will load and show on the screen
    //SDL_Surface *gImage = NULL;

    //Current displayed image
    SDL_Surface *gCurrentSurface = NULL;

    //Key press surfaces constants

    enum KeyPressSurfaces {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL //This will always contain the total
    };

    //The images that correspond to a keypress
    SDL_Surface * gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

    char *key_images[KEY_PRESS_SURFACE_TOTAL] = {
        "images/lesson04/press.bmp",
        "images/lesson04/up.bmp",
        "images/lesson04/down.bmp",
        "images/lesson04/left.bmp",
        "images/lesson04/right.bmp"
    };


    gWindow = init_surface(&gScreenSurface);

    if (gWindow) {
        if (load_all_images(gKeyPressSurfaces, key_images, KEY_PRESS_SURFACE_TOTAL)) {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Set default current surface
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }//User presses a key                    
                }

                //------------------------- Lesson 18 specific code!! -------------------------
                //Set texture based on current keystate
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                if (currentKeyStates[ SDL_SCANCODE_UP ]) {
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                } else if (currentKeyStates[ SDL_SCANCODE_DOWN ]) {
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                } else if (currentKeyStates[ SDL_SCANCODE_LEFT ]) {
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                } else if (currentKeyStates[ SDL_SCANCODE_RIGHT ]) {
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                } else {
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                }



                //Apply the current image
                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        } else {
            printf("Unable to load image %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }

    //Free resources and close SDL
    close(&gCurrentSurface, &gWindow);

    return (EXIT_SUCCESS);
}

bool load_all_images(SDL_Surface **sdl_image_list, char **images_path, int total) {
    for (int i = 0; i < total; i++) {
        sdl_image_list[i] = loadMedia(images_path[i]);

        if (sdl_image_list[i] == NULL) {
            return false;
        }
    }

    return true;
}

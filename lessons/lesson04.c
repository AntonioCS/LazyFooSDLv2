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
#include "common/init.h"
#include "common/loadmedia.h"
#include "common/close.h"

#define IMAGE_PATH_SIZE 25

//void load_all_images(SDL_Surface *[]);

int main(int argc, char** argv) {
    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The surface contained by the window
    SDL_Surface *gScreenSurface = NULL;

    //The image we will load and show on the screen
    SDL_Surface *gImage = NULL;

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
    SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

    char key_images[KEY_PRESS_SURFACE_TOTAL][IMAGE_PATH_SIZE] = {
        "images/press.bmp",
        "images/up.bmp",
        "images/down.bmp",
        "images/left.bmp",
        "images/right.bmp"
    };


    gWindow = init(&gScreenSurface);

    if (gWindow) {
        /*
        for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
            gKeyPressSurfaces[i] = loadMedia(key_images[i]);

            if (gKeyPressSurfaces[i] == NULL) {
                printf("Unable to load image at position %d: %s", i, SDL_GetError());
                exit(EXIT_FAILURE);
            }
        }*/
    }

    //Free resources and close SDL
    close(&gImage, &gWindow);

    return (EXIT_SUCCESS);
}


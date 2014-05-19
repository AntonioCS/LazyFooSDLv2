/*
 * File:   main.c
 * Author: AntonioCS
 *
 * Created on 15 de Maio de 2014, 15:16
 */

#include "SDL_Helper.h"

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gXOut = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;
TTF_Font *gFont = NULL;

Uint32 sdl_unused_flags = 0;

int main(int argc, char** argv) {
    //lesson01(); //In this tutorial we will be setting up the SDL library and creating our first window.
    //lesson02(); //Now that we can get a window to appear, let blit an image onto it.
    //lesson03(); //Here's we'll start handling user input by allow the user to X out the window. - Game Loop
    //lesson04(); //Here we'll learn to handle keyboard input.
    //lesson05(); //Optimized Surface Loading and Soft Stretching
    //lesson06(); //Extension Libraries and Loading Other Image Formats
    //lesson07(); //Texture Loading and Rendering
    //lesson08(); //Geometry Rendering
    lesson09(); //The Viewport

    return (EXIT_SUCCESS);
}


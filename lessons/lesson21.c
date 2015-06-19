/* 
 * File:   lesson21.c
 * Author: antoniocs
 *
 * Created on 18 de Junho de 2015, 7:30
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common/init_renderer.h"
#include "common/init_only_sdlimage.h"
#include "common/init_audio.h"
#include "common/resource_path.h"
#include "class/LTexture.class.h"

static bool init_music_vars(Mix_Music **, Mix_Chunk **, Mix_Chunk **, Mix_Chunk **, Mix_Chunk **);

int main(int argc, char** argv) {
   
    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = init_renderer(&gRenderer);

    //The music that will be played
    Mix_Music *gMusic = NULL;

    //The sound effects that will be used
    Mix_Chunk *gScratch = NULL;
    Mix_Chunk *gHigh = NULL;
    Mix_Chunk *gMedium = NULL;
    Mix_Chunk *gLow = NULL;

    if (gWindow != NULL && init_sdlimage() && init_sdlaudio()) {
        bool quit = false;

        //Scene texture
        LTexture *gPromptTexture = LTexture_Init(gRenderer);

        if (gPromptTexture &&
                gPromptTexture->loadFromFile(gPromptTexture, resource_path("images/lesson21/prompt.png"))) {

            if (!init_music_vars(&gMusic, &gScratch, &gHigh, &gMedium, &gLow)) {
                printf("Unable to init sounds\n");
                goto terminate;
            }

            //Event handler
            SDL_Event e;

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit ----------- Quit also with ESCAPE key pressed
                    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                        quit = true;
                    }
                        //Handle key press
                    else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                                //Play high sound effect
                            case SDLK_1:
                                Mix_PlayChannel(-1, gHigh, 0);
                                break;

                                //Play medium sound effect
                            case SDLK_2:
                                Mix_PlayChannel(-1, gMedium, 0);
                                break;

                                //Play low sound effect
                            case SDLK_3:
                                Mix_PlayChannel(-1, gLow, 0);
                                break;

                                //Play scratch sound effect
                            case SDLK_4:
                                Mix_PlayChannel(-1, gScratch, 0);
                                break;

                            case SDLK_9:
                                //If there is no music playing
                                if (Mix_PlayingMusic() == 0) {
                                    //Play the music
                                    Mix_PlayMusic(gMusic, -1);
                                } //If music is being played
                                else {
                                    //If the music is paused
                                    if (Mix_PausedMusic() == 1) {
                                        //Resume the music
                                        Mix_ResumeMusic();
                                    } //If the music is playing
                                    else {
                                        //Pause the music
                                        Mix_PauseMusic();
                                    }
                                }
                                break;

                            case SDLK_0:
                                //Stop the music
                                Mix_HaltMusic();
                                break;
                        }
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                gPromptTexture->render(gPromptTexture, 0, 0, NULL);

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

terminate:
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    exit(EXIT_SUCCESS);
}

bool init_music_vars(Mix_Music **gMusic, Mix_Chunk **gScratch, Mix_Chunk **gHigh, Mix_Chunk **gMedium, Mix_Chunk **gLow) {
    bool success = true;

    //Load music
    *gMusic = Mix_LoadMUS(resource_path("sounds/lesson21/beat.wav"));
    if (*gMusic == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    //Load sound effects
    *gScratch = Mix_LoadWAV(resource_path("sounds/lesson21/scratch.wav"));
    if (*gScratch == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    *gHigh = Mix_LoadWAV(resource_path("sounds/lesson21/high.wav"));
    if (*gHigh == NULL) {
        printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    *gMedium = Mix_LoadWAV(resource_path("sounds/lesson21/medium.wav"));
    if (*gMedium == NULL) {
        printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    *gLow = Mix_LoadWAV(resource_path("sounds/lesson21/low.wav"));
    if (*gLow == NULL) {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}
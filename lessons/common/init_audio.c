#include "init_audio.h"

bool init_sdlaudio(void) {
    bool success = true;

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) == 0) {
        //Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
        }
    }
    else {
        printf( "SDL Audio could not initialize! SDL Error: %s\n", SDL_GetError() );
    }

    return success;
}

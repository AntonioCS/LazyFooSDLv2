#include "loadmedia.h"

SDL_Surface *loadMedia(char *path) {
    char full_path[MAX_PATH] = { 0 };

    strcat(full_path, RESOURCES_PATH);
    strcat(full_path, path);

    printf("Loadmedia fullapth: %s\n", full_path);

    //Load splash image
    return SDL_LoadBMP(full_path);
}
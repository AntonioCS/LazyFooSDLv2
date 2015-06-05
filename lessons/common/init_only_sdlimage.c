#include "init_only_sdlimage.h"

bool init_sdlimage() {
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    return (IMG_Init(imgFlags) & imgFlags);
}
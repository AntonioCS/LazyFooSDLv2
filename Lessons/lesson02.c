#include "../SDL_Helper.h"

void lesson02() {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        //Load media
        if (!loadMedia(resources_path("images/hello_world.bmp"))) {
            printf("Failed to load media!\n");
        }
        else {
            //Apply the image
            SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
            //Update the surface
            SDL_UpdateWindowSurface(gWindow);
            //Wait two seconds
            SDL_Delay(2000);
        }
    }

    //Free resources and close SDL
    close();
}
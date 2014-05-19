#include "../SDL_Helper.h"

void lesson07() {
    //Start up SDL and create window
    if (!init_with_image()) {
        printf("Failed to initialize!\n");
    }
    else {
        //Load media
        if (!loadMediaTexture(resources_path("images/lesson07/texture.png"))) {
            printf("Failed to load media!\n");
        }
        else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                //Clear screen
                SDL_RenderClear(gRenderer);

                //Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                //Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    //Free resources and close SDL
    close();
}
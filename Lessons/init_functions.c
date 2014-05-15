#include "../SDL_Helper.h"
//#include "LTexture.h"
#include <string.h> //MAX_PATH, strcat, memset

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool init_with_image() {
    bool success = true;
    if (init()) {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        //Create renderer for window
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == NULL) {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            //Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
        }

    }

    return success;
}

bool init_with_image_font() {
    bool success = true;
    if (init_with_image()) {
        //Initialize SDL_ttf
        if (TTF_Init() == -1) {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
    }

    return success;
}

bool loadMedia(char *path) {
    //Loading success flag
    bool success = true;

    //Load splash image
    gXOut = SDL_LoadBMP(path);
    if (gXOut == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
        success = false;
    }

    return success;
}

bool loadMediaTexture(char *path) {
    //Loading success flag
    bool success = true;

    //Load texture
    gTexture = loadTexture(path);
    if (gTexture == NULL) {
        printf("Failed to load texture image!\n");
        success = false;
    }

    //Nothing to load
    return success;
}

SDL_Texture *loadTexture(char *path) {
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void close() {
    //Deallocate surface
    if (gXOut != NULL) {
        SDL_FreeSurface(gXOut);
        gXOut = NULL;
    }

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

static void destroy_window() {
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    gWindow = NULL;
    gRenderer = NULL;
}

void closeAlsoImg() {
    destroy_window();

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void closeAlsoImgAndTtf() {
    destroy_window();

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

/*
bool loadmediaFont(ltstruct *textTure, char *font, char *text, SDL_Color *textColor) {
    //Loading success flag
    bool success = true;

    //Open the font
    gFont = TTF_OpenFont(font, 28);
    if (gFont == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    else {
        //Render text
        if (!lt_loadFromRenderedText(textTure, text, *textColor)) {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }

    return success;
}
*/

bool loadLazyFont() {
    bool success = true;
    gFont = TTF_OpenFont(resources_path("fonts/lazy.ttf"), 28);

    if (gFont == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    return success;
}
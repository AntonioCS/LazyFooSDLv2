
#include "LTexture.class.h"

//Private struct

struct p_data {
    //The actual hardware texture
    SDL_Texture *mTexture;

    SDL_Renderer *gRenderer;

    //Image dimensions
    int mWidth;
    int mHeight;
};

static bool loadFromFile(LTexture *, char *);
static void render(LTexture *, int, int, SDL_Rect *);
static int getWidth(LTexture *);
static int getHeight(LTexture *);
static void ltFree(LTexture *);
//Set color modulation
static void setColor(LTexture *, Uint8, Uint8, Uint8);
//Set blending
static void setBlendMode(LTexture *, SDL_BlendMode);
//Set alpha modulation
static void setAlpha(LTexture *, Uint8);

LTexture *LTexture_Init(SDL_Renderer *gRenderer) {
    LTexture *lt_new = malloc(sizeof (LTexture));

    if (lt_new) {
        struct p_data *lt_p_data = malloc(sizeof (struct p_data));

        if (lt_p_data) {
            lt_p_data->mHeight = 0;
            lt_p_data->mWidth = 0;
            lt_p_data->mTexture = NULL;
            lt_p_data->gRenderer = gRenderer;

            lt_new->privateData = lt_p_data;

            lt_new->free = ltFree;
            lt_new->getHeight = getHeight;
            lt_new->getWidth = getWidth;
            lt_new->loadFromFile = loadFromFile;
            lt_new->render = render;

            lt_new->setColor = setColor;

            lt_new->setBlendMode = setBlendMode;
            lt_new->setAlpha = setAlpha;
        } else {
            //printf("Unable to allocate memory for LTexture internal structure\n");
            free(lt_new);
            lt_new = NULL;
        }

    } else {
        //printf("Unable to allocate memory for LTexture\n");
    }

    return lt_new;
}

bool loadFromFile(LTexture *lt, char *path) {
    //Get rid of preexisting texture
    ltFree(lt);
    struct p_data *pd = lt->privateData;

    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        //Color key image (set transparency color)
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(pd->gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        } else {
            //Get image dimensions
            pd->mWidth = loadedSurface->w;
            pd->mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    pd->mTexture = newTexture;
    return (pd->mTexture != NULL);
}

void ltFree(LTexture *lt) {
    struct p_data *pd = lt->privateData;

    //Free texture if it exists
    if (pd->mTexture != NULL) {
        SDL_DestroyTexture(pd->mTexture);
        pd->mTexture = NULL;

        pd->mWidth = 0;
        pd->mHeight = 0;
    }
}

void render(LTexture *lt, int x, int y, SDL_Rect *clip) {
    struct p_data *pd = lt->privateData;

    SDL_Rect renderQuad = {
        .x = x,
        .y = y,
        .w = (clip != NULL ? clip->w : pd->mWidth),
        .h = (clip != NULL ? clip->h : pd->mHeight)
    };


    SDL_RenderCopy(pd->gRenderer, pd->mTexture, clip, &renderQuad);
}

int getWidth(LTexture *lt) {
    struct p_data *pd = lt->privateData;
    return pd->mWidth;
}

int getHeight(LTexture *lt) {
    struct p_data *pd = lt->privateData;
    return pd->mHeight;
}

void setColor(LTexture *lt, Uint8 red, Uint8 green, Uint8 blue) {
    struct p_data *pd = lt->privateData;

    //Modulate texture
    SDL_SetTextureColorMod(pd->mTexture, red, green, blue);
}

//Set blending
void setBlendMode(LTexture *lt, SDL_BlendMode blending) {
    struct p_data *pd = lt->privateData;
    //Set blending function
    SDL_SetTextureBlendMode(pd->mTexture, blending);
}

//Set alpha modulation
void setAlpha(LTexture *lt, Uint8 alpha) {
    struct p_data *pd = lt->privateData;

    SDL_SetTextureAlphaMod(pd->mTexture, alpha);
}
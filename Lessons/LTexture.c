
#include "LTexture.h"

//Private struct
typedef struct {
    //The actual hardware texture
    SDL_Texture *mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
} p_data;

static bool loadFromFile(LTexture *, char *,SDL_Renderer *);
static void render(LTexture *, int, int, SDL_Renderer *);
static int getWidth(LTexture *);
static int getHeight(LTexture *);
static void lt_free(LTexture *);

LTexture *lt_init() {
    LTexture *lt_new = malloc(sizeof (LTexture));

    if (lt_new) {
        p_data *lt_p_data = malloc(sizeof (p_data));

        if (lt_p_data) {
            lt_p_data->mHeight = 0;
            lt_p_data->mWidth = 0;
            lt_p_data->mTexture = NULL;

            lt_new->private_data = lt_p_data;

            lt_new->free = lt_free;
            lt_new->getHeight = getHeight;
            lt_new->getWidth = getWidth;
            lt_new->loadFromFile = loadFromFile;
            lt_new->render = render;
        }
        else {
            printf("Unable to allocate memory for LTexture internal structure\n");
            exit(-1);
        }

    }
    else {
        printf("Unable to allocate memory for LTexture\n");
        exit(-1);
    }
}

bool loadFromFile(LTexture *lt, char *path, SDL_Renderer *gRenderer) {
    //Get rid of preexisting texture
    lt_free(lt);
    p_data *pd = lt->private_data;

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    else {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }
        else {
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

void lt_free(LTexture *lt) {
    p_data *pd = lt->private_data;

    //Free texture if it exists
    if (pd->mTexture != NULL) {
        SDL_DestroyTexture(pd->mTexture);
        pd->mTexture = NULL;

        pd->mWidth = 0;
        pd->mHeight = 0;
    }
}

void render(LTexture *lt,int x, int y, SDL_Renderer *gRenderer) {
    p_data *pd = lt->private_data;

    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, pd->mWidth, pd->mHeight};
    SDL_RenderCopy(gRenderer, pd->mTexture, NULL, &renderQuad);
}


int getWidth(LTexture *lt) {
    p_data *pd = lt->private_data;
    return pd->mWidth;
}

int getHeight(LTexture *lt) {
    p_data *pd = lt->private_data;
    return pd->mHeight;
}
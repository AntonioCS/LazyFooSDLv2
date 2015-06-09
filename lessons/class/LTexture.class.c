
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

static bool load_from_file(LTexture *, char *);
static void render(LTexture *, int, int, SDL_Rect *);
static int get_width(LTexture *);
static int get_height(LTexture *);
static void lt_free(LTexture *);
//Set color modulation
static void set_color(LTexture *, Uint8, Uint8, Uint8);

LTexture *lt_init(SDL_Renderer *gRenderer) {
    LTexture *lt_new = malloc(sizeof (LTexture));

    if (lt_new) {
        struct p_data *lt_p_data = malloc(sizeof (struct p_data));

        if (lt_p_data) {
            lt_p_data->mHeight = 0;
            lt_p_data->mWidth = 0;
            lt_p_data->mTexture = NULL;
            lt_p_data->gRenderer = gRenderer;

            lt_new->private_data = lt_p_data;

            lt_new->free = lt_free;
            lt_new->get_height = get_height;
            lt_new->get_width = get_width;
            lt_new->load_from_file = load_from_file;
            lt_new->render = render;
            lt_new->set_color = set_color;
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

bool load_from_file(LTexture *lt, char *path) {
    //Get rid of preexisting texture
    lt_free(lt);
    struct p_data *pd = lt->private_data;

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

void lt_free(LTexture *lt) {
    struct p_data *pd = lt->private_data;

    //Free texture if it exists
    if (pd->mTexture != NULL) {
        SDL_DestroyTexture(pd->mTexture);
        pd->mTexture = NULL;

        pd->mWidth = 0;
        pd->mHeight = 0;
    }
}

void render(LTexture *lt, int x, int y, SDL_Rect *clip) {
    struct p_data *pd = lt->private_data;

    SDL_Rect renderQuad = {
        .x = x,
        .y = y,
        .w = (clip != NULL ? clip->w : pd->mWidth),
        .h = (clip != NULL ? clip->h : pd->mHeight)
    };


    SDL_RenderCopy(pd->gRenderer, pd->mTexture, clip, &renderQuad);
}

int get_width(LTexture *lt) {
    struct p_data *pd = lt->private_data;
    return pd->mWidth;
}

int get_height(LTexture *lt) {
    struct p_data *pd = lt->private_data;
    return pd->mHeight;
}

void set_color(LTexture *lt, Uint8 red, Uint8 green, Uint8 blue) {
    struct p_data *pd = lt->private_data;
    
    //Modulate texture
    SDL_SetTextureColorMod(pd->mTexture, red, green, blue);
}
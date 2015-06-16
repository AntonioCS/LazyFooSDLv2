#include "LButton.class.h"

enum LButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_OVER_MOTION,
    BUTTON_SPRITE_MOUSE_DOWN,
    BUTTON_SPRITE_MOUSE_UP,

    BUTTON_SPRITE_TOTAL
};

//Private struct

struct privateData {
    //Top left position
    SDL_Point mPosition;
    //Currently used global sprite
    enum LButtonSprite mCurrentSprite;

    LTexture *texture;
    SLD_Rect *gSpriteClips;
};

//Sets top left position
static void setPosition(LButton *, int, int);
//Handles mouse event
static void handleEvent(LButton *, SDL_Event *);
//Shows button sprite
static void render(LButton *);
//Initiate private data struct and assign to given LButton object
static bool initPrivateData(LButton *, LTexture *, SDL_Rect []);
//Attach function to the function pointers in the LButton object
static void hookFunctions(LButton *);

// ------------------------------------------------------------------------
// -------------------- Directly accessed functions -----------------------
// ------------------------------------------------------------------------

LButton *LButton_Init(LTexture *texture, SDL_Rect clips[]) {

    LButton *self = malloc(sizeof (LButton));

    if (self && initPrivateData(self, texture, clips)) {
        hookFunctions(self);
    }

    return self;
}

int LButton_TotalSpriteButtons(void) {
    return BUTTON_SPRITE_TOTAL;
}

// ------------------------------------------------------------------------
// -------------------- Directly accessed functions END -------------------
// ------------------------------------------------------------------------

bool initPrivateData(LButton *self, LTexture *texture, SDL_Rect clips[]) {
    struct privateData *pd = malloc(sizeof (struct privateData));

    if (pd != NULL) {
        pd->mPosition.x = 0;
        pd->mPosition.y = 0;
        pd->mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        pd->texture = texture;
        pd->gSpriteClips = clips;

        self->privateData = pd;
    }

    return (pd != NULL);
}

void hookFunctions(LButton *self) {
    self->handleEvent = handleEvent;
    self->render = render;
    self->setPosition = setPosition;
}

void setPosition(LButton *self, int x, int y) {
    struct privateData *pd = self->privateData;

    pd->mPosition.x = x;
    pd->mPosition.y = y;
}

void handleEvent(LButton *self, SDL_Event *e) {
    struct privateData *pd = self->privateData;

    //If mouse event happened
    if (e->type == SDL_MOUSEMOTION ||
            e->type == SDL_MOUSEBUTTONDOWN ||
            e->type == SDL_MOUSEBUTTONUP) {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in button
        bool inside = true;
        /*
                //Mouse is left of the button
                if (x < mPosition.x) {
                    inside = false;
                }//Mouse is right of the button
                else if (x > mPosition.x + BUTTON_WIDTH) {
                    inside = false;
                }//Mouse above the button
                else if (y < mPosition.y) {
                    inside = false;
                }//Mouse below the button
                else if (y > mPosition.y + BUTTON_HEIGHT) {
                    inside = false;
                }
         */
        if (x < pd->mPosition.x || //Mouse is left of the button
                x > pd->mPosition.x + BUTTON_WIDTH || //Mouse is right of the button
                y < pd->mPosition.y || //Mouse above the button
                y > pd->mPosition.y + BUTTON_HEIGHT) { //Mouse below the button
            inside = false;
        }


        //Mouse is outside button
        if (!inside) {
            pd->mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }//Mouse is inside button
        else {
            //Set mouse over sprite
            switch (e->type) {
                case SDL_MOUSEMOTION:
                    pd->mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    pd->mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;

                case SDL_MOUSEBUTTONUP:
                    pd->mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

void render(LButton *self) {
    struct privateData *pd = self->privateData;

    //Show current button sprite
    pd->texture->render(
        pd->texture,
        pd->mPosition.x,
        pd->mPosition.y,
        pd->gSpriteClips[pd->mCurrentSprite]
    );    
}
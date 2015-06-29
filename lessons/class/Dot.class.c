#include "Dot.class.h"
#include "LTexture.class.h"

#define ASSIGN_FUNCTION(self, function) self->function = function
#define create_pd(self) struct privateData *pd = self->privateData

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

/**
 * Private struct
 */
struct privateData {
    //The dimensions of the dot
    int width; //20;
    int height; //20;

    //Maximum axis velocity of the dot
    int vel; // = 10;

    //The X and Y offsets of the dot
    int mPosX;
    int mPosY;

    //The velocity of the dot
    int mVelX;
    int mVelY;

    LTexture *gDotTexture;
};

// --------------- Setup function prototype ---------------
//Initiate private data struct and assign to given object
static bool initPrivateData(Dot *, LTexture *);
//Attach function to the function pointers
static void hookFunctions(Dot *);
// --------------- Setup function prototype END------------


// ------------------------------------------------------------------------
// -------------------- Public methods prototypes -------------------------
// ------------------------------------------------------------------------

//Takes key presses and adjusts the dot's velocity
static void handleEvent(Dot *, SDL_Event *e);
//Moves the dot
static void move(Dot *);
//Shows the dot on the screen
static void render(Dot *);

// ------------------------------------------------------------------------
// -------------------- Public methods prototypes END ---------------------
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
// -------------------- Directly accessed functions -----------------------
// ------------------------------------------------------------------------

Dot *Dot_Init(LTexture *gDotTexture) {
    Dot *self = malloc(sizeof (Dot));

    if (self && initPrivateData(self, gDotTexture)) {
        hookFunctions(self);
    }

    return self;
}
// ------------------------------------------------------------------------
// -------------------- Directly accessed functions END -------------------
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
// -------------------- Setup functions -----------------------------------
// ------------------------------------------------------------------------

bool initPrivateData(Dot *self, LTexture *gDotTexture) {
    struct privateData *pd = malloc(sizeof (struct privateData));

    if (pd != NULL) {
        pd->height = 20;
        pd->width = 20;

        pd->vel = 10;

        //Initialize the offsets
        pd->mPosX = 0;
        pd->mPosY = 0;

        //Initialize the velocity
        pd->mVelX = 0;
        pd->mVelY = 0;

        pd->gDotTexture = gDotTexture;

        self->privateData = pd;
    }

    return (pd != NULL);
}

void hookFunctions(Dot *self) {
    ASSIGN_FUNCTION(self, handleEvent);
    ASSIGN_FUNCTION(self, move);
    ASSIGN_FUNCTION(self, render);
}

// ------------------------------------------------------------------------
// -------------------- Setup functions END -------------------------------
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// -------------------- Public methods ------------------------------------
// ------------------------------------------------------------------------

void handleEvent(Dot *self, SDL_Event *e) {
    create_pd(self);

    //If a key was pressed
    if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
        //Adjust the velocity
        switch (e->key.keysym.sym) {
            case SDLK_UP: 
                pd->mVelY -= pd->vel;
                break;
            case SDLK_DOWN: 
                pd->mVelY += pd->vel;
                break;
            case SDLK_LEFT: 
                pd->mVelX -= pd->vel;
                break;
            case SDLK_RIGHT: 
                pd->mVelX += pd->vel;
                break;
        }
    }        //If a key was released
    else if (e->type == SDL_KEYUP && e->key.repeat == 0) {
        //Adjust the velocity
        switch (e->key.keysym.sym) {
            case SDLK_UP: 
                pd->mVelY += pd->vel;
                break;
            case SDLK_DOWN: 
                pd->mVelY -= pd->vel;
                break;
            case SDLK_LEFT: 
                pd->mVelX += pd->vel;
                break;
            case SDLK_RIGHT: 
                pd->mVelX -= pd->vel;
                break;
        }
    }
}

void move(Dot *self) {
    create_pd(self);
    
    //Move the dot left or right
    pd->mPosX += pd->mVelX;

    //If the dot went too far to the left or right
    if ((pd->mPosX < 0) || (pd->mPosX + pd->width > SCREEN_WIDTH)) {
        //Move back
        pd->mPosX -= pd->mVelX;
    }

    //Move the dot up or down
    pd->mPosY += pd->mVelY;

    //If the dot went too far up or down
    if ((pd->mPosY < 0) || (pd->mPosY + pd->height > SCREEN_HEIGHT)) {
        //Move back
        pd->mPosY -= pd->mVelY;
    }
}

void render(Dot *self) {
    create_pd(self);
    
    //Show the dot
    pd->gDotTexture->render(pd->gDotTexture, pd->mPosX, pd->mPosY, NULL);
}


// ------------------------------------------------------------------------
// -------------------- Public methods END --------------------------------
// ------------------------------------------------------------------------
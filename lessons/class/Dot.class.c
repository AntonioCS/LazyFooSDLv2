#include "Dot.class.h"
#include "LTexture.class.h"

#define ASSIGN_FUNCTION(self, function) self->function = function
#define create_pd(self) struct privateData *pd = self->privateData

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

//The dimensions of the dot
static const int DOT_WIDTH = 20;
static const int DOT_HEIGHT = 20;

/**
 * Private struct
 */
struct privateData {
    //Maximum axis velocity of the dot
    int vel; // = 10;

    //The X and Y offsets of the dot
    int mPosX;
    int mPosY;

    //The velocity of the dot
    int mVelX;
    int mVelY;

    LTexture *gDotTexture;

    //lesson 27 - Dots collision box
    SDL_Rect mCollider;
};

// --------------- Setup function prototype ---------------
//Initiate private data struct and assign to given object
static bool initPrivateData(Dot *, LTexture *);
//Attach function to the function pointers
static void hookFunctions(Dot *);
// --------------- Setup function prototype END------------


static bool checkCollision(SDL_Rect *, SDL_Rect *);

// ------------------------------------------------------------------------
// -------------------- Public methods prototypes -------------------------
// ------------------------------------------------------------------------

//Takes key presses and adjusts the dot's velocity
static void handleEvent(Dot *, SDL_Event *e);
//Moves the dot
//static void move(Dot *);
//lesson 27
static void move(Dot *, SDL_Rect *);
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
        pd->vel = 10;

        //Initialize the offsets
        pd->mPosX = 0;
        pd->mPosY = 0;

        //Initialize the velocity
        pd->mVelX = 0;
        pd->mVelY = 0;

        pd->gDotTexture = gDotTexture;

        //Set collision box dimension
        //lesson 27
        pd->mCollider.w = DOT_WIDTH;
        pd->mCollider.h = DOT_HEIGHT;

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
    }//If a key was released
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

//void move(Dot *self) {
//lesson 27

void move(Dot *self, SDL_Rect *wall) {
    create_pd(self);

    //Move the dot left or right
    pd->mPosX += pd->mVelX;
    pd->mCollider.x = pd->mPosX;

    //If the dot went too far to the left or right
    if ((pd->mPosX < 0) || (pd->mPosX + DOT_WIDTH > SCREEN_WIDTH) || checkCollision(&(pd->mCollider), wall)) {
        //Move back
        pd->mPosX -= pd->mVelX;
        pd->mCollider.x = pd->mPosX;
    }

    //Move the dot up or down
    pd->mPosY += pd->mVelY;
    pd->mCollider.y = pd->mPosY;

    //If the dot went too far up or down
    if ((pd->mPosY < 0) || (pd->mPosY + DOT_HEIGHT > SCREEN_HEIGHT) || checkCollision(&(pd->mCollider), wall)) {
        //Move back
        pd->mPosY -= pd->mVelY;
        pd->mCollider.y = pd->mPosY;
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

bool checkCollision(SDL_Rect *a, SDL_Rect *b) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a->x;
    rightA = a->x + a->w;
    topA = a->y;
    bottomA = a->y + a->h;

    //Calculate the sides of rect B
    leftB = b->x;
    rightB = b->x + b->w;
    topB = b->y;
    bottomB = b->y + b->h;

    //If any of the sides from A are outside of B    
    if (bottomA <= topB ||
            topA >= bottomB ||
            rightA <= leftB ||
            leftA >= rightB) {
        return false;
    }

    //If none of the sides from A are outside B
    return true;

}

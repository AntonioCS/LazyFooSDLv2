#include "LTimer.class.h"

#define ASSIGN_FUNCTION(self, function) self->function = function
#define create_pd(self) struct privateData *pd = self->privateData

/**
 * Private struct
 */
struct privateData {
    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;

};

// --------------- Setup function prototype ---------------
//Initiate private data struct and assign to given object
static bool initPrivateData(LTimer *);
//Attach function to the function pointers
static void hookFunctions(LTimer *);
// --------------- Setup function prototype END------------


// ------------------------------------------------------------------------
// -------------------- Public methods prototypes -------------------------
// ------------------------------------------------------------------------

//The various clock actions
static void start(LTimer *);
static void stop(LTimer *);
static void pause(LTimer *);
static void unpause(LTimer *);

//Gets the timer's time
static Uint32 getTicks(LTimer *);

//Checks the status of the timer
static bool isStarted(LTimer *);
static bool isPaused(LTimer *);

// ------------------------------------------------------------------------
// -------------------- Public methods prototypes END ---------------------
// ------------------------------------------------------------------------



// ------------------------------------------------------------------------
// -------------------- Directly accessed functions -----------------------
// ------------------------------------------------------------------------

LTimer *LTimer_Init() {

    LTimer *self = malloc(sizeof (LTimer));

    if (self && initPrivateData(self)) {
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

bool initPrivateData(LTimer *self) {
    struct privateData *pd = malloc(sizeof (struct privateData));

    if (pd != NULL) {
        //Initialize the variables
        pd->mStartTicks = 0;
        pd->mPausedTicks = 0;

        pd->mPaused = false;
        pd->mStarted = false;

        self->privateData = pd;
    }

    return (pd != NULL);
}

void hookFunctions(LTimer *self) {
    ASSIGN_FUNCTION(self, start);
    ASSIGN_FUNCTION(self, stop);
    ASSIGN_FUNCTION(self, pause);
    ASSIGN_FUNCTION(self, unpause);
    ASSIGN_FUNCTION(self, getTicks);
    ASSIGN_FUNCTION(self, isStarted);
    ASSIGN_FUNCTION(self, isPaused);
}

// ------------------------------------------------------------------------
// -------------------- Setup functions END -------------------------------
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// -------------------- Public methods ------------------------------------
// ------------------------------------------------------------------------


//The various clock actions

void start(LTimer *self) {
    create_pd(self);

    //Start the timer
    pd->mStarted = true;

    //Unpause the timer
    pd->mPaused = false;

    //Get the current clock time
    pd->mStartTicks = SDL_GetTicks();
    pd->mPausedTicks = 0;
}

void stop(LTimer *self) {
    create_pd(self);

    //Stop the timer
    pd->mStarted = false;

    //Unpause the timer
    pd->mPaused = false;

    //Clear tick variables
    pd->mStartTicks = 0;
    pd->mPausedTicks = 0;
}

void pause(LTimer *self) {
    create_pd(self);

    //If the timer is running and isn't already paused
    if (pd->mStarted && !pd->mPaused) {
        //Pause the timer
        pd->mPaused = true;

        //Calculate the paused ticks
        pd->mPausedTicks = SDL_GetTicks() - pd->mStartTicks;
        pd->mStartTicks = 0;
    }
}

void unpause(LTimer *self) {
    create_pd(self);

    if (pd->mStarted && pd->mPaused) {
        //Unpause the timer
        pd->mPaused = false;

        //Reset the starting ticks
        pd->mStartTicks = SDL_GetTicks() - pd->mPausedTicks;

        //Reset the paused ticks
        pd->mPausedTicks = 0;
    }
}

//Gets the timer's time

Uint32 getTicks(LTimer *self) {
    create_pd(self);

    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if (pd->mStarted) {
        //If the timer is paused
        if (pd->mPaused) {
            //Return the number of ticks when the timer was paused
            time = pd->mPausedTicks;
        } else {
            //Return the current time minus the start time
            time = SDL_GetTicks() - pd->mStartTicks;
        }
    }

    return time;
}

//Checks the status of the timer

bool isStarted(LTimer *self) {
    create_pd(self);

    return pd->mStarted;
}

bool isPaused(LTimer *self) {
    create_pd(self);

    return (pd->mPaused && pd->mStarted);
}

// ------------------------------------------------------------------------
// -------------------- Public methods END --------------------------------
// ------------------------------------------------------------------------
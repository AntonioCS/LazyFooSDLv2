#include "LTimer.class.h"

#define ASSIGN_FUNCTION(self, function) self->function = function

//Private struct
struct privateData {

};

// --------------- Setup function prototype ---------------
//Initiate private data struct and assign to given object
static bool initPrivateData(LTimer *);
//Attach function to the function pointers
static void hookFunctions(LTimer *);
// --------------- Setup function prototype END------------


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
        //Set up code here

        self->privateData = pd;
    }

    return (pd != NULL);
}

void hookFunctions(LTimer *self) {
    //ASSIGN_FUNCTION(self, function);
}

// ------------------------------------------------------------------------
// -------------------- Setup functions END -------------------------------
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// -------------------- Class Functions -----------------------------------
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
// -------------------- Class Functions END -------------------------------
// ------------------------------------------------------------------------
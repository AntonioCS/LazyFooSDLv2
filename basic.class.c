#include "basic.class.h"

#define ASSIGN_FUNCTION(self, function) self->function = function

//Private struct
struct privateData {

};

// --------------- Setup function prototype ---------------
//Initiate private data struct and assign to given object
static bool initPrivateData(CLASSNAME *);
//Attach function to the function pointers
static void hookFunctions(CLASSNAME *);
// --------------- Setup function prototype END------------


// ------------------------------------------------------------------------
// -------------------- Directly accessed functions -----------------------
// ------------------------------------------------------------------------

CLASSNAME *CLASSNAME_Init() {

    CLASSNAME *self = malloc(sizeof (CLASSNAME));

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

bool initPrivateData(CLASSNAME *self) {
    struct privateData *pd = malloc(sizeof (struct privateData));

    if (pd != NULL) {
        //Set up code here

        self->privateData = pd;
    }

    return (pd != NULL);
}

void hookFunctions(CLASSNAME *self) {
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
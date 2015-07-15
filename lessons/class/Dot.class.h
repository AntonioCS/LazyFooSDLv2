#ifndef DOT_CLASS_H
#define	DOT_CLASS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct Dot Dot;

    struct Dot {
        //Example function
        //void (*function)(Dot *);

        //Takes key presses and adjusts the dot's velocity
        void (*handleEvent)(Dot *, SDL_Event *e);

        //Moves the dot
        //void (*move)(Dot *);
        //Lesson 27 - Moves the dot and checks collision
        void (*move)(Dot *, SDL_Rect *);

        //Shows the dot on the screen
        void (*render)(Dot *);

        //lesson 28
        //Return the colliders (per pixel)
        SDL_Rect (*getColliders)(Dot *);


        //Private of struct
        void *privateData;
    };

    Dot *Dot_Init();

#ifdef	__cplusplus
}
#endif

#endif	/* Dot_CLASS_H */


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
        void (*move)(Dot *);

        //Shows the dot on the screen
        void (*render)(Dot *);


        //Private of struct
        void *privateData;
    };

    Dot *Dot_Init();

#ifdef	__cplusplus
}
#endif

#endif	/* Dot_CLASS_H */


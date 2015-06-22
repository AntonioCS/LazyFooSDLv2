#ifndef LTimer_CLASS_H
#define	LTimer_CLASS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct LTimer LTimer;

    struct LTimer {

        //Example function
        //void (*function)(LTimer *);

        //Private of struct
        void *privateData;
    };

    LTimer *LTimer_Init();

#ifdef	__cplusplus
}
#endif

#endif	/* LTimer_CLASS_H */


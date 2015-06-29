#ifndef CLASSNAME_CLASS_H
#define	CLASSNAME_CLASS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct CLASSNAME CLASSNAME;

    struct CLASSNAME {

        //Example function
        //void (*function)(CLASSNAME *);

        //Private of struct
        void *privateData;
    };

    CLASSNAME *CLASSNAME_Init();   

#ifdef	__cplusplus
}
#endif

#endif	/* CLASSNAME_CLASS_H */


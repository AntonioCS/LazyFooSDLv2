/* 
 * File:   LButton.class.h
 * Author: antoniocs
 *
 * Created on 14 de Junho de 2015, 13:28
 */

#ifndef LBUTTON_CLASS_H
#define	LBUTTON_CLASS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LTexture.class.h"


#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct LButton LButton;

    struct LButton {
        //Sets top left position
        void (*setPosition)(LButton *, int , int);

        //Handles mouse event
        void (*handleEvent)(LButton *, SDL_Event *);

        //Shows button sprite
        void (*render)(LButton *);

        void *privateData;
    };

    LButton *LButton_Init(LTexture *, SDL_Rect []);

    int LButton_TotalSpriteButtons(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LBUTTON_CLASS_H */


/* 
 * File:   LTexture.class.h
 * Author: antoniocs
 *
 * Created on 6 de Junho de 2015, 20:19
 */

#ifndef LTEXTURE_CLASS_H
#define	LTEXTURE_CLASS_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct LTexture LTexture;

    //Texture wrapper struct

    struct LTexture {
        //Loads image at specified path
        bool (*loadFromFile)(LTexture *, char *);

        //Deallocates texture
        void (*free)(LTexture *);

        //Renders texture at given point
        void (*render)(LTexture *, int, int, SDL_Rect *);
        //Same as above
        void (*renderAngle)(LTexture *, int , int, SDL_Rect *, double, SDL_Point *, SDL_RendererFlip);

        //Gets image dimensions
        int (*getWidth)(LTexture *);
        int (*getHeight)(LTexture *);

        //Set color modulation
        void (*setColor)(LTexture *, Uint8, Uint8, Uint8);

        //Set blending
        void (*setBlendMode)(LTexture *, SDL_BlendMode);

        //Set alpha modulation
        void (*setAlpha)(LTexture *, Uint8);

        
        //Creates image from font string bool
        bool (*loadFromRenderedText)(LTexture *, char *, TTF_Font *, SDL_Color);
        
        void *privateData;
    };

    LTexture *LTexture_Init(SDL_Renderer *);


#ifdef	__cplusplus
}
#endif

#endif	/* LTEXTURE_CLASS_H */


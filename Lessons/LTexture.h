/*
 * File:   LTexture.h
 * Author: AntonioCS
 *
 * Created on 17 de Maio de 2014, 18:49
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#ifndef LTEXTURE_H
#define	LTEXTURE_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct LTexture LTexture;

    //Texture wrapper struct

    struct LTexture {
        //Loads image at specified path
        bool (*loadFromFile)(LTexture *, char *, SDL_Renderer *);

        //Deallocates texture
        void (*free)(LTexture *);

        //Renders texture at given point
        void (*render)(LTexture *, int, int, SDL_Renderer *);

        //Gets image dimensions
        int (*getWidth)(LTexture *);
        int (*getHeight)(LTexture *);

        void *private_data;
    };

    LTexture *lt_init();

#ifdef	__cplusplus
}
#endif

#endif	/* LTEXTURE_H */


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
        bool (*load_from_file)(LTexture *, char *);

        //Deallocates texture
        void (*free)(LTexture *);

        //Renders texture at given point
        void (*render)(LTexture *, int, int, SDL_Rect *);
        
        //Gets image dimensions
        int (*get_width)(LTexture *);
        int (*get_height)(LTexture *);

        //Set color modulation
        void (*set_color)(LTexture *, Uint8, Uint8, Uint8);

        void *private_data;
    };

    LTexture *lt_init(SDL_Renderer *);


#ifdef	__cplusplus
}
#endif

#endif	/* LTEXTURE_CLASS_H */


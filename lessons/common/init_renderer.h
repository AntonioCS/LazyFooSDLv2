/* 
 * File:   init_renderer.h
 * Author: antoniocs
 *
 * Created on 2 de Junho de 2015, 8:31
 */

#ifndef INIT_RENDERER_H
#define	INIT_RENDERER_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>


#ifdef	__cplusplus
extern "C" {
#endif

    struct renderer_RGBA {
        Uint8  r;
        Uint8  g;
        Uint8  b;
        Uint8  a;
    };

    SDL_Renderer *_init_renderer(SDL_Window *, struct renderer_RGBA *);

#define init_renderer(window, __VA_ARGS__) _init_renderer(window, (struct renderer_RGBA){.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF, __VA_ARGS__});


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_RENDERER_H */


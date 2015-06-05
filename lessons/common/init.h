/* 
 * File:   init.h
 * Author: antoniocs
 *
 * Created on 4 de Junho de 2015, 8:08
 */

#ifndef INIT_H
#define	INIT_H

#include <SDL.h>
#include <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define init(x) _Generic((x), \
    SDL_Renderer *: init_renderer, \
    SDL_Surface **: init_surface, \
    default: init_surface)(x)


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */


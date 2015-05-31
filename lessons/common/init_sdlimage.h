/* 
 * File:   init_sdlimage.h
 * Author: antoniocs
 *
 * Created on 31 de Maio de 2015, 18:21
 */

#ifndef INIT_SDLIMAGE_H
#define	INIT_SDLIMAGE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "init.h"

#ifdef	__cplusplus
extern "C" {
#endif

SDL_Window *init_sdlimage(SDL_Surface **);


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_SDLIMAGE_H */


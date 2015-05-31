/* 
 * File:   optimize_image.h
 * Author: antoniocs
 *
 * Created on 30 de Maio de 2015, 12:57
 */

#ifndef OPTIMIZE_IMAGE_H
#define	OPTIMIZE_IMAGE_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif

SDL_Surface *optimize_image(SDL_Surface *, SDL_Surface *);

#ifdef	__cplusplus
}
#endif

#endif	/* OPTIMIZE_IMAGE_H */


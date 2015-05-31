/* 
 * File:   loadmedia_sdlimage.h
 * Author: antoniocs
 *
 * Created on 31 de Maio de 2015, 18:48
 */

#ifndef LOADMEDIA_SDLIMAGE_H
#define	LOADMEDIA_SDLIMAGE_H

#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include "resource_path.h"

#ifdef	__cplusplus
extern "C" {
#endif

SDL_Surface *loadMedia_sdlimage(char *);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADMEDIA_SDLIMAGE_H */


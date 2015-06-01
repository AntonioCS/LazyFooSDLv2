/* 
 * File:   loadtexture.h
 * Author: antoniocs
 *
 * Created on 01 June 2015, 10:21
 */

#ifndef LOADTEXTURE_H
#define	LOADTEXTURE_H

#include <SDL.h>
#include <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif

SDL_Texture *loadTexture(SDL_Surface **, SDL_Renderer *);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADTEXTURE_H */


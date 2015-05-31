/* 
 * File:   loadmedia.h
 * Author: antoniocs
 *
 * Created on 27 de Maio de 2015, 21:32
 */

#ifndef LOADMEDIA_H
#define	LOADMEDIA_H

#include <SDL.h>
#include <stdio.h>
#include "resource_path.h"

#ifdef	__cplusplus
extern "C" {
#endif

SDL_Surface *loadMedia(char *);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADMEDIA_H */


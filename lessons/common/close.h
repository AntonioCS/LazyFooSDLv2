/* 
 * File:   close.h
 * Author: antoniocs
 *
 * Created on 27 de Maio de 2015, 22:03
 */

#ifndef CLOSE_H
#define	CLOSE_H

#include <SDL.h>
#include <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif

void close(SDL_Surface **gScreenSurface, SDL_Window **gWindow);


#ifdef	__cplusplus
}
#endif

#endif	/* CLOSE_H */


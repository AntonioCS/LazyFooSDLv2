/* 
 * File:   init.h
 * Author: antoniocs
 *
 * Created on 27 de Maio de 2015, 19:49
 */

#ifndef INIT_H
#define	INIT_H
    
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
SDL_Window *init(SDL_Surface **);

#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */


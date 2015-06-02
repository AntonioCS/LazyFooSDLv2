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

    SDL_Renderer *init_renderer(SDL_Window *);


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_RENDERER_H */


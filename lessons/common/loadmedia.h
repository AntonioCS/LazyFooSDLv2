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
#include <string.h> //strcat
#include <stdlib.h> //MAX_PATH

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef MAX_PATH
    #define MAX_PATH 550
#endif

//#define resources_path(file) "C:/Users/antoniocs/Projects/Personal/c/LazyFooSDLv2/resources/"file
#define RESOURCES_PATH "C:/Users/antoniocs/Projects/Personal/c/LazyFooSDLv2/resources/"

SDL_Surface *loadMedia(char *);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADMEDIA_H */


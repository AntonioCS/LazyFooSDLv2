/* 
 * File:   resource_path.h
 * Author: antoniocs
 *
 * Created on 31 de Maio de 2015, 18:29
 */

#ifndef RESOURCE_PATH_H
#define	RESOURCE_PATH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //calloc

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef MAX_PATH
    #define MAX_PATH 550
#endif

#define RESOURCES_FULLPATH "C:/Users/antoniocs/Projects/Personal/c/LazyFooSDLv2/resources/"

    char *resource_path(char *);

#ifdef	__cplusplus
}
#endif

#endif	/* RESOURCE_PATH_H */


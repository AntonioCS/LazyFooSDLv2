/* 
 * File:   init_audio.h
 * Author: antoniocs
 *
 * Created on 19 de Junho de 2015, 8:02
 */

#ifndef INIT_AUDIO_H
#define	INIT_AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

bool init_sdlaudio(void);

#ifdef	__cplusplus
}
#endif

#endif	/* INIT_AUDIO_H */


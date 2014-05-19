/*
 * File:   SDL_Helper.h
 * Author: AntonioCS
 *
 * Created on 15 de Maio de 2014, 15:42
 */

#ifndef SDL_HELPER_H
#define	SDL_HELPER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h> //MAX_PATH
#include <SDL.h>
#include <SDL_image.h> //lesson 06
#include <SDL_ttf.h> //lesson 16
#include <SDL_mixer.h> //lesson 21
//#include "LTexture.h"
//#include "LTimer.h"


#ifdef	__cplusplus
extern "C" {
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#ifndef MAX_PATH
#define MAX_PATH (500)
#endif

#define resources_path(p) "E:/programming/c/SDL2/LazyFooSDLv2/resources/"p

#define TEXT_SIZE 500

//#define eprintf(...) fprintf (stderr, __VA_ARGS__)
#define write_text(to,...) memset(to, 0, TEXT_SIZE); snprintf(to, TEXT_SIZE, __VA_ARGS__);

#define render_middle(texture) lt_render(texture, (SCREEN_WIDTH - lt_getWidth(texture)) / 2, (SCREEN_HEIGHT - lt_getHeight(texture)) / 2);

//The window we'll be rendering to
extern SDL_Window *gWindow;
//The surface contained by the window
extern SDL_Surface *gScreenSurface;
//The image we will load and show on the screen
extern SDL_Surface *gHelloWorld;
extern SDL_Surface *gXOut;//lesson 03
//The window renderer
extern SDL_Renderer* gRenderer;
//Current displayed texture
extern SDL_Texture* gTexture;

extern Uint32 sdl_unused_flags;

//Globally used font
extern TTF_Font *gFont;

//Starts up SDL and creates window
bool init();
//Starts up SDL and SDL_image and creates window
bool init_with_image();

//Starts up SDL, SDL_image SDL_ttf and creates window
bool init_with_image_font();

//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
void closeAlsoImg();
void closeAlsoImgAndTtf();

bool loadMediaTexture(char *);
SDL_Texture *loadTexture(char *);
SDL_Surface* loadOptimizedSurface(char *);

//bool loadmediaFont(ltstruct *,char *,char *,SDL_Color *);

bool loadLazyFont();

void lesson01();
void lesson02();
void lesson03();
void lesson04();
void lesson05();
void lesson06();
void lesson07();
void lesson08();
void lesson09();
void lesson10();
void lesson11();
void lesson12();
void lesson13();
void lesson14();
void lesson15();
void lesson16();
void lesson17();
void lesson18();
void lesson19();
void lesson20();
void lesson21();
void lesson22();
void lesson23();
void lesson24();
void lesson25();
void lesson26();
void lesson27();
void lesson28();
void lesson29();
void lesson30();
void lesson31();
void lesson32();
void lesson33();
void lesson34();
void lesson35();
void lesson36();
void lesson37();
void lesson38();
void lesson39();
void lesson40();
void lesson41();
void lesson42();
void lesson43();
void lesson44();
void lesson45();
void lesson46();
void lesson47();
void lesson48();
void lesson49();
void lesson50();



#ifdef	__cplusplus
}
#endif

#endif	/* SDL_HELPER_H */


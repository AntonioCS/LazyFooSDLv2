SDL_HEADER_DIR=C:/SDL2/SDL2-2.0.3/i686-w64-mingw32/include/SDL2/
SDL_HEADER_DIR_IMAGE=C:/SDL2/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2/

SDL_LINKER_DIR=C:/SDL2/SDL2-2.0.3/i686-w64-mingw32/lib/
SDL_LINKER_DIR_IMAGE=C:/SDL2/SDL2_image-2.0.0/i686-w64-mingw32/lib/

SDL_LINKER_OPTIONS=-lmingw32 -lSDL2main -lSDL2
SDL_LINKER_OPTIONS_IMAGE=-lSDL2_image

SDL_OPTIONS=-I$(SDL_HEADER_DIR) -L$(SDL_LINKER_DIR) $(SDL_LINKER_OPTIONS)
SDL_OPTIONS_IMAGE=-I$(SDL_HEADER_DIR) -I$(SDL_HEADER_DIR_IMAGE) -L$(SDL_LINKER_DIR) -L$(SDL_LINKER_DIR_IMAGE) $(SDL_LINKER_OPTIONS) $(SDL_LINKER_OPTIONS_IMAGE)

CFLAGS=-Wall -g -std=c11
CC=gcc

COMMON=lessons/common/init_surface.c lessons/common/loadmedia.c lessons/common/resource_path.c lessons/common/close.c
COMMON_SDLIMAGE=lessons/common/init_surface.c lessons/common/init_only_sdlimage.c lessons/common/loadmedia_sdlimage.c lessons/common/resource_path.c lessons/common/close.c
COMMON_SDLIMAGE_RENDERER=lessons/common/init_renderer.c lessons/common/init_only_sdlimage.c lessons/common/loadmedia_sdlimage.c lessons/common/resource_path.c

#NOTE!!!!! - The order is important. The .c files must come before the linker flags
#http://stackoverflow.com/questions/11893996/why-does-the-order-of-l-option-in-gcc-matter

#Hello SDL
lesson01: lessons/lesson01.c lessons/common/init_surface.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS) -o bin/$@

#Getting an image on the screen
lesson02: lessons/lesson02.c $(COMMON)
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS) -o bin/$@

#Event driven programming
lesson03: lessons/lesson03.c $(COMMON)
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS) -o bin/$@

#Key presses
lesson04: lessons/lesson04.c $(COMMON)
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS) -o bin/$@

#Optimized surface loading and soft stretching
lesson05: lessons/lesson05.c $(COMMON) lessons/common/optimize_image.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS) -o bin/$@

#Extension libraries and loading other image formats (SDL_Image)
lesson06: lessons/lesson06.c $(COMMON_SDLIMAGE) lessons/common/optimize_image.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS_IMAGE) -o bin/$@

#Texture loading and rendering
lesson07: lessons/lesson07.c $(COMMON_SDLIMAGE) lessons/common/optimize_image.c lessons/common/loadtexture.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS_IMAGE) -o bin/$@

#Geometry rendering
lesson08: lessons/lesson08.c lessons/common/init_renderer.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS_IMAGE) -o bin/$@

#The Viewport
lesson09: lessons/lesson09.c $(COMMON_SDLIMAGE_RENDERER) lessons/common/loadtexture.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS_IMAGE) -o bin/$@

#Color Keying
lesson10: lessons/lesson10.c $(COMMON_SDLIMAGE_RENDERER) lessons/class/LTexture.class.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS_IMAGE) -o bin/$@

#Clip Rendering and Sprite Sheets
lesson11: lessons/lesson11.c $(COMMON_SDLIMAGE_RENDERER) lessons/class/LTexture.class.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS_IMAGE) -o bin/$@

#Color Modulation
lesson12: lessons/lesson12.c $(COMMON_SDLIMAGE_RENDERER) lessons/class/LTexture.class.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS_IMAGE) -o bin/$@




#Animated Sprites and Vsync
lesson14: lessons/lesson14.c $(COMMON_SDLIMAGE_RENDERER) lessons/class/LTexture.class.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS_IMAGE) -o bin/$@
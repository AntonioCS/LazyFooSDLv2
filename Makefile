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

COMMON=lessons/common/init.c lessons/common/loadmedia.c lessons/common/close.c

#NOTE!!!!! - The order is important. The .c files must come before the linker flags
#http://stackoverflow.com/questions/11893996/why-does-the-order-of-l-option-in-gcc-matter

lesson01: lessons/lesson01.c #lessons/common/init.c
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS) -o bin/$@

lesson02: lessons/lesson02.c $(COMMON)
	$(CC) $+ $(CFLAGS) $(SDL_OPTIONS) -o bin/$@
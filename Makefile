SDL_HEADER_DIR=C:/SDL2/SDL2-2.0.3/i686-w64-mingw32/include/SDL2/
SDL_LINKER_DIR=C:/SDL2/SDL2-2.0.3/i686-w64-mingw32/lib/
SDL_LINKER_OPTIONS=-lmingw32 -lSDL2main -lSDL2

CFLAGS=-Wall -g -std=c11 -I$(SDL_HEADER_DIR) -L$(SDL_LINKER_DIR) $(SDL_LINKER_OPTIONS) -o
CC=gcc

#NOTE!!!!! - The order is important. The .c files must come before the linker flags
#http://stackoverflow.com/questions/11893996/why-does-the-order-of-l-option-in-gcc-matter

lesson01: main.c Lessons/lesson01.c
	$(CC) $+ $(CFLAGS) $@

lesson02: Lessons/lesson02.c
	$(CC) $(CFLAGS) $@ $+

lesson03: Lessons/lesson03.c
	$(CC) $(CFLAGS) $@ $+

lesson04: Lessons/lesson04.c
	$(CC) $(CFLAGS) $@ $+

lesson05: Lessons/lesson05.c
	$(CC) $(CFLAGS) $@ $+


CC = gcc

OBJS = main.c logic.c rendering.c

SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_gfx -lSDL2_ttf

OBJ_NAME = play

all: $(OBJS)
	$(CC) $(OBJS) $(SDL_FLAGS) -o build/$(OBJ_NAME)

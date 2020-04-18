#include <stdio.h>
#include <SDL2/SDL.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"

int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Tic Tac Toe",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window, -1, render_flags);

    if (!renderer)
    {
        printf("Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Game game =
    {
        .board = { EMPTY, EMPTY, EMPTY, 
                   EMPTY, EMPTY, EMPTY,
                   EMPTY, EMPTY, EMPTY },
        .state = RUNNING_STATE,
        .player = PLAYER_X
    };

    SDL_Event event;

    while (game.state != QUIT_STATE)
    {
        if (game.state != RUNNING_STATE)
        {
            SDL_Delay(1000);
            reset_game(&game);
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    game.state = QUIT_STATE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    click_on_cell(&game, 
                                  event.button.x / CELL_WIDTH,
                                  event.button.y / CELL_HEIGHT);
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        render_game(renderer, &game);
        SDL_RenderPresent(renderer);

        SDL_Delay(1000/60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

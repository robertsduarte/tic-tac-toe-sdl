#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "game.h"

const SDL_Color grid_color      = { .r = 255, .g = 255, .b = 255 };
const SDL_Color x_color         = { .r = 255, .g = 25,  .b = 25  };
const SDL_Color o_color         = { .r = 50,  .g = 100, .b = 255 };
const SDL_Color tie_color       = { .r = 100, .g = 100, .b = 100 };

void render_grid(SDL_Renderer *renderer, const SDL_Color *color)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    
    for (int i = 1; i < N; i++)
    {
        // vertical line
        SDL_RenderDrawLine(renderer,
                           i * CELL_WIDTH, 0,                   // x1, y1
                           i * CELL_WIDTH, SCREEN_HEIGHT);      // x2, y2
        // horizontal line
        SDL_RenderDrawLine(renderer,
                           0,            i * CELL_HEIGHT,
                           SCREEN_WIDTH, i * CELL_HEIGHT);
    }
}

void render_x(SDL_Renderer *renderer,
              int row, int column,
              const SDL_Color *color)
{
    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;
     
    thickLineRGBA(renderer,
                  center_x - half_box_side, center_y - half_box_side,   // x1, y1
                  center_x + half_box_side, center_y + half_box_side,   // x2, y2
                  10,                                                   // width
                  color->r, color->g, color->b, 255);                   // color

    thickLineRGBA(renderer,
                  center_x - half_box_side, center_y + half_box_side,
                  center_x + half_box_side, center_y - half_box_side,
                  10,
                  color->r, color->g, color->b, 255);
}

void render_o(SDL_Renderer *renderer,
              int row, int column,
              const SDL_Color *color)
{
    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    // outter blue circle
    filledCircleRGBA(renderer,
                     center_x, center_y, half_box_side + 5,     // x, y, radius
                     color->r, color->g, color->b, 255);        // color
    
    // inner black circle
    filledCircleRGBA(renderer,
                     center_x, center_y, half_box_side - 5,
                     0, 0, 0, 255);
}

void render_board(SDL_Renderer *renderer, 
                  const int *board,
                  const SDL_Color *x_color, 
                  const SDL_Color *o_color)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            switch (board[i * N + j])
            {
                case PLAYER_X:
                    render_x(renderer, i, j, x_color);
                    break;
                case PLAYER_O:
                    render_o(renderer, i, j, o_color);
                    break;
            }
        }
    }
}

void render_running_state(SDL_Renderer *renderer, const Game *game)
{
    render_grid(renderer, &grid_color);
    render_board(renderer, game->board, &x_color, &o_color);
}

void render_game_over_state(SDL_Renderer *renderer,
                            const Game *game,
                            const SDL_Color *color)
{
    render_grid(renderer, color);
    render_board(renderer, game->board, color, color);
}

void render_game(SDL_Renderer *renderer, const Game *game)
{
    switch (game->state)
    {
        case RUNNING_STATE:
            render_running_state(renderer, game);
            break;
        case X_WON_STATE:
            render_game_over_state(renderer, game, &x_color);
            break;
        case O_WON_STATE:
            render_game_over_state(renderer, game, &o_color);
            break;
        case TIE_STATE:
            render_game_over_state(renderer, game, &tie_color);
            break;
    }
}

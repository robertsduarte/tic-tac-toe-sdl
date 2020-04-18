#include "game.h"
#include "logic.h"

int check_player_won(Game *game, int player)
{
    int column_count = 0, row_count = 0, main_diag_count = 0, anti_diag_count = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (game->board[j * N + i] == player)
                column_count++;
            if (game->board[i * N + j] == player)
                row_count++;
        }

        if (column_count >= N || row_count >= N)
            return 1;

        column_count = 0; row_count = 0;

        if (game->board[i * N + i] == player)
            main_diag_count++;
        if (game->board[i * N + N - i -1] == player)
            anti_diag_count++;
    }

    return main_diag_count >= N || anti_diag_count >= N;
}

int count_cells(const int *board, int value)
{
    int count = 0;
    
    for (int i = 0; i < N * N; i++)
    {
        if (board[i] == value)
            count++;
    }

    return count;
}

void check_game_over(Game *game)
{
    if (check_player_won(game, PLAYER_X))
        game->state = X_WON_STATE;
    else if (check_player_won(game, PLAYER_O))
        game->state = O_WON_STATE;
    else if (count_cells(game->board, EMPTY) == 0)
        game->state = TIE_STATE;
}

void switch_player(Game *game)
{
    if (game->player == PLAYER_X)
        game->player = PLAYER_O;
    else if (game->player == PLAYER_O)
        game->player = PLAYER_X;
}

void player_turn(Game *game, int column, int row)
{
    if (game->board[column + row * N] == EMPTY)
    {
        game->board[column + row * N] = game->player;
        switch_player(game);
        check_game_over(game);
    }
}

void reset_game(Game *game)
{
    game->player = PLAYER_X;
    game->state = RUNNING_STATE;
    
    for (int i = 0; i < N * N; i++)
        game->board[i] = EMPTY;
}

void click_on_cell(Game *game, int column, int row)
{
    if (game->state == RUNNING_STATE)
        player_turn(game, column, row);
    else
        reset_game(game);
}

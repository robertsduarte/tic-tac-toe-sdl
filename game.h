// screen attributes
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

// game states
#define QUIT_STATE      0
#define RUNNING_STATE   1
#define X_WON_STATE     2
#define O_WON_STATE     3
#define TIE_STATE       4

// total row/column number
#define N               3

// cell attributes
#define CELL_WIDTH      (SCREEN_WIDTH / 3)
#define CELL_HEIGHT     (SCREEN_HEIGHT / 3)

// player/cell value
#define EMPTY           0
#define PLAYER_X        1
#define PLAYER_O        2

typedef struct
{
    int board[N*N];
    int state;
    int player;
} Game;

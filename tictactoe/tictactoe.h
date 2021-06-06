// TICTACTOE.C
// NATHAN CORCORAN 2021

#ifndef CGAME_H
#define CGAME_H

// DATA STRUCTURES ============================================================

// Stores all data regarding current game board state.
typedef struct Board {
    int x, y, **brd;
} Board;

// Stores all data regarding player's desired turn.
typedef struct Turn {
    char x;
    int y, id;
} Turn;

// Stores all data regardinng player.
typedef struct Player {
    int id;
} Player;

// FUNCTION DEFINITIONS =======================================================

// Prints current game board to screen.
void shw_bd(Board *board);

// Prompts player to give desired turn. If turn is illegal,
// prompt player for another turn.
void prmpt_plr(Player *plr, Turn *plrtrn);

// Checks if player's desired turn is legal,
// if legal returns 1, else returns 0.
int chk_trn(Turn *plr_trn);

// Checks if any player has won, given the current game board.
// Returns 1 if true, else returns 0.
int chk_won(Board *board);

// Initialises players' ids.
void setup_plrs(Player *plr1, Player *plr2);

// Initialises the game board and allocates memory apoprorpriately.
void crt_brd(Board *board);

// Updates game board with player's desired move. If turn is not legal
// given game board, prompt player for another turn.
void updt_brd(Board *board, Turn *plr_trn, Player *plr);

// Frees all memory being allocated to game board.
void fr_brd(Board *board);

#endif

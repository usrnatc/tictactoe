// TICTACTOE.C
// NATHAN CORCORAN 2021

// IMPORTS ====================================================================

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tictactoe.h"

// DRIVER FUNCTIONS ===========================================================

int main(int argc, char **argv)
{

    Player plr1;
    Player plr2;
    Board brd;
    crt_brd(&brd);
    setup_plrs(&plr1, &plr2);
    shw_bd(&brd);
    while (1)
    {
        Turn plr_trn;
        prmpt_plr(&plr1, &plr_trn);
        updt_brd(&brd, &plr_trn, &plr1);
        shw_bd(&brd);
        if (chk_won(&brd))
        {
            printf("Player 1 has won.\n");
            break;
        }

        prmpt_plr(&plr2, &plr_trn);
        updt_brd(&brd, &plr_trn, &plr2);
        shw_bd(&brd);
        if (chk_won(&brd))
        {
            printf("Player 2 has won.\n");
            break;
        }
    }

    fr_brd(&brd);
    return 0;
}

// INNIT FUNCTIONS ============================================================

// Initialises the game board and allocates memory apoprorpriately.
void crt_brd(Board *board)
{

    board->x = board->y = 3;
    board->brd = (int **)malloc(sizeof(int *) * board->y);
    for (int i = 0; i < board->y; i++)
    {
        board->brd[i] = (int *)malloc(sizeof(int) * board->x);
    }
    for (int i = 0; i < board->y; i++)
    {
        for (int j = 0; j < board->x; j++)
        {
            board->brd[i][j] = 0;
        }
    }
}

// Initialises players' ids.
void setup_plrs(Player *plr1, Player *plr2)
{

    plr1->id = 1;
    plr2->id = 2;
}

// Updates game board with player's desired move. If turn is not legal
// given game board, prompt player for another turn.
void updt_brd(Board *board, Turn *plr_trn, Player *plr)
{

    int ix = (int)plr_trn->x - 65;
    if (board->brd[plr_trn->y][ix] == 0)
    {
        board->brd[plr_trn->y][ix] = plr_trn->id;
    }
    else
    {
        printf("Bad Guess\n");
        prmpt_plr(plr, plr_trn);
    }
}

// UTILITY FUNCTIONS ==========================================================


// Prompts player to give desired turn. If turn is illegal,
// prompt player for another turn.
void prmpt_plr(Player *plr, Turn *plrtrn)
{

    fflush(stdin);
    int y, xIndex = 0, yIndex = 0;
    char x, line[100];
    printf("Player %d > ", plr->id);
    fgets(line, 100, stdin);
    if (!feof(stdin))
    {
        if (sscanf(line, "%1[A-Z]%n%2d%n", &x, &xIndex, &y,
                   &yIndex) == 2)
        {
            plrtrn->x = x;
            plrtrn->y = y;
            plrtrn->id = plr->id;
            if (!chk_trn(plrtrn))
            {
                printf("Bad Guess - chk_trn error\n");
                prmpt_plr(plr, plrtrn);
            }
        }
        else
        {
            printf("Bad guess - sscanf error\n");
            prmpt_plr(plr, plrtrn);
        }
    }
    else
    {
        fprintf(stderr, "Bad Guess\n");
        exit(-1);
    }
}

// DISPLAY FUNCTIONS ==========================================================

// Prints current game board to screen.
void shw_bd(Board *board)
{

    for (int i = 0; i < board->y; i++)
    {
        for (int j = 0; j < board->x; j++)
        {
            if (board->brd[i][j] == 0)
            {
                if (j == board->x - 1)
                {
                    printf("    ");
                }
                else
                {
                    printf("   |");
                }
            }
            else
            {
                if (j == board->x - 1)
                {
                    printf(" %d  ", board->brd[i][j]);
                }
                else
                {
                    printf(" %d |", board->brd[i][j]);
                }
            }
        }
        if (i == board->y - 1)
        {
            printf("\n");
        }
        else
        {
            printf("\n-----------\n");
        }
    }
}

// ANALYSIS FUNCTIONS =========================================================

// Checks if player's desired turn is legal, if legal returns 1,
// else returns 0.
int chk_trn(Turn *plr_trn)
{

    if ((int)plr_trn->x > 64 && (int)plr_trn->x < 68 &&
        plr_trn->y > -1 && plr_trn->y < 3)
    {
        return 1;
    }
    return 0;
}

// Checks if any player has won, given the current game board.
// Returns 1 if true, else returns 0.
int chk_won(Board *board)
{

    int t = 0;
    // check vertical
    for (int i = 0; i < board->x; i++)
    {
        if (board->brd[0][i] > 0 && board->brd[1][i] > 0 &&
            board->brd[2][i] > 0)
        {
            if (board->brd[0][i] == board->brd[1][i] &&
                board->brd[1][i] == board->brd[2][i])
            {
                t = 1;
                break;
            }
        }
    }
    if (t)
        return t;

    // check horizontal
    for (int i = 0; i < board->y; i++)
    {
        if (board->brd[i][0] > 0 && board->brd[i][1] > 0 &&
            board->brd[i][2] > 0)
        {
            if (board->brd[i][0] == board->brd[i][1] &&
                board->brd[i][1] == board->brd[i][2])
            {
                t = 1;
                break;
            }
        }
    }
    if (t)
        return t;

    // check left diagonal
    if (board->brd[0][0] > 0 && board->brd[1][1] > 0 && board->brd[2][2] > 0)
    {
        if (board->brd[0][0] == board->brd[1][1] &&
            board->brd[1][1] == board->brd[2][2])
        {
            return 1;
        }
    }

    // check right diagonal
    if (board->brd[0][2] > 0 && board->brd[1][1] > 0 && board->brd[2][0] > 0)
    {
        if (board->brd[0][2] == board->brd[1][1] &&
            board->brd[1][1] == board->brd[2][0])
        {
            return 1;
        }
    }
    return 0;
}

// MEMORY FUNCTIONS ===========================================================

// Frees all memory being allocated to game board.
void fr_brd(Board *board)
{

    for (int i = 0; i < board->y; i++)
    {
        free(board->brd[i]);
    }
    free(board->brd);
    board->brd = NULL;
}

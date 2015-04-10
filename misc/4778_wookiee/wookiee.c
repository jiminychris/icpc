#include <stdio.h>

#define X 'X'
#define O 'O'
#define EMPTY '*'

void ctHelper(unsigned int *ct, char mark, char player)
{
    *ct = (mark == player) ? *ct + 1 : 0;
}

char willWin(char board[5][5], char player, unsigned int r, unsigned int c)
{
    board[r][c] = player;
    char flag = 0;
    unsigned int ct1, ct2, ct3, ct4, ct5, ct6, ct7, ct8, i, j;

    ct3 = ct4 = ct5 = ct6 = ct7 = ct8 = 0;
    for (i = 0; i < 5; ++i)
    {
        ct1 = ct2 = 0;
        for (j = 0; j < 5; ++j)
        {
            ctHelper(&ct1, board[i][j], player);
            ctHelper(&ct2, board[j][i], player);
            if (i == j) ctHelper(&ct3, board[i][j], player);
            if (i == j + 1) ctHelper(&ct4, board[i][j], player);
            if (i + 1 == j) ctHelper(&ct5, board[i][j], player);
            if (i + j == 3) ctHelper(&ct6, board[i][j], player);
            if (i + j == 4) ctHelper(&ct7, board[i][j], player);
            if (i + j == 5) ctHelper(&ct8, board[i][j], player);
            /*printf("%u %u %u %u %u\n", ct1, ct2, ct3, ct4, ct5);*/
            flag = ct1 >= 4 || ct2 >= 4 || ct3 >= 4 || ct4 >= 4 
                   || ct5 >= 4 || ct6 >= 4 || ct7 >= 4 || ct8 >= 4;
            if (flag) goto done;
        }
    }
done:
    board[r][c] = EMPTY;
    return flag;
}

int main(int argc, char *argv[])
{
    char board[5][5];
    char iWin, heWins, flag;
    unsigned int i, j;

    scanf(" %c", &board[0][0]);
    while (board[0][0] != 'F')
    {
        for (j = 1; j < 5; ++j)
            scanf(" %c", &board[0][j]);
        for (i = 1; i < 5; ++i)
            for (j = 0; j < 5; ++j)
                scanf(" %c", &board[i][j]);


        /*for (i = 0; i < 5; ++i)
            for (j = 0; j < 5; ++j)
                printf("%c", board[i][j]);*/

        for (i = 0; i < 5; ++i)
        {
            for (j = 0; j < 5; ++j)
            {
                if (board[i][j] != EMPTY) continue;
                board[i][j] = O;
                flag = !willWin(board, O, i, j) && !willWin(board, X, i, j);
                if (flag) goto print;
            }
        }

print:
        printf("%u\n", i * 5 + j + 1);

        scanf(" %c", &board[0][0]);
    }

    return 0;
}
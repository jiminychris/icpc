#include <stdio.h>

int main(int argc, char *argv[])
{
    int r, c;
    char board[100][100];
    int i, j;
    int x, y;
    int ct;

    scanf("%d %d\n", &r, &c);
    while (r != 0)
    {
        for (j=0; j<r; j++)
        {
            for (i=0; i<c; i++)
            {
                scanf("%c", &(board[j][i]));
            }
            scanf("\n");
        }

        for (j=0; j<r; j++)
        {
            for (i=0; i<c; i++)
            {
                if (board[j][i] == '.')
                {
                    ct = 0;
                    for (y=j-1; y<=j+1; y++)
                        for (x=i-1; x<=i+1; x++)
                        {
                            ct += (!(x == i && y == j) && x >= 0 && x < c && y >= 0 && y < r && board[y][x] == '*');
                        }
                    printf("%c", '0'+ct);
                }
                else
                    printf("%c", board[j][i]);
            }
            printf("\n");
        }
        scanf("%d %d\n", &r, &c);
    }

    return 0;
}
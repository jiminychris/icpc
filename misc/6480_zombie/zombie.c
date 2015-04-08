#include <stdio.h>

int main(int argc, char *argv[])
{
    int i, j, n;
    int villages[20];

    scanf("%d", &n);

    for (j = 0; j < n; j++)
    {
        for (i = 0; i < 20; ++i)
            scanf("%d", &villages[i]);
        for (i = 19; i > 0; --i)
        {
            villages[i - 1] += villages[i] / 2;
            villages[i] %= 2;
        }
        printf("%d", villages[0]);
        for (i = 1; i < 20; ++i)
            printf(" %d", villages[i]);
        printf("\n");
    }

    return 0;
}
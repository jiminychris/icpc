#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned int n, m, k, sum;
    unsigned int i, j;
    int pattern[100];

    scanf("%u %u %u", &n, &m, &k);
    while (n != 0)
    {
        sum = 0;
        for (i=0; i<k; i++)
            scanf("%d", &pattern[i]);
        j = 0;
        for (i=0; i<m; i++)
        {
            sum += n;
            n += pattern[j];
            j += 1;
            if (j == k) j = 0;
        }
        printf("%u\n", sum);
        scanf("%u %u %u", &n, &m, &k);
    }

    return 0;
}
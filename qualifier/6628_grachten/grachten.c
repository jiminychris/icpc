#include <stdio.h>

long unsigned int gcd(long unsigned int a, long unsigned int b)
{
    while (a != b)
    {
        if (a > b) a = a - b;
        else b = b - a;
    }
    return a;
}

int main(int argc, char *argv[])
{
    long unsigned int a, b, c;
    long unsigned int n, d, f;

    scanf("%lu %lu %lu", &a, &b, &c);
    while (!feof(stdin))
    {
        n = a * b;
        d = c - b;
        f = gcd(n, d);
        printf("%lu/%lu\n", n/f, d/f);

        scanf("%lu %lu %lu", &a, &b, &c);
    }

    return 0;
}
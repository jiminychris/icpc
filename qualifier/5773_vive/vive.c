#include <stdio.h>

unsigned long int abs(signed long int x)
{
    return x < 0 ? -x : x;
}

int main(int argc, char *argv[])
{
    unsigned long int a, b, c, d, temp;
    unsigned int i;

    scanf("%lu %lu %lu %lu", &a, &b, &c, &d);
    while (a != 0)
    {
        i = 0;
        while (!(a == b && b == c && c == d))
        {
            i += 1;
            temp = a;
            a = abs(a-b);
            b = abs(b-c);
            c = abs(c-d);
            d = abs(d-temp);
        }
        printf("%u\n", i);
    
        scanf("%lu %lu %lu %lu", &a, &b, &c, &d);
    }

    return 0;
}
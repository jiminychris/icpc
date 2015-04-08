#include <cstdio>
#include <cstdint>
#include <cinttypes>
#include <cmath>
#include <cassert>

uint64_t gcd(uint64_t a, uint64_t b)
{
    if (b == 0) return a;
    return gcd(b, a%b);
}

uint64_t combination(uint64_t a, uint64_t b)
{
    uint64_t prod = 1;
    uint64_t i;
    uint64_t g;
    uint64_t c = b < a-b ? b : a-b;
    uint64_t d = b > a-b ? b : a-b;

    uint64_t cacc = 1;
    for (i=a; i>d; i--)
    {
        cacc *= c;
        c -= 1;
        g = prod;
        prod *= i;
        assert(g < prod);
        g = gcd(cacc, prod);
        assert(g != 0);
        prod /= g;
        cacc /= g;
    }

    for (i=2; i<=c; i++)
        prod /= i;
    assert(cacc != 0);
    return prod/cacc;
}

int main(int argc, char *argv[])
{
    uint64_t n;
    uint64_t r;
    unsigned int max;
    signed int i;
    char found;
    uint64_t sum;
    unsigned int p, highBits;

    const uint64_t one = 1;

    scanf("%" SCNu64, &n);
    while (!feof(stdin))
    //for (n=0; n<1000; n++)
    {
        sum = 0;
        r = n;
        i = 64;
        found = 0;
        while (!found && --i >= 0)
        {
            found = (r & (one << i)) > 0;
        }
        max = i;
        highBits = 0;
        p = 3;
        while (r > 0)
        {
            while (p <= max)
            {
                sum += combination(max, p);
                p += 3;
            }
            r &= ~(one << max);

            i = 64;
            found = 0;
            while (!found && --i >= 0)
                found = (r & (one << i)) > 0;
            max = i;
            p = 2-highBits%3;
            highBits += 1;
            if (r == 0 && p == 0 && max > 0) sum += 1; 
        }

        printf("Day %" SCNu64 ": Level = %" SCNu64 "\n", n, sum);
        scanf("%" SCNu64, &n);
    }

    return 0;
}
#include <stdio.h>
#include <math.h>
#include <assert.h>

struct point
{
    float x;
    float y;
    float z;
};

double distance(struct point *a, struct point *b)
{
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + pow(a->z - b->z, 2));
}

int main(int argc, char *argv[])
{
    long unsigned int n, i, j, ct;
    double k;
    struct point points[100000];

    scanf("%d %lf", &n, &k);
    while (n != 0)
    {
        ct = 0;
        for (i=0; i<n; i++)
        {
            scanf("%f %f %f", &points[i].x, &points[i].y, &points[i].z);
            for (j=0; j<i; j++)
                if (distance(&points[i], &points[j]) < k) ct += 1;
        }
        printf("%ld\n", ct);
        scanf("%d %lf", &n, &k);
    }

    return 0;
}
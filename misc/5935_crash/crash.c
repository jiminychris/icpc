#include <stdio.h>
#include <math.h>

typedef struct gorelian {
    double x;
    double y;
    double r;
} Gorelian;

void gorelian_print(Gorelian *g)
{
    printf("%lf %lf %lf", g->x, g->y, g->r);
}

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main(int argc, char *argv[])
{
    Gorelian gorelians[100];
    int n, i, j, ct, merged;
    double xsum, ysum;
    double areasum;
    double dist;

    scanf("%d", &n);
    while (n != 0)
    {
        ct = 0;
        for (i = 0; i < n; ++i)
        {
            scanf("%lf", &gorelians[ct].x);
            scanf("%lf", &gorelians[ct].y);
            scanf("%lf", &gorelians[ct].r);

            /* gorelian_print(&gorelians[ct]);
            printf(" landed\n"); */

            do
            {
                xsum = gorelians[ct].x;
                ysum = gorelians[ct].y;
                areasum = pow(gorelians[ct].r, 2);
                j = 0;
                merged = 1;
                while (j < ct)
                {
                    dist = distance(gorelians[ct].x, gorelians[ct].y, gorelians[j].x, gorelians[j].y);
                    if (dist <= gorelians[ct].r || dist <= gorelians[j].r)
                    {
                        /*printf(merged == 1 ? "Merging with " : "and ");
                        gorelian_print(&gorelians[j]);
                        printf("\n");*/
                        xsum += gorelians[j].x;
                        ysum += gorelians[j].y;
                        areasum += pow(gorelians[j].r, 2);

                        gorelians[j] = gorelians[ct - 1];
                        gorelians[ct - 1] = gorelians[ct];
                        ct -= 1;
                        merged += 1;
                    }
                    else
                    {
                        ++j;
                    }
                }

                gorelians[ct].x = xsum / merged;
                gorelians[ct].y = ysum / merged;
                gorelians[ct].r = sqrt(areasum);
            }
            while (merged > 1);

            ct += 1;
        }

        printf("%d\n", ct);
        scanf("%d", &n);
    }
}

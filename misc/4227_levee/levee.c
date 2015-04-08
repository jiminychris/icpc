#include <math.h>
#include <stdio.h>

struct triangle
{
    double area;
    double perimeter;
};

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

double dot(double x0, double y0, double x1, double y1, double x2, double y2)
{
    return (x1-x0)*(x2-x0) + (y1-y0)*(y2-y0);
}

int main(int argc, char *argv[])
{
    double x1, y1, x2, y2, x3, y3, x4, y4;
    double x0, y0;
    double m1, m2;
    double b1, b2;
    double d1, d2, d3, d4;
    double dot1, dot2, dot3, dot4;
    double p1, p2, p3, p4;
    double h1, h2, h3, h4;
    struct triangle t[4];
    struct triangle temp;

    int i, j;

    scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
    while (!(x1 == 0.0 && y1 == 0.0 && x2 == 0.0 && y2 == 0.0 && x3 == 0.0 && y3 == 0.0 && x4 == 0.0 && y4 == 0.0))
    {
        b1 = b2 = -1;
        if (x1 == x3)
        {
            m2 = (x2 == x4) ? -1 : (y2-y4) / (x2-x4);
            b2 = y2 - m2*x2;
            x0 = x1;
            y0 = m2*x0 + b2;
        }
        else if (x2 == x4)
        {
            m1 = (x1 == x3) ? -1 : (y1-y3) / (x1-x3);
            b1 = y1 - m1*x1;
            x0 = x2;
            y0 = m1*x0 + b1;
        }
        else
        {
            m1 = (x1 == x3) ? -1 : (y1-y3) / (x1-x3);
            m2 = (x2 == x4) ? -1 : (y2-y4) / (x2-x4);
            b1 = y1 - m1*x1;
            b2 = y2 - m2*x2;
            x0 = (b2-b1)/(m1-m2);
            y0 = m1*x0 + b1;
        }

        d1 = distance(x1, y1, x2, y2);
        dot1 = dot(x2, y2, x1, y1, x0, y0);
        p1 = dot1/pow(d1, 2);
        h1 = distance(x0, y0, x2+(x1-x2)*p1, y2+(y1-y2)*p1);
        t[0].area = h1*d1/2;
        t[0].perimeter = d1 + distance(x1, y1, x0, y0) + distance(x2, y2, x0, y0);

        d2 = distance(x2, y2, x3, y3);
        dot2 = dot(x3, y3, x2, y2, x0, y0);
        p2 = dot2/pow(d2, 2);
        h2 = distance(x0, y0, x3+(x2-x3)*p2, y3+(y2-y3)*p2);
        t[1].area = h2*d2/2;
        t[1].perimeter = d2 + distance(x2, y2, x0, y0) + distance(x3, y3, x0, y0);

        d3 = distance(x3, y3, x4, y4);
        dot3 = dot(x4, y4, x3, y3, x0, y0);
        p3 = dot3/pow(d3, 2);
        h3 = distance(x0, y0, x4+(x3-x4)*p3, y4+(y3-y4)*p3);
        t[2].area = h3*d3/2;
        t[2].perimeter = d3 + distance(x3, y3, x0, y0) + distance(x4, y4, x0, y0);

        d4 = distance(x4, y4, x1, y1);
        dot4 = dot(x1, y1, x4, y4, x0, y0);
        p4 = dot4/pow(d4, 2);
        h4 = distance(x0, y0, x1+(x4-x1)*p4, y1+(y4-y1)*p4);
        t[3].area = h4*d4/2;
        t[3].perimeter = d4 + distance(x4, y4, x0, y0) + distance(x1, y1, x0, y0);

        /*printf("%lf %lf %lf %lf\n", d1, d2, d3, d4);
        printf("%lf %lf %lf %lf\n", dot1, dot2, dot3, dot4);
        printf("%lf %lf %lf %lf\n", p1, p2, p3, p4);
        printf("%lf %lf %lf %lf\n", h1, h2, h3, h4);
        printf("%lf %lf %lf %lf\n", t[0].area, t[1].area, t[2].area, t[3].area);*/

        for (i=0; i<4; i++)
        {
            t[i].area = floor(t[i].area * 1000 + .5) / 1000;
            t[i].perimeter = floor(t[i].perimeter * 1000 + .5) / 1000;
        }

        for (j=0; j<3; j++)
            for (i=j; i<4; i++)
                if ((t[i].area > t[j].area) || (t[i].area == t[j].area && t[i].perimeter > t[j].perimeter))
                {
                    temp.area = t[j].area;
                    temp.perimeter = t[j].perimeter;
                    t[j].area = t[i].area;
                    t[j].perimeter = t[i].perimeter;
                    t[i].area = temp.area;
                    t[i].perimeter = temp.perimeter;
                }

        printf("%.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf\n",
            t[0].area, t[0].perimeter, t[1].area, t[1].perimeter,
            t[2].area, t[2].perimeter, t[3].area, t[3].perimeter);


        scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
    }

    
    return 0;
}
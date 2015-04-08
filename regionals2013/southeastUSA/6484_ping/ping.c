#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char intervals[1001];
    int i, j, len;
    char isFirst;

    scanf("%s", intervals);
    len = strlen(intervals);
    while (intervals[1] != '\0')
    {
        isFirst = 1;
        for (i=1; i<len; i++)
            if (intervals[i] == '1')
            {
                if (isFirst)
                {
                    printf("%d", i);
                    isFirst = 0;
                } 
                else printf(" %d", i);
                for (j=i+i; j<len; j+=i)
                    intervals[j] = intervals[j] == '0' ? '1' : '0';
            }
        printf("\n");
        scanf("%s", intervals);
        len = strlen(intervals);
    }

    return 0;
}
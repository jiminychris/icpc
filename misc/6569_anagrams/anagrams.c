#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char first[1024];
    char second[1024];
    int counts[26];
    int i;
    unsigned int j;
    char flag;

    /* init case counter and scan first pair of strings */
    j = 1;
    gets(first);
    gets(second);

    /* expecting lowercase strings. Any END means we're done. */
    while (first[0] != 'E')
    {
        flag = 0;
        if (strlen(first) == strlen(second))
        {
            /* reset character counts */
            for (i = 0; i < 26; ++i) counts[i] = 0;

            /* count each character in first string */
            i = 0;
            while (first[i] != '\0') counts[first[i++]-'a'] += 1;

            /* un-count each character in second string */
            i = 0;
            while (second[i] != '\0') counts[second[i++]-'a'] -= 1;

            /* check for any non-zero character counts */
            for (i = 0; i < 26; ++i) 
            {
                if (counts[i] != 0)
                {
                    flag = 1;
                    break;
                }
            }
        }
        else
        {
            flag = 1;
        }

        /* if flag, then character counts were off => different strings */
        printf("Case %lu: %s\n", j, flag ? "different" : "same");

        /* increment case counter and scan next pair of strings */
        j += 1;
        gets(first);
        gets(second);
    }

    return 0;
}
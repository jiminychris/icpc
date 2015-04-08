#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    unsigned int t, e, i, j, k, l;
    char f[9], a1, a2[103];
    char visibility[26][26];
    char received[26];
    char messages[26][50][103];
    unsigned messageCount[26];
    char sent;

    scanf("%u", &t);
    for (i = 0; i < t; ++i)
    {
        for (j = 0; j < 26; ++j)
            for (k = 0; k < 26; ++k) 
                visibility[j][k] = 0;
        for (j = 0; j < 26; ++j)
            messageCount[j] = 0;

        scanf("%u", &e);
        for (j = 0; j < e; ++j)
        {
            scanf("%s %c %s", f, &a1, a2);
            a1 -= 'A';
            if (f[0] == 'V')
            {
                visibility[a1][a2[0]-'A'] = visibility[a2[0]-'A'][a1] = 1;
            }
            else if (f[0] == 'O' || f[0] == 'W')
            {
                visibility[a1][a2[0]-'A'] = visibility[a2[0]-'A'][a1] = 0;
            }
            else
            {
                for (k = 0; k < 26; ++k)
                    received[k] = 0;
                received[a1] = 1;
                sent = 0;
                do
                {
                    for (k = 0; k < 26; ++k)
                    {
                        for (l = 0; l < 26; ++l)
                        {
                            if (received[k] && !received[l] && visibility[l][k])
                            {
                                received[l] = 1;
                                strncpy(messages[l][messageCount[l]++], a2, 103);
                                sent = 1;
                            }
                        }
                    }
                } while (sent);
            }
        }

        if (i > 0) printf("\n");
        for (j = 0; j < 26; ++j)
        {
            if (messageCount[j] > 0)
            {
                printf("%c: [%s", j+'A', messages[j][0]);
                for (k = 0; k < messageCount[j]; ++k)
                {
                    printf(", %s", messages[j][k]);
                }
                printf("]\n");
            }
        }
    }

    return 0;
}
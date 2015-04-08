#include <stdio.h>

char lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a'-'A');
    return c;
}

int main (int argc, char *argv[])
{
    char vowels[6] = { 'a', 'i', 'y', 'e', 'o', 'u' };
    char consonants[20] = { 'b', 'k', 'x', 'z', 'n', 'h', 'd', 'c', 'w', 'g', 'p', 'v', 'j', 'q', 't', 's', 'r', 'l', 'm', 'f' };
    int i, j;
    char ch;

    char str[101];

    scanf("%c", &ch);
    while (!feof(stdin))
    {
        i=0;
        while (ch != '\n')
        {
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
            {
                for (j=0; j<6; j++)
                    if (vowels[j] == lower(ch))
                        str[i] = vowels[(j+3)%6] - (vowels[j] - ch);
                for (j=0; j<20; j++)
                    if (consonants[j] == lower(ch))
                        str[i] = consonants[(j+10)%20] - (consonants[j] - ch);
            }
            else
                str[i] = ch;

            i += 1;
            scanf("%c", &ch);
        }

        str[i] = '\0';
        printf("%s\n", str);
        scanf("%c", &ch);
    }

    return 0;
}

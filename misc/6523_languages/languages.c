#include <stdio.h>
#include <assert.h>
#include <string.h>

struct language
{
    char name[257];
    char words[257][267];
    int numWords;
};

void lower(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 'a' - 'A';
        i += 1;
    }
}

int main(int argc, char *argv[])
{
    struct language languages[100];
    int numLanguages;
    int i, j, k, letter;
    char c;
    char buf[257];

    scanf("%d", &numLanguages);

    for (i=0; i<numLanguages; i++)
    {
        scanf("%s", languages[i].name);
        c = ' ';
        while (c != '\n')
        {
            letter = 0;
            while (c == ' ') c = getchar();
            while (c != ' ' && c != '\n')
            {
                languages[i].words[languages[i].numWords][letter] = c;
                letter += 1;
                c = getchar();
            }
            languages[i].words[languages[i].numWords][letter] = '\0';
            lower(languages[i].words[languages[i].numWords]);
            languages[i].numWords += 1;
        }
    }

    while (!feof(stdin))
    {
        while (c == ' ' || c == '\n' || c == ',' || c == '.' || c == '!' || c == ';' || c == '?' || c == '(' || c == ')')
            c = getchar();
        while (c != '\n')
        {
            i = 0;
            while (!(c == ' ' || c == '\n' || c == ',' || c == '.' || c == '!' || c == ';' || c == '?' || c == '(' || c == ')'))
            {
                buf[i++] = c;
                c = getchar();
            }
            buf[i] = '\0';
            for (j=0; j<numLanguages; j++)
            {
                for (k=0; k<languages[j].numWords; k++)
                {
                    lower(buf);
                    if (strcmp(languages[j].words[k], buf) == 0)
                    {
                        printf("%s\n", languages[j].name);
                        while (c != '\n')
                            c = getchar();
                        
                        if ((c = getchar()) == EOF)
                            goto done;
                    }
                }
            }
            while (c == ' ' || c == ',' || c == '.' || c == '!' || c == ';' || c == '?' || c == '(' || c == ')')
                c = getchar();
        }
    }
    done: ;

    return 0;
}
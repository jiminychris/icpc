#include <stdio.h>

void increment(int seq[], int length)
{
    int overflow = 1;
    int i = length - 1;
    while (overflow && i >= 0)
    {
        if ((seq[i] += 1) > 9)
            seq[i] = 0;
        else
            overflow = 0;
        i--;
    }
}

int isPalindrome(int seq[], int length)
{
    int i = 0;
    for (i=0; i<length/2; i++)
        if (seq[i] != seq[length-1-i]) return 0;
    return 1;
}

int findNext(int seq[], int length)
{
    int i = 0;
    while (!isPalindrome(seq, length) && ++i)
        increment(seq, length);
    return i;
}

int main(int argc, char *argv[])
{
    int seq[9];
    char str[9];
    int i = 0;

    scanf("%s", str);
    while (!(str[0] == '0' && str[1] == '\0'))
    {
        i = -1;
        while (str[++i] != '\0')
            seq[i] = str[i] - '0';

        printf("%d\n", findNext(seq, i));

        scanf("%s", str);
    }
    return 0;
}

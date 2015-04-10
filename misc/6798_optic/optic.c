#include <stdio.h>
#include <string.h>

#define GRAPH_SIZE 26

int reach(char graph[GRAPH_SIZE][GRAPH_SIZE], char start, unsigned int nri,
          char reached[], unsigned int *numReached,
          char notReached[], unsigned int *numNotReached)
{
    int i, ct;
    char end;

    reached[(*numReached)++] = start;
    notReached[nri] = notReached[--(*numNotReached)];
    ct = i = 0;
    while (i < *numNotReached)
    {
        end = notReached[i];
        if (graph[start][end])
        {
            ct += 1;
            ct += reach(graph, end, i, reached, numReached,
                notReached, numNotReached);
        }
        else
        {
            i += 1;
        }
    }
    return ct;
}

int main(int argc, char *argv[])
{
    unsigned int t, e, i, j, k, l;
    char f[9], a1, a2;
    char visibility[GRAPH_SIZE][GRAPH_SIZE];
    char messageStore[50][103];
    unsigned int msc;
    char *messages[GRAPH_SIZE][50];
    unsigned int messageCount[GRAPH_SIZE];
    char receivers[GRAPH_SIZE];
    unsigned int receiverCount;
    char nonReceivers[GRAPH_SIZE];
    unsigned int nonReceiverCount;
    char sent;

    scanf("%u", &t);
    for (i = 0; i < t; ++i)
    {
        for (j = 0; j < GRAPH_SIZE; ++j)
            for (k = 0; k < GRAPH_SIZE; ++k) 
                visibility[j][k] = 0;
        for (j = 0; j < GRAPH_SIZE; ++j)
            messageCount[j] = 0;
        msc = 0;

        scanf("%u", &e);
        for (j = 0; j < e; ++j)
        {
            scanf("%s %c %c", f, &a1, &a2);
            a1 -= 'A';
            a2 -= 'A';
            if (f[0] == 'V')
            {
                visibility[a1][a2] = visibility[a2][a1] = 1;
            }
            else if (f[0] == 'O' || f[0] == 'W')
            {
                visibility[a1][a2] = visibility[a2][a1] = 0;
            }
            else /* MESSAGE */
            {
                messageStore[msc][0] = a2 + 'A';
                k = 1;
                do
                    messageStore[msc][k] = getchar();
                while (messageStore[msc][k++] != '"');
                messageStore[msc][k] = '\0';

                for (k = 0; k < GRAPH_SIZE; ++k)
                {
                    receivers[k] = 0;
                    nonReceivers[k] = k;
                }
                receiverCount = 0;
                nonReceiverCount = 26;

                reach(visibility, a1, a1, receivers, &receiverCount, 
                    nonReceivers, &nonReceiverCount);
                for (k = 1; k < receiverCount; ++k)
                    messages[receivers[k]][messageCount[receivers[k]]++] = messageStore[msc];
                msc += 1;
            }
        }

        if (i > 0) printf("\n");
        for (j = 0; j < GRAPH_SIZE; ++j)
        {
            if (messageCount[j] > 0)
            {
                printf("%c: [%s", j+'A', messages[j][0]);
                for (k = 1; k < messageCount[j]; ++k)
                {
                    printf(", %s", messages[j][k]);
                }
                printf("]\n");
            }
        }
    }

    return 0;
}
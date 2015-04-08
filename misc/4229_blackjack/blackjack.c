#include <stdio.h>

int resolveValue(char c)
{
    if (c >= '2' && c <= '9')
        return c - '0';
    return 10;
}

int playerWins(int player, int dealer)
{
    if (player > 21) return 0;
    if (dealer > 21) return 1;
    if (dealer > player) return 0;
    return 1;
}

void deal(int player, int dealer, int playerEleven, int dealerEleven, int count,
    int stopped, char cards[], int *canWin)
{
    int val;
    int eleven;
    char card = cards[count];
    if (count < 4)
    {
        if (count % 2 == 0)
        {
            eleven = playerEleven;
            if (card == 'A')
            {
                if (player + 11 < 22)
                {
                    eleven = 1;
                    val = 11;
                }
                else
                    val = 1;
            }
            else
                val = resolveValue(card);
            if (player+val > 21 && playerEleven)
            {
                eleven = 0;
                val -= 10;
            }
            deal(player+val, dealer, eleven, dealerEleven, count+1, stopped, cards, canWin);
            /*if (card == 'A')
            {
                deal(player+1, dealer, playerEleven, dealerEleven, count+1, stopped, cards, canWin);
                deal(player+11, dealer, playerEleven, dealerEleven, count+1, stopped, cards, canWin);
            }
            else
                deal(player+resolveValue(card), dealer, playerEleven, dealerEleven, count+1, stopped, cards, canWin);*/
        }
        else
        {
            eleven = dealerEleven;
            if (card == 'A')
            {
                if (dealer + 11 < 22)
                {
                    eleven = 1;
                    val = 11;
                }
                else
                    val = 1;
            }
            else
                val = resolveValue(card);
            if (dealer+val > 21 && dealerEleven)
            {
                eleven = 0;
                val -= 10;
            }
            deal(player, dealer+val, playerEleven, eleven, count+1, stopped, cards, canWin);
            /*if (card == 'A')
            {
                if (dealer + 11 < 22)
                    deal(player, dealer+11, playerEleven, dealerEleven, count+1, stopped, cards, canWin);
                else
                    deal(player, dealer+1, playerEleven, dealerEleven, count+1, stopped, cards, canWin);
            }
            else
                deal(player, dealer+resolveValue(card), playerEleven, dealerEleven, count+1, stopped, cards, canWin);*/
        }
    }
    else if (card == '\0')
        *canWin = *canWin || playerWins(player, dealer);
    else if (stopped)
    {
        if (dealer > 16)
            *canWin = *canWin || playerWins(player, dealer);
        else
        {
            eleven = dealerEleven;
            if (card == 'A')
            {
                if (dealer + 11 < 22)
                {
                    eleven = 1;
                    val = 11;
                }
                else
                    val = 1;
            }
            else
                val = resolveValue(card);
            if (dealer+val > 21 && dealerEleven)
            {
                eleven = 0;
                val -= 10;
            }
            deal(player, dealer+val, playerEleven, eleven, count+1, stopped, cards, canWin);
        }
    }
    else if (player <= 21)
    {
        eleven = playerEleven;
        deal(player, dealer, playerEleven, dealerEleven, count, 1, cards, canWin);
        if (card == 'A')
        {
            if (player + 11 < 22)
            {
                eleven = 1;
                val = 11;
            }
            else
                val = 1;
        }
        else
            val = resolveValue(card);
        if (player+val > 21 && playerEleven)
        {
            eleven = 0;
            val -= 10;
        }
        deal(player+val, dealer, eleven, dealerEleven, count+1, stopped, cards, canWin);
    }
}

int main(int argc, char *argv[])
{
    char cards[53];
    int canWin;

    scanf("%s", cards);
    while (cards[1] != 'O')
    {
        canWin = 0;
        deal(0, 0, 0, 0, 0, 0, cards, &canWin);
        printf("%s\n", canWin ? "Yes" : "No");
        scanf("%s", cards);
    }

    return 0;
}
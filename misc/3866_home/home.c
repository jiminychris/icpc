#include <stdio.h>
#include <string.h>

struct instruction
{
    char type;
    int direction;
    char number[120];
    char road[120];
};

char compass[4][10] = {
    "north",
    "east",
    "south",
    "west"
};

char directions[2][10] = {
    "left",
    "right"
};

int main(int argc, char *argv[])
{
    int n, i, orientation;
    int ct = 0;
    struct instruction stack[100];
    struct instruction *current, *next;
    char str[120];

    scanf("%d", &n);
    while (n != 0)
    {
        for (i=0; i<n; i++)
        {
            current = &stack[i];
            scanf("%s", str);
            current->type = str[0];
            if (current->type == 'H')
            {
                scanf("%s", str);
                switch(str[0])
                {
                    case 'n':
                        orientation = 0;
                        break;
                    case 'e':
                        orientation = 1;
                        break;
                    case 's':
                        orientation = 2;
                        break;
                    default:
                        orientation = 3;
                        break;
                }
                scanf("%s", str);
                scanf("%s ", current->number);
                fgets(current->road, 120, stdin);
                current->road[strlen(current->road)-1] = '\0';
            }
            else if (current->type == 'A')
            {
                scanf("%s", str);
                scanf("%s ", current->number);
                fgets(current->road, 120, stdin);
                current->road[strlen(current->road)-1] = '\0';
            }
            else if (current->type == 'T')
            {
                scanf("%s", str);
                if (str[0] == 'r')
                {
                    current->direction = 1;
                    orientation++;
                }
                else
                {
                    current->direction = 0;
                    orientation--;
                }
                scanf("%s ", str);
                fgets(current->road, 120, stdin);
                current->road[strlen(current->road)-1] = '\0';
            }
            else
            {
                scanf("%s ", str);
                fgets(current->road, 120, stdin);
                current->road[strlen(current->road)-1] = '\0';
            }
        }

        printf("Directions %d:\n", ++ct);
        for (i=n-1; i>=0; i--)
        {
            current = &stack[i];
            next = &stack[i-1];
            if (current->type == 'A')
            {
                printf("Head %s from %s %s\n", compass[(orientation+2) % 4], current->number, current->road);
            }
            else if (current->type == 'T')
            {
                printf("Turn %s at %s\n", directions[(current->direction+1) % 2], next->road);
            }
            else if (current->type == 'C')
            {
                printf("Continue on %s\n", next->road);
            }
            else
            {
                printf("Arrive at %s %s\n", current->number, current->road);
            }
        }
        printf("\n");
        scanf("%d", &n);
    }

    return 0;
}
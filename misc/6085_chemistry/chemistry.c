#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define GROUP "GROUP"
#define LEAF "LEAF"

#define OPAREN "OPAREN"
#define CPAREN "CPAREN"
#define SYMBOL "SYMBOL"
#define NUMBER "NUMBER"
#define JOIN "JOIN"

struct node
{
    char *type;
    long int ival;
    char sval[4];
    struct node *left;
    struct node *right;
};

struct node *currentNode;
char buf[101];
struct node elements[101];
int numElements;
int bufptr;

struct node *match(char *type);
void lex();
int check(char *type);

int APending();
int MPending();
int GPending();
int SPending();
int CPending();

struct node *A();
struct node *M();
struct node *G();
struct node *S();
struct node *C();

void eval(struct node *tree, long int mult);

void lex()
{
    char ch = buf[bufptr++];
    int i;
    char numbuf[100];

    currentNode = malloc(sizeof(*currentNode));
    switch(ch)
    {
    case '(':
        currentNode->type = OPAREN;
        break;
    case ')':
        currentNode->type = CPAREN;
        break;
    default:
        if (ch >= 'A' && ch <= 'Z')
        {
            currentNode->type = SYMBOL;
            currentNode->sval[0] = ch;
            ch = buf[bufptr];
            if (ch >= 'a' && ch <= 'z')
            {
                currentNode->sval[1] = ch;
                ch = buf[++bufptr];
                if (ch >= 'a' && ch <= 'z')
                {
                    bufptr += 1;
                    currentNode->sval[2] = ch;
                }
            }
        }
        else if (ch >= '0' && ch <= '9')
        {
            currentNode->type = NUMBER;
            i = 0;
            while (ch >= '0' && ch <= '9')
            {
                numbuf[i] = ch;
                ch = buf[bufptr++];
                i += 1;
            }
            numbuf[i] = '\0';
            bufptr -= 1;
            currentNode->ival = atol(numbuf);
        }
        else
        {
            /*printf("Unknown item: %d\n", ch);
            exit(1);*/
        }
        break;
    }
}

struct node *match(char *type)
{
    assert(check(type));
    struct node *old = currentNode;
    lex();

    return old;
}

int check(char *type)
{
    if (currentNode->type == 0) return 0;
    int result = strcmp(currentNode->type, type) == 0;
    return result;
}

int MPending()
{
    return GPending();
}

int GPending()
{
    return SPending();
}

int SPending()
{
    int result = check(OPAREN)
        || APending();
    return result;
}

int APending()
{
    return check(SYMBOL);
}

int CPending()
{
    return check(NUMBER);
}

struct node *M()
{
    struct node *tree = malloc(sizeof(*tree));
    tree->type = JOIN;
    tree->left = G();
    if (MPending())
    {
        tree->right = M();
    }
    return tree;
}

struct node *G()
{
    struct node *tree = S();
    tree->ival = 1;
    if (CPending())
        tree->ival = C()->ival;
    return tree;
}

struct node *S()
{
    struct node *tree;
    if (check(OPAREN))
    {
        match(OPAREN);
        tree = M();
        tree->type = GROUP;
        match(CPAREN);
    }
    else
    {
        tree = A();
        tree->type = LEAF;
    }
    return tree;
}

struct node *C()
{
    return match(NUMBER);
}

struct node *A()
{
    return match(SYMBOL);
}

void eval(struct node *tree, long int mult)
{
    if (tree == 0) return;

    int i;

    if (strcmp(tree->type, JOIN) == 0)
    {
        eval(tree->left, mult);
        eval(tree->right, mult);
    }
    else if (strcmp(tree->type, GROUP) == 0)
    {
        eval(tree->left, mult * tree->ival);
        eval(tree->right, mult * tree->ival);
    }
    else if (strcmp(tree->type, LEAF) == 0)
    {
        long num = tree->ival * mult;
        for (i=0; i<numElements; i++)
        {
            if (strcmp(tree->sval, elements[i].sval) == 0)
            {
                elements[i].ival += num;
                break;
            }
        }
        if (i == numElements)
        {
            strncpy(elements[numElements].sval, tree->sval, 4);
            elements[numElements].ival = num;
            numElements += 1;
        }
    }
    else
    {
        printf("Unrecognized type: %s", tree->type);
        exit(1);
    }
}

void test0()
{
    strncpy(buf, "H2O", 100);
    bufptr = 0;
    lex();
    struct node *tree = M();

    assert(tree != 0);

    struct node *h2 = tree->left;

    assert(h2 != 0);

    assert(strcmp(h2->type, LEAF) == 0);
    assert(strcmp(h2->sval, "H") == 0);
    assert(h2->ival == 2);

    assert(tree->right != 0);

    struct node *o = tree->right->left;

    assert(o != 0);

    assert(strcmp(o->type, LEAF) == 0);
    assert(strcmp(o->sval, "O") == 0);
    assert(o->ival == 1);
}

void test1()
{
    strncpy(buf, "(AlC2)3Na4", 100);
    bufptr = 0;
    lex();
    struct node *tree = M();

    assert(tree != 0);

    struct node *alc2 = tree->left;
    assert(alc2 != 0);
    assert(strcmp(alc2->type, GROUP) == 0);
    assert(alc2->ival == 3);

    struct node *al = alc2->left;
    assert(al != 0);
    assert(strcmp(al->type, LEAF) == 0);
    assert(strcmp(al->sval, "Al") == 0);
    assert(al->ival == 1);

    assert(alc2->right != 0);
    struct node *c2 = alc2->right->left;
    assert(c2 != 0);
    assert(strcmp(c2->type, LEAF) == 0);
    assert(strcmp(c2->sval, "C") == 0);
    assert(c2->ival == 2);

    assert(tree->right != 0);
    struct node *na4 = tree->right->left;
    assert(na4 != 0);
    assert(strcmp(na4->type, LEAF) == 0);
    assert(strcmp(na4->sval, "Na") == 0);
    assert(na4->ival == 4);
}

int main(int argc, char *argv[])
{
    /*test0();
    test1();
    return 0;*/
    int i, j;
    while (scanf("%s", buf) != EOF)
    {
        bufptr = 0;
        numElements = 0;
        lex();
        eval(M(), 1);
        for (i=0; i<numElements; i++)
        {
            for (j=i+1; j<numElements; j++)
            {
                if (strcmp(elements[j].sval, elements[i].sval) < 0)
                {
                    strncpy(elements[numElements].sval, elements[i].sval, 4);
                    elements[numElements].ival = elements[i].ival;

                    strncpy(elements[i].sval, elements[j].sval, 4);
                    elements[i].ival = elements[j].ival;

                    strncpy(elements[j].sval, elements[numElements].sval, 4);
                    elements[j].ival = elements[numElements].ival;
                }
            }
        }

        for (i=0; i<numElements; i++)
        {
            if (i > 0) printf("+");
            if (elements[i].ival != 1) printf("%ld", elements[i].ival);
            printf("%s", elements[i].sval);
        }
        printf("\n");
    }

    return 0;
}
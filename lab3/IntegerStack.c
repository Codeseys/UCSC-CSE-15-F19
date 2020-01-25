// Subset.c
// Baladithya Balamurugan
// CruzId: bbalamur
// Class: CSE-15-1
// Date: 11/5/19
// Integer stack ADT
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "IntegerStack.h"

typedef struct IntegerStackObj
{
    int *item;
    int numItems;
    int size;
} * IntegerStack;

void doubleItemArray(IntegerStack S)
{
    if (S == NULL)
    {
        fprintf(stderr, "IntegerStack Error: doubleItemArray() called on NULL IntegerList reference");
        exit(EXIT_FAILURE);
    }
    int i;
    int *newArray;
    int *oldArray = S->item;
    S->size *= 2;
    newArray = calloc(S->size, sizeof(int));
    for (i = 0; i < (S->numItems); i++)
    {
        newArray[i] = oldArray[i];
    }
    S->item = newArray;
    free(oldArray);
}

IntegerStack newIntegerStack()
{
    IntegerStack StackyBoi = malloc(sizeof(IntegerStack));
    StackyBoi->item = calloc(1, sizeof(int));
    StackyBoi->numItems = 0;
    StackyBoi->size = 1;
    return StackyBoi;
}

void freeIntegerStack(IntegerStack *pS)
{
    if (pS != NULL && *pS != NULL)
    {
        free((*pS)->item);
        free(*pS);
        *pS = NULL;
    }
}

int isEmpty(IntegerStack S)
{
    if (S == NULL)
    {
        fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerList reference");
        exit(EXIT_FAILURE);
    }
    if (S->numItems == 0)
        return 1;
    else
        return 0;
}

void push(IntegerStack S, int x)
{
    if (S->numItems == S->size)
    {
        doubleItemArray(S);
    }
    S->item[S->numItems++] = x;
}

int pop(IntegerStack S)
{
    if (S == NULL)
    {
        fprintf(stderr, "IntegerStack Error: pop() called on NULL IntegerList reference");
        exit(EXIT_FAILURE);
    }
    if (!isEmpty(S))
    {
        int poppedOff = S->item[S->numItems - 1];
        S->numItems--;
        return poppedOff;
    }
    else
        return 0;
}
int peek(IntegerStack S)
{
    if (S == NULL)
    {
        fprintf(stderr, "IntegerStack Error: peek() called on NULL IntegerList reference");
        exit(EXIT_FAILURE);
    }
    if (!isEmpty(S))
        return S->item[S->numItems - 1];
    else
        return 0;
}
void popAll(IntegerStack S)
{
    if (S == NULL)
    {
        fprintf(stderr, "IntegerStack Error: popAll() called on NULL IntegerList reference");
        exit(EXIT_FAILURE);
    }
    {
        freeIntegerStack(&S);
        S = newIntegerStack();
    }
}
void printIntegerStack(FILE *out, IntegerStack S)
{
    if (S == NULL)
    {
        fprintf(stderr, "IntegerStack Error: printIntegerStack() called on NULL IntegerList reference");
        exit(EXIT_FAILURE);
    }
    for (int i = S->numItems - 1; i >= 0; i--)
    {
        fprintf(out, "%d ", S->item[i]);
    }
    fprintf(out, "\n");
}
int equals(IntegerStack S, IntegerStack T)
{
    if (S == NULL)
    {
        fprintf(stderr, "IntegerStack Error: equals() called on NULL IntegerList reference");
        exit(EXIT_FAILURE);
    }
    if (S->numItems != T->numItems)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < S->numItems; i++)
        {
            if (S->item[i] != T->item[i])
                return 0;
        }
    }
    return 1;
}
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

void expandByOne(IntegerStack L)
{
    int newSize = L->size + 1;
    int *newArray;
    int *oldArray = L->item;
    int newNumItems = 1 + L->numItems + 1;
    newArray = calloc(newSize, sizeof(int));
    memcpy(newArray + 1, oldArray, L->size * sizeof(int));
    L->item = newArray;
    L->size = newSize;
    L->numItems = newNumItems;
    free(oldArray);
}

void shrinkByOne(IntegerStack L)
{
    int newSize = L->size - 1;
    int *newArray;
    int *oldArray = L->item;
    int newNumItems = L->numItems - 1;
    newArray = calloc(newSize, sizeof(int));
    memcpy(newArray, oldArray + 1, (L->size * sizeof(int)) - sizeof(int));
    L->item = newArray;
    L->size = newSize;
    L->numItems = newNumItems;
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
    if (S->numItems == 0)
        return 1;
    else
        return 0;
}
void push(IntegerStack S, int x)
{
    expandByOne(S);
    S->item[0] = x;
}
int pop(IntegerStack S)
{
    if (!isEmpty(S))
    {
        int poppedOff = S->item[0];
        shrinkByOne(S);
        return poppedOff;
    }
    else
        return 0;
}
int peek(IntegerStack S)
{
    if (!isEmpty(S))
    {
        return S->item[0];
    }
    else
        return 0;
}
void popAll(IntegerStack S)
{
    int *oldArray = S->item;
    int *newArray = calloc(1, sizeof(int));
    free(oldArray);
    S->item = newArray;
    S->numItems = 0;
    S->size = 1;
    //IntegerStack S = newIntegerStack();
}
void printIntegerStack(FILE *out, IntegerStack S)
{
    for (int i = 0; i < S->size; i++)
    {
        fprintf(out, "%d ", S->item[i]);
    }
}
int equals(IntegerStack S, IntegerStack T)
{
    if (S->size != T->size)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < S->size; i++)
        {
            if (S->item[i] != T->item[i])
                return 0;
        }
    }
    return 1;
}

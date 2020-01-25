//-----------------------------------------------------------------------------
// Dictionary.c
// Binary Search Tree implementation of the Dictionary ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

typedef struct NodeObj
{
    struct NodeObj *prev;
    char *key;
    char *value;
    struct NodeObj *next;

} NodeObj;

typedef NodeObj *Node;

Node newNode(char *k, char *v)
{
    Node genesis = malloc(sizeof(NodeObj));
    genesis->prev = NULL;
    genesis->key = k;
    genesis->value = v;
    genesis->next = NULL;
    return genesis;
}

void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

typedef struct DictionaryObj
{
    Node node;
    int numPairs;
} DictionaryObj;

Dictionary newDictionary()
{
    Dictionary genesis = malloc(sizeof(DictionaryObj));
    genesis->node = NULL;
    genesis->numPairs = 0;
    return genesis;
}

void makeEmpty(Dictionary D)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling makeEmpty() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    Node current = D->node;
    while (current->next != NULL)
    {
        current = current->next;
        freeNode(&current->prev);
    }
    freeNode(&current);
    D->node = NULL;
    D->numPairs = 0;
}

void freeDictionary(Dictionary *pD)
{
    if (pD != NULL && *pD != NULL)
    {
        makeEmpty(*pD);
        //printf("YEET");
        free(*pD);
        *pD = NULL;
    }
}

Node findKey(Node N, char *k)
{
    if (N == NULL || strcmp(N->key, k) == 0)
        return N;
    else
        return findKey(N->next, k);
}

int countChars(Node N)
{
    int count = 0;
    if (N != NULL)
        count += strlen(N->key) + strlen(N->value) + 2 + countChars(N->next);
    return count;
}

int size(Dictionary D)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling size() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    return D->numPairs;
}

char *lookup(Dictionary D, char *k)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling lookup() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    return (findKey(D->node, k) == NULL ? NULL : findKey(D->node, k)->value);
}

void insert(Dictionary D, char *k, char *v)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling insert() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    if (findKey(D->node, k) != NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: cannot insert() duplicate key: \"%s\"\033[0m\n", k);
        exit(EXIT_FAILURE);
    }
    Node current = D->node;
    if (current == NULL)
    {
        D->node = newNode(k, v);
    }
    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        Node N = newNode(k, v);
        N->prev = current;
        current->next = N;
        // freeNode(&N);
    }
    D->numPairs++;
}

void delete (Dictionary D, char *k)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling delete() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }

    if (lookup(D, k) == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: cannot delete() non-existent key: \"%s\"\033[0m\n", k);
        exit(EXIT_FAILURE);
    }
    if (lookup(D, k) != NULL)
    {
        Node current = findKey(D->node, k);
        if (current->next == NULL && current->prev != NULL)
        {
            current->prev->next = NULL;
            freeNode(&current);
        }
        else if (current->next != NULL && current->prev == NULL)
        {
            D->node = current->next;
            D->node->prev = NULL;
            freeNode(&current);
        }
        else if (current->next == NULL && current->prev == NULL)
        {
            D->node = NULL;
            freeNode(&current);
        }
        else
        {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            freeNode(&current);
        }
        D->numPairs--;
        freeNode(&current);
    }
}

char *DictionaryToString(Dictionary D)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling DictionaryToString() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    Node current = D->node;
    char *str = calloc(countChars(D->node) + 1, sizeof(char));
    if (current == NULL)
    {
        strcat(str, "yeet");
    }
    while (current != NULL)
    {
        strcat(str, current->key);
        strcat(str, " ");
        strcat(str, current->value);
        strcat(str, "\n");
        current = current->next;
    }
    strcat(str, "\0");
    return str;
}
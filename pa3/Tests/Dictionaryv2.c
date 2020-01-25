#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

typedef struct NodeObj
{
    struct NodeObj *prev;
    char *key;
    char *value;

} * Node;

Node newNode(Node oldNode, char *k, char *v)
{
    Node genesis = malloc(sizeof(Node));
    genesis->prev = oldNode;
    genesis->key = k;
    genesis->value = v;
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

void deleteAll(Node R)
{
    if (R->prev != NULL)
    {
        deleteAll(R->prev);
        freeNode(&R);
    }
}

typedef struct DictionaryObj
{
    Node node;
    int numPairs;

} * Dictionary;

Dictionary newDictionary()
{
    Dictionary genesis = malloc(sizeof(Dictionary));
    genesis->node = NULL;
    genesis->numPairs = 0;
    return genesis;
}

void freeDictionary(Dictionary *pD)
{
    if (pD != NULL && *pD != NULL)
    {
        makeEmpty(*pD);
        free(*pD);
        *pD = NULL;
    }
}

void makeEmpty(Dictionary D)
{
    deleteAll(D->node);
    D->node = NULL;
    D->numPairs = 0;
}

Node findKey(Node current, char *k)
{
    if (current == NULL || strcmp(k, current->key) == 0)
        return current;
    else
        return findKey(current->prev, k);
}

int countChars(Dictionary D)
{
    int numChars = 0;
    Node current = D->node;
    while (current->prev != NULL)
    {
        numChars += strlen(current->key) + strlen(current->value);
        current = current->prev;
    }
    return numChars;
}

int size(Dictionary D)
{
    if (D == NULL)
    {
        fprintf(stderr,
                "Dictionary Error: calling size() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    else
        return D->numPairs;
}

char *lookup(Dictionary D, char *k)
{
    Node target = findKey(D->node, k);
    if (target != NULL)
        return target->value;
    else
        return NULL;
}
void insert(Dictionary D, char *k, char *v)
{
    if (lookup(D, k) == NULL)
    {
        Node newnode = newNode(D->node, k, v);
        D->node = newnode;
        D->numPairs += 1;
    }
}

void delete (Dictionary D, char *k)
{
    if (lookup(D, k) != NULL)
    {
        Node tempNode = D->node;
        D->node = D->node->prev;
        freeNode(&tempNode);
    }
}
char *DictionaryToString(Dictionary D)
{
    Node current = D->node;
    char *str = calloc(countChars(D), sizeof(char));
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
        current = current->prev;
    }
    strcat(str, "\0");
    return str;
}

void printLL(Dictionary D)
{
    Node current = D->node;
    while (current != NULL)
    {
        printf("\t%s\t%s\n", current->key, current->value);
        current = current->prev;
    }
}

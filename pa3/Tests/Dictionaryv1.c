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

} * Node;

Node newNode(char *k, char *v)
{
    Node genesis = malloc(sizeof(Node));
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

Node findKey(Dictionary D, char *k)
{
    Node current = D->node;
    while (current->next != NULL)
    {
        if (strcmp(current->key, k) == 0)
        {
            return current;
        }
        else
        {
            current = current->next;
        }
    }
    return NULL;
}

int countChars(Dictionary D)
{
    int numChars = 0;
    Node current = D->node;
    while (current->next != NULL)
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
    return D->numPairs;
}
char *lookup(Dictionary D, char *k)
{
    Node target = findKey(D, k);
    if (target != NULL)
    {
        return target->value;
    }
    else
    {
        return NULL;
    }
}
void insert(Dictionary D, char *k, char *v)
{
    if (lookup(D, k) == NULL)
    {
        Node N = D->node;
        Node newnode = newNode(k, v);
        newnode->prev = N;
        N->next = newnode;
        D->node = newnode;
        D->numPairs += 1;
    }
}
void delete (Dictionary D, char *k)
{
    if (lookup(D, k) != NULL)
    {
        Node tempNode = D->node;
        D->node = D->node->next;
        freeNode(&tempNode);
    }
}
void deleteAll(Node R)
{
    if (R->prev != NULL)
    {
        deleteAll(R->next);
        freeNode(&R);
    }
}
void makeEmpty(Dictionary D)
{
    deleteAll(D->node);
    freeDictionary(&D);
    D = newDictionary();
}
char *DictionaryToString(Dictionary D)
{
    Node current = D->node;
    while (current->next != NULL)
    {
        printf("\t%s\t%s\n", current->key, current->value);
    }
    return NULL;
}

void printLL(Dictionary D)
{
    Node current = D->node;
    while (current->prev != NULL)
    {
        printf("\t%s\t%s\n", current->key, current->value);
    }
}
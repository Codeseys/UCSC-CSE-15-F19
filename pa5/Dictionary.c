#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

const int tableSize = 101; // or some prime other than 101

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift)
{
    int sizeInBits = 8 * sizeof(unsigned int);
    shift = shift & (sizeInBits - 1);
    if (shift == 0)
        return value;
    return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char *input)
{
    unsigned int result = 0xBAE86554;
    while (*input)
    {
        result ^= *input++;
        result = rotate_left(result, 5);
    }
    return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char *key)
{
    return pre_hash(key) % tableSize;
}

typedef struct NodeObj
{
    struct NodeObj *prev;
    char *key;
    char *value;
    struct NodeObj *next;

} NodeObj;

typedef NodeObj *Node;

//node constructor
Node newNode(char *k, char *v)
{
    Node N = malloc(sizeof(NodeObj));
    N->prev = NULL;
    N->key = k;
    N->value = v;
    N->next = NULL;
    return N;
}

//node destructor
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
    Node *table;
    int size;
} DictionaryObj;

Dictionary newDictionary()
{
    Dictionary genesis = malloc(sizeof(DictionaryObj));
    genesis->size = 0;
    genesis->table = calloc(tableSize, sizeof(Node));
    return genesis;
}

void freeRow(Node Row)
{
    if (Row == NULL)
        return;
    Node current = Row;
    while (current->next != NULL)
    {
        current = current->next;
        freeNode(&current->prev);
    }
    freeNode(&current);
    Row = NULL;
}

void makeEmpty(Dictionary D)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling makeEmpty() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tableSize; i++)
    {
        freeRow(D->table[i]);
        D->table[i] = NULL;
    }
    D->size = 0;
}

void freeDictionary(Dictionary *pD)
{
    if (pD != NULL && *pD != NULL)
    {
        makeEmpty(*pD);
        //printf("YEET");
        free((*pD)->table);
        free(*pD);
        *pD = NULL;
    }
}

// size()
// Return the number of (key, value) pairs in Dictionary D.
int size(Dictionary D)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling size() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    return D->size;
}

Node findKey(Node N, char *k)
{
    if (N == NULL || strcmp(N->key, k) == 0)
        return N;
    else
        return findKey(N->next, k);
}

// lookup()
// If D contains a pair whose key matches argument k, then return the
// corresponding value, otherwise return NULL.
char *lookup(Dictionary D, char *k)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling lookup() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    int idx = hash(k);
    // printf("\n im fookin finding %s in %d\n", k, idx);

    return (findKey(D->table[idx], k) == NULL ? NULL : findKey(D->table[idx], k)->value);
}

// insert()
// Insert the pair (k,v) into D.
// Pre: lookup(D, k)==NULL (D does not contain a pair whose first member is k.)
void insert(Dictionary D, char *k, char *v)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling insert() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    if (lookup(D, k) != NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: cannot insert() duplicate key: \"%s\"\033[0m\n", k);
        exit(EXIT_FAILURE);
    }

    Node temp = newNode(k, v);
    int idx = hash(k);
    if (D->table[idx] == NULL)
    {
        D->table[idx] = temp;
        // printf("\n im fookin putting %s in index: %d\n", v, idx);
    }
    else
    {
        D->table[idx]->prev = temp;
        temp->next = D->table[idx];
        D->table[idx] = temp;
    }
    D->size++;
}

// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
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
        int idx = hash(k);
        Node current = findKey(D->table[idx], k);
        // printf("\n im fookin deleting %s in %d\n", current->value, idx);
        if (current->next == NULL && current->prev != NULL)
        {
            current->prev->next = NULL;
            freeNode(&current);
        }
        else if (current->next != NULL && current->prev == NULL)
        {
            D->table[idx] = current->next;
            D->table[idx]->prev = NULL;
            freeNode(&current);
        }
        else if (current->next == NULL && current->prev == NULL)
        {
            D->table[idx] = NULL;
            freeNode(&current);
        }
        else
        {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            freeNode(&current);
        }
        D->size--;
        freeNode(&current);
    }
}

int countCharsPerRow(Node N)
{
    int count = 0;
    if (N != NULL)
        count += strlen(N->key) + strlen(N->value) + 2 + countCharsPerRow(N->next);
    return count;
}

int countTotalChars(Dictionary D)
{
    int totalLen = 0;
    for (int i = 0; i < tableSize; i++)
    {
        Node current = D->table[i];
        totalLen += countCharsPerRow(current);
    }
    return totalLen;
}

// DictionaryToString()
// Determines a text representation of the current state of Dictionary D. Each
// (key, value) pair is represented as the chars in key, followed by a space,
// followed by the chars in value, followed by a newline '\n' char. The pairs
// occur in alphabetical order by key. The function returns a pointer to a char
// array, allocated from heap memory, containing the text representation
// described above, followed by a terminating null '\0' char. It is the
// responsibility of the calling function to free this memory.
char *DictionaryToString(Dictionary D)
{
    if (D == NULL)
    {
        fprintf(stderr, "\033[1;31mDictionary Error: calling DictionaryToString() on NULL Dictionary reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    int totalLen = countTotalChars(D);
    char *str = calloc(totalLen + 1, sizeof(char));
    for (int idx = 0; idx < tableSize; idx++)
    {

        Node current = D->table[idx];
        // if (current == NULL)
        // {
        //     printf("\nThis Shit EMPTY...........YEET\n");
        // }
        // else
        // {
        //     printf("\nThis Shit not empty...........\n");
        // }

        // if (current == NULL)
        // {
        //     strcat(str, "yeet thy beet ");
        // }
        while (current != NULL)
        {
            strcat(str, current->key);
            strcat(str, " ");
            strcat(str, current->value);
            strcat(str, "\n");
            current = current->next;
        }
    }
    strcat(str, "\0");
    return str;
}
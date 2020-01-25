#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "IntegerQueue.h"

typedef struct NodeObj
{
    struct NodeObj *next;
    int item;
} NodeObj;

typedef NodeObj *Node;

Node newNode(int val)
{
    Node temp = malloc(sizeof(NodeObj));
    temp->next = NULL;
    temp->item = val;
    return temp;
}

void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

typedef struct IntegerQueueObj
{
    Node head;
    Node tail;
    int numItems;
} IntegerQueueObj;

IntegerQueue newIntegerQueue()
{
    IntegerQueue genesis = malloc(sizeof(IntegerQueueObj));
    genesis->head = genesis->tail = NULL;
    genesis->numItems = 0;
    return genesis;
}

void dequeueAll(IntegerQueue Q)
{
    if (Q == NULL)
    {
        return;
    }
    Node current = Q->head;
    while (current != NULL)
    {
        Node temp = current;
        current = current->next;
        freeNode(&temp);
    }
    Q->head = Q->tail = NULL;
    Q->numItems = 0;
}

void freeIntegerQueue(IntegerQueue *pQ)
{
    if (pQ != NULL || *pQ != NULL)
    {
        dequeueAll(*pQ);
        free(*pQ);
        *pQ = NULL;
    }
}

int isEmpty(IntegerQueue Q)
{
    if (Q->head == NULL && Q->tail == NULL && Q->numItems == 0)
    {
        return 1;
    }
    return 0;
}

int length(IntegerQueue Q)
{
    return Q->numItems;
}

void enqueue(IntegerQueue Q, int x)
{
    Node temp = newNode(x);
    if (Q->head == NULL && Q->tail == NULL)
    {
        Q->head = Q->tail = temp;
        return;
    }

    Q->tail->next = temp;
    Q->tail = temp;
    Q->numItems++;
}

int dequeue(IntegerQueue Q)
{
    if (isEmpty(Q))
    {
        printf("IntegerQueue is already empty");
        exit(EXIT_FAILURE);
    }
    Node temp = Q->head;
    Q->head = Q->head->next;
    int val = temp->item;
    Q->numItems--;
    freeNode(&temp);
    return val;
}

int peek(IntegerQueue Q)
{
    if (!isEmpty(Q))
    {
        int value = Q->head->item;
        return value;
    }
    else
    {
        printf("IntegerQueue is already empty");
        exit(EXIT_FAILURE);
    }
}

int equals(IntegerQueue Q, IntegerQueue R)
{
    Node q, r;
    if (Q->numItems == R->numItems)
    {
        q = Q->head;
        r = R->head;
        while (q != NULL && r != NULL)
        {
            if (q->item != r->item)
            {
                printf("equals ");
                return 0;
            }
            q = q->next;
            r = r->next;
        }
        printf("equals ");
        return 1;
    }
    printf("equals ");
    return 0;
}

int countDigits(int value)
{
    int result = 0;
    while (value != 0)
    {
        value /= 10;
        result++;
    }
    return result;
}

int countChars(Node N)
{
    int count = 0;
    if (N != NULL)
        count += countDigits(N->item) + 1 + countChars(N->next);
    return count;
}

char *IntegerQueueToString(IntegerQueue Q)
{
    if (Q == NULL)
    {
        fprintf(stderr, "\033[1;31mIntegerQueue Error: calling IntegerQueueToString() on NULL IntegerQueue reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    Node current = Q->head;
    char *str = calloc(countChars(current) + 1, sizeof(char));
    char *strbuf = calloc(countChars(current) + 1, sizeof(char));
    // if (current == NULL)
    // {
    //     fprintf(stderr, "\033[1;31mIntegerQueue Error: calling IntegerQueueToString() on NULL QueueNode reference\033[0m\n");
    //     strcat(str, "yeet dis SHIET EMPTY");
    // }
    int first = 1;
    while (current != NULL)
    {
        printf("\033[1;31mstrcat\033[0m ");
        if (first == 1)
        {
            sprintf(strbuf, "%d", current->item);
            first = 0;
        }
        else
            sprintf(strbuf, " %d", current->item);
        strcat(str, strbuf);
        current = current->next;
    }
    // strcat(str, " ");
    printf("\033[1;31mstrcat\033[0m ");
    strcat(str, "\0");
    free(strbuf);
    printf("toString ");
    return str;
}

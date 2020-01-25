//-----------------------------------------------------------------------------
// IntegerQueue.c
// # Baladithya Balamurugan
// # CruzId: bbalamur
// # Class: CSE-15-1
// # Date: 12/03/19
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "IntegerQueue.h"

typedef struct QueueNodeObj
{
    struct QueueNodeObj *prev;
    int value;
    struct QueueNodeObj *next;
} QueueNodeObj;

typedef QueueNodeObj *QueueNode;

QueueNode
newQueueNode(int val)
{
    QueueNode newQueueNode = malloc(sizeof(QueueNodeObj));
    newQueueNode->prev = NULL;
    newQueueNode->value = val;
    newQueueNode->next = NULL;
    return newQueueNode;
}

void freeQueueNode(QueueNode *qN)
{
    if (qN != NULL && *qN != NULL)
    {
        free(*qN);
        *qN = NULL;
    }
}

typedef struct IntegerQueueObj
{
    QueueNode head;
    QueueNode tail;
    int size;
} IntegerQueueObj;

IntegerQueue
newIntegerQueue()
{
    IntegerQueue newQueue = malloc(sizeof(IntegerQueueObj));
    newQueue->head = NULL;
    newQueue->tail = NULL;
    newQueue->size = 0;
    return newQueue;
}

void dequeueAll(IntegerQueue Q)
{
    if (Q == NULL)
    {
        exit(EXIT_FAILURE);
    }
    QueueNode current = Q->head;
    while (current != NULL)
    {
        // printf("i am working ho\n");
        current = current->next;
        freeQueueNode(&current->prev);
    }
    // freeQueueNode(&current);
    Q->head = Q->tail = NULL;
    Q->size = 0;
}

void freeIntegerQueue(IntegerQueue *pQ)
{
    if (pQ != NULL && *pQ != NULL)
    {
        dequeueAll(*pQ);
        free(*pQ);
        *pQ = NULL;
    }
}

int isEmpty(IntegerQueue Q)
{
    if (Q->head == NULL)
    {
        return 1;
    }
    return 0;
}

int length(IntegerQueue Q)
{
    return Q->size;
}

void enqueue(IntegerQueue Q, int x)
{
    QueueNode temp = newQueueNode(x);
    if (Q->head == NULL && Q->tail == NULL)
    {
        Q->head = Q->tail = temp;
        Q->size++;
        return;
    }

    Q->tail->next = temp;
    temp->prev = Q->tail;
    Q->tail = temp;
    Q->size++;
}

int dequeue(IntegerQueue Q)
{
    if (!isEmpty(Q))
    {
        if (Q->head->next == NULL)
        {
            int value;
            value = Q->head->value;
            freeQueueNode(&Q->head);
            Q->head = Q->tail = NULL;
            Q->size--;
            return value;
        }
        else
        {
            int value = Q->head->value;
            Q->head = Q->head->next;
            QueueNode temp = Q->head->prev;
            freeQueueNode(&temp);
            Q->size--;
            return value;
        }
    }
    else
    {
        printf("IntegerQueue is already empty");
        exit(EXIT_FAILURE);
    }
}

int peek(IntegerQueue Q)
{
    if (!isEmpty(Q))
    {
        int value = Q->head->value;
        return value;
    }
    else
    {
        printf("IntegerQueue is already empty");
        exit(EXIT_FAILURE);
    }
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

int countChars(QueueNode N)
{
    int count = 0;
    if (N != NULL)
        count += countDigits(N->value) + 1 + countChars(N->next);
    return count;
}

char *IntegerQueueToString(IntegerQueue Q)
{
    if (Q == NULL)
    {
        fprintf(stderr,
                "\033[1;31mIntegerQueue Error: calling IntegerQueueToString() on NULL IntegerQueue reference\033[0m\n");
        exit(EXIT_FAILURE);
    }
    QueueNode current = Q->head;
    char *str = calloc(countChars(Q->head) + 1, sizeof(char));
    char *strbuf = calloc(countChars(Q->head) + 1, sizeof(char));
    int first = 1;
    while (current != NULL)
    {
        //printf("\033[1;31mstrcat\033[0m ");
        if (first)
        {
            sprintf(strbuf, "%d", current->value);
            first = 0;
        }
        else
            sprintf(strbuf, " %d", current->value);
        strcat(str, strbuf);
        current = current->next;
    }
    // strcat(str, " ");
    //printf("\033[1;31mstrcat\033[0m ");
    strcat(str, "\0");
    free(strbuf);
    //printf("toString ");
    return str;
}

int equals(IntegerQueue Q, IntegerQueue R)
{
    QueueNode q, r;
    if (Q->size == R->size)
    {
        q = Q->head;
        r = R->head;
        while (q != NULL || r != NULL)
        {
            if (q->value != r->value)
            {
                //printf("equals ");
                return 0;
            }
            q = q->next;
            r = r->next;
        }
        // printf("equals ");
        return 1;
    }
    // printf("equals ");
    return 0;
}

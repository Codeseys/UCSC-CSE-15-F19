//-----------------------------------------------------------------------------
// Dictionary.c
// Binary Search Tree implementation of the Dictionary ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

// Private Types and Functions ------------------------------------------------

// NodeObj
typedef struct NodeObj
{
    char *key;
    char *value;
    struct NodeObj *left;
    struct NodeObj *right;
} NodeObj;

// Node
typedef NodeObj *Node;

// newNode()
// Constructor for Node type.
Node newNode(char *k, char *v)
{
    Node N = malloc(sizeof(NodeObj));
    N->key = k;
    N->value = v;
    N->left = N->right = NULL;
    return (N);
}

// freeNode()
// Destructor for Node type
void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

// DictionaryObj
typedef struct DictionaryObj
{
    Node root;
    int numPairs;
} DictionaryObj;

// findKey()
// Returns the Node containing key k in the subtree rooted at R, or returns
// NULL if no such Node exists.
Node findKey(Node R, char *k)
{
    if (R == NULL || strcmp(k, R->key) == 0)
        return R;
    if (strcmp(k, R->key) < 0)
        return findKey(R->left, k);
    else // strcmp(k, R->key)>0
        return findKey(R->right, k);
}

// findParent()
// Returns the parent of N in the subtree rooted at R, or returns NULL if N is
// equal to R.
// Pre: R != NULL
Node findParent(Node N, Node R)
{
    Node P = NULL;
    if (N != R)
    {
        P = R;
        while (P->left != N && P->right != N)
        {
            if (strcmp(N->key, P->key) < 0)
                P = P->left;
            else
                P = P->right;
        }
    }
    return P;
}

// findLeftmost()
// Returns the leftmost Node in the subtree rooted at R, or NULL if R is NULL.
Node findLeftmost(Node R)
{
    Node L = R;
    if (L != NULL)
        for (; L->left != NULL; L = L->left)
            ;
    return L;
}

// countChars()
// Returns the number of characters in the (key, value) pairs contained in the
// subtree rooted at R, including a separating space and newline for each pair.
// Used by DictionaryToString() to allocate sufficient heap memory. Uses an
// in-order traversal of the BST.
int countChars(Node R)
{
    int count = 0;
    if (R != NULL)
    {
        count += countChars(R->left);
        count += strlen(R->key) + strlen(R->value) + 2;
        count += countChars(R->right);
    }
    return count;
}

// toStringInOrder()
// Uses an in-order traversal of the subtree rooted at R to copy the pairs in
// that subtree, including a separating space and newline for each pair, to the
// char array pointed to by buf, and ending with a terminating null '\0'
// character. Returns a pointer to the terminating null. Used by function
// DictionaryToString().
char *toStringInOrder(char *buf, Node R)
{
    if (R != NULL)
    {
        buf = toStringInOrder(buf, R->left);
        strcpy(buf, R->key);
        buf += strlen(R->key);
        *buf = ' ';
        buf++;
        strcpy(buf, R->value);
        buf += strlen(R->value);
        *buf = '\n';
        buf++;
        buf = toStringInOrder(buf, R->right);
    }
    return buf;
}

// deleteAll()
// deletes all Nodes in the subtree rooted at R.
void deleteAll(Node R)
{
    if (R != NULL)
    {
        deleteAll(R->left);
        deleteAll(R->right);
        freeNode(&R);
    }
}

// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Constructor for the Dictionary type.
Dictionary newDictionary()
{
    Dictionary D = malloc(sizeof(DictionaryObj));
    D->root = NULL;
    D->numPairs = 0;
    return D;
}

// freeDictionary()
// Destructor for the Dictionary type.
void freeDictionary(Dictionary *pD)
{
    if (pD != NULL && *pD != NULL)
    {
        makeEmpty(*pD);
        free(*pD);
        *pD = NULL;
    }
}

// ADT operations -------------------------------------------------------------

// size()
// Return the number of (key, value) pairs in Dictionary D.
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

// lookup()
// If D contains a pair whose key matches argument k, then return the
// corresponding value, otherwise return NULL.
char *lookup(Dictionary D, char *k)
{
    Node N;
    if (D == NULL)
    {
        fprintf(stderr,
                "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    N = findKey(D->root, k);
    return (N == NULL ? NULL : N->value);
}

// insert()
// Insert the pair (k,v) into D.
// Pre: lookup(D, k)==NULL (D does not contain a pair whose first member is k.)
void insert(Dictionary D, char *k, char *v)
{
    Node N, A, B;
    if (D == NULL)
    {
        fprintf(stderr,
                "Dictionary Error: calling insert() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    if (findKey(D->root, k) != NULL)
    {
        fprintf(stderr,
                "Dictionary Error: cannot insert() duplicate key: \"%s\"\n", k);
        exit(EXIT_FAILURE);
    }

    N = newNode(k, v);
    B = NULL;
    A = D->root;
    while (A != NULL)
    {
        B = A;
        if (strcmp(k, A->key) < 0)
        {
            A = A->left;
        }
        else
        {
            A = A->right;
        }
    }
    if (B == NULL)
    {
        D->root = N;
    }
    else if (strcmp(k, B->key) < 0)
    {
        B->left = N;
    }
    else
    {
        B->right = N;
    }
    (D->numPairs)++;
}

// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete (Dictionary D, char *k)
{
    Node N, P, S;
    if (D == NULL)
    {
        fprintf(stderr,
                "Dictionary Error: calling delete() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    N = findKey(D->root, k);
    if (N == NULL)
    {
        fprintf(stderr,
                "Dictionary Error: cannot delete() non-existent key: \"%s\"\n", k);
        exit(EXIT_FAILURE);
    }

    if (N->left == NULL && N->right == NULL)
    { // case 1 (no children)
        if (N == D->root)
        {
            D->root = NULL;
            freeNode(&N);
        }
        else
        {
            P = findParent(N, D->root);
            if (P->right == N)
            {
                P->right = NULL;
            }
            else
            {
                P->left = NULL;
            }
            freeNode(&N);
        }
    }
    else if (N->right == NULL)
    { // case 2 (left but no right child)
        if (N == D->root)
        {
            D->root = N->left;
            freeNode(&N);
        }
        else
        {
            P = findParent(N, D->root);
            if (P->right == N)
            {
                P->right = N->left;
            }
            else
            {
                P->left = N->left;
            }
            freeNode(&N);
        }
    }
    else if (N->left == NULL)
    { // case 2 (right but no left child)
        if (N == D->root)
        {
            D->root = N->right;
            freeNode(&N);
        }
        else
        {
            P = findParent(N, D->root);
            if (P->right == N)
            {
                P->right = N->right;
            }
            else
            {
                P->left = N->right;
            }
            freeNode(&N);
        }
    }
    else
    { // case3: (two children: N->left!=NULL && N->right!=NULL)
        S = findLeftmost(N->right);
        N->key = S->key;
        N->value = S->value;
        P = findParent(S, N);
        if (P->right == S)
        {
            P->right = S->right;
        }
        else
        {
            P->left = S->right;
        }
        freeNode(&S);
    }
    (D->numPairs)--;
}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D)
{
    if (D == NULL)
    {
        fprintf(stderr,
                "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }

    deleteAll(D->root);
    D->root = NULL;
    D->numPairs = 0;
}

// Other Operations -----------------------------------------------------------

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
    char *str;
    //int i, n;
    int n;
    if (D == NULL)
    {
        fprintf(stderr,
                "Dictionary Error: calling DictionaryToString() on NULL Dictionary "
                "reference\n");
        exit(EXIT_FAILURE);
    }

    n = countChars(D->root);
    str = calloc(n + 1, sizeof(char));
    toStringInOrder(str, D->root);
    str[n] = '\0';
    return str;
}
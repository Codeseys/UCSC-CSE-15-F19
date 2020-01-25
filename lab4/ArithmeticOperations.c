// ArtithmeticOperations.c
// Baladithya Balamurugan
// CruzId: bbalamur
// Class: CSE-15-1
// Date: 11/18/19
// Reads a file input and prints an integer solved by given operations and operands

#include <stdio.h>
#include <stdlib.h>

typedef int (*fptr_t)(int, int);

int sum(int x, int y) { return x + y; }
int diff(int x, int y) { return x - y; }
int prod(int x, int y) { return x * y; }
int quot(int x, int y) { return x / y; }
int rem(int x, int y) { return x % y; }

int apply(fptr_t fp, int x, int y) { return fp(x, y); }

int compute(fptr_t fcn[5], int *A, int *idx, int n)
{
    if (n == 1)
        return apply(fcn[idx[0]], A[0], A[1]);
    else
        return apply(fcn[idx[n - 1]], compute(fcn, A, idx, n - 1), A[n]);
}

void testCompute()
{

    fptr_t op[] = {sum, diff, prod, quot, rem};
    int A[] = {3, 2, 5, 4, 6, 7, 9, 2, 8};
    int opCode[] = {0, 2, 1, 4, 2, 2, 3, 1};
    int n = 8;

    printf("%d\n", compute(op, A, opCode, n));
}

int main(int argc, char *argv[])
{
    fptr_t operatorlist[] = {sum, diff, prod, quot, rem};
    FILE *fi;
    if (argc != 2)
    {
        printf("Usage: %s input-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((fi = fopen(argv[1], "r+")) == NULL)
    {
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    rewind(fi);
    int n;
    int temp;
    if (fscanf(fi, "%d", &n) != 0)
        ;
    //make array of appt size
    int *opCode = calloc(n, sizeof(int));
    int *A = calloc(n + 1, sizeof(int));
    //input operator order
    for (int i = 0; i < n; i++)
    {
        fscanf(fi, "%d", &temp);
        opCode[i] = temp;
    }

    //input operands
    for (int i = 0; i <= n; i++)
    {
        fscanf(fi, "%d", &temp);
        A[i] = temp;
    }
    // testCompute();
    int result = compute(operatorlist, A, opCode, n);
    printf("%d\n", result);
    fclose(fi);
    free(fi);
    free(A);
    free(opCode);
    return EXIT_SUCCESS;
}
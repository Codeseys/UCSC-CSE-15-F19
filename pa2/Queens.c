// Queens.c
// Baladithya Balamurugan
// CruzId: bbalamur
// Class: CSE-15-1
// Date: 10/26/19
//
// Psuedocode:
//     1. if ?? > ?? (a queen was placed on row ??, and hence a solution was
//     found)
//     2. if we are in verbose mode
//     3. print that solution
//     4. return 1
//     5. else
//     6. for each square on row ??
//     7. if that square is safe
//     8. place a queen on that square
//     9. recur on row (?? + 1), then add the returned value to an accumulating
//     sum
//     10. remove the queen from that square
//     11. return the accumulated sum

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YEET return EXIT_FAILURE;
#define U_DUMB fprintf(stderr, "Usage: Queens [-v] number\nOption: -v verbose output, print all solutions\n");

void placeQueen(int **B, int n, int i, int j)
{
    B[i][j] = 1;
    for (int k = i + 1; k <= n; k++)
    {
        B[k][j] -= 1;
    }
    if (j != n)
    {
        for (int k = 1, l = 1; i + k <= n && j + l <= n; k++, l++)
        {
            B[i + k][j + l] -= 1;
        }
    }
    if (j != 1)
    {
        for (int k = 1, l = -1; i + k <= n && j + l > 0; k++, l--)
        {
            B[i + k][j + l] -= 1;
        }
    }
    B[i][0] = j;
}
void removeQueen(int **B, int n, int i, int j)
{
    B[i][j] = 0;
    for (int k = i + 1; k <= n; k++)
    {
        B[k][j] += 1;
    }
    if (j != n)
    {
        for (int k = 1, l = 1; i + k <= n && j + l <= n; k++, l++)
        {
            B[i + k][j + l] += 1;
        }
    }
    if (j != 1)
    {
        for (int k = 1, l = -1; i + k <= n && j + l > 0; k++, l--)
        {
            B[i + k][j + l] += 1;
        }
    }
    B[i][0] = 0;
}
void printBoard(int **B, int n)
{
    printf("(%d", B[1][0]);
    for (int i = 2; i <= n; i++)
    {
        printf(", %d", B[i][0]);
    }
    printf(")\n");
}
void print_Board(int **B, int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("(");
        bool fst = true;
        for (int j = 1; j <= n; j++)
        {
            if (fst)
            {
                printf("%d", B[i][j]);
                fst = false;
            }
            else
            {
                printf(", %d", B[i][j]);
            }
        }
        printf(")\n");
    }
}
int findSolutions(int **B, int n, int i, char *mode)
{
    int count = 0;
    if (i > n)
    {
        if (strcmp("-v", mode) == 0)
        {
            printBoard(B, n);
        }
        return 1;
    }
    else
    {

        for (int j = 1; j <= n; j++)
        {
            if (B[i][j] == 0)
            {
                placeQueen(B, n, i, j);
                count += findSolutions(B, n, i + 1, mode);
                removeQueen(B, n, i, j);
            }
        }
    }
    return count;
}

int **board_initializer(int n)
{
    int **B = calloc(n + 1, sizeof(int *));
    for (int i = 0; i <= n; i++)
    {
        B[i] = calloc(n + 1, sizeof(int));
    }
    return B;
}

void board_killer(int **B, int n)
{
    for (int i = 0; i <= n; i++)
    {
        free(B[i]);
    }
    free(B);
}
bool num_iter(char *gstr)
{
    for (int i = 0; gstr[i] != '\0'; i++)
    {
        if (!isdigit(gstr[i]))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    int n;
    char *verbose = "-v";
    if (argc == 3)
    {
        if (strcmp(argv[1], verbose) == 0 && num_iter(argv[2]))
        {
            n = atoi(argv[2]);
            if (n > 15)
            {
                YEET;
            }
            int **B = board_initializer(n);
            printf("%d-Queens has %d solutions\n", n,
                   findSolutions(B, n, 1, argv[1]));
            board_killer(B, n);
        }
        else
        {
            U_DUMB;
            YEET;
        }
    }
    else if (argc == 2)
    {
        if (num_iter(argv[1]))
        {
            n = atoi(argv[1]);
            if (n > 15)
            {
                YEET;
            }

            int **B = board_initializer(n);
            printf("%d-Queens has %d solutions\n", n, findSolutions(B, n, 1, " "));
            board_killer(B, n);
        }
        else
        {
            U_DUMB;
            YEET;
        }
    }
    else
    {
        U_DUMB;
        YEET;
    }

    return EXIT_SUCCESS;
}

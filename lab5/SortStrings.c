// Baladithya Balamurugan
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

void printArray(FILE *out, char **A, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        fprintf(out, "%s\n", A[i]);
    }
    fprintf(out, "\n");
}

void swap(char **A, int i, int j)
{
    char *temp = calloc(200, sizeof(char)); // 200 max string length
    if (strcmp(A[i], A[j]) != 0)
    {
        strcpy(temp, A[i]);
        strcpy(A[i], A[j]);
        strcpy(A[j], temp);
    }
    free(temp);
}

int Partition(char **A, int p, int r)
{
    int i, j;
    char *x = A[r];
    i = p - 1;
    for (j = p; j < r; j++)
    {
        if (strcmp(A[j], x) <= 0)
        {
            i++;
            swap(A, i, j);
        }
    }
    swap(A, i + 1, r);
    return (i + 1);
}

void QuickSort(char **A, int p, int r)
{
    int q;
    if (p < r)
    {
        q = Partition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

int main(int argc, char **argv)
{
    FILE *in, *out;
    char temp[200];
    if (argc != 3)
    {
        printf("Usage: %s input-file output-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((in = fopen(argv[1], "r+")) == NULL)
    {
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ((out = fopen(argv[2], "w+")) == NULL)
    {
        printf("Unable to write to file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    rewind(in);
    int wordCount;
    fscanf(in, "%d\n", &wordCount);
    printf("Word Count: %d\n", wordCount);

    char **arr = calloc(wordCount, sizeof(char *));

    for (int i = 0; i < wordCount; i++)
    {
        fscanf(in, "%s", temp);
        arr[i] = calloc(200, sizeof(char)); // 200 is the max length
        strcpy(arr[i], temp);
        // printf("%s \n", temp);
        // printf("%s \n", arr[i]);
    }

    QuickSort(arr, 0, wordCount - 1);
    printArray(out, arr, wordCount);

    for (int i = 0; i < wordCount; i++)
    {
        free(arr[i]);
    }
    free(arr);

    fclose(in);
    fclose(out);
    return (EXIT_SUCCESS);
}
// charType.c
// Baladithya Balamurugan
// CruzId: bbalamur
// Class: CSE-15-1
// Date: 10/11/19
// Reads a file input and outputs to categories per line in file
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

void extract_chars(char *s, char *a, char *d, char *p, char *w)
{
    int a_count = 0;
    int d_count = 0;
    int p_count = 0;
    int w_count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isalnum(s[i]))
        {
            if (isalpha(s[i]))
            {
                a[a_count] = s[i];
                a_count++;
            }
            else
            {
                d[d_count] = s[i];
                d_count++;
            }
        }
        else if (ispunct(s[i]))
        {
            p[p_count] = s[i];
            p_count++;
        }
        else if (isspace(s[i]))
        {
            w[w_count] = s[i];
            w_count++;
        }
    }
    a[a_count] = '\0';
    d[d_count] = '\0';
    p[p_count] = '\0';
    w[w_count] = '\0';
}

void checker(char *line)
{
    int a = 0;
    int d = 0;
    int p = 0;
    int w = 0;
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (isalnum(line[i]))
        {
            if (isalpha(line[i]))
            {
                a++;
            }
            else
            {
                d++;
            }
        }
        else if (ispunct(line[i]))
        {
            p++;
        }
        else if (iswspace(line[i]))
        {
            w++;
        }
    }
    printf("%d alphabetical characters\n", a);
    printf("%d numeric characters\n", d);
    printf("%d punct characters\n", p);
    printf("%d whitespace characters\n", w);
}

char *isplural(char *q)
{
    if (strlen(q) == 0 || strlen(q) > 1)
    {
        return "characters";
    }
    else
    {
        return "character";
    }
}

int main(int argc, char const *argv[])
{
    FILE *fi;
    FILE *fo;

    if (argc != 3)
    {
        printf("Usage: %s input-file output-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // open input file for reading
    if ((fi = fopen(argv[1], "r+")) == NULL)
    {
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // open output file for writing
    if ((fo = fopen(argv[2], "w+")) == NULL)
    {
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    char *line = (char *)calloc(MAX_STRING_LENGTH, sizeof(char));
    char *a = (char *)calloc(MAX_STRING_LENGTH, sizeof(char));
    char *d = (char *)calloc(MAX_STRING_LENGTH, sizeof(char));
    char *p = (char *)calloc(MAX_STRING_LENGTH, sizeof(char));
    char *w = (char *)calloc(MAX_STRING_LENGTH, sizeof(char));
    assert(line != NULL && a != NULL && d != NULL && p != NULL && w != NULL);

    rewind(fi);
    int count = 1;

    while (fgets(line, 100, fi))
    {
        // checker(line);
        fprintf(fo, "line %d contains:\n", count);
        extract_chars(line, a, d, p, w);
        fprintf(fo, "%d alphabetical %s: %s\n", (int)strlen(a), isplural(a), a);
        fprintf(fo, "%d numeric %s: %s\n", (int)strlen(d), isplural(d), d);
        fprintf(fo, "%d punctuation %s: %s\n", (int)strlen(p), isplural(p), p);
        fprintf(fo, "%d whitespace %s: %s\n", (int)strlen(w), isplural(w), w);
        count++;
    }
    fclose(fi);
    fclose(fo);
    free(line);
    free(a);
    free(d);
    free(p);
    free(w);
    return 0;
}

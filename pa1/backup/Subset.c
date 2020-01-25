// Subset.c
// Baladithya Balamurugan
// CruzId: bbalamur
// Class: CSE-15-1
// Date: 10/3/19
// Prints a Custom Message to stdout
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

// print the output from given bit array
void printSet(int B[], int n) {
  bool fstiter = true;
  printf("%c", '{');
  for (int i = 1; i <= n; i++) {
    if (B[i] == 1) {
      if (fstiter) {
        printf("%d", i);
        fstiter = false;
      } else {
        printf(", %d", i);
      }
    }
  }
  printf("%c\n", '}');
}

// debug print the bit array raw
void printyet(int B[], int n) {
  printf("{");
  for (int i = 1; i <= n; i++) {
    printf("%d ", B[i]);
  }
  printf("}\n");
}

// create subsets by bit array inclusion/exclusion (recursive)
void printSubsets(int B[], int n, int k, int i) {
  if ((n - i) + 1 < k) {
    return;
  }
  if (k == 0) {
    printSet(B, n);
    return;
  }

  B[i] = 1;
  printSubsets(B, n, k - 1, i + 1);
  B[i] = 0;
  printSubsets(B, n, k, i + 1);
}

// copies char string from param then returns new charstring pointer
char *duplicate_string(const char *ogstr) {
  size_t len = strlen(ogstr) + 1;
  char *newstr = malloc(len);
  return (char *)memcpy(newstr, ogstr, len);
}

// checking if arg is int ONLY
bool num_iter(char gstr[]) {
  for (int i = 0; gstr[i] != '\0'; i++) {
    if (!isdigit(gstr[i])) {
      //printf("f");
      printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)\n");
      return false;
    }
  }
  return true;
}

// main: accepts argv then sends as param to recursive subset function
int main(int argc, char *argv[]) {
  int B[MAX_SIZE + 1] = {0};
  int n, k;
  char *nstr;
  char *kstr;
  if (argc < 3) {
    printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)\n");
    return EXIT_FAILURE;
  }
  nstr = duplicate_string(argv[1]);
  kstr = duplicate_string(argv[2]);
  if (num_iter(nstr) == true) {

    n = atoi(nstr);
  } else {
    return EXIT_FAILURE;
  }

  if (num_iter(kstr) == true) {

    k = atoi(kstr);
  } else {
    return EXIT_FAILURE;
  }
  if (n < k) {

    printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)\n");
    return EXIT_FAILURE;
  }
  if (k == 0) {
    printf("{ }\n");
    return EXIT_SUCCESS;
  }

  // printf("n: %d k: %d\n", n, k);

  printSubsets(B, n, k, 1);

  // printSet(B, n);

  return EXIT_SUCCESS;
}
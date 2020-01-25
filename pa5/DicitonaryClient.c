//-----------------------------------------------------------------------------
// DictionaryClient1.java
// A rather weak test of the Dictionary ADT.
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

int main()
{
    int i;
    Dictionary A = newDictionary();
    char *str;
    char *v;
    char *k = calloc(100, sizeof(char));
    insert(A, "1", "a");
    insert(A, "2", "b");
    insert(A, "3", "c");
    insert(A, "4", "d");
    insert(A, "5", "e");
    insert(A, "6", "f");
    insert(A, "7", "g");
}
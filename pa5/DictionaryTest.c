//-----------------------------------------------------------------------------
// DictionaryTest.java
// A rather weak test of the Dictionary ADT.
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

int main()
{
    int i;
    printf("\033[1;32m# LOG:\033[0m\tCreating Dictionary....\n");
    Dictionary A = newDictionary();
    printf("\033[1;32m# LOG:\033[0m\tCreated Dictionary yayyyyy!!!\n");
    char *str;
    char *v;
    char *k = calloc(100, sizeof(char));
    printf("\033[1;32m# LOG:\033[0m\tInserting first entry....\n");
    insert(A, "meep", "yeep");
    printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");

    printf("\033[1;32m# LOG:\033[0m\tInserting second entry....\n");
    insert(A, "yee", "haw");
    printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");

    printf("\033[1;32m# LOG:\033[0m\tInserting third entry....\n");
    insert(A, "baby", "yoda");
    printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");

    printf("\033[1;32m# LOG:\033[0m\tInserting fourth entry....\n");
    insert(A, "cyber", "truck");
    printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");

    printf("\033[1;32m# LOG:\033[0m\tInserting fifth entry....\n");
    insert(A, "trash", "man");
    printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");

    printf("\033[1;32m# LOG:\033[0m\tInserting sixt entry....\n");
    insert(A, "steel", "kilogram");
    printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");

    printf("\033[1;32m# LOG:\033[0m\tInserting seventh entry....\n");
    insert(A, "feather", "kilogram");
    printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");

    printf("\033[1;32m# LOG:\033[0m\tConverting Dicitonary into a string....\n");
    str = DictionaryToString(A);
    printf("\033[1;32m# LOG:\033[0m\tConversion COMPLETE!!!\n");
    printf("%s\n", str);
    free(str);

    printf("\033[1;32m# LOG:\033[0m\tLogic checking from key: 0 to key: 10\n");

    for (i = 0; i <= 10; i++)
    {
        sprintf(k, "%d", i);
        v = lookup(A, k);
        printf("k=%s, value=%s\n", k, v);
    }
    printf("\n");
    printf("\033[1;32m# LOG:\033[0m\tDeleting entry with key \"meep\"\n");
    delete (A, "meep");
    printf("\033[1;32m# LOG:\033[0m\tDeletion Successful!!\n");

    printf("\033[1;32m# LOG:\033[0m\tDeleting entry with key \"cyber\"\n");
    delete (A, "cyber");
    printf("\033[1;32m# LOG:\033[0m\tDeletion Successful!!\n");

    printf("\033[1;32m# LOG:\033[0m\tDeleting entry with key \"trash\"\n");
    delete (A, "trash");
    printf("\033[1;32m# LOG:\033[0m\tDeletion Successful!!\n");

    printf("\033[1;32m# LOG:\033[0m\tConverting Dicitonary into a string....\n");
    str = DictionaryToString(A);
    printf("\033[1;32m# LOG:\033[0m\tConversion COMPLETE!!!\n");
    printf("%s\n", str);
    free(str);

    printf("\033[1;32m# LOG:\033[0m\tCalculating Dicitonary size....\n");
    printf("size(A) = %d\n", size(A));
    printf("\033[1;32m# LOG:\033[0m\tDicitonary size calculated\n");

    printf("\033[1;32m# LOG:\033[0m\tMaking Dictionary empty....\n");
    makeEmpty(A);
    printf("\033[1;32m# LOG:\033[0m\tDictionary emptied WOOT!!\n");

    printf("\033[1;32m# LOG:\033[0m\tCalculating Dicitonary size....\n");
    printf("size(A) = %d\n", size(A));
    printf("\033[1;32m# LOG:\033[0m\tDicitonary size calculated\n");

    printf("\033[1;32m# LOG:\033[0m\tConverting Dicitonary into a string....\n");
    str = DictionaryToString(A);
    printf("\033[1;32m# LOG:\033[0m\tConversion COMPLETE!!!\n");
    printf("%s\n", str);
    free(str);

    free(k);
    printf("\033[1;32m# LOG:\033[0m\tFreeing Dictionary....\n");
    freeDictionary(&A);
    printf("\033[1;32m# LOG:\033[0m\tDictionary Freed WOOT!!\n");

    return EXIT_SUCCESS;
}
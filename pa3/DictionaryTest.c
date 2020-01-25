#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delay(int number_of_seconds);
int main() {
  printf("\033[1;32m# LOG:\033[0m\tCreating Dictionary....\n");
  Dictionary D = newDictionary();
  printf("\033[1;32m# LOG:\033[0m\tCreated Dictionary yayyyyy!!!\n");
  char *str;
  printf("\033[1;32m# LOG:\033[0m\tInserting first entry....\n");
  insert(D, "first", "value of first");
  printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");
  printf("\033[1;32m# LOG:\033[0m\tInserting second entry....\n");
  insert(D, "second", "value of second");
  printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");
  printf("\033[1;32m# LOG:\033[0m\tInserting third entry....\n");
  insert(D, "third", "value of third");
  printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");
  printf("\033[1;32m# LOG:\033[0m\tInserting fourth entry....\n");
  insert(D, "4th", "value of 4th");
  printf("\033[1;32m# LOG:\033[0m\tInsterted woop!!\n");

  printf("\033[1;32m# LOG:\033[0m\tConverting Dicitonary into a string....\n");
  str = DictionaryToString(D);
  printf("\033[1;32m# LOG:\033[0m\tConversion COMPLETE!!!\n");
  printf("%s", str);
  printf(
      "\033[1;32m# LOG:\033[0m\tDeleting second entry with key \"second\"\n");
  delete (D, "second");
  printf("\033[1;32m# LOG:\033[0m\tDeletion Successful!!\n");
  free(str);
  printf("\033[1;32m# LOG:\033[0m\tConverting Dicitonary into a string....\n");
  str = DictionaryToString(D);
  printf("\033[1;32m# LOG:\033[0m\tConversion COMPLETE!!!\n");
  printf("%s", str);
  printf("\033[1;32m# LOG:\033[0m\tInserting fifth entry...\n");
  insert(D, "second", "YEET");
  printf("\033[1;32m# LOG:\033[0m\tInserted woop!!\n");
  free(str);
  printf("\033[1;32m# LOG:\033[0m\tConverting Dicitonary into a string....\n");
  str = DictionaryToString(D);
  printf("\033[1;32m# LOG:\033[0m\tConversion COMPLETE!!!\n");
  printf("%s", str);
  printf("\033[1;32m# LOG:\033[0m\tFreeing Dictionary....\n");
  freeDictionary(&D);
  printf("\033[1;32m# LOG:\033[0m\tDictionary Freed WOOT!!\n");
  free(str);
  printf("\033[1;32m# LOG:\033[0m\tConverting Dicitonary into a string....\n");
  str = DictionaryToString(D);
  printf("\033[1;32m# LOG:\033[0m\tConversion COMPLETE!!!\n");
  printf("%s", str);
  return 0;
}

void delay(int number_of_seconds) {
  // Converting time into milli_seconds
  int milli_seconds = 1000 * number_of_seconds;

  // Stroing start time
  clock_t start_time = clock();

  // looping till required time is not acheived
  while (clock() < start_time + milli_seconds)
    ;
}
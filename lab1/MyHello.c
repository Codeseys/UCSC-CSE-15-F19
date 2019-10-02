// Hello.c
// Baladithya Balamurugan
// CruzId: bbalamur
// Class: CSE-15-1
// Date: 10/1/19
// Prints a Custom Message to stdout
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define AUTHOR "Codeseys"

int main(){
 time_t t = time(NULL);
 struct tm tm = *localtime(&t);
 printf("Yeet Yeet it's %s running this program at %d-%d-%d %d:%d:%d\n", AUTHOR, tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
 return EXIT_SUCCESS;
}
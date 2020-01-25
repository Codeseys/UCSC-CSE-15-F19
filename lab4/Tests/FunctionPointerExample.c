//-----------------------------------------------------------------------------
// FunctionPointerExamples.c
// Examples in the use of function pointers
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

// Define fptr_t type
typedef double (*fptr_t)(double, double);

double add(double x, double y)
{
    return x + y;
}

double sub(double x, double y)
{
    return x - y;
}

double mult(double x, double y)
{
    return x * y;
}

double apply(fptr_t fp, double x, double y)
{
    return fp(x, y);
}

int main()
{

    fptr_t fp; // same as: double (*fp)(double, double)

    // Use fp to call functions.
    fp = add;
    printf("%.1f\n", fp(1.0, 2.0)); // prints 3.0
    fp = sub;
    printf("%.1f\n", fp(3.0, 4.0)); // prints -1.0
    fp = mult;
    printf("%.1f\n\n", fp(5.0, 6.0)); // prints 30.0

    // Use function apply() to call functions.
    printf("%.1f\n", apply(add, 1.0, 2.0));    // prints 3.0
    printf("%.1f\n", apply(sub, 3.0, 4.0));    // prints -1.0
    printf("%.1f\n\n", apply(mult, 5.0, 6.0)); // prints 30.0

    // Use 4 more variables of type fptr_t.
    fptr_t fp1, fp2, fp3, temp;
    fp1 = add;
    fp2 = sub;
    fp3 = mult;
    printf("%.1f\n", fp1(fp2(1.0, 2.0), fp3(3.0, 4.0)));   // prints 11.0
    printf("%.1f\n", fp2(fp3(1.0, 2.0), fp1(3.0, 4.0)));   // prints -5.0
    printf("%.1f\n\n", fp3(fp1(1.0, 2.0), fp2(3.0, 4.0))); // prints -3.0

    // Function pointer variables can be re-assigned.
    temp = fp1;                                            // now temp = add
    fp1 = fp2;                                             // now fp1 = sub
    fp2 = fp3;                                             // now fp2 = mult
    fp3 = temp;                                            // now fp3 = add
    printf("%.1f\n", fp1(fp2(1.0, 2.0), fp3(3.0, 4.0)));   // prints -5.0
    printf("%.1f\n", fp2(fp3(1.0, 2.0), fp1(3.0, 4.0)));   // prints -3.0
    printf("%.1f\n\n", fp3(fp1(1.0, 2.0), fp2(3.0, 4.0))); // prints 11.0

    // Names of defined functions are constant pointers and cannot be reassigned.
    // add = fp1; // uncomment for syntax error

    // Functon pointers contain addresses of blocks within the code segment.
    printf("some addresses within the code segment:\n");
    printf("%p\n", fp1);
    printf("%p\n", fp2);
    printf("%p\n", fp3);
    printf("%p\n", sub);
    printf("%p\n", mult);
    printf("%p\n", add);
    printf("%p\n\n", apply);

    // Function pointers cannot be dereferenced, but they can be cast as other
    // types of pointers, and then dereferenced.  Here we cast fp1 as the type
    // pointer-to-unsigned-long, then follow the pointer and print out the
    // value at that location (in hexadecimal).  In this way we can see some
    // of the bytes (actually 8 bytes) in the code segment.
    printf("some contents of the code segment:\n");
    printf("%lx\n\n", *((unsigned long *)fp1));

    // Function pointer variables themselves, being local variables in a
    // function, are part of stack memory.
    printf("some addresses within stack memory:\n");
    printf("%p\n", &fp1);
    printf("%p\n", &fp2);
    printf("%p\n\n", &fp3);

    // The code segment should never be accessed from within a program, either
    // read from (as above), and especially never written to. As usual the
    // compiler will not prevent you from trying to do bad things like this.
    // Below is an attempt to overwite an area of memory containing program
    // instructions. It will compile, but fortunately it results in a
    // segmentation fault.
    // *((unsigned long*)fp1) = 6;  // uncomment for (probably) a seg-fault

    return EXIT_SUCCESS;
}
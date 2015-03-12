/* Copyright (c) 2015 Medicine Yeh */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <string.h>     /* For memcpy */
void printArray(int *values, int size);
int compare (const void * a, const void * b);

#define glue(x,y) x ## y
/* inline function with lambda macro definition */
#define lambda_1(value, size, lambda_function) do {\
    int compare_ lambda_function;\
    qsort(value, 6, sizeof(int), compare_);\
}while(0)

#define lambda_2(value, size, arg1, arg2, lambda_function) do {\
    int compare_ (const void * arg1, const void * arg2) {lambda_function;};\
    qsort(value, 6, sizeof(int), compare_);\
}while(0)

#define lambda_3(value, size, lambda_function) do {\
    int compare_ (const void * a, const void * b) {lambda_function;};\
    qsort(value, 6, sizeof(int), compare_);\
}while(0)

int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

void printArray(int *values, int size)
{
    int n;

    for (n = 0; n < 6; n++)
        printf ("%d ", values[n]);
    printf("\n");
}

int main()
{
    int values[6] = {0};
    int values_2[] = { 40, 10, 100, 90, 20, 25 };
    
    memcpy(values, values_2, 6 * sizeof(int)); //Initialize array
    qsort(values, 6, sizeof(int), compare); //Sort
    printArray(values, 6); //Print

    memcpy(values, values_2, 6 * sizeof(int)); //Initialize array
    lambda_1(values, 6, (const void * a, const void * b) {return ( *(int*)a + *(int*)b );});
    printArray(values, 6);

    memcpy(values, values_2, 6 * sizeof(int)); //Initialize array
    lambda_2(values, 6, a, b, return (*(int*)a - *(int*)b););
    printArray(values, 6);

    memcpy(values, values_2, 6 * sizeof(int)); //Initialize array
    lambda_3(values, 6, return ( *(int*)a - *(int*)b ););
    printArray(values, 6);

    memcpy(values, values_2, 6 * sizeof(int)); //Initialize array
    lambda_2(values, 6, a, b, 
        if (*(int*)a > *(int*)b) return 1;
        else return -1;
        );
    printArray(values, 6);

    return 0;
}



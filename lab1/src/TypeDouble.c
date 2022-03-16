#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "TypeInfo.h"
#include "SqrMatrix.h"

static void print(void* value)
{
    printf("%lf", *(double*)value);
}

static void *input(void* value)
{
    double *ret = malloc(sizeof(double));
    scanf("%lf", ret);
    return ret;
}

static void* sum(void* a, void* b)
{
    double *c = malloc(sizeof(double));
    *c = *(double*)a + *(double*)b;
    return c;
}

static void* mult(void* a, void* b)
{
    double *c = malloc(sizeof(double));
    *c = *(double*)a * *(double*)b;
    return c;
}

static void* negative(void* value)
{
    double *ret = malloc(sizeof(double));
    *ret = -(*(double*)value);
    return ret;
}

TypeInfo TypeInfoDouble()
{
    static TypeInfo typeInfo = {NULL};

    if (typeInfo.prvt == NULL)
    {
        double *zero = malloc(sizeof(double));
        double *one = malloc(sizeof(double));

        *zero = 0;
        *one = 1;

        typeInfo = TypeInfoInit(sizeof(double), &print, &input, &sum, &mult, &negative, zero, one);
    }

    return typeInfo;
}

SqrMatrix SqrMatrixInitDouble(size_t size)
{   
    SqrMatrix matrix = SqrMatrixInit(TypeInfoDouble(), size);
    return matrix;
}

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "TypeInfo.h"
#include "SqrMatrix.h"
#include "TypeComplex.h"

const Complex COMPLEX_ZERO = {0, 0};
const Complex COMPLEX_ONE = {1, 0};

Complex ComplexPlus(Complex a, Complex b)
{
    Complex c = {a.re + b.re, a.im + b.im};
    return c;
}

Complex ComplexMult(Complex a, Complex b)
{
    Complex c = {a.re * b.re - a.im * b.im , a.im * b.re + a.re * b.im};
    return c;
}

Complex ComplexNegative(Complex num)
{
    Complex ret = {-num.re, -num.im};
    return ret;
}

Complex ComplexInput()
{
    Complex num;
    scanf("%lf %lf", &num.re, &num.im);
    return num;
}

void ComplexPrint(Complex num)
{
    printf("%lf + (%lf * i)", num.re, num.im);
}

//----------------------------------------------funcs for TypeInfo-------------------------------------
static void print(void* value)
{
    ComplexPrint(*(Complex*)value);
}

static void *input(void* value)
{
    Complex *ret = malloc(sizeof(Complex));
    *ret = ComplexInput();
    return ret;
}

static void *sum(void* a, void* b)
{
    Complex *c = malloc(sizeof(Complex));
    *c = ComplexPlus(*(Complex*)a, *(Complex*)b);
    return c;
}

static void *mult(void* a, void* b)
{
    Complex *c = malloc(sizeof(Complex));
    *c = ComplexMult(*(Complex*)a, *(Complex*)b);
    return c;
}

static void *negative(void* value)
{
    Complex *ret = malloc(sizeof(Complex));
    *ret = ComplexNegative(*(Complex*)value);
    return ret;
}

TypeInfo TypeInfoCompl()
{
    static TypeInfo typeInfo = {NULL};

    if (typeInfo.prvt == NULL)
    {
        Complex *zero = malloc(sizeof(Complex));
        Complex *one = malloc(sizeof(Complex));

        *zero = COMPLEX_ZERO;
        *one = COMPLEX_ONE;

        typeInfo = TypeInfoInit(sizeof(Complex), &print, &input, &sum, &mult, &negative, zero, one);
    }

    return typeInfo;
}

SqrMatrix SqrMatrixInitCompl(size_t size)
{   
    SqrMatrix matrix = SqrMatrixInit(TypeInfoCompl(), size);
    return matrix;
}

SqrMatrix SqrMatrixComplZero(size_t size)
{
    return SqrMatrixZero(TypeInfoCompl(), size);
}

SqrMatrix SqrMatrixComplOne(size_t size)
{
    return SqrMatrixOne(TypeInfoCompl(), size);
}
//----------------------------------------------------------------------------------------

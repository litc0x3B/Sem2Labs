#pragma once

#include "SqrMatrix.h"


typedef struct Complex
{   
    double re;
    double im;
} Complex;

extern const Complex COMPLEX_ZERO;
extern const Complex COMPLEX_ONE;

Complex ComplexPlus(Complex a, Complex b);
Complex ComplexMult(Complex a, Complex b);
Complex ComplexNegative(Complex num);

Complex ComplexInput();
void ComplexPrint(Complex num);

SqrMatrix SqrMatrixInitCompl(size_t size);
SqrMatrix SqrMatrixComplZero(size_t size);
SqrMatrix SqrMatrixComplOne(size_t size);
TypeInfo TypeInfoCompl();




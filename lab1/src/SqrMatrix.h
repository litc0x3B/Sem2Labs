#pragma once
#include "TypeInfo.h"

typedef struct SqrMatrix{
    void* prvt;
} SqrMatrix;

//Constructor and destructor
SqrMatrix SqrMatrixInit(TypeInfo typeInfo, size_t size);
void SqrMatrixFree(SqrMatrix matrix);
SqrMatrix SqrMatrixZero(TypeInfo typeInfo, size_t size);
SqrMatrix SqrMatrixOne(TypeInfo typeInfo, size_t size);

//Getters
size_t SqrMatrixGetSize(SqrMatrix matrix);
TypeInfo SqrMatrixGetType(SqrMatrix matrix);
void* SqrMatrixGetValue(SqrMatrix matrix, size_t i, size_t j);

//Setters
void SqrMatrixSetValue(SqrMatrix matrix, void* value, size_t i, size_t j);
void SqrMatrixSetValues(SqrMatrix matrix, void **values);

//Output/Input
void SqrMatrixPrint(SqrMatrix matrix);
void SqrMatrixInput(SqrMatrix matrix);

//Operations
SqrMatrix SqrMatrixSum(SqrMatrix a, SqrMatrix b);
SqrMatrix SqrMatrixMult(SqrMatrix a, SqrMatrix b);
SqrMatrix SqrMatrixMultNum(SqrMatrix matrix, void *num);
SqrMatrix SqrMatrixNeg(SqrMatrix matrix);
SqrMatrix SqrMatrixCpy(SqrMatrix src);


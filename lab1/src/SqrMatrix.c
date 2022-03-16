#include "TypeInfo.h"
#include "SqrMatrix.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>


typedef struct SqrMatrixPrivate
{
    void **storage;
    size_t size;
    TypeInfo typeInfo;
} SqrMatrixPrivate;

//-----------------------------Constructor and destructor---------------------------------------
SqrMatrix SqrMatrixInit(TypeInfo typeInfo, size_t size)
{
    SqrMatrixPrivate *prvt = malloc(sizeof(SqrMatrixPrivate));

    prvt->typeInfo = typeInfo;
    prvt->size = size;

    prvt->storage = malloc(size * sizeof(void *));

    for (size_t i = 0; i < size; i++)
    {
        prvt->storage[i] = calloc(size, TypeInfoGetSize(typeInfo));
    }

    SqrMatrix matrix;
    matrix.prvt = prvt;
    return matrix;
}

SqrMatrix SqrMatrixOne(TypeInfo typeInfo, size_t size)
{
    SqrMatrix matrix = SqrMatrixInit(typeInfo, size);

    for (size_t i = 0; i < SqrMatrixGetSize(matrix); i++)
    {
        for (size_t j = 0; j < SqrMatrixGetSize(matrix); j++)
        {
            if (i == j)
            {
                SqrMatrixSetValue(matrix, TypeInfoOne(SqrMatrixGetType(matrix)), i, j);
            }
            else 
            {
                SqrMatrixSetValue(matrix, TypeInfoZero(SqrMatrixGetType(matrix)), i, j);
            }
            
        }
    }

    return matrix;
}

SqrMatrix SqrMatrixZero(TypeInfo typeInfo, size_t size)
{
    SqrMatrix matrix = SqrMatrixInit(typeInfo, size);

    for (size_t i = 0; i < SqrMatrixGetSize(matrix); i++)
    {
        for (size_t j = 0; j < SqrMatrixGetSize(matrix); j++)
        {
            SqrMatrixSetValue(matrix, TypeInfoZero(SqrMatrixGetType(matrix)), i, j);
        }
    }

    return matrix;
}

void SqrMatrixFree(SqrMatrix matrix)
{
    SqrMatrixPrivate *prvt = matrix.prvt;

    for (size_t i = 0; i < prvt->size; i++)
        free(prvt->storage[i]);

    free(prvt->storage);
    free(prvt);
}

//--------------------------------Getters-----------------------------
void* SqrMatrixGetValue(SqrMatrix matrix, size_t i, size_t j) 
{
    if (i < 0 || i >= SqrMatrixGetSize(matrix) || j < 0 || j >= SqrMatrixGetSize(matrix))
    {
        raise(SIGABRT); //Index out of range
    }

    char **storage = (char **)(((SqrMatrixPrivate*)(matrix.prvt))->storage);
    return &storage[i][j * TypeInfoGetSize(SqrMatrixGetType(matrix))];
}

size_t SqrMatrixGetSize(SqrMatrix matrix) 
{
    return ((SqrMatrixPrivate *)(matrix.prvt))->size;
}

TypeInfo SqrMatrixGetType(SqrMatrix matrix) 
{
    return ((SqrMatrixPrivate *)(matrix.prvt))->typeInfo;
}

//-------------------------------------Setters--------------------------------
void SqrMatrixSetValue(SqrMatrix matrix, void *value, size_t i, size_t j)
{
    if (i < 0 || i >= SqrMatrixGetSize(matrix) || j < 0 || j >= SqrMatrixGetSize(matrix))
    {
        raise(SIGABRT); //Index out of range
    }

    SqrMatrixPrivate *prvt = matrix.prvt;

    size_t typeSize = TypeInfoGetSize(prvt->typeInfo);
    char **arr = (char **)(prvt->storage);
    memcpy(&arr[i][j * typeSize], value, typeSize);
}

void SqrMatrixSetValues(SqrMatrix matrix, void **values)
{
    for (size_t i = 0; i < SqrMatrixGetSize(matrix); i++) 
    {
        for (size_t j = 0; j < SqrMatrixGetSize(matrix); j++){
            SqrMatrixSetValue(matrix, &((char**)values)[i][j * TypeInfoGetSize(SqrMatrixGetType(matrix))], i, j);
        }
    }
}

//------------------------------------I/O------------------------------------

//redo this func later
void SqrMatrixPrint(SqrMatrix matrix)
{
    SqrMatrixPrivate *prvt = matrix.prvt;

    size_t typeSize = TypeInfoGetSize(prvt->typeInfo);

    for (size_t i = 0; i < prvt->size; i++)
    {

        for (size_t j = 0; j < prvt->size; j++)
        {

            char **arr = (char **)(prvt->storage);
            TypeInfoPrint(prvt->typeInfo, &arr[i][j * typeSize]);
            printf("\t");
        }

        printf("\n");
    }
}

void SqrMatrixInput(SqrMatrix matrix)
{
    for (size_t i = 0; i < SqrMatrixGetSize(matrix); i++)
    {
        for (size_t j = 0; j < SqrMatrixGetSize(matrix); j++)
        {
            void* input = TypeInfoInput(SqrMatrixGetType(matrix));
            SqrMatrixSetValue(matrix, input, i, j);
            free(input);
        }
    }
}


//---------------------------------Operations--------------------------------------------
SqrMatrix SqrMatrixSum(SqrMatrix a, SqrMatrix b) 
{
    if (!TypeInfoCompare(SqrMatrixGetType(a), SqrMatrixGetType(b)))
    {
        raise(SIGABRT); //Attemp to make calculations with matrices of differnt types
    }

    if (SqrMatrixGetSize(a) != SqrMatrixGetSize(b))
    {
        raise(SIGABRT); //Attemp to calulate sum of matrices with different sizes
    }
    
    SqrMatrix c = SqrMatrixInit(SqrMatrixGetType(a), SqrMatrixGetSize(a));

    for (size_t i = 0; i < SqrMatrixGetSize(c); i++)
    {
        for (size_t j = 0; j < SqrMatrixGetSize(c); j++) 
        {   
            void *sum = TypeInfoSum(SqrMatrixGetType(c), SqrMatrixGetValue(a, i, j), SqrMatrixGetValue(b, i, j));
            SqrMatrixSetValue(c, sum, i, j);
            free(sum);
        }
    }

    return c;
}


SqrMatrix SqrMatrixMultNum(SqrMatrix matrix, void *num)
{
    SqrMatrix ret = SqrMatrixInit(SqrMatrixGetType(matrix), SqrMatrixGetSize(matrix));

    for (size_t i = 0; i < SqrMatrixGetSize(matrix); i++)
    {
        for (size_t j = 0; j < SqrMatrixGetSize(matrix); j++)
        {
            void* mult = TypeInfoMult(SqrMatrixGetType(matrix), SqrMatrixGetValue(matrix, i, j), num);
            SqrMatrixSetValue(ret, mult, i, j);
            free(mult);
        }
    }

    return ret;
}

SqrMatrix SqrMatrixMult(SqrMatrix a, SqrMatrix b) 
{
    if (!TypeInfoCompare(SqrMatrixGetType(a), SqrMatrixGetType(b)))
    {
        raise(SIGABRT); //Attemp to make calculations with matrices of differnt types
    }

    if (SqrMatrixGetSize(a) != SqrMatrixGetSize(b))
    {
        raise(SIGABRT); //Attemp to calulate multiplication of matrices with different sizes
    }
    
    SqrMatrix c = SqrMatrixInit(SqrMatrixGetType(a), SqrMatrixGetSize(a));

    for (size_t i = 0; i < SqrMatrixGetSize(a); i++)
    {
        for (size_t j = 0; j < SqrMatrixGetSize(b); j++) 
        {   
            void *sum = TypeInfoZero(SqrMatrixGetType(c));

            for (size_t k = 0; k < SqrMatrixGetSize(c); k++)
            {
                void *mult = TypeInfoMult(SqrMatrixGetType(c), SqrMatrixGetValue(a, i, k), SqrMatrixGetValue(b, k, j));
                void *newSum = TypeInfoSum(SqrMatrixGetType(c), sum, mult);

                if (sum != TypeInfoZero(SqrMatrixGetType(c)))
                {
                    free(sum);
                }
                free(mult);
                sum = newSum;
            }

            SqrMatrixSetValue(c, sum, i, j);
            free(sum);
        }
    }

    return c;
}

SqrMatrix SqrMatrixNeg(SqrMatrix matrix)
{
    SqrMatrix ret = SqrMatrixInit(SqrMatrixGetType(matrix),SqrMatrixGetSize(matrix));

    for (size_t i = 0; i < SqrMatrixGetSize(matrix); i++)
    {
        for (size_t j = 0; j < SqrMatrixGetSize(matrix); j++) 
        {   
            void* value = SqrMatrixGetValue(matrix, i, j);
            void* negative = TypeInfoNegative(SqrMatrixGetType(matrix), value);
            SqrMatrixSetValue(ret, negative, i, j);
            free(negative);
        }
    }

    return ret;
}
//--------------------------------------------------------Copy----------------------------------------
SqrMatrix SqrMatrixCpy(SqrMatrix src)
{
    SqrMatrix dest = SqrMatrixInit(SqrMatrixGetType(src), SqrMatrixGetSize(src));

    for (size_t i = 0; i < SqrMatrixGetSize(src); i++)
    {
        for (size_t j = 0; j < SqrMatrixGetSize(src); j++) 
        {   
            SqrMatrixSetValue(dest, SqrMatrixGetValue(src, i, j), i, j);
        }
    }

    return dest;
}

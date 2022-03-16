#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SqrMatrix.h"
#include "TypeComplex.h"
#include "TypeDouble.h"
#include "TypeInfo.h"

const int MAX = 1000;
const int DIVIDER = 100;

void printMult(SqrMatrix matrix1, SqrMatrix matrix2)
{
    printf("A * B: \n");
    SqrMatrix result = SqrMatrixMult(matrix1, matrix2);
    SqrMatrixPrint(result);
    SqrMatrixFree(result);
    printf("\n");
}

void printMultNum(SqrMatrix matrix, void* num)
{
    printf("a * A: \n");
    SqrMatrix result = SqrMatrixMultNum(matrix, num);
    SqrMatrixPrint(result);
    SqrMatrixFree(result);
    printf("\n");
}

void printSum(SqrMatrix matrix1, SqrMatrix matrix2)
{
    printf("A + B: \n");
    SqrMatrix result = SqrMatrixSum(matrix1, matrix2);
    SqrMatrixPrint(result);
    SqrMatrixFree(result);
    printf("\n");
}

void printNegative(SqrMatrix matrix)
{
    printf("-A: \n");
    SqrMatrix result = SqrMatrixNeg(matrix);
    SqrMatrixPrint(result);
    SqrMatrixFree(result);
    printf("\n");
}

void printMultByOne(SqrMatrix matrix)
{
    SqrMatrix one = SqrMatrixOne(SqrMatrixGetType(matrix), SqrMatrixGetSize(matrix));
    SqrMatrix result = SqrMatrixMult(matrix, one);

    printf("A * E: \n");
    SqrMatrixPrint(result);
    printf("\n");

    SqrMatrixFree(one);
    SqrMatrixFree(result);
}

void printMultByZero(SqrMatrix matrix)
{
    SqrMatrix zero = SqrMatrixZero(SqrMatrixGetType(matrix), SqrMatrixGetSize(matrix));
    SqrMatrix result = SqrMatrixMult(matrix, zero);

    printf("A * Z: \n");
    SqrMatrixPrint(result);
    printf("\n");

    SqrMatrixFree(result);
    SqrMatrixFree(zero);
}

void generateRandomDouble(SqrMatrix matrix)
{
    for (size_t i = 0; i < SqrMatrixGetSize(matrix); i++)
    {
        for (size_t j = 0; j < SqrMatrixGetSize(matrix); j++)
        {
            double num = (double)(rand() % MAX) / DIVIDER;
            SqrMatrixSetValue(matrix, &num, i, j);
        }
    }
}

void generateRandomComplex(SqrMatrix matrix)
{
    for (size_t i = 0; i < SqrMatrixGetSize(matrix); i++)
    {
        for (size_t j = 0; j < SqrMatrixGetSize(matrix); j++)
        {
            Complex num = {(double)(rand() % MAX) / DIVIDER, (double)(rand() % MAX) / DIVIDER};
            SqrMatrixSetValue(matrix, &num, i, j);
        }
    }
}


void AutoTest()
{
    for (int i = 0; i < 4; i++)
    {
        printf("***********************************************************\n");
        printf("Test #%d\n", i + 1);

        SqrMatrix matrix1;
        SqrMatrix matrix2;
        void* num;

        int size = rand() % 7 + 2;

        if (i % 2)
        {
            matrix1 = SqrMatrixInitCompl(size);
            matrix2 = SqrMatrixInitCompl(size);

            Complex numCompl = {(double)(rand() % MAX) / DIVIDER, (double)(rand() % MAX) / DIVIDER};
            num = &numCompl;
            generateRandomComplex(matrix1);
            generateRandomComplex(matrix2);
        }
        else 
        {
            matrix1 = SqrMatrixInitDouble(size);
            matrix2 = SqrMatrixInitDouble(size);

            double numDouble= (double)(rand() % MAX) / DIVIDER;
            num = &numDouble;
            generateRandomDouble(matrix1);
            generateRandomDouble(matrix2);
        }

        printf("A:\n");
        SqrMatrixPrint(matrix1);
        printf("\n");
        printf("B:\n");
        SqrMatrixPrint(matrix2);
        printf("\n");
        printf("a:\n");
        TypeInfoPrint(SqrMatrixGetType(matrix1), num);
        printf("\n\n");
        

        printMultNum(matrix1, num);
        printSum(matrix1, matrix2);
        printMult(matrix1, matrix2);
        printMultByOne(matrix1);
        printMultByZero(matrix1);

        SqrMatrixFree(matrix1);
        SqrMatrixFree(matrix2);
    }
}

void TestDouble()
{
    size_t size;

    printf("enter matrices size:\n");
    scanf("%zu", &size);
    SqrMatrix matrix1 = SqrMatrixInitDouble(size);
    SqrMatrix matrix2 = SqrMatrixInitDouble(size);

    printf("enter matrix A:\n");
    SqrMatrixInput(matrix1);

    printf("enter matrix B:\n");
    SqrMatrixInput(matrix2);

    printf("enter number a:\n");
    double num;
    scanf("%lf", &num);
    printf("\n");

    printMultNum(matrix1, &num);
    printSum(matrix1, matrix2);
    printMult(matrix1, matrix2);
    printMultByOne(matrix1);
    printMultByZero(matrix1);

    SqrMatrixFree(matrix1);
    SqrMatrixFree(matrix2);
}

void TestComplex()
{
    size_t size;

    printf("enter matrices size:\n");
    scanf("%zu", &size);
    SqrMatrix matrix1 = SqrMatrixInitCompl(size);
    SqrMatrix matrix2 = SqrMatrixInitCompl(size);

    printf("enter matrix A (format for an element: <Re> <Im>):\n");
    SqrMatrixInput(matrix1);

    printf("enter matrix B (format for an element: <Re> <Im>):\n");
    SqrMatrixInput(matrix2);

    printf("enter number a (format for an element: <Re> <Im>):\n");
    Complex num = ComplexInput();
    printf("\n");

    printMultNum(matrix1, &num);
    printSum(matrix1, matrix2);
    printMult(matrix1, matrix2);
    printMultByOne(matrix1);
    printMultByZero(matrix1);

    SqrMatrixFree(matrix1);
    SqrMatrixFree(matrix2);
}

int main()
{
    srand(time(NULL));
    while (1)
    {
        printf("1) auto test\n");
        printf("2) test matrix with real numbers\n");
        printf("3) test matrix with complex numbers\n");
        printf("4) exit\n");
        printf("Please, enter the command: ");

        int cmd;
        scanf("%d", &cmd);
        if (cmd == 1)
        {
            AutoTest();
        }
        else if (cmd == 2)
        {
            TestDouble();
        }
        else if (cmd == 3)
        {
            TestComplex();
        }
        else if (cmd == 4)
        {
            break;
        }
        else 
        {
            printf("Incorrect command");
        }
    }

    TypeInfoFree(TypeInfoDouble());
    TypeInfoFree(TypeInfoCompl());
}


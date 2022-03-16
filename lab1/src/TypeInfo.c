#include "TypeInfo.h"
#include <stdlib.h>

typedef struct TypeInfoPrivate
{
    size_t size;
    void (*print)(void *);
    void *(*input)();
    void *(*addition)(void *, void *);
    void *(*multiplication)(void *, void *);
    void *(*negative)(void *);
    void *zero;
    void *one;
} TypeInfoPrivate;

TypeInfo TypeInfoInit(
    size_t size,
    void (*print)(void *),
    void *(*input)(),
    void *(*addition)(void *, void *),
    void *(*multiplication)(void *, void *),
    void *(*negative)(void *),
    void *zero,
    void *one)
{
    TypeInfoPrivate *prvt = malloc(sizeof(TypeInfoPrivate));

    prvt->size = size;
    prvt->print = print;
    prvt->input = input;
    prvt->addition = addition;
    prvt->multiplication = multiplication;
    prvt->negative = negative;
    prvt->zero = zero;
    prvt->one = one;

    TypeInfo info;
    info.prvt = prvt;

    return info;
}

void TypeInfoFree(TypeInfo info)
{
    if (info.prvt != NULL)
    {
        free(TypeInfoZero(info));
        free(TypeInfoOne(info));
        free(info.prvt);
        info.prvt = NULL;
    }
}

void *TypeInfoSum(TypeInfo info, void *a, void *b)
{
    TypeInfoPrivate *prvt = info.prvt;
    return (*prvt->addition)(a, b);
}

void *TypeInfoMult(TypeInfo info, void *a, void *b)
{
    TypeInfoPrivate *prvt = info.prvt;
    return (*prvt->multiplication)(a, b);
}

void TypeInfoPrint(TypeInfo info, void *value)
{
    TypeInfoPrivate *prvt = info.prvt;
    (*prvt->print)(value);
}

void* TypeInfoInput(TypeInfo info)
{
    TypeInfoPrivate *prvt = info.prvt;
    return (*prvt->input)();
}

size_t TypeInfoGetSize(TypeInfo info)
{
    TypeInfoPrivate *prvt = info.prvt;
    return prvt->size;
}

void *TypeInfoNegative(TypeInfo info, void *value)
{
    TypeInfoPrivate *prvt = info.prvt;
    return (*prvt->negative)(value);
}

int TypeInfoCompare(TypeInfo info1, TypeInfo info2)
{
    return info1.prvt == info2.prvt;
}

void* TypeInfoZero(TypeInfo info)
{
    return ((TypeInfoPrivate*)info.prvt)->zero;
}

void* TypeInfoOne(TypeInfo info)
{
    return ((TypeInfoPrivate*)info.prvt)->one;
}

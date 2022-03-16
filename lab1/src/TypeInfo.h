#pragma once
#include <stddef.h>

typedef struct TypeInfo {
    void* prvt;
} TypeInfo;

TypeInfo TypeInfoInit(
    size_t size,
    void (*print)(void *),
    void *(*input)(),
    void *(*addition)(void *, void *),
    void *(*multiplication)(void *, void *),
    void *(*negative)(void *),
    void *zero,
    void *one);
    
void TypeInfoFree(TypeInfo info);

void *TypeInfoSum(TypeInfo info, void *a, void *b);
void *TypeInfoMult(TypeInfo info, void *a, void *b);
void *TypeInfoNegative(TypeInfo info, void *value);

void TypeInfoPrint(TypeInfo info, void *value);
void* TypeInfoInput(TypeInfo info);

size_t TypeInfoGetSize(TypeInfo info);

void* TypeInfoZero(TypeInfo info);
void* TypeInfoOne(TypeInfo info);

int TypeInfoCompare(TypeInfo info1, TypeInfo info2);
#ifndef LIBSTACK_H
#define LIBSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "common.h"
#define DEFAULT_STACK_CAPACITY 128

typedef struct {
    void* Data;
    int32_t Count;
    size_t  Capacity;
    uint32 SizeofType;
} stack;


#define CAST_TO_VALUE(Type, Value) *(Type*)(Value);
//#define CAST_TO_PTR(Type, Value) (Type*)(Value);
void StackInit(stack* Stack, uint32 SizeofType);
void StackPush(stack* Stack, void* Data);
void* StackPop(stack* Stack);
void* StackTop(stack* Stack);
bool32 StackIsEmpty(stack* Stack);
void StackClear(stack* Stack);
void StackFree(stack* Stack);
int32 StackLen(stack* Stack);
size_t StackCapacity(stack* Stack);

#endif// LIBSTACK_H

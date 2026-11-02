#ifndef LIBDA_H
#define LIBDA_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "common.h"
#define DEFAULT_DA_CAPACITY 128 // inital capacity of dynamic array

//dynamic arrays
typedef struct {
    void* Data;
    int32_t Size;
    size_t  Capacity;
    uint32 SizeofType;
} list;

// TODO: implement pointer storing in list
#define CAST_TO_VALUE(Type, Value) *(Type*)(Value);
//#define CAST_TO_PTR(Type, Value) (Type*)(Value);
void ListInit(list* List, uint32 SizeofType);
void ListPushback(list* List, void* Data);
void ListPushfront(list* List, void* Data);
void ListPushat(list* List,uint32 Index, void* Data);
void ListPopback(list* List);
void ListRemoveat(list* List, uint32 Index); 
void ListClear(list* List);
void* ListGet(list* List, uint32 Index);
int32 ListLen(list* List);
size_t ListCapacity(list* List);
bool32 ListIsEmpty(list* List);
void Shrink(list* List);
void ListFree(list* List);


#endif

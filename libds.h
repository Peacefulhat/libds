/*

libds is a  data structure library

currently supported library:

dynamic arrays (not finished):

#define CAST_TO_VALUE(Type, Value) *(Type*)(Value);
  dereference the pointer to get the value

#define CAST_TO_PTR(Type, Value) (Type*)(Value);
  used to retrive the address of the


void ListInit(list* List, uint32 SizeofType, size_t InitialCapacity);
  Initalize with some capacity and allocate memory for some custom/premitive type) based on SizeofType variable.

void ListPushback(list* List, void* Data);
  add a element at the end of list. O(1)

void Popback(list* List);
  removes the last element in the list. O(1)

void Clear(list* List);
  Reset size but keep allocated memory. capacity remains unchanged. O(1)

void* ListGet(list* List, uint32 Index);
  gets the element at index. O(1);

void Set(list* List, uint32 Index, void* Data);
  replaces element at index with provided element. O(1)

int32 Len(list* List);
  returns the size of list. O(1)

size_t Capacity(list* List);
  returns the capacity of list. O(1)

bool32 IsEmpty(list* List);
  Returns a boolean indicating whether the array has zero elements.

static void Grow(list* List, uint32 ExpectedCapacity);
  increase the capacity of the list. O(n).

void Shrink(list* List, uint32 ExpectedCapacity);
  shrink the capacity of the list. O(n).
 
void ListHeapDestory(list* List);
  deallocates the allocated void* Data in list. O(1)
 
hashtbale (not implemented yet)

*/

#ifndef LIBDS_H
#define LIBDS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// common type alias
typedef  int32_t  int32;
typedef  int      int32;
typedef  int64_t  int64;
typedef  uint32_t uint32;
typedef  uint32_t uint32;
typedef  float    float32;
typedef  double   float64;
typedef  int32    bool32;

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
void ListInit(list* List, uint32 SizeofType, size_t InitialCapacity);
void ListPushback(list* List, void* Data);
void Popback(list* List);
void Clear(list* List);
void* ListGet(list* List, uint32 Index);
void Set(list* List, uint32 Index, void* Data);
int32 Len(list* List);
size_t Capacity(list* List);
bool32 IsEmpty(list* List);
void Shrink(list* List, uint32 ExpectedCapacity);
void ListHeapDestory(list* List);



/*
TODO: implement
void Pushfront(list* List, void* Data); // add element at the front of list
void Pushat(list* List,uint32 Index, void* Data); // add element at given index
void Remove(list* List, uint32 Index); // removes element at given index
*/

#endif

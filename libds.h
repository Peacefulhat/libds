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

void ListPushfront(list* List, void* Data);
  add element at the front of list O(n)

void ListPushat(list* List,uint32 Index, void* Data);
  add element at given index O(n)

void ListRemove(list* List, uint32 Index);
  removes element at given index O(n)

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
#include "libda.h" // dynamic array
#include "libstr.h" // strings
#include "libstack.h"
#endif

#include "libds.h"
#define DA_INI_CAP 5
void ListInit(list* List, uint32 SizeofType, size_t InitialCapacity)
{
    if(List == NULL) {
        printf("Init(): List Invalid address\n");
        return;
    }
    List->Size = 0;
    List->Capacity= InitialCapacity;
    List->SizeofType = SizeofType;
    List->Data = malloc(SizeofType * List->Capacity);
    if(List->Data == NULL) {
        List->Data = NULL;
        List->Size = 0;
        List->Capacity = 0;
        List->SizeofType = 0;
        printf("Init(): Memory allocation failed\n");
        return;
    }
}

static void Grow(list* List)
{
    if((List == NULL)) {
        printf("Grow(): Invalid pointer `List`");
        return;
    }

    if(List->Capacity == 0) {
        List->Capacity = DA_INI_CAP;
    }
    while(List->Size >= List->Capacity) {
        List->Capacity *= 2;
    }
    List->Data = realloc(List->Data, List->Capacity * List->SizeofType);
    if(List->Data == NULL) {
        printf("Grow(): List Data realloc failed\n");
    }
}

void ListPushback(list* List, void* Data)
{
    if(Data == NULL ||(List == NULL)) {
        printf("Pushback(): List or Data pointer was NULL\n");
        return;
    }

    if(List->Size >= List->Capacity) {
        Grow(List);
    }

    if(List->Data) {
        char* Temp = List->Data + (List->SizeofType * List->Size);
        for(int Byte = 0; Byte < List->SizeofType; ++Byte ) {
            Temp[Byte] = *(char*)(Data + Byte);
        }
        List->Size += 1;
    }
}

void Popback(list* List)
{
    if((List == NULL && List->Data)) {
        printf("Popback(): Invalid `List` \n");
        return;
    }

    if(List->Size > 0) {
        List->Size--;
    }
}

void Clear(list* List)
{
    if(List == NULL) {
        printf("Clear(): Invalid `List` \n");
        return;
    }
    List->Size = 0;
}

void* ListGet(list* List, uint32 Index)
{
    if((List == NULL && List->Data)) {
        printf("Get(): List Invalid address\n");
        return NULL;
    }
    return (List->Data + (List->SizeofType * Index));
}

void Set(list* List, uint32 Index, void* Data)
{
    if((List == NULL && List->Data)|| Data == NULL) {
        printf("Set(): List or Data Invalid address\n");
        return;
    }
    char* Temp = List->Data + (Index * List->SizeofType);
    for(int32 Byte = 0; Byte < List->SizeofType; ++Byte) {
        Temp[Byte] = *(char*)(Data + Byte);
    }

}

int32 Len(list* List)
{
    if((List == NULL)) {
        printf("Len(): List, Invalid address");
        return(-1);// invalid length, becasue of invalid List.
    }
    return(List->Size);
}

size_t Capacity(list* List)
{
    if((List == NULL)) {
        printf("Capacity(): List, Invalid address");
        return(-1);// invalid length, becasue of invalid List.
    }
    return(List->Capacity);
}

bool32 IsEmpty(list* List)
{
    if((List == NULL)) {
        printf("IsEmpty(): List, Invalid address");
        return(-1);// invalid address, becasue of invalid List.
    }
    return List->Size == 0;
}


//Todo: auto shrink if we size is like half of capacity
void Shrink(list* List, uint32 ExpectedCapacity)
{

}

void ListHeapDestory(list* List)
{
    if((List != NULL && List->Data != NULL)) {
        free(List->Data);
        List->Size = 0;
        List->Capacity = 0;
        List->Data = NULL;
        return;
    }
    printf("ListHeapDestory(): already freed List");
}

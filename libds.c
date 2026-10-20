#include "libds.h"
#define DA_INI_CAP 16 // inital capacity of dynamic array

void ListInit(list* List, uint32 SizeofType)
{
    if(List == NULL) {
        printf("Init(): List Invalid address\n");
        return;
    }
    List->Size = 0;
    List->Capacity= DA_INI_CAP;
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

static void WriteBytes(void* Dest, void* Data, uint32 SizeofType, uint32 WriteIndex)
{
    if(Dest == NULL || Data == NULL) {
        printf("WriteBytes(): Invalid `Dest` or `Data`");
        return;
    }
    char* Temp = Dest + (SizeofType * WriteIndex);
    for(int Byte = 0; Byte < SizeofType; ++Byte ) {
        Temp[Byte] = *(char*)(Data + Byte);
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
        WriteBytes(List->Data, Data, List->SizeofType, List->Size);
        List->Size += 1;
    }
}


void ListPushfront(list* List, void* Data)
{
    if((List == NULL) || (Data == NULL)) {
        printf("ListPushFront(): Invalid `List` or `Data` \n");
        return;
    }
    if(List->Size == 0 && Data != NULL) {
        ListPushback(List, Data);
        return;
    }

    if(List->Size >= List->Capacity) {
        Grow(List);
    }

    // make space
    uint32 BytesToMove = List->SizeofType * List->Size;
    char* Temp = malloc(List->SizeofType * List->Capacity);
    memcpy(Temp + List->SizeofType, List->Data, BytesToMove);
    free(List->Data);
    List->Data = Temp;
    if(List->Data != NULL) {
        WriteBytes(List->Data, Data, List->SizeofType, 0 );
        List->Size += 1;
    }
}

void ListPushat(list* List,uint32 Index, void* Data)
{
    if((List == NULL) || (Data == NULL)) {
        printf("ListPushFront(): Invalid `List` or `Data` \n");
        return;
    }

    if(List->Size == 0 && Data != NULL) {
        ListPushback(List, Data);
        return;
    }

    if(List->Size >= List->Capacity) {
        Grow(List);
    }

    if((List->Size - Index) < 0) {
        return;

    }
    
    if(Index > List->Size){
        printf("Not a valid index: %d\n", Index);
        return;
    }

        int32 BytesToMoveRight = List->SizeofType * (List->Size - Index); // 0 based index
        int32 BytesOnLeft = List->SizeofType * ( Index + 1);
        char* Temp = malloc(List->SizeofType * List->Capacity);
        memcpy(Temp, List->Data, BytesOnLeft);
        memcpy(Temp + List->SizeofType * (Index + 1), List->Data + (List->SizeofType * Index), BytesToMoveRight);
        free(List->Data);
        List->Data = Temp;
        if(List->Data != NULL) {
            WriteBytes(List->Data, Data, List->SizeofType, Index);
            List->Size += 1;
        }


}



void ListPopback(list* List)
{
    if((List == NULL)) {
        printf("Popback(): Invalid `List` \n");
        return;
    }

    if(List->Size > 0 && List->Data != NULL) {
        List->Size--;
    }
}


void ListRemoveat(list* List, uint32 Index)
{
}

void ListClear(list* List)
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

int32 ListLen(list* List)
{
    if((List == NULL)) {
        printf("Len(): List, Invalid address");
        return(-1);// invalid length, becasue of invalid List.
    }
    return(List->Size);
}

size_t ListCapacity(list* List)
{
    if((List == NULL)) {
        printf("Capacity(): List, Invalid address");
        return(-1);// invalid length, becasue of invalid List.
    }
    return(List->Capacity);
}

bool32 ListIsEmpty(list* List)
{
    if((List == NULL)) {
        printf("IsEmpty(): List, Invalid address");
        return(-1);// invalid address, becasue of invalid List.
    }
    return List->Size == 0;
}


//Todo: use Shrink function.
void Shrink(list* List)
{
    if(List->Capacity >= 2 * List->Size){
        List->Capacity /= 2;
        List->Capacity++;
        char* Temp = malloc(List->Capacity * List->SizeofType);
        memcpy(Temp, List->Data, List->Size);
        free(List->Data);
        List->Data = Temp;
        return;
    }
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

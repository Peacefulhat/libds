#include "libstack.h"
// TODO: better error message
internal void Grow(stack* Stack)
{
    if(Stack == NULL) {
        printf("Grow(): Invalid pointer `Stack`");
        return;
    }

    if(Stack->Capacity == 0) {
        Stack->Capacity = DEFAULT_STACK_CAPACITY;
    }
    while(Stack->Count >= Stack->Capacity) {
        Stack->Capacity *= 2;
    }
    Stack->Data = realloc(Stack->Data, Stack->Capacity * Stack->SizeofType);
    if(Stack->Data == NULL) {
        printf("Grow(): Stack Data realloc failed\n");
    }
}

internal void StackShrink(stack* Stack) {
    if(Stack == NULL){
        printf("StackShrink: Not a valid pointer to Stack\n");
    }
    if(Stack->Count < (Stack->Capacity / 2)){
        Stack->Capacity /= 2 ;
        Stack->Data = realloc(Stack->Data, Stack->Capacity * Stack->SizeofType);
        if(Stack->Data == NULL){
            printf("Shrink: realloc failed for stack shrink\n");
        }
    }
}

internal void WriteBytes(void* Dest, void* Data, uint32 SizeofType, uint32 WriteIndex)
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


void StackInit(stack* Stack, uint32 SizeofType)
{
    if(Stack == NULL) {
        printf("StackInit: `Stack` was NULL");
        return;
    }
    Stack->Capacity = DEFAULT_STACK_CAPACITY;
    Stack->Count = 0;
    Stack->SizeofType = SizeofType;
    uint32 SizeInBytes = SizeofType * Stack->Capacity;
    Grow(Stack);
    if(Stack->Data == NULL) {
        Stack->Data = NULL;
        Stack->Count = 0;
        Stack->Capacity = 0;
        Stack->SizeofType = 0;
        printf("Init(): Memory allocation failed\n");
        return;
    }

}

void StackPush(stack* Stack, void* Data)
{
    if(Stack == NULL || Data == NULL ) {
        printf("StackPush: either provided `Data` or `Stack` was NULL");
        return;
    }

    if(Stack->Count >= Stack->Capacity) {
        Grow(Stack);
    }
    if(Stack->Data) {
        WriteBytes(Stack->Data, Data, Stack->SizeofType, Stack->Count);
        Stack->Count++;
    }
    StackShrink(Stack);
}

void* StackPop(stack* Stack)
{
    void* PopedValue = NULL;
    if(Stack == NULL || Stack->Data == NULL) {
        printf("StackPop: `Stack` or `Stack->Data` was NULL");
        return(PopedValue);
    }
    
    if(Stack->Count > 0) {
        PopedValue = Stack->Data + (Stack->SizeofType * (Stack->Count - 1));
        Stack->Count--;
    } else {
        printf("StackPop: Nothing to pop Stack is empty");
    }
    StackShrink(Stack);
    return (PopedValue);
}

void* StackTop(stack* Stack)
{
    void* Top = NULL;
    if(Stack == NULL || Stack->Data == NULL) {
        printf("StackTop: `Stack` or `Stack->Data` was NULL");
        return (Top);
    }

    if(Stack->Count > 0) {
        Top =  Stack->Data + (Stack->SizeofType * (Stack->Count - 1));
    }

    return(Top);
}
bool32 StackIsEmpty(stack* Stack)
{
    if(Stack == NULL) {
        printf("StackEmpty: Not a valid pointer to Stack\n");
        return (-1);
    }
    return (Stack->Count == 0);
}

void StackClear(stack* Stack)
{
    if(Stack == NULL) {
        printf("StackClear: Not a valid pointer to Stack\n");
        return;
    }
    Stack->Count = 0;
}

void StackFree(stack* Stack)
{
    if(Stack == NULL) {
        printf("StackFree: Not a valid pointer to Stack\n");
        return;
    }
    if(Stack->Data) {
        free(Stack->Data);
        Stack->Data = NULL;
        Stack->Count = 0;
        Stack->Capacity = 0;

    } else {
        printf("StackFree: Stack is Already freed\n");
    }
}

int32 StackLen(stack* Stack)
{
    if(Stack == NULL) {
        printf("StackLen: Not a valid pointer to Stack\n");
        return (-1);
    }
    return (Stack->Count);
}

size_t StackCapacity(stack* Stack)
{
    if(Stack == NULL) {
        printf("StackCapacity: Not a valid pointer to Stack\n");
        return (-1);
    }
    return (Stack->Capacity);
}


//TODO: reserve(capacity):Ensure room for a requested number of elements	Up to \(O(n)\)

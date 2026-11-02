#include "../libds.h"

int main()
{
    stack Buffer = {};
    StackInit(&Buffer, sizeof(int32));
    for(int32 i =0; i< 1000; i++) {
        int32 A = 33 + i;
        StackPush(&Buffer, &A);
    }
    for(int32 i =0; i< 600; i++) {
        int32 A = 33 + i;
        StackPop(&Buffer);
    }
    int32* PushedValues = Buffer.Data;
    for(int32 i = 0; i < Buffer.Count; ++i) {

        printf("Pushedvalue: %d\n", PushedValues[i]);
    }
    /*
    TODO:not sure how to handle this case because the pointer to the memory is still valid.
    int32* PushedValue = Buffer.Data;
    printf("Pushedvalue: %d\n", *PushedValue);
    int32* PopedValue = StackPop(&Buffer);
    if(PopedValue != NULL){
        printf("PopedValue: %d\n", *PopedValue);
    }
    *PushedValue = 23;
    */
    printf("Count:%d\n", Buffer.Count);
    int32* TopValue = StackTop(&Buffer);
    TopValue = StackTop(&Buffer);
    TopValue = StackTop(&Buffer);
    printf("Count:%d\n", Buffer.Count);
    if(TopValue != NULL){
        printf("TopValue: %d\n", *TopValue);
    }
    bool32 isStackEmpty = StackIsEmpty(&Buffer);
    printf("StackEmpty: %d\n", isStackEmpty);
    printf("StackCapacity: %d\n", Buffer.Capacity);

    return(0);
}

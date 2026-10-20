#include "libds.h"

typedef struct {
    int32 X;
    int32 Y;
} point2d;


int main()
{

    list PointList = {};
    ListInit(&PointList, sizeof(int));
    for(int i = 0; i < 10; i++) {
        int32 A = 23 + i;
        ListPushback(&PointList, &A);
    }

    for(int i = 0; i < 10; i++) {
        int32 A = 23 + i * 5;
        ListPushat(&PointList,i, &A);

    }
        int32 A = 23 + 7 * 5;
        ListPushat(&PointList,39, &A);



    for(int i = 0; i < PointList.Size; i++) {
        int32 P = CAST_TO_VALUE(int32, ListGet(&PointList, i));
        printf("int: %d\n", P);
    }
    printf("%d", PointList.Size);
    return(0);
}

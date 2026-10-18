#include "libds.h"

#define POINT_CAP 5
typedef struct {
    int32 X;
    int32 Y;
} point2d;

int main()
{

    list PointList = {};
    ListInit(&PointList, sizeof(int), POINT_CAP);
    for(int i = 0; i < 10; i++) {
        //        point2d P = {25+i , 35+i};
        int32 A = 23 + i;
        //        ListPushback(&PointList, &P);
        ListPushback(&PointList, &A);
    }
    //  ListHeapDestory(&PointList);
    /*    for(int i = 0; i < Len(&PointList); i++){
        point2d P = CAST_TO_VALUE(point2d, ListGet(&PointList, i));
        printf("point2d {%d, %d}\n", P.X, P.Y);
    }

    */
    for(int i = 0; i < 10; i++) {

        int32 P = CAST_TO_VALUE(int32, ListGet(&PointList, i));
        printf("int: %d\n", P);
    } 

    /*
        int32 A = 23;
        int32* Iptr = &A;
        list Intptrs = {};
        ListInit(&Intptrs, sizeof(int32*), POINT_CAP);
        ListPushback(&Intptrs, Iptr);
        int32* Ptr = ListGet(&Intptrs, 0);
    */
    return(0);
}

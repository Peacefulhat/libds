#include "../libds.h"

typedef struct {
    int32 X;
    int32 Y;
} point2d;

int main()
{
    list PointList = {};
    ListInit(&PointList, sizeof(point2d));
    for(int i = 0; i < 2000; i++) {
        for(int j = 0; j<i; j++) {
            point2d P = {25+i, 35+i};
            ListPushback(&PointList, &P);
        }
        ListHeapDestory(&PointList);
    }
    

    for(int i = 0; i < 2000000000; i++) {
        point2d P = {25+i, 35+i};
        ListPushback(&PointList, &P);
    }

    for (int i=0; i < 4; ++i) {
        point2d P = {25+i, 35+i};
        ListPushback(&PointList,&P);
        ListPushback(&PointList,&P);
        ListPushback(&PointList,&P);
        ListPushback(&PointList,&P);

        ListHeapDestory(&PointList);
        ListPushback(&PointList,&P);
        ListPushback(&PointList,&P);
        ListPushback(&PointList,&P);
        ListPushback(&PointList,&P);

    }
    return(0);
}

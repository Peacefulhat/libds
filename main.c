#include "libds.h"

typedef struct {
    int32 X;
    int32 Y;
} point2d;


int main()
{
    string_view Str = CstrAsSv("\nHello, World from libstr");
    printf("%.*s", (int32)Str.Count, Str.Data);
    return(0);
}

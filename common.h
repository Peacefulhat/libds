// comman type aliases
#ifndef COMMON_TYPE_H
#define COMMON_TYPE_H
#include <stdint.h>

// common type alias
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int32_t bool32;
typedef int8_t   schar;
typedef uint8_t  uchar;
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef float  real32;
typedef double real64;

#define  local_persist   static;
#define  global_variable static;
#define  internal        static;

#define SWAP(t, A, B) \
t Temp = A;           \
A = B;                \
B = Temp;             \

#endif

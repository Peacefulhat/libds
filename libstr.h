#ifndef LIBSTR_H
#define LIBSTR_H

//TODO: Error Handling and logging

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include "common.h"
// TODO: remove bool with bool32 and remove stdbool.h
#define FILE_READING 0

#define TODO(message) do { fprintf(stderr, "%s:%d: TODO: %s\n", __FILE__, __LINE__, message); abort(); } while(0)
#define UNREACHABLE(message) do { fprintf(stderr, "%s:%d: UNREACHABLE: %s\n", __FILE__, __LINE__, message); abort(); } while(0)
#define SWAP(type, A, B) do { type T = A; A = B; B = T; } while (0)

// Dynamic array inital capacity
#ifndef DA_INIT_CAP
#define DA_INIT_CAP 5
#endif

//String Builder
typedef struct {
    char* Data;
    size_t Count;
    size_t Capacity;
} string_builder;

// String View
typedef struct {
    const char* Data;
    size_t Count;
} string_view;

// some useful function, to remove use of string.h
size_t CstrLen(const char* Str);
void Memcpy(void* Dest, void* Src, size_t SizeInBytes);
// String Builder functions
bool ReadEntireFileAsSb(const char *FilePath, string_builder *Sb);
void SbAppendItem(string_builder* Sb, char Item);
void SbAppendManySB(string_builder* Dest, string_builder* Src);
void SbAppendManyCstr(string_builder* Sb, const char* Items);
void SbAppendBuffer(string_builder* Sb, const char* Buffer, size_t BufferSize);
void SbAppendSv(string_builder* Sb, string_view* Sv);
void SbAppendNull(string_builder* Sb);
void SbDataResize(string_builder* Sb, size_t NewSize);
char SbPopItem(string_builder* Sb);
char SbFirstItem(string_builder* Sb);
char SbLastItem(string_builder* Sb);
void SbFree(string_builder* Sb);;
void FreeSbData(string_builder* Sb);
string_builder CstrAsSb(const char*);
const char* SbToCstr(string_builder* Sb);
void SbToSv(string_builder* Sb, string_view* Sv);

// String Views functions
string_view CstrAsSv(const char* Cstr);
string_view SvTrimLeft(string_view Sv);
string_view SvTrimRight(string_view Sv);
string_view SvTrim(string_view Sv);
string_view SvChopByDelim(string_view* Sv, char Delim);
string_view SvChopBySv(string_view* A, string_view* B);
bool SvChopPrefix(string_view *Sv, string_view Prefix);
bool SvChopSuffix(string_view *Sv, string_view Suffix);
string_view SvChopLeft(string_view* Sv, size_t N);
string_view SvChopRight(string_view* Sv, size_t N);
int SvEq(string_view A, string_view B);
int SvEqn(string_view A, string_view B);


#if FILE_READING
// File Reading
char* ReadEntireFile(char* FilePath);
#endif

#endif //


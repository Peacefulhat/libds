#include "libstr.h"
// TODO: use your own implement and remove string.h dependency
size_t CstrLen(const char* Str)
{
    size_t Length = 0;
    if(Str != NULL) {
        for(size_t Index = 0; Str[Index]!='\0'; Index++) {
            Length++;
        }
    }
    return Length;
}

void Memcpy(void* Dest, void* Src, size_t SizeInBytes)
{
    char* Dest2 = Dest;
    char* Src2 = Src;
    if(Dest != NULL && Src != NULL && SizeInBytes >= 0) {

        for(size_t Index = 0; Index < SizeInBytes; Index++) {
            Dest2[Index] = Src2[Index];
        }

    } else {
        printf("Memcpy: Dest or Src was NULL");
        return;
    }
}

// String Builder
internal int64 GetFileSize(FILE* File)
{
    if(!File) {
        return (1);
    }
    if(fseek(File, 0, SEEK_END) != 0) {
        return (1);
    }
    int64 Size = 0;
    if((Size = ftell(File)) == -1) {
        return (1);
    }
    fseek(File, 0, SEEK_SET);
    return (Size);
}

bool ReadEntireFileAsSb(const char *FilePath, string_builder *Sb)
{
    bool Result = false;
    size_t NewCount = 0;
    long long FileSize = 0;
    FILE *Fp = fopen(FilePath, "rb");
    FileSize = GetFileSize(Fp);
    if(FileSize == 1) {
        fprintf(stderr, "Unable to get the %s size\n", FilePath);
        return (Result);
    }
    NewCount = FileSize + Sb->Count;
    if(NewCount > Sb->Capacity) {
        Sb->Data = (char*)realloc(Sb->Data, NewCount);
        assert(Sb->Data != NULL && "Buy More RAM");
        Sb->Capacity = NewCount;
    }
    fread(Sb->Data + Sb->Count, FileSize, 1, Fp);
    if(ferror(Fp)) {
        fprintf(stderr, "Couldn't read the file %s", FilePath);
        return(Result);
    }
    Sb->Count = NewCount;
    return (!Result);
}

// Reserve memory for Data pointer in string_builder
internal void SbReserveMem(string_builder* Sb, uint32 ExpectedCapacity)
{
    if(Sb == NULL) {
        return;
    }
    if(Sb->Capacity == 0) {
        Sb->Capacity = DA_INIT_CAP;
    }
    while(ExpectedCapacity > Sb->Capacity) {
        Sb->Capacity *= 2;
    }
    Sb->Data = realloc(Sb->Data, Sb->Capacity * sizeof(*(Sb->Data)));
    assert(Sb->Data != NULL && "Buy more RAM");
}

// this called function is called if string builder variable is on stack and the data is on heap
void FreeSbData(string_builder* Sb)
{
    if(Sb == NULL) {
        return;
    }
    if(Sb->Data == NULL) {
        return;
    }
    free(Sb->Data);
    Sb->Data = NULL;
    Sb->Count = 0;
    Sb->Capacity = 0;
}

// this is called if both data and the string builder variable is on heap
void SbFree(string_builder* Sb)
{
    if(Sb == NULL) {
        return;
    }
    FreeSbData(Sb);
    free(Sb);
}


// adds single element
void SbAppendItem(string_builder* Sb, char Item)
{
    if(Sb == NULL) {
        return;
    }
    SbReserveMem(Sb, Sb->Count + 1);
    Sb->Data[Sb->Count++] = Item;
}

void SbAppendManySB(string_builder* Dest, string_builder* Src)
{
    if(Dest == NULL || Src == NULL) {
        return;
    }
    SbReserveMem(Dest, Dest->Count + Src->Count);
    memcpy(Dest->Data + Dest->Count, Src->Data, Src->Count * sizeof(*(Dest->Data)));
    Dest->Count += Src->Count;
}

// Append a NULL-terminated string to a string builder
void SbAppendManyCstr(string_builder* Sb, const char* Items)
{
    if(Sb == NULL) {
        return;
    }
    size_t ItemsCount = strlen(Items);
    SbReserveMem(Sb, Sb->Count + (ItemsCount));
    memcpy(Sb->Data + Sb->Count, Items, ItemsCount * sizeof(*(Sb->Data)));
    Sb->Count += ItemsCount;
}


// Append a sized buffer to a string builder
void SbAppendBuffer(string_builder* Sb, const char* Buffer, size_t BufferSize)
{
    if(Sb == NULL) {
        return;
    }
    if(Buffer == NULL) {
        return;
    }
    SbReserveMem(Sb, Sb->Count + BufferSize);
    memcpy(Sb->Data + Sb->Count, Buffer, BufferSize * sizeof(*(Sb->Data)));
    Sb->Count += BufferSize;
}

// Append a string view to a string builder
void SbAppendSv(string_builder* Sb, string_view* Sv)
{
    if(Sb == NULL || Sv == NULL) {
        return;
    }
    SbAppendBuffer(Sb, Sv->Data, Sv->Count);
}

// Append Null at the end of sb Buffer
void SbAppendNull(string_builder* Sb)
{
    if(Sb == NULL) {
        return;
    }
    SbAppendItem(Sb, '\0');
}

void SbDataResize(string_builder* Sb, size_t NewSize)
{
    if(Sb == NULL) {
        return;
    }
    SbReserveMem(Sb, NewSize);
    Sb->Count = (NewSize);
}

char SbPopItem(string_builder* Sb)
{
    if(Sb == NULL) {
        return (0);
    }
    assert(Sb->Count > 0);
    return (Sb->Data[Sb->Count--]);
}

char SbFirstItem(string_builder* Sb)
{
    if(Sb == NULL) {
        return (0);
    }
    assert(Sb->Count > 0);
    return (Sb->Data[0]);
}


char SbLastItem(string_builder* Sb)
{
    if(Sb == NULL) {
        return (0);
    }
    assert(Sb->Count > 0);
    return (Sb->Data[Sb->Count - 1]);
}

string_builder CstrAsSb(const char* Cstr)
{
    string_builder NewSb = {};
    if(Cstr == NULL) {
        //logging
        return(NewSb);
    }
    int64 CstrLen = strlen(Cstr);

    SbReserveMem(&NewSb, CstrLen);
    memcpy (NewSb.Data, Cstr, sizeof(char) * CstrLen);
    NewSb.Count += CstrLen;
    return(NewSb);
}

const char* SbToCstr(string_builder* Sb)
{
    if(Sb == NULL) {
        // logging
        return NULL;
    }
    char* Cstr = (char*)malloc((Sb->Count + 1) * sizeof(char));
    assert(Cstr !=NULL && "Buy More Ram\n");
    memcpy(Cstr, Sb->Data, Sb->Count);
    Cstr[Sb->Count] = '\0';
    return(Cstr);
}

void SbToSv(string_builder* Sb, string_view* Sv)
{
    if(Sb == NULL || Sv == NULL) {
        return;
    }
    Sv->Count = Sb->Count;
    Sv->Data = Sb->Data;
}

#define PRINT_SV_OR_SBP(Str) printf("{\n%.*s\n}\n", (int32_t)(Str)->Count, (Str)->Data)
#define PRINT_SV_OR_SB(Str)  printf("{\n%.*s\n}\n", (int32_t)(Str).Count, (Str).Data)
#define PRINT_SV(Str)  printf("%.*s\n", (int32_t)(Str).Count, (Str).Data)

string_view CstrAsSv(const char* Cstr)
{
    return (string_view) {
        .Data = Cstr,
        .Count = strlen(Cstr)
    };
}

string_view SvTrimLeft(string_view Sv)
{
    int32 Index = 0;
    while(Index < Sv.Count && Sv.Data[Index] == ' ') {
        ++Index;

    }
    return (string_view) {
        .Data = Sv.Data + Index,
        .Count = Sv.Count - Index
    };
}

string_view SvTrimRight(string_view Sv)
{
    int32 Index = 0;
    while(Index < Sv.Count && isspace(Sv.Data[Sv.Count - 1 - Index])) {
        ++Index;
    }
    return (string_view) {
        .Data = Sv.Data,
        .Count = Sv.Count - Index
    };
}

string_view SvTrim(string_view Sv)
{
    return (SvTrimRight(SvTrimLeft(Sv)));
}

// chop By string_view or something
// not the best implementation but for now it good enough before i write optimized verison.
string_view SvChopBySv(string_view* A, string_view* B)
{
    string_view Result = {};
    if(A == NULL || B == NULL) {
        // logging
        // return empty string_view
    }
    uint32 Len = 0;

    uint32 Index = 0;
    //TODO: use strncmp()
    while(Index < A->Count) {
        if(A->Data[Index] == B->Data[0]) {
            Len++;
            for(uint32 Idx = 1; Idx < B->Count; ++Idx) {
                if(A->Data[Index + Idx] == B->Data[Idx]) {
                    Len++;
                }
            }
            if(Len == B->Count) {

                break;
            }
        }
        Len = 0;
        Index++;
    }
    Result = (string_view) {
        .Data = A->Data,
        .Count = Index
    };
    if(Len == B->Count) {
        A->Data += Index + B->Count ;
        A->Count -= Index + B->Count;
    } else {
        A->Data += Index;
        A->Count -= Index;
    }
    return (Result);
}

string_view SvChopByDelim(string_view* Sv, char Delim)
{
    if(Sv == NULL) {
        return (string_view) {
            .Data = NULL,
            .Count = 0
        };
    }
    int32 Index = 0;
    while(Index < Sv->Count && (Sv->Data[Index] != Delim )) {
        Index++;
    }
    string_view Result = {Sv->Data, Index};
    if(Index < Sv->Count) {
        Sv->Data+=Index + 1;
        Sv->Count-= Index + 1;
    } else {
        // return what ever there is left
        Sv->Count -= Index ;
        Sv->Data += Index ;
    }
    return (Result);
}


// remove any prefix and return true if it was choped,
//else return false and string_view remains unchanged.
bool SvChopPrefix(string_view *Sv, string_view Prefix)
{
    if(Sv == NULL) {
        return (false);
    }
    bool PrefixRem = false;
    if (SvEqn(*Sv, Prefix)) {
        SvChopLeft(Sv, Prefix.Count);
        PrefixRem = true;
    }
    return(PrefixRem);
}

// remove any suffix and return true if it was choped,
//else return false and string_view remains unchanged.

bool SvChopSuffix(string_view *Sv, string_view Suffix)
{
    if(Sv == NULL) {
        return (false);
    }
    bool SuffixRem = false;
    string_view Temp = *Sv;
    Temp.Data += Temp.Count - Suffix.Count;
    if (SvEqn(Temp, Suffix)) {
        SvChopRight(Sv, Suffix.Count);
        SuffixRem = true;
    }
    return(SuffixRem);
}

string_view SvChopLeft(string_view* Sv, size_t N)
{
    string_view Result= {};
    if(Sv == NULL) {
        // logging
        // Return empty string_view
    }
    if(N > Sv->Count) {
        N = Sv->Count;
    }
    Sv->Data += N;
    Sv->Count -= N;
    Result = *Sv;
    return (Result);
}

string_view SvChopRight(string_view *Sv, size_t N)
{
    string_view Result = {};
    if (N > Sv->Count) {
        N = Sv->Count;
    }
    Result.Data =  Sv->Data + Sv->Count - N ;
    Result.Count =  N;
    Sv->Count -= N;
    return (Result);
}

int SvEq(string_view A, string_view B)
{
    if(A.Count != B.Count) {
        // if length are not equal.
        return (-1);
    }
    return (strncmp(A.Data, B.Data, A.Count) == 0);
}

// checks first n characters of B in A
int SvEqn(string_view A, string_view B)
{
    if(A.Count <= B.Count) {
        return (strncmp(A.Data, B.Data, B.Count) == 0);
    }
    return (-1);
}

#if FILE_READING
// File Reading
char* ReadEntireFile(char* FilePath)
{
    FILE* File = fopen(FilePath, "r");
    if(!File) {
        return (NULL);
    }

    int64 Size = GetFileSize(File);
    char* FContents = (char*)malloc(Size + 1);

    if(fread(FContents, 1, Size, File) != Size) {
        return (NULL);
    }
    FContents[Size] = '\0';
    return (FContents);
}
#endif


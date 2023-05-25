#pragma once
typedef unsigned char byte;

struct SLOTHEAP {
    int cb;
    byte* ab;
    struct SLOT* pslotFree;
    int cAlloc;
    int cInUse;
};

struct SLOT {
    struct SLOT* pslotNext;
};
#pragma once
#include <basic.h>
#include <dl.h>

struct LO {
    struct BASIC field0_0x0;
    enum   OID oid;
    struct DLE dleOid;
    struct SW* psw;
    struct ALO* paloParent;
    struct DLE dleChild;
    struct LO* ploCidNext;
    struct MQ* pmqFirst;
    char*  pchzName;
    struct CFrame* pframe;
    struct PXR* ppxr;
    unsigned long dtickPerf;
};

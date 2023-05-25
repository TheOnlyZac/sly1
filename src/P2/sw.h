#pragma once
#include <bis.h>
#include <dl.h>
#include <light.h>
#include <lo.h>
#include <slotheap.h>
#include <sound.h>
#include <sw.h>
#include <vec.h>

struct PSL {
    int cploCloneFree;
    struct LO** aploClone;
};

struct SW {
    struct LO field0_0x0;
    int cpsoAll;
    int cpsoRoot;
    struct DL dlRoot;
    struct DL dlChild;
    struct DL dlMRD;
    struct DL dlBusy;
    struct DL dlBusySo;
    struct DL dlMRDRealClock;
    struct DL adlHash[512];
    struct LO* aploCidHead[162];
    struct OBR* aaobr;
    byte* aaoxf;
    struct OXA* aoxa;
    struct OXA* poxaFree;
    struct OXA* poxaAlloc;
    int fAaoxValid;
    struct SLOTHEAP slotheapOx;
    struct SLOTHEAP slotheapXp;
    struct SLOTHEAP slotheapXa;
    struct SLOTHEAP slotheapMq;
    struct SLOTHEAP slotheapAct;
    struct SLOTHEAP slotheapRip;
    struct RIPG* pripgFree;
    struct RIPG* pripgDefault;
    struct SLOTHEAP slotheapBlip;
    struct SLOTHEAP slotheapBlipsp;
    struct SLOTHEAP slotheapAsega;
    struct DL dlAsega;
    struct DL dlAsegaRealClock;
    struct DL dlAsegaPending;
    struct SLOTHEAP slotheapSma;
    struct DL dlSma;
    struct SLOTHEAP slotheapAmb;
    struct DL dlAmb;
    struct SLOTHEAP slotheapExc;
    struct DL dlExc;
    struct SLOTHEAP slotheapExplste;
    struct DL dlExplste;
    struct DL dlLight;
    struct SLOTHEAP slotheapShadow;
    struct DL dlShadow;
    struct SLOTHEAP slotheapStso;
    struct SLOTHEAP slotheapFader;
    struct DL dlFader;
    struct DL dlRealClockFader;
    struct DL dlShape;
    struct DL dlPathzone;
    enum LVK lvk;
    struct DL dlProxy;
    struct DL dlFly;
    struct DL dlDprize;
    struct DL dlRat;
    struct DL dlRathole;
    struct DL dlDartFree;
    struct DL dlSpire;
    struct DL dlRail;
    struct DL dlLanding;
    struct DL dlBusyLasen;
    struct DL dlBlipg;
    struct DL dlBlipgFree;
    struct DL dlCrfod;
    struct VAULT* pvault;
    struct LO* aploStock[29];
    struct RGBA rgbaSky;
    struct LSM lsmDefault;
    int ibnk;
    enum MUSID musid;
    int cisi;
    struct ISI aisi[16];
    struct VISMAP* pvismap;
    struct MQ* pmqCallbackFirst;
    struct MQ* pmqCallbackLast;
    int cpaloRemerge;
    struct ALO** apaloRemerge;
    struct VECTOR dvGravity;
    int csplcSplice;
    struct SPLC* asplcSplice;
    uint symidScheduledCallbackList;
    int symidMax;
    char** mpsymidachz;
    int coptidExtra;
    char** mpoptidachzExtra;
    int cpsl;
    struct PSL apsl[128];
    int cclueAll;
    int cchkpntAll;
    float dtChallengePar;
    int cgoldAll;
    float gexcMenu;
    int cHandsOff;
    //struct RSE arse[4];
    int irse;
    struct MBG* pmbg;
    float rDarken;
    float rDarkenSmooth;
};

static SW g_sw;
extern SW* g_psw;

void SetupBulkDataFromBrx(int fLoadBulkData, CBinaryInputStream* pbis);
void LoadSwFromBrx(SW* psw, CBinaryInputStream* pbis);
void DeleteSw(SW* psw);
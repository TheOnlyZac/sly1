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
    LO** aploClone;
};

struct SW {
    LO field0_0x0;
    int cpsoAll;
    int cpsoRoot;
    DL dlRoot;
    DL dlChild;
    DL dlMRD;
    DL dlBusy;
    DL dlBusySo;
    DL dlMRDRealClock;
    DL adlHash[512];
    LO* aploCidHead[162];
    //OBR* aaobr;
    byte* aaoxf;
    //OXA* aoxa;
    //OXA* poxaFree;
    //OXA* poxaAlloc;
    int fAaoxValid;
    SLOTHEAP slotheapOx;
    SLOTHEAP slotheapXp;
    SLOTHEAP slotheapXa;
    SLOTHEAP slotheapMq;
    SLOTHEAP slotheapAct;
    SLOTHEAP slotheapRip;
    //RIPG* pripgFree;
    //RIPG* pripgDefault;
    SLOTHEAP slotheapBlip;
    SLOTHEAP slotheapBlipsp;
    SLOTHEAP slotheapAsega;
    DL dlAsega;
    DL dlAsegaRealClock;
    DL dlAsegaPending;
    SLOTHEAP slotheapSma;
    DL dlSma;
    SLOTHEAP slotheapAmb;
    DL dlAmb;
    SLOTHEAP slotheapExc;
    DL dlExc;
    SLOTHEAP slotheapExplste;
    DL dlExplste;
    DL dlLight;
    SLOTHEAP slotheapShadow;
    DL dlShadow;
    SLOTHEAP slotheapStso;
    SLOTHEAP slotheapFader;
    DL dlFader;
    DL dlRealClockFader;
    DL dlShape;
    DL dlPathzone;
    //LVK lvk;
    DL dlProxy;
    DL dlFly;
    DL dlDprize;
    DL dlRat;
    DL dlRathole;
    DL dlDartFree;
    DL dlSpire;
    DL dlRail;
    DL dlLanding;
    DL dlBusyLasen;
    DL dlBlipg;
    DL dlBlipgFree;
    DL dlCrfod;
    //VAULT* pvault;
    LO* aploStock[29];
    RGBA rgbaSky;
    LSM lsmDefault;
    int ibnk;
    //MUSID musid;
    int cisi;
    ISI aisi[16];
    //VISMAP* pvismap;
    MQ* pmqCallbackFirst;
    MQ* pmqCallbackLast;
    int cpaloRemerge;
    ALO** apaloRemerge;
    VECTOR dvGravity;
    int csplcSplice;
    //SPLC* asplcSplice;
    uint symidScheduledCallbackList;
    int symidMax;
    char** mpsymidachz;
    int coptidExtra;
    char** mpoptidachzExtra;
    int cpsl;
    PSL apsl[128];
    int cclueAll;
    int cchkpntAll;
    float dtChallengePar;
    int cgoldAll;
    float gexcMenu;
    int cHandsOff;
    //RSE arse[4];
    int irse;
    //MBG* pmbg;
    float rDarken;
    float rDarkenSmooth;
};

static SW g_sw;
extern SW* g_psw;

void SetupBulkDataFromBrx(int fLoadBulkData, CBinaryInputStream* pbis);
void LoadSwFromBrx(SW* psw, CBinaryInputStream* pbis);
void DeleteSw(SW* psw);

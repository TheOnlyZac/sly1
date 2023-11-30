/**
 * @file sw.h
 *
 * @brief Declares the scene world and related classes.
*/
#pragma once
#include <bis.h>
#include <dl.h>
#include <light.h>
#include <lo.h>
#include <slotheap.h>
#include <sound.h>
#include <sw.h>
#include <vec.h>

/**
 * @brief Unknown, needs more research
*/
struct PSL {
    int cploCloneFree;
    LO** aploClone;
};

/**
 * @brief Scene World
 *
 * The scene world is the game world. It contains all the objects in the game
 * world, and is responsible for rendering them.
*/
struct SW {
    LO field0_0x0;
    int cpsoAll; // count of all scene objects
    int cpsoRoot; // count of root scene objects
    DL dlRoot;
    DL dlChild;
    DL dlMRD;
    DL dlBusy;
    DL dlBusySo;
    DL dlMRDRealClock;
    DL adlHash[512];
    LO* aploCidHead[162]; // array of linked lists of scene objects, indexed by collision ID(?)
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

// Global variables
static SW g_sw; // Current scene world
extern SW* g_psw; // Pointer to the current scene world

/**
 * @brief Sets up bulk data from BRX.
 *
 * @param fLoadBulkData Whether to load bulk data.
 * @param pbis Pointer to the binary input stream.
 *
 * @todo Implement this function.
*/
void SetupBulkDataFromBrx(int fLoadBulkData, CBinaryInputStream* pbis);

/**
 * @brief Loads the scene world from BRX.
 *
 * @param psw Pointer to the scene world.
 * @param pbis Pointer to the binary input stream.
 *
 * @todo Implement this function.
*/
void LoadSwFromBrx(SW* psw, CBinaryInputStream* pbis);

/**
 * @brief Deletes the scene world.
 *
 * @param psw Pointer to the scene world.
 *
 * @todo Implement this function.
*/
void DeleteSw(SW* psw);

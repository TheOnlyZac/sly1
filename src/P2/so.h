#pragma once
#include <zap.h>
#include <util.h>
#include <iostream>

typedef int GRFPVA;


/**
 * Scene Object
 *
 * A scene object is a physical object in the game world.
 *
 * todo: identify missing fields and rewrite
 */
struct SO
{
    char padding[0x2e0];
    //DLE dleRoot;
    //DL dlPhys;
    //DLE dlePhys;
    //struct VECTOR_153 dvGravity;
    float gBuoyancy;
    float gViscosity;
    float m;
    undefined4 field_0x37c;
    //struct VECTOR_153 posWorldPrev;
    //struct GEOM_153 geomLocal;
    //struct GEOM_153 geomWorld;
    struct LVO_153* plvo;
    float sRadiusSelf;
    float sRadiusAll;
    float sRadiusPrune;
    byte field_0x3f8;
    byte field_0x3f9;
    byte field_0x3fa;
    byte field_0x3fb;
    byte field_0x3fc;
    byte field_0x3fd;
    byte field_0x3fe;
    byte field_0x3ff;
    //struct VECTOR_153 posPrune;
    //struct BSPC_153 bspc;
    int cnpg;
    struct NPG_153* anpg;
    int* mpibspinpg;
    int chsg;
    struct HSG_153* ahsg;
    int* mpisurfihsgMic;
    //DLE dleBusySo;
    //struct VECTOR_153 posMin;
    //struct VECTOR_153 posMax;
    //struct CONSTR_153 constrForce;
    byte field_0x471;
    byte field_0x472;
    byte field_0x473;
    byte field_0x474;
    byte field_0x475;
    byte field_0x476;
    byte field_0x477;
    byte field_0x478;
    byte field_0x479;
    byte field_0x47a;
    byte field_0x47b;
    byte field_0x47c;
    byte field_0x47d;
    byte field_0x47e;
    byte field_0x47f;
    //struct CONSTR_153 constrTorque;
    byte field_0x491;
    byte field_0x492;
    byte field_0x493;
    byte field_0x494;
    byte field_0x495;
    byte field_0x496;
    byte field_0x497;
    byte field_0x498;
    byte field_0x499;
    byte field_0x49a;
    byte field_0x49b;
    byte field_0x49c;
    byte field_0x49d;
    byte field_0x49e;
    byte field_0x49f;
    //struct OXA_153.conflict* poxa;
    undefined4 field_0x4a4;
    undefined4 field_0x4a8;
    undefined4 field_0x4ac;
    //struct VECTOR_153 dpos;
    //struct VECTOR_153 drot;
    //struct XA_153.conflict* pxa;
    //struct XP_153.conflict* pxpInternal;
    GRFPVA grfpvaXpValid;
    int ipsoRoot;
    int ipso;
    undefined4 field_0x4e4;
    undefined4 field_0x4e8;
    undefined4 field_0x4ec;
    //struct VECTOR_153 posComLocal;
    ZOK zok;
    SO* psoPhysHook;
    //struct GEOM_153 geomCameraLocal;
};

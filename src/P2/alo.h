/**
 * @file alo.h
*/
#ifndef ALO_H
#define ALO_H

struct ALO {
    //LO field0_0x0;
    //DL dlChild;
    //DLE dleBusy;
    //DLE dleMRD;
    //ALO* paloRoot;
    ALO* paloFreezeRoot;
    //DLE dleFreeze;
    //DL dlFreeze;
    int cpmrg;
    //MRG* apmrg[4];
    float sMRD;
    float sCelBorderMRD;
    int grfzon;
    float dsMRDSnap;
    //FRZ frz;
    //XF xf;
    //VECTOR posOrig;
    //MATRIX3 matOrig;
    //VECTOR eulOrig;
    //DL dlAct;
    //ACT* pactPos;
    //ACT* pactRot;
    //ACT* pactScale;
    //ACT** apactPose;
    //ACT* pactRestore;
    //ACTLA* pactla;
    //ACTBANK* pactbank;
    //IKH* pikh;
    //CLQ* pclqPosSpring;
    //CLQ* pclqPosDamping;
    //CLQ* pclqRotSpring;
    //CLQ* pclqRotDamping;
    //SMPA* psmpaPos;
    //SMPA* psmpaRot;
    //ALOX* palox;
    int cframeStatic;
    //GLOBSET globset;
    //SHADOW* pshadow;
    //THROB* pthrob;
    float sFastShadowRadius;
    float sFastShadowDepth;
    int fRealClock;
    //FADER* pfader;
    float dtUpdatePause;
    //ASEGD* pasegd;
    float sRadiusRenderSelf;
    float sRadiusRenderAll;
    //SFX* psfx;
    //FICG ficg;
    int cposec;
    //POSEC* aposec;
    //ACTREF* pactrefCombo;
    //DLR* pdlrFirst;
    //ACK ackRot;
};

#endif // ALO_H

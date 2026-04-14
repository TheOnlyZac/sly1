#include <shdanim.h>
#include <shd.h>
#include <gs.h>
#include <clock.h>


extern CLOCK g_clock;

int CbFromSaak(SAAK saak)
{
    switch (saak) {
        case SAAK_Loop:
        case SAAK_PingPong: return 0x4C;
        case SAAK_Shuffle:
        case SAAK_Hologram: return 0x38;
        case SAAK_Eyes: return 0x78;
        case SAAK_Scroller: return 0x44;
        case SAAK_Circler: return 0x3C;
        case SAAK_Looker: return 0x50;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", PvtsaaFromSaak__F4SAAK);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", PsaaLoadFromBrx__FP18CBinaryInputStream);

void InitSaa(SAA *psaa, SAAF *psaaf) {

    int grfsai = psaa->sai.grfsai | 0x1;
    psaa->oid = (OID)psaaf->oid;
    psaa->sai.grfsai = grfsai;
    
    if(psaaf->grfsaaf != 0) {
        psaa->sai.grfsai = psaa->sai.grfsai | 0x4;
    }
}

void PostSaaLoad(SAA *psaa) {
    if(psaa->sai.pshd == NULL) {
        psaa->sai.pshd = PshdFindShader__F3OID(psaa->oid);
    }
}


int FUpdatableSaa(SAA *psaa) {
    if(psaa->tUpdates != g_clock.t) {
        psaa->tUpdates = g_clock.t;
        return 1;
    }
    return 0;
}

float UCompleteSaa(SAA *psaa) {
    return 0.0f;
}

SAI *PsaiFromSaaShd(SAA *psaa, SHD *pshd) {
    if(pshd->oid == psaa->oid) {
        return &psaa->sai;
    }
    return (SAI *)NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", InitLoop__FP4LOOPP4SAAF);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", PostLoopLoad__FP4LOOP);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", UpdateLoop__FP4LOOPf);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", UCompleteLoop__FP4LOOP);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", InitPingpong__FP8PINGPONGP4SAAF);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", PostPingpongLoad__FP8PINGPONG);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", UpdatePingpong__FP8PINGPONGf);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", UCompletePingpong__FP8PINGPONG);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", InitShuffle__FP7SHUFFLEP4SAAF);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", UpdateShuffle__FP7SHUFFLEf);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", InitHologram__FP8HOLOGRAMP4SAAF);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", PostHologramLoad__FP8HOLOGRAM);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", NotifyHologramRender__FP8HOLOGRAMP3ALOP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", InitScroller__FP8SCROLLERP4SAAF);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", UpdateScroller__FP8SCROLLERf);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", UCompleteScroller__FP8SCROLLER);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", SetScrollerMasterSpeeds__FP8SCROLLERff);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", InitCircler__FP7CIRCLERP4SAAF);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", UpdateCircler__FP7CIRCLERf);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", UCompleteCircler__FP7CIRCLER);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", InitLooker__FP6LOOKERP4SAAF);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", SetLookerSgvr__FP6LOOKERP4SGVRP7GLOBSETP4GLOBP7SUBGLOB);

void SetVecPosad(VECTOR *pvec, POSAD *pposad) {
    pvec->x = pposad->x;
    pvec->y = pposad->y;
    pvec->z = pposad->z;
}

void SetUvPuvqd(UVF *puv, UVQ *puvqd) {
    puv->u = puvqd->u;
    puv->v = puvqd->v;
}

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", NotifyLookerRender__FP6LOOKERP3ALOP3RPL);

JUNK_ADDIU(60);
JUNK_WORD(0x0003100B);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", FUN_001b5b58);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", FUN_001b5c40);

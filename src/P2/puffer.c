#include <puffer.h>
#include <po.h>
#include <rog.h>
#include <find.h>
#include <sm.h>
#include <difficulty.h>

INCLUDE_ASM("asm/nonmatchings/P2/puffer", InitPuffer__FP6PUFFER);

extern SNIP D_0026A728;

void LoadPufferFromBrx(PUFFER *ppuffer, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(ppuffer, pbis);
    SnipAloObjects(ppuffer, 1, &D_0026A728);
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PostPufferLoad__FP6PUFFER);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PresetPufferAccel__FP6PUFFERf);

int FFilterPuffer(PUFFER *ppuffer, SO *pso)
{
    if ((STRUCT_OFFSET(pso, 0x538, unsigned long long) & ((unsigned long long)0x8000 << 28)) != 0)
    {
        if (!FIsBasicDerivedFrom(pso, (CID)0x1F))
            return 0;
    }

    return STRUCT_OFFSET(pso, 0x50, SO *) != ppuffer;
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffer__FP6PUFFERf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PpufftChoosePuffer__FP6PUFFER);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_001973d8);

extern void *D_0026A904;

void FUN_00197458(void *p, int n)
{
    OID oidGoal;
    OID oidCur;

    if (n == 1)
    {
        if (STRUCT_OFFSET(D_0026A904, 0x6B8, SMA *) != NULL)
        {
            GetSmaGoal(STRUCT_OFFSET(D_0026A904, 0x6B8, SMA *), &oidGoal);
            GetSmaCur(STRUCT_OFFSET(D_0026A904, 0x6B8, SMA *), &oidCur);

            if (oidGoal != (OID)0x3F4 && oidCur != (OID)0x3F4)
            {
                SetSmaGoal(STRUCT_OFFSET(D_0026A904, 0x6B8, SMA *), (OID)0x3F5);
                FUN_001973d8(D_0026A904);
            }
        }
    }
}

void OnPufferActive(PUFFER *ppuffer, int fActive, PO *ppoOther)
{
    OnPoActive(ppuffer, fActive, ppoOther);
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePufferActive__FP6PUFFERP3JOYf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00197788);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00197848);

void FUN_00197a08(void *pv1, void *pv2)
{
    ROST *prost = STRUCT_OFFSET(pv2, 0xC14, ROST *);
    SetRostRosts(prost, ROSTS_Close);
    RemoveDlEntry((DL *)((char *)pv1 + 0x6A8), prost);
    AppendDlEntry((DL *)((char *)pv1 + 0x69C), prost);
    STRUCT_OFFSET(pv2, 0xC14, ROST *) = 0;
}

extern float D_0026A83C;
extern float D_0026A840;

void FUN_00197a68(void *pv, void *p)
{
    float dx = D_0026A83C;
    float dy = D_0026A840;
    STRUCT_OFFSET(p, 0x98, float) = dx;
    STRUCT_OFFSET(p, 0x94, float) = dy;
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", AddPufferWaterAcceleration__FP6PUFFERP5WATERf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", HandlePufferMessage__FP6PUFFER5MSGIDPv);

void PostPuffcLoad(PUFFC *ppuffc)
{
    PostStepguardLoad((STEPGUARD *)ppuffc);
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PresetPuffcAccel__FP5PUFFCf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_001982a0);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffcGoal__FP5PUFFCi);

void FUN_00197a08(void *pv1, void *pv2);

void OnPuffcExitingSgs(PUFFC *ppuffc, SGS sgsNext)
{
    if (STRUCT_OFFSET(ppuffc, 0x724, int) == SGS_Stun)
    {
        VU_VECTOR vec;

        FUN_00197a08(PpoCur(), ppuffc);

        vec = STRUCT_OFFSET(ppuffc, 0x150, VU_VECTOR);
        STRUCT_OFFSET((&vec), 0x8, int) = 0;
        (*(void (**)(PUFFC *, VU_VECTOR *))((uint8_t *)STRUCT_OFFSET(ppuffc, 0x0, void *) + 0x90))(ppuffc, &vec);
    }

    OnStepguardExitingSgs((STEPGUARD *)ppuffc, sgsNext);
}

void OnPuffcEnteringSgs(PUFFC *ppuffc, SGS sgsPrev, ASEG *pasegOverride)
{
    OnStepguardEnteringSgs((STEPGUARD *)ppuffc, sgsPrev, pasegOverride);
    if (STRUCT_OFFSET(ppuffc, 0x724, int) == SGS_Stun)
    {
        FUN_001c8920(ppuffc);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffcSgs__FP5PUFFC);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", HandlePuffcMessage__FP5PUFFC5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffc__FP5PUFFCf);

int FCanPuffcAttack(PUFFC *ppuffc)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00198860);

extern SNIP D_0026A8E0;

void PostPuffbLoad(PUFFB *ppuffb)
{
    LO *plo;

    SnipAloObjects(ppuffb, 3, &D_0026A8E0);
    PostAloLoad(ppuffb);
    plo = PloFindSwObjectByClass(ppuffb->psw, FSO_FindAll, CID_TURRET, NULL);
    if (plo != NULL)
    {
        STRUCT_OFFSET(plo, 0x684, int)++;
    }
}

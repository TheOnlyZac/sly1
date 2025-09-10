#include <jump.h>
#include <find.h>

extern DL g_dlJmt;

INCLUDE_ASM(const s32, "P2/jump", PresetJtAccelJump__FP2JT);

INCLUDE_ASM(const s32, "P2/jump", UpdateJtActiveJump__FP2JTP3JOY);

INCLUDE_ASM(const s32, "P2/jump", FCheckJtSingleEdge__FP2JTP2SOP4EDGEP6VECTOR);

INCLUDE_ASM(const s32, "P2/jump", FCheckJtEdgeNormal__FP2JTP6VECTORT1);

INCLUDE_ASM(const s32, "P2/jump", FCheckJtEdgeGrab__FP2JTP2SOP6VECTOR3XPKPvT2);

INCLUDE_ASM(const s32, "P2/jump", PxpFindJtBestEdge__FP2JTPiP6VECTOR);

INCLUDE_ASM(const s32, "P2/jump", JtsResetJt__FP2JT);

INCLUDE_ASM(const s32, "P2/jump", HandleJtDiveEffect__FP2JT);

INCLUDE_ASM(const s32, "P2/jump", FUN_0017ece8);

INCLUDE_ASM(const s32, "P2/jump", UpdateJtJump__FP2JT);

INCLUDE_ASM(const s32, "P2/jump", FTimeJtJumpToTarget__FP2JTP6VECTORN31Pf);

INCLUDE_ASM(const s32, "P2/jump", GetJtJumpVelocity__FP2JTP6VECTOR);

INCLUDE_ASM(const s32, "P2/jump", GetJtJumpToTargetVelocity__FP2JTP6VECTOR);

INCLUDE_ASM(const s32, "P2/jump", GetJtJumpBoostVelocity__FP2JTP6VECTOR);

void StartupJmt()
{
    InitDl(&g_dlJmt, 0x50);
}

void ResetJmtList()
{
    ClearDl(&g_dlJmt);
}

void OnJmtAdd(JMT *pjmt)
{
    OnLoAdd(pjmt);
    AppendDlEntry(&g_dlJmt, pjmt);
}

void OnJmtRemove(JMT *pjmt)
{
    OnLoRemove(pjmt);
    RemoveDlEntry(&g_dlJmt, pjmt);
}

INCLUDE_ASM(const s32, "P2/jump", CloneJmt__FP3JMTT0);

void PostJmtLoad(JMT *pjmt)
{
    PostLoLoad(pjmt);

    if (pjmt->oidSetIgnoreJt != OID_Nil)
    {
        pjmt->psoSetIgnoreJt = (SO *)PloFindSwObject(pjmt->psw, 0x104, pjmt->oidSetIgnoreJt, pjmt);
    }
}

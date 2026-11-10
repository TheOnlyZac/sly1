#include <jump.h>
#include <find.h>
#include <mat.h>
#include <clip.h>
#include <bsp.h>

extern DL g_dlJmt;
extern VECTOR g_normalZ;
extern VECTOR D_00263EC0[22];

INCLUDE_ASM("asm/nonmatchings/P2/jump", PresetJtAccelJump__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jump", UpdateJtActiveJump__FP2JTP3JOY);

INCLUDE_ASM("asm/nonmatchings/P2/jump", FCheckJtSingleEdge__FP2JTP2SOP4EDGEP6VECTOR);

int FCheckJtEdgeNormal(JT *pjt, VECTOR *pposEdge, VECTOR *pnormal)
{
    int cHit = 0;
    MATRIX3 mat;
    MATRIX4 mat4;
    VECTOR posA;
    VECTOR posB;
    LSG lsg;

    STRUCT_OFFSET(&mat, 0x00, qword) = STRUCT_OFFSET(pnormal, 0x00, qword);
    GetNormalVectors(&mat.avec[0], &mat.avec[1], &g_normalZ, &g_normalZ);
    LoadMatrixFromPosRot(pposEdge, &mat, &mat4);

    for (uint i = 0; i < 22; i += 2)
    {
        MultiplyMatrix4Vector(&mat4, &D_00263EC0[i], 1.0f, &posA);
        MultiplyMatrix4Vector(&mat4, &D_00263EC0[i + 1], 1.0f, &posB);

        for (void *pnode = *STRUCT_OFFSET(pjt, 0x480, void **); pnode; pnode = STRUCT_OFFSET(pnode, 0x4, void *))
        {
            SO *pso = STRUCT_OFFSET(pnode, 0xC, SO *);
            if (STRUCT_OFFSET(pso, 0x538, ulong) & ((ulong)1 << 42))
                continue;

            for (SO *psoChild = STRUCT_OFFSET(pso, 0x2D8, SO *); psoChild; psoChild = STRUCT_OFFSET(psoChild, 0x2E4, SO *))
            {
                if (STRUCT_OFFSET(psoChild, 0x538, ulong) & ((ulong)1 << 43))
                    continue;

                if (ClsgClipEdgeToObject(psoChild, &posA, &posB, 1, &lsg) > 0)
                {
                    if ((int)i < 4)
                        return 0;
                    if (lsg.au[0] == 0.0f)
                        return 0;
                    if (lsg.anormal[0].z > 0.7f)
                        cHit++;
                }
            }
        }
    }

    return cHit >= 2;
}

INCLUDE_ASM("asm/nonmatchings/P2/jump", FCheckJtEdgeGrab__FP2JTP2SOP6VECTOR3XPKPvT2);

INCLUDE_ASM("asm/nonmatchings/P2/jump", PxpFindJtBestEdge__FP2JTPiP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/jump", JtsResetJt__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jump", HandleJtDiveEffect__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jump", FUN_0017ece8);

INCLUDE_ASM("asm/nonmatchings/P2/jump", UpdateJtJump__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/jump", FTimeJtJumpToTarget__FP2JTP6VECTORN31Pf);

INCLUDE_ASM("asm/nonmatchings/P2/jump", GetJtJumpVelocity__FP2JTP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/jump", GetJtJumpToTargetVelocity__FP2JTP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/jump", GetJtJumpBoostVelocity__FP2JTP6VECTOR);

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

void CloneJmt(JMT *pjmt, JMT *pjmtBase)
{
    DLE dleJmt = pjmt->dleJmt;
    CloneLo(pjmt, pjmtBase);
    pjmt->dleJmt = dleJmt;
}

void PostJmtLoad(JMT *pjmt)
{
    PostLoLoad(pjmt);

    if (pjmt->oidSetIgnoreJt != OID_Nil)
    {
        pjmt->psoSetIgnoreJt = (SO *)PloFindSwObject(pjmt->psw, 0x104, pjmt->oidSetIgnoreJt, pjmt);
    }
}

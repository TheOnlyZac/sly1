#include <barrier.h>
#include <bbmark.h>

void InitBarrier(BARRIER *pbarrier)
{
    InitSo(pbarrier);
    SetSoConstraints(pbarrier, CT_Locked, (VECTOR *)nullptr, CT_Locked, (VECTOR *)nullptr);
    STRUCT_OFFSET(pbarrier, 0x590, OID) = OID_Nil; // pbarrier->barwarp.oidWarp
}

void CloneBarrier(BARRIER *pbarrier, BARRIER *pbarrierBase)
{
    CloneSo(pbarrier, pbarrierBase);
    if (!pbarrier->paloParent)
    {
        RecalcSwOxfFilterForObject(pbarrier->psw, pbarrier);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/barrier", PostBarrierLoad__FP7BARRIER);

INCLUDE_ASM("asm/nonmatchings/P2/barrier", UpdateBarrier__FP7BARRIERf);

INCLUDE_ASM("asm/nonmatchings/P2/barrier", FIgnoreBarrierIntersection__FP7BARRIERP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/barrier", NotifyBarrierImpact__FP7BARRIERP2XPi);

void AddBarrierObject(BARRIER *pbarrier, OID oid)
{
    int coid = STRUCT_OFFSET(pbarrier, 0x554, int); // pbarrier->coid
    OID *aoid = &STRUCT_OFFSET(pbarrier, 0x558, OID); // pbarrier->aoid
    aoid[coid] = oid;
    STRUCT_OFFSET(pbarrier, 0x554, int) = coid + 1; // pbarrier->coid
}

void AddBarrierClass(BARRIER *pbarrier, CID cid)
{
    int ccid = STRUCT_OFFSET(pbarrier, 0x568, int); // pbarrier->ccid
    CID *acid = &STRUCT_OFFSET(pbarrier, 0x56c, CID); // pbarrier->acid
    acid[ccid] = cid;
    STRUCT_OFFSET(pbarrier, 0x568, int) = ccid + 1; // pbarrier->ccid
}

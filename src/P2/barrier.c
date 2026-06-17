#include <barrier.h>
#include <bbmark.h>

void InitBarrier(BARRIER *pbarrier)
{
    InitSo(pbarrier);
    SetSoConstraints(pbarrier, CT_Locked, NULL, CT_Locked, NULL);
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

extern VECTOR D_00248D30;

INCLUDE_ASM("asm/nonmatchings/P2/barrier", UpdateBarrier__FP7BARRIERf);
#ifdef SKIP_ASM
void UpdateBarrier(BARRIER *pbarrier, float dt)
{
    UpdateSo(pbarrier, dt);

    SO *psoWarp = STRUCT_OFFSET(pbarrier, 0x5A0, SO *);
    if (psoWarp)
    {
        VECTOR *pvecZero = &D_00248D30;

        (*(void (**)(SO *, VECTOR *))((char *)psoWarp->pvtlo + 0x90))(psoWarp, pvecZero);

        psoWarp = STRUCT_OFFSET(pbarrier, 0x5A0, SO *);
        (*(void (**)(SO *, VECTOR *))((char *)psoWarp->pvtlo + 0x94))(psoWarp, pvecZero);

        int state = STRUCT_OFFSET(pbarrier, 0x580, int);
        void *pvResult;
        if (state == 1)
        {
            psoWarp = STRUCT_OFFSET(pbarrier, 0x5A0, SO *);
            (*(void (**)(SO *, void *))((char *)psoWarp->pvtlo + 0x84))(
                psoWarp, &STRUCT_OFFSET(pbarrier, 0x590, int));
            pvResult = STRUCT_OFFSET(pbarrier, 0x5A0, void *);
        }
        else if (state == 2)
        {
            SO *psoWarpSrc = STRUCT_OFFSET(pbarrier, 0x590, SO *);
            VECTOR vec;
            ConvertAloPos(STRUCT_OFFSET(psoWarpSrc, 0x18, ALO *), NULL,
                          (VECTOR *)((char *)psoWarpSrc + 0x40), &vec);
            psoWarp = STRUCT_OFFSET(pbarrier, 0x5A0, SO *);
            (*(void (**)(SO *, VECTOR *))((char *)psoWarp->pvtlo + 0x84))(psoWarp, &vec);
            pvResult = STRUCT_OFFSET(pbarrier, 0x5A0, void *);
        }
        else
        {
            pvResult = STRUCT_OFFSET(pbarrier, 0x5A0, void *);
        }

        STRUCT_OFFSET(pbarrier, 0x5A0, void *) = NULL;
        STRUCT_OFFSET(pbarrier, 0x5A4, void *) = pvResult;
    }
}
#endif // SKIP_ASM

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

#include <splice/vecmat.h>
#include <sce/memset.h>
#include <splice/gc.h>
#include <slotheap.h>
#include <memory.h>

/**
 * @todo Once the data for this TU is migrated the code can be made much simpler.
 */

extern int _t18CStructTypeFactory1Z6VECTOR$s_cmax;
extern int _t18CStructTypeFactory1Z7MATRIX4$s_cmax;
extern int _t18CStructTypeFactory1Z3CLQ$s_cmax;
extern int _t18CStructTypeFactory1Z2LM$s_cmax;
extern int _t18CStructTypeFactory1Z3SMP$s_cmax;

extern byte *_t18CStructTypeFactory1Z6VECTOR$s_acref;
extern byte *_t18CStructTypeFactory1Z7MATRIX4$s_acref;
extern byte *_t18CStructTypeFactory1Z3CLQ$s_acref;
extern byte *_t18CStructTypeFactory1Z2LM$s_acref;
extern byte *_t18CStructTypeFactory1Z3SMP$s_acref;

extern SLOTHEAP _t18CStructTypeFactory1Z6VECTOR$s_slotheap;
extern SLOTHEAP _t18CStructTypeFactory1Z7MATRIX4$s_slotheap;
extern SLOTHEAP _t18CStructTypeFactory1Z3CLQ$s_slotheap;
extern SLOTHEAP _t18CStructTypeFactory1Z2LM$s_slotheap;
extern SLOTHEAP _t18CStructTypeFactory1Z3SMP$s_slotheap;

VECTOR *PvectorNew()
{
    VECTOR *pvector = (VECTOR *)PvAllocSlotheapUnsafe(&_t18CStructTypeFactory1Z6VECTOR$s_slotheap);
    if (pvector)
    {
        memset(pvector, 0, _t18CStructTypeFactory1Z6VECTOR$s_slotheap.cb);
    }
    else
    {
        g_gc.Collect();
        pvector = (VECTOR *)PvAllocSlotheapClearImpl(&_t18CStructTypeFactory1Z6VECTOR$s_slotheap);
    }

    return pvector;
}

void IncrefVector(VECTOR *pvector)
{
    // TODO: Size of VECTOR should be 16 bytes.
    _t18CStructTypeFactory1Z6VECTOR$s_acref[((uint)pvector - (uint)_t18CStructTypeFactory1Z6VECTOR$s_slotheap.ab) / 16]++;
}

void DecrefVector(VECTOR *pvector)
{
    // TODO: Size of VECTOR should be 16 bytes.
    uint index = ((uint)pvector - (uint)_t18CStructTypeFactory1Z6VECTOR$s_slotheap.ab) / 16;

    if (--_t18CStructTypeFactory1Z6VECTOR$s_acref[index])
        return;

    FreeSlotheapPv(&_t18CStructTypeFactory1Z6VECTOR$s_slotheap, pvector);
}

JUNK_NOP();
JUNK_ADDIU(10);

MATRIX4 *PmatrixNew()
{
    MATRIX4 *pmatrix = (MATRIX4 *)PvAllocSlotheapUnsafe(&_t18CStructTypeFactory1Z7MATRIX4$s_slotheap);
    if (pmatrix)
    {
        memset(pmatrix, 0, _t18CStructTypeFactory1Z7MATRIX4$s_slotheap.cb);
    }
    else
    {
        g_gc.Collect();
        pmatrix = (MATRIX4 *)PvAllocSlotheapClearImpl(&_t18CStructTypeFactory1Z7MATRIX4$s_slotheap);
    }

    return pmatrix;
}

void IncrefMatrix(MATRIX4 *pmatrix)
{
    uint index = ((uint)pmatrix - (uint)_t18CStructTypeFactory1Z7MATRIX4$s_slotheap.ab) / sizeof(MATRIX4);
    _t18CStructTypeFactory1Z7MATRIX4$s_acref[index]++;
}

void DecrefMatrix(MATRIX4 *pmatrix)
{
    uint index = ((uint)pmatrix - (uint)_t18CStructTypeFactory1Z7MATRIX4$s_slotheap.ab) / sizeof(MATRIX4);

    if (--_t18CStructTypeFactory1Z7MATRIX4$s_acref[index])
        return;

    FreeSlotheapPv(&_t18CStructTypeFactory1Z7MATRIX4$s_slotheap, pmatrix);
}

void DeleteMatrix(MATRIX4 *pmatrix)
{
    FreeSlotheapPv(&_t18CStructTypeFactory1Z7MATRIX4$s_slotheap, pmatrix);
}
 
CLQ *PclqNew()
{
    CLQ *pclq = (CLQ *)PvAllocSlotheapUnsafe(&_t18CStructTypeFactory1Z3CLQ$s_slotheap);
    if (pclq)
    {
        memset(pclq, 0, _t18CStructTypeFactory1Z3CLQ$s_slotheap.cb);
    }
    else
    {
        g_gc.Collect();
        pclq = (CLQ *)PvAllocSlotheapClearImpl(&_t18CStructTypeFactory1Z3CLQ$s_slotheap);
    }

    return pclq;
}

void IncrefClq(CLQ *pclq)
{
    uint index = ((uint)pclq - (uint)_t18CStructTypeFactory1Z3CLQ$s_slotheap.ab) / sizeof(CLQ);
    _t18CStructTypeFactory1Z3CLQ$s_acref[index]++;
}

void DecrefClq(CLQ *pclq)
{
    uint index = ((uint)pclq - (uint)_t18CStructTypeFactory1Z3CLQ$s_slotheap.ab) / sizeof(CLQ);

    if (--_t18CStructTypeFactory1Z3CLQ$s_acref[index])
        return;

    FreeSlotheapPv(&_t18CStructTypeFactory1Z3CLQ$s_slotheap, pclq);
}

JUNK_NOP();
JUNK_ADDIU(10);

LM *PlmNew()
{
    LM *plm = (LM *)PvAllocSlotheapUnsafe(&_t18CStructTypeFactory1Z2LM$s_slotheap);
    if (plm)
    {
        memset(plm, 0, _t18CStructTypeFactory1Z2LM$s_slotheap.cb);
    }
    else
    {
        g_gc.Collect();
        plm = (LM *)PvAllocSlotheapClearImpl(&_t18CStructTypeFactory1Z2LM$s_slotheap);
    }

    return plm;
}

void IncrefLm(LM *plm)
{
    uint index = ((uint)plm - (uint)_t18CStructTypeFactory1Z2LM$s_slotheap.ab) / sizeof(LM);
    _t18CStructTypeFactory1Z2LM$s_acref[index]++;
}

void DecrefLm(LM *plm)
{
    uint index = ((uint)plm - (uint)_t18CStructTypeFactory1Z2LM$s_slotheap.ab) / sizeof(LM);

    if (--_t18CStructTypeFactory1Z2LM$s_acref[index])
        return;

    FreeSlotheapPv(&_t18CStructTypeFactory1Z2LM$s_slotheap, plm);
}

JUNK_NOP();
JUNK_ADDIU(10);

SMP *PsmpNew()
{
    SMP *psmp = (SMP *)PvAllocSlotheapUnsafe(&_t18CStructTypeFactory1Z3SMP$s_slotheap);
    if (psmp)
    {
        memset(psmp, 0, _t18CStructTypeFactory1Z3SMP$s_slotheap.cb);
    }
    else
    {
        g_gc.Collect();
        psmp = (SMP *)PvAllocSlotheapClearImpl(&_t18CStructTypeFactory1Z3SMP$s_slotheap);
    }

    return psmp;
}

void IncrefSmp(SMP *psmp)
{
    uint index = ((uint)psmp - (uint)_t18CStructTypeFactory1Z3SMP$s_slotheap.ab) / sizeof(SMP);
    _t18CStructTypeFactory1Z3SMP$s_acref[index]++;
}

void DecrefSmp(SMP *psmp)
{
    uint index = ((uint)psmp - (uint)_t18CStructTypeFactory1Z3SMP$s_slotheap.ab) / sizeof(SMP);

    if (--_t18CStructTypeFactory1Z3SMP$s_acref[index])
        return;

    FreeSlotheapPv(&_t18CStructTypeFactory1Z3SMP$s_slotheap, psmp);
}

void StartupSpliceStructuredTypeFactories()
{
    // TODO: Size of VECTOR should be 16 bytes.
    CreateSlotheapSw(&_t18CStructTypeFactory1Z6VECTOR$s_slotheap, 0x10, _t18CStructTypeFactory1Z6VECTOR$s_cmax);
    _t18CStructTypeFactory1Z6VECTOR$s_acref = (byte *)PvAllocSwClearImpl(_t18CStructTypeFactory1Z6VECTOR$s_cmax);

    CreateSlotheapSw(&_t18CStructTypeFactory1Z7MATRIX4$s_slotheap, sizeof(MATRIX4), _t18CStructTypeFactory1Z7MATRIX4$s_cmax);
    _t18CStructTypeFactory1Z7MATRIX4$s_acref = (byte *)PvAllocSwClearImpl(_t18CStructTypeFactory1Z7MATRIX4$s_cmax);

    CreateSlotheapSw(&_t18CStructTypeFactory1Z3CLQ$s_slotheap, sizeof(CLQ), _t18CStructTypeFactory1Z3CLQ$s_cmax);
    _t18CStructTypeFactory1Z3CLQ$s_acref = (byte *)PvAllocSwClearImpl(_t18CStructTypeFactory1Z3CLQ$s_cmax);

    CreateSlotheapSw(&_t18CStructTypeFactory1Z2LM$s_slotheap, sizeof(LM) ,_t18CStructTypeFactory1Z2LM$s_cmax);
    _t18CStructTypeFactory1Z2LM$s_acref = (byte *)PvAllocSwClearImpl(_t18CStructTypeFactory1Z2LM$s_cmax);

    CreateSlotheapSw(&_t18CStructTypeFactory1Z3SMP$s_slotheap, sizeof(SMP), _t18CStructTypeFactory1Z3SMP$s_cmax);
    _t18CStructTypeFactory1Z3SMP$s_acref = (byte *)PvAllocSwClearImpl(_t18CStructTypeFactory1Z3SMP$s_cmax);
}

void ShutdownSpliceStructuredTypeFactories()
{
    return;
}

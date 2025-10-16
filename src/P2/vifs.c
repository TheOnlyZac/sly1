#include <vifs.h>

VIFS::VIFS()
{
    m_fPad = 1;
    m_unMask = 0;
    m_fCheckCnt = 0;
}

JUNK_NOP();
JUNK_ADDIU(10);

INCLUDE_ASM("asm/nonmatchings/P2/vifs", Align__4VIFSi);

void VIFS::AddVifBaseOffset(int iqwBase, int diqwOffset)
{
    AddDmaInt(this, iqwBase | 0x03000000);
    AddDmaInt(this, diqwOffset | 0x02000000);
}

/**
 * @todo Figure out why using the inlined function doesn't work here.
 */
void VIFS::AddVifMscal(void *pv)
{
    int i = (int)pv < 0 ? (int)pv + 7 : (int)pv;
    uchar *p = m_pb;
    m_pb = p + 4;
    *(int *)p = (i >> 3) | 0x14000000;
}

/**
 * @todo Figure out why using the inlined function doesn't work here.
 */
void VIFS::AddVifMscalf(void *pv)
{
    int i = (int)pv < 0 ? (int)pv + 7 : (int)pv;
    uchar *p = m_pb;
    m_pb = p + 4;
    *(int *)p = (i >> 3) | 0x15000000;
}

void VIFS::AddVifFlush()
{
    AddDmaInt(this, 0x11000000);
}

void VIFS::AddVifFlusha()
{
    AddDmaInt(this, 0x13000000);
}

void VIFS::AddVifFlushe()
{
    AddDmaInt(this, 0x10000000);
}

void VIFS::AddVifStcycl(int wl, int cl)
{
    AddDmaInt(this, cl | (wl << 8) | 0x1000000);
}

INCLUDE_ASM("asm/nonmatchings/P2/vifs", AddVifStrow__4VIFSP2QW);

INCLUDE_ASM("asm/nonmatchings/P2/vifs", AddVifStmask__4VIFSUi);

INCLUDE_ASM("asm/nonmatchings/P2/vifs", CbUnpackSetup__4VIFS3UPKii);

INCLUDE_ASM("asm/nonmatchings/P2/vifs", UnpackHelper__4VIFS3UPKiiPiPPUi);

INCLUDE_ASM("asm/nonmatchings/P2/vifs", AddVifUnpack__4VIFS3UPKiPvi);

INCLUDE_ASM("asm/nonmatchings/P2/vifs", AddVifUnpackRefs__4VIFS3UPKiPviPPPv);

/**
 * @todo Figure out why using the inlined function doesn't work here.
 */
void VIFS::AddVifDirect(int cqw, QW *aqw, int fInt)
{
    Align(3);
    
    uchar *p = m_pb;
    m_pb = p + 4;
    *(int *)p = cqw | 0x50000000 | (fInt << 31);
    
    AddDmaBulk(cqw, aqw);
}

/**
 * @todo Figure out why using the inlined function doesn't work here.
 */
void VIFS::AddVifDirectRefs(int cqw, QW *aqw, int fInt)
{
    Align(3);
    
    uchar *p = m_pb;
    m_pb = p + 4;
    *(int *)p = cqw | 0x50000000 | (fInt << 31);
    
    AddDmaRefs(cqw, aqw);
}

void VIFS::AddVifGifs(GIFS *pgifs)
{
    AddVifDirect((uint)(pgifs->m_pb - pgifs->m_ab) >> 4, (QW *)pgifs->m_ab, 0);
}

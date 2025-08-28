#include <gifs.h>

/**
 * @todo 100% match, but checksum check fails.
 */
INCLUDE_ASM(const s32, "P2/gifs", __4GIFS);
/*
GIFS::GIFS()
{
    m_fEndPrim = 1;
    m_pqwPrim = 0;
    m_creg = 0;
    m_cregAll = 0;
}
*/

INCLUDE_ASM(const s32, "P2/gifs", AddPrimEnd__4GIFS);

INCLUDE_ASM(const s32, "P2/gifs", EndPrim__4GIFSi);

void GIFS::CheckReg(int fExpectPack, int regExpect)
{
    m_cregAll++;
}

INCLUDE_ASM(const s32, "P2/gifs", AddPrimBulk__4GIFSiiiUlPP2QW);

INCLUDE_ASM(const s32, "P2/gifs", AddPrimPack__4GIFSiiUl);

void GIFS::PackRGBA(uint rgba)
{
    CheckReg(1, 1);
    QW *pqw = ((QW *)m_pb)++;
    pqw->aun[0] = (rgba) & 0xff;
    pqw->aun[1] = (rgba & 0xff00) >> 8;
    pqw->aun[2] = (rgba >> 16) & 0xff;
    pqw->aun[3] = (rgba >> 24) & 0xff;
}

void GIFS::PackUV(int u, int v)
{
    CheckReg(1, 3);
    QW *pqw = ((QW *)m_pb)++;
    pqw->an[0] = u;
    pqw->an[1] = v;
}

INCLUDE_ASM(const s32, "P2/gifs", PackSTQ__4GIFSfff);

void GIFS::PackXYZ(int x, int y, int z)
{
    CheckReg(1, 5);
    QW *pqw = ((QW *)m_pb)++;
    pqw->an[0] = x;
    pqw->an[1] = y;
    pqw->al[1] = z;
}

void GIFS::PackXYZF(int x, int y, int z, int fog)
{
    CheckReg(1, 4);
    QW *pqw = ((QW *)m_pb)++;
    pqw->an[0] = x;
    pqw->an[1] = y;
    pqw->an[2] = z;
    pqw->an[3] = (fog & 0xff) << 4;
}

INCLUDE_ASM(const s32, "P2/gifs", PackXYZFNoKick__4GIFSiiii);

void GIFS::PackAD(long int a, long int d)
{
    CheckReg(1, 14);
    QW *pqw = ((QW *)m_pb)++;
    pqw->aul[0] = d;
    pqw->aul[1] = a;
}

INCLUDE_ASM(const s32, "P2/gifs", junk_00161760);

INCLUDE_ASM(const s32, "P2/gifs", AddPrimList__4GIFSiUl);

INCLUDE_ASM(const s32, "P2/gifs", ListRGBAQ__4GIFSUif);

INCLUDE_ASM(const s32, "P2/gifs", junk_00161858);

INCLUDE_ASM(const s32, "P2/gifs", ListUV__4GIFSii);

INCLUDE_ASM(const s32, "P2/gifs", ListXYZF__4GIFSiiii);

INCLUDE_ASM(const s32, "P2/gifs", junk_00161950);

INCLUDE_ASM(const s32, "P2/gifs", AddImage__4GIFSi);

#include <glbs.h>
#include <sw.h>
#include <sce/memset.h>

INCLUDE_ASM("asm/nonmatchings/P2/glbs", __4GLBS);

GLBS::~GLBS()
{
    return;
}

void GLBS::SetTransform(VECTOR *ppos, MATRIX3 *pmat)
{
    EndStrip();
    LoadMatrixFromPosRot(ppos, pmat, &m_rgld.matObjectToWorld);
    LoadMatrixFromPosRotInverse(ppos, pmat, &m_rgld.matWorldToObject);
}

void GLBS::FindLights(VECTOR *ppos, float sRadius)
{
    if (m_pshd->shdk != SHDK_ThreeWay)
    {
        m_cplightStatic = 0;
        m_cplightAll = 0;
        m_rgld.trlk = TRLK_Nil;
        return;
    }

    m_rgld.twps = TwpsFindSwLights(g_psw, ppos, sRadius, 1, 0x10, &m_cplightStatic, &m_cplightAll, m_aplight);
    m_rgld.trlk = TRLK_Quick;
}

void GLBS::ResetStrip()
{
    m_pshd = NULL;
    m_cvtxg = 0;
    memset(m_avtxg, 0, 148 * sizeof(VTXG));
}

INCLUDE_ASM("asm/nonmatchings/P2/glbs", BeginStrip__4GLBSP3SHD);

INCLUDE_ASM("asm/nonmatchings/P2/glbs", DrawPrelit__4GLBS);

INCLUDE_ASM("asm/nonmatchings/P2/glbs", DrawThreeWay__4GLBS);

INCLUDE_ASM("asm/nonmatchings/P2/glbs", EndStrip__4GLBS);

void GLBS::SetNormal(VECTOR *ppos)
{
    STRUCT_OFFSET(this, 0xFC, float) = ppos->x;
    STRUCT_OFFSET(this, 0x100, float) = ppos->y;
    STRUCT_OFFSET(this, 0x104, float) = ppos->z;
}

JUNK_NOP();
JUNK_WORD(0xE4800110);

extern "C" void SetRgba__4GLBSG4RGBA(GLBS *pglbs, RGBA *prgba)
{
    struct PACK { int v; } __attribute__((packed));
    *(PACK *)((char *)pglbs + 0x114) = *(PACK *)prgba;
}

void GLBS::SetUv(UVF *puv)
{
    struct PACK { long long v; } __attribute__((packed));
    *(PACK *)((char *)this + 0x118) = *(PACK *)puv;
}

INCLUDE_ASM("asm/nonmatchings/P2/glbs", AddVtx__4GLBSi);

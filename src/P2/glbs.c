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
    m_pshd = (SHD *)nullptr;
    m_cvtxg = 0;
    memset(m_avtxg, 0, 148 * sizeof(VTXG));
}

INCLUDE_ASM("asm/nonmatchings/P2/glbs", BeginStrip__4GLBSP3SHD);

INCLUDE_ASM("asm/nonmatchings/P2/glbs", DrawPrelit__4GLBS);

INCLUDE_ASM("asm/nonmatchings/P2/glbs", DrawThreeWay__4GLBS);

INCLUDE_ASM("asm/nonmatchings/P2/glbs", EndStrip__4GLBS);

INCLUDE_ASM("asm/nonmatchings/P2/glbs", SetNormal__4GLBSP6VECTOR);

JUNK_WORD(0xE4800110);

INCLUDE_ASM("asm/nonmatchings/P2/glbs", SetRgba__4GLBSG4RGBA);

INCLUDE_ASM("asm/nonmatchings/P2/glbs", SetUv__4GLBSP3UVF);

INCLUDE_ASM("asm/nonmatchings/P2/glbs", AddVtx__4GLBSi);

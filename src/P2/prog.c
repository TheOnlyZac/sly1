#include <prog.h>
#include <dmas.h>
#include <util.h>
#include <shd.h>

CProg::CProg(RGBA *rgbaComplete, RGBA *rgbaRemain, RGBA *rgbaWarning, RGBA *rgbaTrouble)
{
    m_rgbaComplete = *rgbaComplete;
    m_rgbaRemain = *rgbaRemain;
    m_rgbaWarning = *rgbaWarning;
    m_rgbaTrouble = *rgbaTrouble;
    m_fActive = 0;
    m_cRetry = 0;
    m_nRemain = 0;
    m_nTarget = 0;
    m_nMax = 0;
}

void CProg::Begin()
{
    m_fActive = 0;
    m_cRetry = 0;
    m_nRemain = 0;
    m_nTarget = 0;
    m_nMax = 0;
}

void CProg::SetRemain(int nRemain)
{
    if (m_fActive != 0)
    {
        if (m_nTarget == 0)
        {
            m_nTarget = nRemain;
            m_nMax = nRemain << 1;
            ClearFrameBuffers();
        }
        else if (this->m_nRemain == nRemain)
        {
            m_cRetry = m_cRetry + 1;
        }
        else
        {
            m_cRetry = 0;
        }
        this->m_nRemain = nRemain;
        Draw();
    }
}

void CProg::End()
{
    m_fActive = 0;
    m_cRetry = 0;
    m_nRemain = 0;
    m_nTarget = 0;
    m_nMax = 0;
}

/**
 * @todo 34.96% matched
 * https://decomp.me/scratch/06mco
 *
 * @note Stack frame doesn't line up.
 */
INCLUDE_ASM(const s32, "P2/prog", Draw__5CProg);
#ifdef SKIP_ASM
#define UNK_CONST (float)0x43CE745D
void CProg::Draw() {
    DMAS dmas;
    RGBA bgColor;
    uint nMax;
    float truncated;
    float truncated2;
    float ratio;
    uint nMaxOriginal;
    int cRetry;
    byte bGreenFg;
    byte bBlueFg;
    byte bRedFg;

    nMax = this->m_nMax;
    nMaxOriginal = nMax;
    ratio = (this->m_nTarget * 620.0f) / nMax;

    //func_001611B8();
    dmas.AllocStatic(0x40, (QW *)0x0);
    dmas.AddDmaCnt();

    bRedFg = this->m_rgbaComplete.bRed;
    bGreenFg = this->m_rgbaComplete.bGreen;
    bBlueFg = this->m_rgbaComplete.bBlue;

    truncated = GTrunc(UNK_CONST) * 1.1f;
    GTrunc(UNK_CONST);

    //DrawRect_19DDA0(10.0f, (float) ((s32) ratio + 0xA), bRedFg, bGreenFg, bBlueFg, 0xFF);

    cRetry = this->m_cRetry;
    if (cRetry <= 0) {
        bgColor = this->m_rgbaRemain;
    } else if (cRetry == 1) {
        bgColor = this->m_rgbaWarning;
    } else {
        bgColor = this->m_rgbaTrouble;
    }

    truncated2 = GTrunc(UNK_CONST) * 1.1f;
    GTrunc(UNK_CONST);

    //DrawRect_19DDA0((f32) ((s32) ratio + 0xA), (f32) ((s32) nMaxOriginal + 0xA), bgColor.bRed, bgColor.bGreen, bgColor.bBlue, 0xFF);

    //func_00161200(); // might pass dmas as argument or be class method
    dmas.AddDmaEnd();
    dmas.EndDmaCnt();
    dmas.Detach(0, 0);

    //BlastAqwGifsBothFrames(0x0);
}
#endif

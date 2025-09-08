#include <prog.h>
#include <dmas.h>
#include <util.h>
#include <render.h>
#include <gs.h>

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

INCLUDE_ASM(const s32, "P2/prog", Draw__5CProg);
#ifdef SKIP_ASM
/**
 * @todo 34.05% matched.
 * Stack frame doesn't line up.
 * https://decomp.me/scratch/06mco
 */
void CProg::Draw() {
    QW aqwProgress[64];
    GIFS gifs = GIFS();
    RGBA fgColor, bgColor;
    float xLeft, yTop, xRight, yBottom;

    const float width = 620.0f;
    const float offsetY = 412.9091f;

    int totalWidth = (int)(((float)m_nTarget * width) / (float)m_nMax);
    int filledWidth = (int)((float)totalWidth * (float)(m_nTarget - m_nRemain) / (float)m_nTarget);

    gifs.AllocStatic(0x40, aqwProgress);
    gifs.AddDmaCnt();

    fgColor = m_rgbaComplete;

    xLeft = 10.0f;
    yTop = GTrunc(offsetY) * 1.1;
    xRight = (float)filledWidth + 10.0f;
    yBottom = GTrunc(offsetY) * 1.1 + 6.6;
    FillScreenRect(fgColor.bRed, fgColor.bGreen, fgColor.bBlue, 0xFF, xLeft, yTop, xRight, yBottom, &gifs);

    if (m_cRetry < 1) {
        bgColor = m_rgbaRemain;
    } else if (m_cRetry == 1) {
        bgColor = m_rgbaWarning;
    } else {
        bgColor = m_rgbaTrouble;
    }

    xLeft = filledWidth + 10.0f;
    yTop = GTrunc(offsetY) * 1.1;
    xRight = (float)totalWidth + 10.0f;
    yBottom = GTrunc(offsetY) * 1.1 + 6.6;
    FillScreenRect(bgColor.bRed, bgColor.bGreen, bgColor.bBlue, 0xFF, xLeft, yTop, xRight, yBottom, &gifs);

    gifs.AddPrimEnd();
    gifs.AddDmaEnd();
    gifs.EndDmaCnt();
    gifs.Detach(0x0, 0x0);
    BlastAqwGifsBothFrames(aqwProgress);
}
#endif

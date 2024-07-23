#include "common.h"
#include "prog.h"
#include "gs.h"

INCLUDE_ASM(const s32, "P2/prog", __5CProgG4RGBAN31);

void CProg::Begin()
{
    this->m_fActive = 0;
    this->m_cRetry = 0;
    this->m_nRemain = 0;
    this->m_nTarget = 0;
    this->m_nMax = 0;
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
    this->m_fActive = 0;
    this->m_cRetry = 0;
    this->m_nRemain = 0;
    this->m_nTarget = 0;
    this->m_nMax = 0;
}

INCLUDE_ASM(const s32, "P2/prog", Draw__5CProg);

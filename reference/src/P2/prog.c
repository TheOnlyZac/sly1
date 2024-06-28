/**
 * @file prog.cpp
 *
 * @brief Implements the CProg clas.
*/
#include <prog.h>

void CProg::Begin()

{
    this->m_nMax = 0;
    this->m_fActive = 0;
    this->m_cRetry = 0;
    this->m_nRemain = 0;
    this->m_nTarget = 0;
}

void CProg::SetRemain(int nRemain)
{
    if (this->m_fActive) {
        if (this->m_nTarget == 0) {
            this->m_nTarget = nRemain;
            this->m_nMax = nRemain << 1;
            /* todo: figure out where this comes from
            ClearFrameBuffers(); */
        }
        else {
            if (this->m_nRemain == nRemain) {
                this->m_cRetry += 1;
            }
            else {
                this->m_cRetry = 0;
            }
            this->m_nRemain = nRemain;
        }
        Draw();
    }
}

void CProg::Draw()
{
	// todo
	// ...
}

void CProg::End()

{
    this->m_nMax = 0;
    this->m_fActive = 0;
    this->m_cRetry = 0;
    this->m_nRemain = 0;
    this->m_nTarget = 0;
}

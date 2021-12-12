#include <prog.h>

void CProg::SetRemain(int nRemain)

{
    /* todo: define function
    ClearReset(); */
    if (this->m_fActive != 0) {
        if (this->m_nTarget == 0) {
            this->m_nTarget = nRemain;
            this->m_nMax = nRemain << 1;
            /* todo: define function
            ClearFrameBuffers(); */
        }
        else {
            if (this->m_nRemain == nRemain) {
                this->m_cRetry += 1;
            }
            else {
                this->m_cRetry = 0;
            }
        }
        this->m_nRemain = nRemain;
        /* todo: define function
        Draw(); */
    }
    return;
}
#include <dl.h>

extern void *D_0027B314; // global iterator list (DLI::s_pdliFirst)
#define s_pdliFirst (*(DLI**)&D_0027B314)

void InitDl(DL *pdl, int ibDle)
{
    pdl->ibDle = ibDle;
}

void ClearDl(DL *pdl)
{
    pdl->tail = nullptr;
    pdl->head = nullptr;
}

void ClearDle(DLE *pdle)
{
    pdle->prev = nullptr;
    pdle->next = nullptr;
}

DLE *PdleFromDlEntry(DL *pdl, void *pv)
{
    return (DLE *)((uchar *)pv + pdl->ibDle);
}

void AppendDlEntry(DL *pdl, void *pv)
{
    DLE *newEntry = PdleFromDlEntry(pdl, pv);
    if (pdl->tail == nullptr)
    {
        pdl->head = pv;
    }
    else
    {
        DLE *currentTail = PdleFromDlEntry(pdl, pdl->tail);
        newEntry->prev = pdl->tail;
        currentTail->next = pv;
    }
    pdl->tail = pv;
}

void PrependDlEntry(DL *pdl, void *pv)
{
    DLE *newEntry = PdleFromDlEntry(pdl, pv);
    if (pdl->head == nullptr)
    {
        pdl->tail = pv;
        pdl->head = pv;
    }
    else
    {
        DLE *currentHead = PdleFromDlEntry(pdl, pdl->head);
        newEntry->next = pdl->head;
        currentHead->prev = pv;
        pdl->head = pv;
    }
}

void InsertDlEntryBefore(DL *pdl, void *pvNext, void *pv)
{
    if (pvNext == nullptr)
    {
        AppendDlEntry(pdl, pv);
    }
    else if (pvNext == pdl->head)
    {
        PrependDlEntry(pdl, pv);
    }
    else
    {
        DLE *newEntry = PdleFromDlEntry(pdl, pv);
        DLE *nextEntry = PdleFromDlEntry(pdl, pvNext);
        void *prevEntryPointer = nextEntry->prev;
        DLE *prevEntry = PdleFromDlEntry(pdl, prevEntryPointer);
        newEntry->next = pvNext;
        newEntry->prev = prevEntryPointer;
        nextEntry->prev = pv;
        prevEntry->next = pv;
    }
}

//  Pretty sure this is a STUB func. Asm shows the function is void and empty. -Zryu
INCLUDE_ASM(const s32, "P2/dl", func_001525F8);

void RemoveDlEntry(DL* pdl, void* pv)
{
    DLE* pentry;
    DLI* pcurrent;
    void* pprev;
    DLE* ptemp;

    pentry = PdleFromDlEntry(pdl, pv);
    pcurrent = s_pdliFirst;

    // Loop through global iterator list to find DLI that houses the DLE we're looking for.
    while (pcurrent != nullptr)
    {
        if ((DLE *)pcurrent->m_ppv == pentry)
        {
            // If the DLE is the current index of the DLI, replace the with prev.
            pprev = pentry->prev;
            if (pprev != nullptr)
            {
                ptemp = PdleFromDlEntry(pdl, pprev);
                (DLE *)pcurrent->m_ppv = ptemp;
            }
            else
            {
                (DLE *)pcurrent->m_ppv = pdl;
            }
        }

        pcurrent = pcurrent->m_pdliNext;
    }

    // Adjust head
    pprev = pentry->prev;
    if (pprev != nullptr)
    {
        ptemp = PdleFromDlEntry(pdl, pprev);
        ptemp->next = pentry->next;
    }
    else
    {
        pdl->head = pentry->next;
    }

    // Adjust tail
    pprev = pentry->next;
    if (pprev != nullptr)
    {
        ptemp = PdleFromDlEntry(pdl, pprev);
        ptemp->prev = pentry->prev;
    }
    else
    {
        pdl->tail = pentry->prev;
    }

    // Clear links
    pentry->next = nullptr;
    pentry->prev = nullptr;
}

bool FFindDlEntry(DL *pdl, void *pv)
{
    DLE *pdle = PdleFromDlEntry(pdl, pv);
    return (pdle->next != 0) || (pdl->tail == pv);
}

bool FIsDlEmpty(DL *pdl)
{
    return pdl->head == nullptr;
}

void MergeDl(DL* pdlDst, DL* pdlSrc)
{

    if (pdlSrc->head)
    {

        if (pdlDst->head == nullptr)
        {
            memcpy(pdlDst, pdlSrc, 12);
            ClearDl(pdlSrc);
            return;
        }

        DLE* pdstTail = PdleFromDlEntry(pdlDst, pdlDst->tail);
        DLE* psrcHead = PdleFromDlEntry(pdlSrc, pdlSrc->head);

        pdstTail->next = pdlSrc->head;
        psrcHead->prev = pdlDst->tail;

        pdlDst->tail = pdlSrc->tail;
        ClearDl(pdlSrc);
    }
}

int CPvDl(DL *pdl)
{
    void *pCurItem = pdl->head;
    int iCount = 0;

    if (pCurItem != 0)
    {
        while (pCurItem)
        {
            DLE *pDle = (DLE *)((unsigned char *)pCurItem + pdl->ibDle);

            pCurItem = pDle->next;
            iCount++;
        }
    }
    return iCount;
}

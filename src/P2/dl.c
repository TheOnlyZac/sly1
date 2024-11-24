#include "common.h"
#include <dl.h>

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
    return (DLE *)((u8 *)pv + pdl->ibDle);
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
        void* prevEntryPointer = nextEntry->prev;
        DLE *prevEntry = PdleFromDlEntry(pdl, prevEntryPointer);
        newEntry->next = pvNext;
        newEntry->prev = prevEntryPointer;
        nextEntry->prev = pv;
        prevEntry->next = pv;
    }
}

INCLUDE_ASM(const s32, "P2/dl", func_001525F8);

INCLUDE_ASM(const s32, "P2/dl", RemoveDlEntry__FP2DLPv);

bool FFindDlEntry(DL *pdl, void *pv)
{
    DLE *pdle = PdleFromDlEntry(pdl, pv);
    return (pdle->next != 0) || (pdl->tail == pv);
}

bool FIsDlEmpty(DL *pdl)
{
    return pdl->head == nullptr;
}

INCLUDE_ASM(const s32, "P2/dl", MergeDl__FP2DLT0);

int CPvDl(DL* pdl)
{
  void* pCurItem = pdl->head;
  int iCount = 0;

  if (pCurItem != 0) {
    while(pCurItem) {
      DLE* pDle = (DLE*)((unsigned char*)pCurItem + pdl->ibDle);

      pCurItem = pDle->next;
      iCount++;
    }
  }
  return iCount;
}

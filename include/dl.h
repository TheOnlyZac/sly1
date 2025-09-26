/**
 * @file dl.h
 *
 * @brief Doubly-linked list.
 */
#ifndef DL_H
#define DL_H

#include "common.h"
#include <oid.h>

/**
 * @brief Doubly Linked list
 */
struct DL
{
    void *head;
    void *tail;
    int ibDle;
};

/**
 * @brief Doubly Linked list Element
 *
 * @param next Points to the next element in the chain.
 * @param prev Points to the previous element in the chain.
 */
struct DLE
{
    void *next;
    void *prev;
};

/**
 * @brief Doubly Linked-list Iterator. Used to iterate through DLs in the global list (Singly Linked-list).
 * 
 * @param m_pdl The actual doubly linked list the iterator is navigating.
 * @param m_ppv A pointer to the current element/node inside that list.
 * @param m_ibDle Offset the the DLE structure.
 * @param m_pdliNext Next DLI in the chain.
 */
struct DLI
{
    DL *m_pdl;
    void **m_ppv;
    int m_ibDle;
    DLI *m_pdliNext;
};

/**
 * @brief Unknown.
 */
struct DLIM
{
    // ...
};

/**
 * @brief Unknown.
 */
struct DLR
{
    OID oidChild;
    DLR *pdlrNext;
};

/**
 * @brief Initialize a doubly linked list.
 *
 * @param pdl Pointer to the doubly linked list.
 * @param ibDle Offset to the DLE structure within the list element.
 */
void InitDl(DL *pdl, int ibDle);

/**
 * @brief Clear a doubly linked list.
 *
 * @param pdl Pointer to the doubly linked list.
 */
void ClearDl(DL *pdl);

/**
 * @brief Clear a doubly linked list element.
 *
 * @param pdle Pointer to the doubly linked list element.
 */
void ClearDle(DLE *pdle);

/**
 * @brief Get the DLE structure from a list element.
 *
 * @param pdl Pointer to the doubly linked list.
 * @param pv Pointer to the list element.
 * @return Pointer to the DLE structure.
 */
DLE *PdleFromDlEntry(DL *pdl, void *pv);

/**
 * @brief Append an element to the end of the doubly linked list.
 *
 * @param pdl Pointer to the doubly linked list.
 * @param pv Pointer to the list element.
 */
void AppendDlEntry(DL *pdl, void *pv);

/**
 * @brief Prepend an element to the beginning of the doubly linked list.
 *
 * @param pdl Pointer to the doubly linked list.
 * @param pv Pointer to the list element.
 */
void PrependDlEntry(DL *pdl, void *pv);

/**
 * @brief Insert an element before a specified element in the doubly linked list.
 *
 * @param pdl Pointer to the doubly linked list.
 * @param pvNext Pointer to the element before which the new element will be inserted.
 * @param pv Pointer to the new list element.
 */
void InsertDlEntryBefore(DL *pdl, void *pvNext, void *pv);

/**
 * @brief Remove an element from the doubly linked list and manage the doubly linked list iterator, incase the element being removed is a current iterator for an DLI instance.
 *
 * @param pdl Doubly linked list to remove the element from.
 * @param pv Element to remove.
 */
void RemoveDlEntry(DL *pdl, void *pv);

/**
 * @brief Determine if a list element is in the doubly linked list.
 *
 * @param pdl Doubly linked list to search.
 * @param pv List element to search for.
 * @return true if the element is in the list, false otherwise.
 */
bool FFindDlEntry(DL *pdl, void *pv);

/**
 * @brief Check if the doubly linked list is empty.
 *
 * @param pdl Pointer to the doubly linked list.
 * @return true if the list is empty, false otherwise.
 */
bool FIsDlEmpty(DL *pdl);

/**
 * @brief Merge two doubly linked lists.
 *
 * @param pdlDst Destination doubly linked list.
 * @param pdlSrc Source doubly linked list.
 */
void MergeDl(DL *pdlDst, DL *pdlSrc);

/**
 * @brief Traverse a doubly linked list starting from the head and count the number of elements.
 *
 * @param pdl Pointer to the doubly linked list.
 * @return The number of elements in the doubly linked list.
 */
int CPvDl(DL *pdl);

#endif // DL_H

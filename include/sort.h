/**
 * @file sort.h
 */
#ifndef SORT_H
#define SORT_H

#include "common.h"

/**
 * @brief Comparison function pointer for sorting.
 */
typedef int (* PFNCMP)(void *, void *);

/**
 * @brief Swaps two entries in an array.
 * The swap is performed using 4-bytes at a time.
 *
 * @param afoo Pointer to the array.
 * @param cb   Size of each element in bytes.
 * @param i1   Index of the first element to swap.
 * @param i2   Index of the second element to swap.
 */
void SwapEntries(void *afoo, int cb, int i1, int i2);

/**
 * @brief Sorts an array in-place using the heap sort algorithm.
 *
 * @param afoo   Pointer to the array.
 * @param iMac   Number of elements in the array.
 * @param cb     Size of each element in bytes.
 * @param pfncmp Pointer to a comparison function.
 */
void HeapSort(void *afoo, int iMac, int cb, PFNCMP pfncmp);

#endif // SORT_H

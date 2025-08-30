/**
 * @file so.h
 *
 * @brief Scene objects.
*/
#ifndef SO_H
#define SO_H

#include <alo.h>

// Forward.
class CBinaryInputStream;

enum FSO
{
    FSO_FindChild = 0x1,
    FSO_FindImmediateChild = 0x2,
    FSO_FindParent = 0x3,
    FSO_FindNearest = 0x4,
    FSO_FindAll = 0x5,
    GRFFSO_FindMask = 0xFF,
    FSO_IncludeRemovedObjects = 0x100,
    FSO_ReturnActualCount = 0x200
};

typedef int GRFFSO;

/**
 * @brief Scene object.
 *
 * @todo Implement struct.
 */
struct SO : public ALO
{
    // ...
};

/**
 * @brief Initialize the given SO.
 *
 * @param pso Pointer to the SO.
 *
 * @todo Verify this is actually that function.
 */
void InitSo(SO *pso);

/**
 * @brief Event handler for SO added to world(?)
 *
 * @param pso Pointer to the SO.
 */
void OnSoAdd(SO *pso);

/**
 * @brief Event handler for SO removed from world(?)
 *
 * @param pso Pointer to the SO.
 */
void OnSoRemove(SO *pso);

/**
 * @brief Clones an SO.
 */
void CloneSo(SO *pso, SO *psoBase);

/**
 * @brief Load SO from BRX.
 *
 * @param pso Pointer to the SO.
 * @param pbis Pointer to the binary input stream.
 */
void LoadSoFromBrx(SO *pso, CBinaryInputStream *pbis);

#endif // SO_H

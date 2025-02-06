/**
 * @file brx.h
 *
 * @brief Binary Resource Archive.
 */
#ifndef BRX_H
#define BRX_H

#include "common.h"

/**
 * @todo 
 */
void LoadOptionsFromBrx(void *pvStruct, CBinaryInputStream *pbis);

/**
 * @brief Get the PLO index from a stock OID.
 */
uint IploFromStockOid(int oid);

#endif // BRX_H

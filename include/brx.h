/**
 * @file brx.h
 *
 * @brief Binary Resource Archive.
 */
#ifndef BRX_H
#define BRX_H

#include "common.h"

/**
 * @brief Builds the eopids array.
 */
void StartupBrx();

/**
 * @brief Get the PLO index from a stock OID.
 */
uint IploFromStockOid(int oid);

/**
 * @todo
 */
void LoadOptionsFromBrx(void *pvStruct, CBinaryInputStream *pbis);

#endif // BRX_H

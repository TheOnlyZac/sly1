/**
 * @file rs.h
 *
 * @note No functions are declared here.
 */
#ifndef RS_H
#define RS_H

#include "common.h"
#include <oid.h>

/**
 * @brief Unknown.
 *
 * @todo Figure out what this struct represents.
 */
struct RSMG
{
    OID oidRoot;
    OID oidSM;
    OID oidTriggerGoal;
    OID oidUntriggerGoal;
};

#endif // RS_H

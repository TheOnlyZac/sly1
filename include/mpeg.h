/**
 * @file mpeg.h
 *
 * @brief Mpeg video.
 */
#ifndef MPEG_H
#define MPEG_H

#include "common.h"
#include <oid.h>

class CMpeg
{
public:
    OID oid_1;
    OID oid_2;
    // todo

    void ExecuteOids();
    // void Execute(OID* oid);
    // void Start();
    // void Update();
    // void Finish();
};

extern CMpeg g_mpeg;

#endif // MPEG_H

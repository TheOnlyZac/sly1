/**
 * @file mpeg.h
 *
 * @brief Mpeg video.
 */
#ifndef MPEG_H
#define MPEG_H

#include "common.h"
#include <oid.h>
#include <bas.h>

class CMpeg
{
public:
    OID oid_1;
    OID oid_2;
    // todo

    void ExecuteOids();
    void Execute(OID *poid);
    void Start(CBinaryAsyncStream *pbas);
    void Update();
    void Finish();
};

void StartupMpeg();

extern CMpeg g_mpeg;

extern "C" void FUN_0018f0e8(CMpeg *pmpeg, void *pv);

extern "C" int FAccept__10CMpegAudioiPUc(void *pmpega, int cb, uchar *pb);

extern "C" void CbDemuxed__5CMpegi(CMpeg *pmpeg, int nParam);

extern "C" void Execute__5CMpeg(CMpeg *pmpeg, OID *poid);

#endif // MPEG_H

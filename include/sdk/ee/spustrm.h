/**
 * @file include/sdk/ee/spustrm.h
 *
 * @brief SPU audio streaming data structures for MPEG playback.
 */
#ifndef SCE_SPUSTRM_H
#define SCE_SPUSTRM_H

/**
 * @brief Header preface for SPU audio stream chunks.
 */
struct SpuStreamHeaderPreface
{
    char achId[4];
    int cbHeader;
};

/**
 * @brief Format parameters and loop points for SPU audio stream.
 */
struct SpuStreamHeader
{
    int ssk;
    int hz;
    int cchan;
    int cbInterleave;
    int ibLoopStart;
    int ibLoopEnd;
};

/**
 * @brief Body preface preceding audio sample payload chunks.
 */
struct SpuStreamBodyPreface
{
    char achId[4];
    int cbBody;
};

/**
 * @brief Full SPU audio stream header composed of prefaces and channel info.
 */
struct SpuStreamPreface
{
    SpuStreamHeaderPreface sshp;
    SpuStreamHeader ssh;
    SpuStreamBodyPreface ssbp;
};

#endif // SCE_SPUSTRM_H

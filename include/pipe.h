/**
 * @file pipe.h
 */
#ifndef PIPE_H
#define PIPE_H

#include "common.h"
#include <lo.h>
#include <vec.h>

/**
 * @class PIPE
 * @brief Pipe that JT can climb on.
 * @todo Implement the struct.
 */
struct PIPE : public LO
{
    /* 0x34 */ undefined4 unk;
    /* 0x38 */ DLE dlePipe;
    /* 0x40 */ VU_VECTOR normal; // TODO: Verify name.
    /* 0x50 */ int unk_0x50;
    /* 0x54 */ int unk_0x54;
    /* 0x58 */ int unk_0x58;
    /* 0x5C */ float unk_0x5c;
    /* 0x60 */ STRUCT_PADDING(1);
    /* 0x64 */ OID oid; // TODO: Verify name.
    /* 0x68 */ LO *plo; // TODO: Verify type and name.
};

void StartupPipe();

void ResetPipeList();

void InitPipe(PIPE *ppipe);

void OnPipeAdd(PIPE *ppipe);

void OnPipeRemove(PIPE *ppipe);

void PostPipeLoad(PIPE *ppipe);

void ClonePipe(PIPE *ppipe, PIPE *ppipeBase);

#endif // PIPE_H

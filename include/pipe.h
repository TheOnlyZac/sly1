/**
 * @file pipe.h
 */
#ifndef PIPE_H
#define PIPE_H

#include "common.h"
#include <lo.h>

/**
 * @class PIPE
 * @brief Pipe that JT can climb on.
 * @todo Implement the struct.
 */
struct PIPE : public LO
{
    // ...
};

void StartupPipe();

void ResetPipeList();

void InitPipe(PIPE *ppipe);

void OnPipeAdd(PIPE *ppipe);

void OnPipeRemove(PIPE *ppipe);

// void PostPipeLoad(); // TODO

void ClonePipe(PIPE *ppipe, PIPE *ppipeBase);

#endif // PIPE_H

/**
 * @file steppipe.h
 */
#ifndef STEPPIPE_H
#define STEPPIPE_H

#include "common.h"
#include <pipe.h>
#include <joy.h>
#include <jt.h>

void PostJtLoadPipe(JT *pjt);

void GetJtPipeGoalMat(JT *pjt, PIPE *ppipe, float s, MATRIX3 *pmat);

void PresetJtAccelPipe(JT *pjt);

void UpdateJtActivePipe(JT *pjt, JOY *pjoy);

void UpdateJtInternalXpsPipe(JT *pjt);

void SetJtJtpdk(JT *pjt, JTPDK jtpdk);

void PlaceJtOnPipe(JT *pjt, PIPE *ppipe);

#endif // STEPPIPE_H

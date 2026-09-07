/**
 * @file cplcy.h
 *
 * @brief Camera policy.
 *
 * @todo Either move the camera policy structs from cm.h here, or delete this header.
 */
#ifndef CPLCY_H
#define CPLCY_H

#include "common.h"
#include <cm.h>

void InitCplcy(CPLCY *pcplcy, CM *pcm);

void SetCpmanCpmt(CPMAN *pcpman, CPMT cpmt);

void PushCplookLookk(CPLOOK *pcplook, LOOKK lookk);

LOOKK LookkPopCplook(CPLOOK *pcplook);

LOOKK LookkCurCplook(CPLOOK *pcplook);

#endif // CPLCY_H

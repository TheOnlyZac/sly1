/**
 * @file stephang.h
 */
#ifndef STEPHANG_H
#define STEPHANG_H

#include "common.h"
#include <joy.h>
#include <jt.h>

// Forward.
struct BL;
struct FX;
struct ASEGBL;

typedef int GRFAHX;

void PostJtLoadSwing(JT *pjt, BL *ablSwing, ASEGBL **ppasegbl);

void AnticipateJtForce_(JT *pjt, SO *psoOther, VECTOR *pposOther, VECTOR *pdv, FX *afx);

void CalculateJtHangAccel(JT *pjt);

void PresetJtAccelHang(JT *pjt);

void AddJtExternalAccelerations(JT *pjt, XA *pxa, float dt);

void UpdateJtActiveHang(JT *pjt, JOY *pjoy);

void CheckJtUnhook(JT *pjt);

void UpdateJtHookOx(JT *pjt, LO *ploHook, int fHook);

void AddJtHookXps(JT *pjt, GRFAHX grfahx, LO *ploHook, VECTOR *pposHook, VECTOR *pvecHook, VECTOR *pposHang);

void GetJtHangHeading(JT *pjt, float *pradForward);

void UpdateJtIkHang(JT *pjt);

#endif // STEPHANG_H

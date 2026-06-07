#include <stephang.h>
#include <math.h>

INCLUDE_ASM("asm/nonmatchings/P2/stephang", PostJtLoadSwing__FP2JTP2BLPP6ASEGBL);

INCLUDE_ASM("asm/nonmatchings/P2/stephang", AnticipateJtForce__FP2JTP2SOP6VECTORT2P2FX);

INCLUDE_ASM("asm/nonmatchings/P2/stephang", CalculateJtHangAccel__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/stephang", PresetJtAccelHang__FP2JT);

void AddJtExternalAccelerations(JT *pjt, XA *pxa, float dt)
{
    SO *pso = STRUCT_OFFSET(pjt, 0x22AC, SO *);
    SO *psoBody = STRUCT_OFFSET(pso, 0x4, SO *);
    AddSoAcceleration(psoBody, (VECTOR *)((uint8_t *)pjt + 0x22D0));
    pso = STRUCT_OFFSET(pjt, 0x22AC, SO *);
    psoBody = STRUCT_OFFSET(pso, 0x4, SO *);
    AddSoAngularAcceleration(psoBody, (VECTOR *)((uint8_t *)pjt + 0x22E0));
}

INCLUDE_ASM("asm/nonmatchings/P2/stephang", UpdateJtActiveHang__FP2JTP3JOY);

INCLUDE_ASM("asm/nonmatchings/P2/stephang", CheckJtUnhook__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/stephang", UpdateJtHookOx__FP2JTP2LOi);

INCLUDE_ASM("asm/nonmatchings/P2/stephang", AddJtHookXps__FP2JTiP2LOP6VECTORN23);

void GetJtHangHeading(JT *pjt, float *pradForward)
{
    ALO *paloHook = STRUCT_OFFSET(pjt, 0x2204, ALO *);
    ALO *paloParent = STRUCT_OFFSET(paloHook, 0x18, ALO *);
    VECTOR vec;
    ConvertAloVec(paloParent, NULL, (VECTOR *)((uint8_t *)paloHook + 0x50), &vec);
    *pradForward = atan2f(vec.y, vec.x);
}

INCLUDE_ASM("asm/nonmatchings/P2/stephang", UpdateJtIkHang__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/stephang", FUN_001cdd98);

INCLUDE_ASM("asm/nonmatchings/P2/stephang", FUN_001cdf78);

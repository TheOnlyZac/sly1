#include <clip.h>

INCLUDE_ASM("asm/nonmatchings/P2/clip", PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/clip", FUN_00141b48);

INCLUDE_ASM("asm/nonmatchings/P2/clip", ClsgClipEdgeToObject__FP2SOP6VECTORT1iP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/clip", ClsgClipEdgeToObjectPruned__FP2SOP3BSPP6VECTORT2iP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/clip", ClsgClipCylinderToObject__FP2SOP6VECTORT1fiP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/clip", ClsgClipLineToSphere__FP6VECTORfT0T0iP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/clip", ClsgClipEdgeToSphere__FP6VECTORfT0T0iP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/clip", ClsgClipCylinderToSphere__FP6VECTORfT0T0fiP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/clip", ClsgClipEdgeToCylinder__FP6VECTORT0fT0T0iP3LSG);

JUNK_WORD(0x27BD01C0);

int SgnCompareMaa(MAA *pmaa1, MAA *pmaa2)
{
    float d = pmaa1->u - pmaa2->u;
    if (d < -1e-4f)
        return -1;
    if (1e-4f < d)
        return 1;
    return pmaa1->iu - pmaa2->iu;
}

INCLUDE_ASM("asm/nonmatchings/P2/clip", ClsgMergeAlsg__FiP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/clip", ClsgClipCylinderToBsp__FP4BSPCP4GEOMP6VECTORT2fiP3LSG);

JUNK_WORD(0x27BD0120);

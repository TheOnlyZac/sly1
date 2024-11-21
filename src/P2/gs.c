#include "common.h"
#include <gs.h>

INCLUDE_ASM(const s32, "P2/gs", BlendDisplayOnBufferMismatch__Fv);

INCLUDE_ASM(const s32, "P2/gs", VBlankS_Interrupt__Fi);

INCLUDE_ASM(const s32, "P2/gs", SyncVBlank__Fv);

INCLUDE_ASM(const s32, "P2/gs", SwapGsBuffers__Fv);

INCLUDE_ASM(const s32, "P2/gs", RestoreGsBuffers__Fv);

INCLUDE_ASM(const s32, "P2/gs", GS_Interrupt__Fi);

INCLUDE_ASM(const s32, "P2/gs", ResetGs__Fv);

INCLUDE_ASM(const s32, "P2/gs", SendDmaSyncGsFinish__FP10sceDmaChanP2QW);

INCLUDE_ASM(const s32, "P2/gs", BuildClearGifs__FP2QWG4RGBAi);

INCLUDE_ASM(const s32, "P2/gs", StartupGs__Fv);

INCLUDE_ASM(const s32, "P2/gs", BlastAqwGifsBothFrames__FP2QW);

INCLUDE_ASM(const s32, "P2/gs", ClearFrameBuffers__Fv);

INCLUDE_ASM(const s32, "P2/gs", FadeFramesToBlack__Ff);

INCLUDE_ASM(const s32, "P2/gs", ResetGsMemory__Fv);

INCLUDE_ASM(const s32, "P2/gs", NLog2__FUi);

void InitGsb(GSB *set_igs_value,int igs_initial_amount,int igs_maximum_amount)

{
  set_igs_value->igsMac = igs_initial_amount;
  set_igs_value->igsMin = igs_initial_amount;
  set_igs_value->igsMax = igs_maximum_amount;
}

INCLUDE_ASM(const s32, "P2/gs", ResetGsb__FP3GSB);

INCLUDE_ASM(const s32, "P2/gs", IgsAllocGsb__FP3GSBi);

INCLUDE_ASM(const s32, "P2/gs", BuildImageGifs__FiiiiiiP4GIFS);

INCLUDE_ASM(const s32, "P2/gs", BuildClutTex2__FP4CLUTi);

INCLUDE_ASM(const s32, "P2/gs", BuildClutGifs__FP4CLUTiP4GIFS);

INCLUDE_ASM(const s32, "P2/gs", BuildBmpTex0__FP3BMPi);

INCLUDE_ASM(const s32, "P2/gs", BuildBmpGifs__FP3BMPiP4GIFS);

INCLUDE_ASM(const s32, "P2/gs", FBuildUploadBitmapGifs__FiP3GSBP4GIFS);

INCLUDE_ASM(const s32, "P2/gs", UploadBitmaps__FiP3GSB);

INCLUDE_ASM(const s32, "P2/gs", PqwGifsBitmapUpload__Fi);

INCLUDE_ASM(const s32, "P2/gs", PropagateSur__FP3SUR);

INCLUDE_ASM(const s32, "P2/gs", ReferenceShaderAqwRegs__FP3SHDP4SHDPP2QWiiP3SAI);

INCLUDE_ASM(const s32, "P2/gs", ReferenceUVAnimation__FP2QWiP3SAI);

INCLUDE_ASM(const s32, "P2/gs", RebaseSurs__FiiPvT2);

INCLUDE_ASM(const s32, "P2/gs", PropagateSurs__Fv);

INCLUDE_ASM(const s32, "P2/gs", PqwVifsBitmapUpload__Fi);

INCLUDE_ASM(const s32, "P2/gs", DrawOnBitmap__FP3BMPP4GIFS);

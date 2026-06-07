#include <shd.h>
#include <gs.h>
#include <blip.h>

extern GRFZON g_grfzonShaders;
extern byte *g_pbBulkData;

INCLUDE_ASM("asm/nonmatchings/P2/shd", Tex0FromTexIframeCtk__FP3TEXi3CTK);

INCLUDE_ASM("asm/nonmatchings/P2/shd", PackTexGifs__FP3TEXi3CTK4SHDKP4GIFS);

void LoadClutFromBrx(CBinaryInputStream *pbis, CLUT *pclut)
{
    pbis->Read(0xc, pclut);
    pclut->prgba = (RGBA *)(g_pbBulkData + (uint)pclut->prgba);
    pclut->cqwColors = (uint)pclut->crgba * 4 + 0xf >> 4;
}

INCLUDE_ASM("asm/nonmatchings/P2/shd", LoadColorTablesFromBrx__FP18CBinaryInputStream);

void LoadBmpFromBrx(CBinaryInputStream *pbis, BMP *pbmp)
{
    pbis->Read(0x14, pbmp);
    pbmp->pbPixels = (byte *)(g_pbBulkData + (int)pbmp->pbPixels);
    pbmp->cqwPixels = pbmp->cbPixels + 0xf >> 4;
}

INCLUDE_ASM("asm/nonmatchings/P2/shd", LoadBitmapsFromBrx__FP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/shd", LoadFontsFromBrx__FP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/shd", LoadTexFromBrx__FP18CBinaryInputStreamP3TEX);

INCLUDE_ASM("asm/nonmatchings/P2/shd", LoadShadersFromBrx__FP18CBinaryInputStream);

void UploadPermShaders()
{
    GSB gsbPerm;
    InitGsb(&gsbPerm, 0x1e00, 0x4000);
    UploadBitmaps(0x10000000, &gsbPerm);
    g_grfzonShaders = 0;
}

extern "C" {
    extern GSB D_002626D8;
    extern int D_002626CC;
}
void PropagateSurs();

void PropagateShaders(GRFZON grfzonCamera)
{
    PropagateSais();
    if (grfzonCamera != g_grfzonShaders)
    {
        ResetGsb(&D_002626D8);
        UploadBitmaps(grfzonCamera, &D_002626D8);
        FillShaders(grfzonCamera);
        PropagateSurs();
        PropagateBlipgShaders(grfzonCamera);
        D_002626CC = 2;
        g_grfzonShaders = grfzonCamera;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/shd", FillShaders__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/shd", UnloadShaders__Fv);

JUNK_WORD(0xE4A00008);

INCLUDE_ASM("asm/nonmatchings/P2/shd", ConvertRgbToHsv__FP6VECTORT0);

INCLUDE_ASM("asm/nonmatchings/P2/shd", ConvertHsvToRgb__FP6VECTORT0);

INCLUDE_ASM("asm/nonmatchings/P2/shd", ConvertUserHsvToUserRgb__FP6VECTORT0);

INCLUDE_ASM("asm/nonmatchings/P2/shd", ConvertUserRgbToUserHsv__FP6VECTORT0);

JUNK_ADDIU(10);
JUNK_NOP();
JUNK_NOP();
JUNK_ADDIU(50);

INCLUDE_ASM("asm/nonmatchings/P2/shd", PshdFindShader__F3OID);

INCLUDE_ASM("asm/nonmatchings/P2/shd", SetSaiIframe__FP3SAIi);

extern SAI *g_psaiUpdate;
extern SAI *g_psaiUpdateTail;

void SetSaiDuDv(SAI *psai, float du, float dv)
{
    SAI *psaiNext;

    if (!STRUCT_OFFSET(psai, 0x4, int))
        return;

    if (STRUCT_OFFSET(psai, 0xc, float) == du &&
        STRUCT_OFFSET(psai, 0x10, float) == dv)
        return;

    psaiNext = STRUCT_OFFSET(psai, 0x18, SAI *);
    STRUCT_OFFSET(psai, 0xc, float) = du;
    STRUCT_OFFSET(psai, 0x10, float) = dv;

    if (psaiNext != 0)
        return;

    if (psai == g_psaiUpdateTail)
        return;

    if (g_psaiUpdateTail == 0)
        g_psaiUpdateTail = psai;

    STRUCT_OFFSET(psai, 0x18, SAI *) = g_psaiUpdate;
    g_psaiUpdate = psai;
}

INCLUDE_ASM("asm/nonmatchings/P2/shd", PropagateSais__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/shd", UpdateShaders__Ff);

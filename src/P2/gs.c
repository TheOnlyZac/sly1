#include <gs.h>
#include <sdk/ee/eekernel.h>
#include <memory.h>
#include <gifs.h>

INCLUDE_ASM("asm/nonmatchings/P2/gs", BlendDisplayOnBufferMismatch__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/gs", VBlankS_Interrupt__Fi);

extern int D_002BE460;
extern int D_002BE46C;

void SyncVBlank()
{
    D_002BE46C = 1;
    WaitSema(D_002BE460);
}

INCLUDE_ASM("asm/nonmatchings/P2/gs", SwapGsBuffers__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/gs", RestoreGsBuffers__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/gs", GS_Interrupt__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/gs", ResetGs__Fv);

extern "C" int func_00202120();
extern "C" void func_00202058(int);
extern int D_002BE464;
extern int D_002BE468;

void SendDmaSyncGsFinish(sceDmaChan *pdc, QW *pqw)
{
    D_002BE468 = 1;
    *(volatile uint64_t *)0x12001000 |= 2;
    func_00202058(func_00202120() & ~0x200);
    FlushCache(0);
    sceDmaSend(pdc, pqw);
    WaitSema(D_002BE464);
}

INCLUDE_ASM("asm/nonmatchings/P2/gs", BuildClearGifs__FP2QWG4RGBAi);

INCLUDE_ASM("asm/nonmatchings/P2/gs", StartupGs__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/gs", BlastAqwGifsBothFrames__FP2QW);

extern QW D_002BE1A0[];

void ClearFrameBuffers()
{
    DMAS dmas;
    QW aqw[2];

    dmas.AllocStatic(2, aqw);
    dmas.AddDmaRefs(0x2C, D_002BE1A0);
    dmas.AddDmaEnd();
    dmas.Detach(NULL, NULL);
    BlastAqwGifsBothFrames(aqw);
}

INCLUDE_ASM("asm/nonmatchings/P2/gs", FadeFramesToBlack__Ff);

extern GSB D_002626D8;
extern int D_002626D0;

void ResetGsMemory()
{
    InitGsb(&D_002626D8, 0x1E00, 0x4000);
    D_002626D0 = 0;
}

uint NLog2(uint value)
{
    uint log2 = 0;
    uint bit = 1;

    while (bit < value && log2 < 31)
    {
        bit <<= 1;
        log2++;
    }

    return log2;
}

void InitGsb(GSB *pgsb, int igsMin, int igsMax)
{
    pgsb->igsMac = igsMin;
    pgsb->igsMin = igsMin;
    pgsb->igsMax = igsMax;
}

void ResetGsb(GSB *pGsb)
{
    pGsb->igsMac = pGsb->igsMin;
}

int IgsAllocGsb(GSB *pgsb, int iCount)
{
    int igsOld = pgsb->igsMac;
    pgsb->igsMac += iCount;
    return igsOld;
}

void BuildImageGifs(int dbp, int dbw, int psm, int dsax, int dsay, int cqw, GIFS *pgifs)
{
    pgifs->AddPrimPack(0, 1, 0xE);
    pgifs->PackAD(0x50, ((long)dbp << 32) | ((long)dbw << 48) | ((long)psm << 56));
    pgifs->PackAD(0x51, 0);
    pgifs->PackAD(0x52, (long)dsax | ((long)dsay << 32));
    pgifs->PackAD(0x53, 0);
    pgifs->AddImage(cqw);
}

INCLUDE_ASM("asm/nonmatchings/P2/gs", BuildClutTex2__FP4CLUTi);

INCLUDE_ASM("asm/nonmatchings/P2/gs", BuildClutGifs__FP4CLUTiP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/gs", BuildBmpTex0__FP3BMPi);

INCLUDE_ASM("asm/nonmatchings/P2/gs", BuildBmpGifs__FP3BMPiP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/gs", FBuildUploadBitmapGifs__FiP3GSBP4GIFS);

extern int g_cclutUpload;
extern int g_cbmpUpload;
int FBuildUploadBitmapGifs(int grfzon, GSB *pgsb, GIFS *pgifs);

void UploadBitmaps(GRFZON grfzon, GSB *pgsb)
{
    if (grfzon == 0)
        return;

    {
        GIFS gifs;
        QW *pqw;

        InitStackImpl();
        gifs.AllocStack(((g_cclutUpload * 3 + g_cbmpUpload) << 3) | 4);
        gifs.AddDmaCnt();
        if (FBuildUploadBitmapGifs(grfzon, pgsb, &gifs))
        {
            gifs.AddPrimPack(0, 1, 0xE);
            gifs.PackAD(0x3F, 0);
            gifs.PackAD(0x61, 0);
            gifs.AddPrimEnd();
            gifs.AddDmaEnd();
            gifs.Detach(NULL, &pqw);
            SendDmaSyncGsFinish(g_pdcGif, pqw);
        }
        FreeStackImpl();
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/gs", PqwGifsBitmapUpload__Fi);

void PropagateSur(SUR *psur)
{
    CopyAb(psur->pvDst, psur->pvSrc, psur->cb);
    
    if (psur->cvtx)
    {
        int *p = (int *)psur->pvDst;
        int v0 = p[0];
        int v1 = p[0x10 / 4];
        
        v0 |= 0x8000;
        v0 |= (int)psur->cvtx;
        v1 |= 0x8000;
        
        p[0] = v0;
        p[0x10 / 4] = v1;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/gs", ReferenceShaderAqwRegs__FP3SHDP4SHDPP2QWiiP3SAI);

INCLUDE_ASM("asm/nonmatchings/P2/gs", ReferenceUVAnimation__FP2QWiP3SAI);

INCLUDE_ASM("asm/nonmatchings/P2/gs", RebaseSurs__FiiPvT2);

extern SUR D_0027DC20[];

void PropagateSurs()
{
    int isur;

    for (isur = 0; isur < D_002626D0; isur++)
    {
        PropagateSur(&D_0027DC20[isur]);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/gs", PqwVifsBitmapUpload__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/gs", DrawOnBitmap__FP3BMPP4GIFS);

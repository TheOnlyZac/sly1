#include <cd.h>
#include <text.h>
#include <989snd.h>
#include <sdk/libcdvd.h>

extern int g_scecd;
extern int s_retCdRead;
extern int s_retCdError;
extern sceCdRMode s_cdmode;

INCLUDE_ASM("asm/nonmatchings/P2/cd", CpchzTokenizePath__FPc);

bool FValidCdMmode()
{
    // TODO: This is the only way I managed to get the code to match.
    // This might be possible to clean up, but I wasn't able to. - 545u
    int type = sceCdGetDiskType();
    if (g_scecd == type)
    {
        type = g_scecd;
    }
    else
    {
        g_scecd = type;
    }

    return g_scecd == SCECdPS2DVD;
}

void SetCdMmode()
{
    if (g_scecd == SCECdPS2DVD)
    {
        sceCdMmode(2);
    }
}

void StartupCd()
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/cd", UpdateCd__Fv);

extern short D_00249E20;
extern char D_00249E28[];
extern char D_00249E30[];
extern char D_00249E38[];

INCLUDE_ASM("asm/nonmatchings/P2/cd", CdPath__FPcT0i);
#ifdef SKIP_ASM
void CdPath(char *pchzDest, char *pchzPath, int fIncludeDevice)
{
    char achz[0x100];

    *(short *)achz = D_00249E20;
    strcpy1(achz, pchzPath);
    int ctoken = ((int (*)(char *))CpchzTokenizePath)(achz);
    if (1 < ctoken)
    {
        int itoken = ctoken - 1;
        do
        {
            achz[strlen(achz)] = '\\';
            itoken--;
        } while (itoken != 0);
    }

    char *pchzDevice;
    if (fIncludeDevice)
    {
        pchzDevice = D_00249E30;
    }
    else
    {
        pchzDevice = D_00249E38;
    }
    sprintf(pchzDest, D_00249E28, pchzDevice, achz);
}
#endif // SKIP_ASM

void ReadCd(uint isector, uint csector, void *pv)
{
    do
    {
        s_retCdRead = snd_StreamSafeCdRead(isector, csector, pv, &s_cdmode);
        if (s_retCdRead == 1)
        {
            break;
        }

        snd_StreamSafeCdSync(0);
        s_retCdError = snd_StreamSafeCdGetError();
    } while (true);
}

void ReadCdDirect(uint isector, uint csector, void *pv)
{
    do
    {
        s_retCdRead = sceCdRead(isector, csector, pv, &s_cdmode);
        if (s_retCdRead == 1)
        {
            break;
        }

        sceCdSync(0);
        s_retCdError = sceCdGetError();
    } while (true);
}

bool FCdCompleted(int fBlock)
{
    return !snd_StreamSafeCdSync(!fBlock);
}

JUNK_ADDIU(10);

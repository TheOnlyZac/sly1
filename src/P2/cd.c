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

INCLUDE_ASM("asm/nonmatchings/P2/cd", CdPath__FPcT0i);
#ifdef SKIP_ASM

// TODO: Remove once .rodata is migrated.
extern const char D_00249E28[]; // "%s\\%s"
extern const char D_00249E38[]; // 0x00000000
extern const char D_00249E30[]; // "cdrom0:"
extern const ushort D_00249E20; // '\\\0'

/**
 * @todo 80.87% match. Loop isn't matching correctly and rodata isn't migrated.
 */
void CdPath(char *pchzDst, char *pchzPath, int fIncludeDevice)
{
    char achzTokens[256];
    *((ushort *)achzTokens) = D_00249E20; // NOTE: Needed for the "lhu" instruction.
    strcpy1(achzTokens, pchzPath);

    int ctoken = CpchzTokenizePath(achzTokens);
    if (ctoken > 1)
    {
        for (int i = ctoken - 1; i != 0; i--)
        {
            achzTokens[strlen(achzTokens)] = '\\';
        }
    }

    sprintf(pchzDst, (char *)D_00249E28, (fIncludeDevice != 0) ? D_00249E30 : D_00249E38, achzTokens);
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

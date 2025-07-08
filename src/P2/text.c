#include <text.h>
#include <memory.h>

INCLUDE_ASM(const s32, "P2/text", CchParsePchzInt__FPcPi);

INCLUDE_ASM(const s32, "P2/text", CchParsePchzTft__FPcP3TFTPPc);

INCLUDE_ASM(const s32, "P2/text", WriteTftPchz__FP3TFTP5OSTRMPc);

INCLUDE_ASM(const s32, "P2/text", FNegTftUl__FP3TFTP2UL);

INCLUDE_ASM(const s32, "P2/text", UnRadixFromChConversion__Fc);

INCLUDE_ASM(const s32, "P2/text", CchAchFromUl__FPciUlUi);

INCLUDE_ASM(const s32, "P2/text", WriteTftUl__FP3TFTP5OSTRMUl);

INCLUDE_ASM(const s32, "P2/text", ExpFirstFromG__Fd);

INCLUDE_ASM(const s32, "P2/text", ChDigitFromG__Fdii);

INCLUDE_ASM(const s32, "P2/text", CchAchFromDouble__FPciP3TFTd);

INCLUDE_ASM(const s32, "P2/text", WriteTftDouble__FP3TFTP5OSTRMd);

INCLUDE_ASM(const s32, "P2/text", WriteTft__FP3TFTP5OSTRMPPcPci);

INCLUDE_ASM(const s32, "P2/text", CchOstrmPrintf__FP5OSTRMPcT1);

INCLUDE_ASM(const s32, "P2/text", vprintf);

INCLUDE_ASM(const s32, "P2/text", printf);

INCLUDE_ASM(const s32, "P2/text", vsprintf);

INCLUDE_ASM(const s32, "P2/text", sprintf);

INCLUDE_ASM(const s32, "P2/text", _vsnprintf);
INCLUDE_ASM(const s32, "P2/text", func_001E20B0);

INCLUDE_ASM(const s32, "P2/text", _snprintf);
INCLUDE_ASM(const s32, "P2/text", func_001E20F8);

extern "C" uint strlen(const char *pchz)
{
    uint len = 0;

    while(*pchz != '\0') {
        pchz++;
        len++;
    }

    return len;
}

extern "C" char *strcpy(char *dst, const char *src)
{
    CopyAb(dst, (char *)src, strlen(src) + 1);
    return dst;
}

// INCLUDE_ASM(const s32, "P2/text", strcpy1);
extern "C" char *strcpy1(char *dst, char *src)
{
    uint dstLength = strlen(dst);
    uint srcLength = strlen(src);
    CopyAb(dst + dstLength, src, srcLength + 1);
    return dst;
}

extern "C" char *strchr(char *pchz, int ch)
{
    while(*pchz != '\0')
    {
        if(*pchz == ch)
        {
            return pchz;
        }
        pchz++;
    }
    return (char *)nullptr;
}

INCLUDE_ASM(const s32, "P2/text", func_001E2210);

INCLUDE_ASM(const s32, "P2/text", UpperizePchz__FPc);

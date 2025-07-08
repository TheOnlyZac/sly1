#include <text.h>
#include <memory.h>
#include <stdarg.h>

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

extern "C" int printf(char *pchzFormat, ...) {
    va_list arg;
    va_start(arg, pchzFormat);
    int ret = vprintf(pchzFormat, arg);
    va_end(arg);
    return ret;
}

INCLUDE_ASM(const s32, "P2/text", vsprintf);

extern "C" int sprintf(char *pchzDest, char *pchzFormat, ...)
{
    va_list arg;
    va_start(arg, pchzFormat);
    int ret = vsprintf(pchzDest, pchzFormat, arg);
    va_end(arg);
    return ret;
}

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

extern "C" char *strcpy(char *pchzDst, const char *pchzSrc)
{
    CopyAb(pchzDst, (char *)pchzSrc, strlen(pchzSrc) + 1);
    return pchzDst;
}

extern "C" char *strcpy1(char *pchzDst, char *pchzSrc)
{
    uint dstLength = strlen(pchzDst);
    uint srcLength = strlen(pchzSrc);
    CopyAb(pchzDst + dstLength, pchzSrc, srcLength + 1);
    return pchzDst;
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

/**
 * @file text.h
 *
 * @brief Text manipulation functions.
 */
#ifndef TEXT_H
#define TEXT_H

#include "common.h"
#include <stream.h>

/**
 * @brief Text format value width.
 *
 * @note Based on may proto.
 */
enum TFVW
{
    TFVW_Nil = -1,
    TFVW_32 = 0,
    TFVW_16 = 1,
    TFVW_64 = 2,
    TFVW_Max = 3
};

/**
 * @brief Text format type.
 *
 * @note Based on may proto.
 */
enum TFTS
{
    TFTS_Nil = -1,
    TFTS_Percent = 0,
    TFTS_Flags = 1,
    TFTS_Width = 2,
    TFTS_Precision = 3,
    TFTS_Type = 4,
    TFTS_Conversion = 5,
    TFTS_Done = 6,
    TFTS_Max = 7
};

/**
 * @brief Text format structure.
 *
 * @note Based on may proto.
 */
struct TFT
{
    int fMinus;
    int fPlus;
    int fSpace;
    int fHash;
    int fZero;
    int fZeroPrecision;
    int cchWidth;
    int cchPrecision;
    TFVW tfvw;
    int cCol;
    int cRow;
    uchar chConversion;
    int fUpperize;
};

int CchParsePchzInt(char *pch, int *pn);
int CchParsePchzTft(char *pchzFormat, TFT *ptft, char **pval);
void WriteTftPchz(TFT *ptft, OSTRM *postrm, char *pchz);
int FNegTftUl(TFT *ptft, union UL *pul); // todo: define type of pul
uint UnRadixFromChConversion(int chConversion);
int CchAchFromUl(char *achDest, int cchDest, ulong ul, uint unRadix);
void WriteTftUl(TFT *ptft, OSTRM *postrm, ulong ul);
int ExpFirstFromG(long g);
char ChDigitFromG(long g, int expFirst, int exp);
int CchAchFromDouble(char *achDest, int cchDest, TFT *ptft, long g);
void WriteTftDouble(TFT *ptft, OSTRM *postrm, long g);
void WriteTft(TFT *ptft, OSTRM *postrm, char **pval, ulong param_4, ulong param_5, undefined8 param_6, double param_7);
int CchOstrmPrintf(OSTRM *postrm, char *pchzFormat, char *val);

extern "C"
{
    /**
     * @todo Document this function.
     */
    int vprintf(char *pchzFormat, char *val);

    /**
     * @brief Print formatted output to stdout.
     *
     * @param pchzFormat The format string.
     * @param ... The arguments to format.
     *
     * @return The number of characters written.
     */
    int printf(char *pchzFormat, ...);

    /**
     * @todo Document this function.
     */
    int vsprintf(char *pchzDest, char *pchzFormat, char *val);

    /**
     * @brief Write formatted output to a string.
     *
     * @param pchzDest The destination string.
     * @param pchzFormat The format string.
     * @param ... The arguments to format.
     *
     * @return The number of characters written.
     */
    int sprintf(char *pchzDest, char *pchzFormat, ...);

    /**
     * @todo Document this function.
     */
    int _vsnprintf(char *pchzDest, int cchDest, char *pchzFormat, char *val);

    /**
     * @brief Write formatted output to a string with a specified length.
     *
     * @param pchzDest The destination string.
     * @param cchDest The maximum number of characters to write.
     * @param pchzFormat The format string.
     * @param ... The arguments to format.
     *
     * @return The number of characters written.
     */
    int _snprintf(char *pchzDest, int cchDest, char *pchzFormat, ...);

    /**
     * @brief Count the number of characters in a string.
     *
     * @param pchz The string to count.
     */
    //uint strlen(char *pchz); // conflicts with built-in strlen

    /**
     * @brief Copy a string.
     *
     * @param pchzDst The destination string.
     * @param pchzSrc The source string.
     */
    //char *strcpy(char *pchzDst, char *pchzSrc); // conflicts with built-in strcpy

    /**
     * @brief Search for a character in a string.
     *
     * @param pchz The string to search.
     * @param ch The character to search for.
     *
     * @return A pointer to the first occurrence of the character in the string, or NULL if the character is not found.
     */
    char *strchr(char *pchz, int ch);
}

void UpperizePchz(char *pchz);

#endif // TEXT_H

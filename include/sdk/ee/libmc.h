/**
 * @file include/sdk/ee/libmc.h
 * @todo Verify that this is the correct directory.
 */
#ifndef LIBMC_H
#define LIBMC_H

typedef struct
{
    unsigned char Resv2;
    unsigned char Sec;
    unsigned char Min;
    unsigned char Hour;
    unsigned char Day;
    unsigned char Month;
    unsigned short Year;
} sceMcStDateTime;

typedef struct
{
    sceMcStDateTime _Create;
    sceMcStDateTime _Modify;
    unsigned int FileSizeByte;
    unsigned short AttrFile;
    unsigned short Reserve1;
    unsigned int Reserve2;
    unsigned int PdaAplNo;
    unsigned char EntryName[32];
} sceMcTblGetDir;

typedef int sceVu0IVECTOR[4];
typedef float sceVu0FVECTOR[4];

typedef struct
{
    unsigned char Head[4];
    unsigned short Reserv1;
    unsigned short OffsLF;
    unsigned int Reserv2;
    unsigned int TransRate;
    sceVu0IVECTOR BgColor[4];
    sceVu0FVECTOR LightDir[3];
    sceVu0FVECTOR LightColor[3];
    sceVu0FVECTOR Ambient;
    unsigned char TitleName[68];
    unsigned char FnameView[64];
    unsigned char FnameCopy[64];
    unsigned char FnameDel[64];
    unsigned char Reserve3[512];
} sceMcIconSys;

extern "C"
{
int sceMcInit();
};

#endif // LIBMC_H

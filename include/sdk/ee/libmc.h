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

extern "C"
{
int sceMcInit();
};

#endif // LIBMC_H

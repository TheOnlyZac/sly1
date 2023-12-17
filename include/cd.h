/**
 * @file cd.h
 *
 * @brief Declarations for the cd system.
*/
#ifndef CD_H
#define CD_H

/**
 * @brief CD State
*/
enum CDS
{
    CDS_Initing = 0,
    CDS_Searching = 1,
    CDS_Waiting = 2,
    CDS_Ready = 3,
    CDS_Dead = 4,
    CDS_Max = 5
};

// Global variables
extern CDS g_cds;

////void CpchzTokenizePath(char *);
////void FValidCdMmode(void);
////void SetCdMmode(void);
////void StartupCd(void);

/**
 * @brief Updates the cd system.
 *
 * @todo Implement this function.
*/
void UpdateCd(void);

////void CdPath(char *, char *, int);
////void ReadCd(unsigned int, unsigned int, void *);
////void ReadCdDirect(unsigned int, unsigned int, void *);
////void FCdCompleted(int);
////void ErrCdLatest(void);

#endif // CD_H

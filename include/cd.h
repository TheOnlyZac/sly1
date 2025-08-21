/**
 * @file cd.h
 *
 * @brief CD system.
 */
#ifndef CD_H
#define CD_H

#include "common.h"

/**
 * @brief CD State.
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

/**
 * @todo Unknown.
 */
void CpchzTokenizePath(char *pchzPath);

/**
 * @brief Checks if the disc is a PS2 DVD.
 */
bool FValidCdMmode(void);

/**
 * @brief Sets the disc media mode.
 */
void SetCdMmode(void);

/**
 * @brief Used to startup the CD system in earlier builds, but now it's empty.
 */
void StartupCd(void);

/**
 * @brief Updates the CD system.
 *
 * @todo Implement this function.
 */
void UpdateCd(void);

/**
 * @todo Unknown.
 */
void CdPath(char *pchzDest, char *pchzPath, int fIncludeDevice);

/**
 * @brief Reads sectors from the CD using the 989snd functions.
 *
 * @param isector Starting sector.
 * @param csector Number of sectors to read.
 * @param pv Pointer to destination.
 */
void ReadCd(uint isector, uint csector, void *pv);

/**
 * @brief Reads sectors from the CD using sce functions.
 *
 * @param isector Starting sector.
 * @param csector Number of sectors to read.
 * @param pv Pointer to destination.
 */
void ReadCdDirect(uint isector, uint csector, void *pv);

/**
 * @brief Checks if the CD operation has completed.
 *
 * @param fBlock Non-zero if should block other CD operations.
 *
 * @return true If completed.
 * @return False If not completed.
 */
bool FCdCompleted(int fBlock);

// TODO: This might not exist?
// void ErrCdLatest(void);

// Global variables
extern CDS g_cds;

#endif // CD_H

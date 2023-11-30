#pragma once
#include <iostream>

typedef unsigned int uint; //todo move to util header

/**
 * @brief File Location
 *
 * Stores the file location and size in bytes.
*/
struct FCL
{
    uint isector; // File ISO Sector Offset.
    uint cb; // File Size.
};

/**
 * @brief File Key
 *
 * Used to identify the file type.
*/
enum FK {
    FK_Nil = -1,
    FK_BrxWorld = 0, // Level File
    FK_IcoIcon = 1, // Icon File
    FK_BnkEffects = 2, // Sound Effect File
    FK_BnkMusic = 3, // Music File
    FK_VagDialog = 4, // Dialog File
    FK_VagAnimation = 5,
    FK_PssMovie = 6, // Video File
    FK_Max = 7
};

/**
 * @brief WAL Entry
 *
 * Stores the file key and file location & size.
*/
struct WALE {
    char* pchzKey; // File Name used for searching for file to load
    struct FCL* pfcl; // File location and size.
};

/**
 * @brief File Location
 *
 * Handles information about the file sector and size.
*/
class CFileLocation
{
public:
    FCL m_fcl; // Sector and Size information

    void Clear();  // Clear file information.
};

/**
 * @brief WAL Catalog
 *
 * Handles the WAC and WAL files.
*/
class CWalCatalog
{
public:
    CFileLocation m_flWac; // WAC ISO File Location and Size.
    CFileLocation m_flWal; // WAL ISO File Location and Size.
    char   m_ab[16384]; // Ptr to WAC Buffer.
    int    m_brxv; // WAC File Count.
    int    m_cpchz; // Number of levels in WAC File.
    int    m_cwale;
    char*  m_apchz[64]; // Buffer used to reference file names in WAC.
    WALE   m_awale[1024]; // This is used to search and reference files in WAC.

    /**
     * @brief Initializes the WAC and WAL files.
     *
     * Stores the WAC and WAL size and iso sector location.
     *
     * @param pflWac WAC File Location and Size.
     * @param pflWal WAL File Location and Size.
    */
    void Init(CFileLocation* pflWac, CFileLocation* pflWal);

    /**
     * @brief Finds a file in the WAC and WAL files.
     *
     * @param pchzKey File Name used for searching for file to load.
     * @param fk File Key used to identify the file type.
     * @param pflResult Stores the file location and size.
     *
     * @return 1 if file is found, 0 if file is not found.
    */
    int  FFindFile(char* pchzKey, FK fk, CFileLocation* pflResult);

    /**
     * @brief Checks if the default world file is found in the WAL file.
     *
     * If so, it loads the splash video file and sound files and starting world
     * (typically Paris) into memory.
     *
     * @param pchzResult Stores the pchz of the default world file.
     * @param pflResult Stores the file location and size.
     *
     * @retval 1 if file is found
     * @retval 0 if file is not found.
    */
    int FDefaultWorld(char* pchzResult, CFileLocation* pflResult);

    /**
     * @brief Builds the file location and size from the WAC and WAL files.
     *
     * @param pwale Stores the file key and file location & size.
     * @param pflResult Stores the file location and size.
    */
    void BuildFl(WALE* pwale, CFileLocation* pflResult);

    /**
     * @brief Not implemented
    */
    void Reload(); // todo
};

/**
 * @brief Catalog
 *
 * Related to the WAC and WAL files.
*/
class CCatalog
{
public:
    CWalCatalog m_wcatCd;

    /**
     * @brief Initializes the catalog.
    */
    void Init();

    /**
     * @brief Finds a file in the catalog
     *
     * @param pchzKey File Name used for searching for file to load.
     * @param fk File Key used to identify the file type.
     * @param pflResult Stores the file location and size.
     *
     * @note not implemented
    */
    int  FFindFile(char* pchzKey, FK fk, CFileLocation* pflResult); // todo

    /**
     * @brief Checks whether the default world file is found in the catalog.
     *
     * If so, it loads the splash video file and sound files and starting world
     * (typically Paris) into memory.
     *
     * @param pchzResult Stores the pchz of the default world file.
     * @param pflResult Stores the file location and size.
     *
     * @retval 1 if file is found
     * @retval 0 if file is not found.
    */
    int FDefaultWorld(char* pchzResult, CFileLocation* pflResult);
};

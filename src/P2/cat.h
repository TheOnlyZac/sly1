#pragma once
#include <iostream>

typedef unsigned int uint;

struct FCL
{
    uint isector; // File ISO Sector Offset.
    uint cb; // File Size.
};

// File Type
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

struct WALE {
    char* pchzKey; // File Name used for searching for file to load
    struct FCL* pfcl; // File location and size.
};

class CFileLocation
{
public:
    FCL m_fcl; // Sector and Size information

    void Clear();  // Clear file information.
};

class CWalCatalog // This is the class that handles the WAC and WAL file
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

    void Init(CFileLocation* pflWac, CFileLocation* pflWal); // Stores WAC and WAL size and iso sector location.
    int  FFindFile(char* pchzKey, FK fk, CFileLocation* pflResult); // Finding a file in the WAC and WAL Files.
    int  FDefaultWorld(char* pchzResult, CFileLocation* pflResult); // Loads the splash video file and sound files and starting world which is paris.
    void BuildFl(WALE* pwale, CFileLocation* pflResult); // Load up file info from WAC.
    void Reload(); // todo
};

class CCatalog
{
public:
    CWalCatalog m_wcatCd;

    void Init();
    int  FFindFile(char* pchzKey, FK fk, CFileLocation* pflResult);
    int  FDefaultWorld(char* pchzResult, CFileLocation* pflResult);
};

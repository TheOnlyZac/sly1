#include <iostream>
#include "CFileLocation/CFileLocation.h"

struct CWalCatalog 
{
    uint32_t wac_sector_offset;
    uint32_t wac_size;
    uint32_t wal_sector_offset;
    uint32_t wal_size;
    uint32_t wac_file_count;
    char file_version;
    uint32_t unk_2;
    uint32_t wac_file_names;
    char** unk_3;
    uint32_t unk_4;
};

static CWalCatalog wac;
//Basically just getting the wac and wal size and sector offset from the ISO and storing it in the wac struct
void Init(CWalCatalog* wac, CFileLocation* wac_file_desc0, CFileLocation* wal_file_desc1);
void Reload(CWalCatalog* wal);

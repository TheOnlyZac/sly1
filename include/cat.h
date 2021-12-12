#pragma once
#include <stdint.h>

struct FCL
{
    uint32_t isector; // sector offset
    uint32_t cb; // size
};

class CFileLocation
{
public:
    FCL m_fcl; // sector and size information

	void Clear();
};

class CWalCatalog
{
public:
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

    void Init(CFileLocation* pflWac, CFileLocation* pflWal);
    void Reload(); // todo
};

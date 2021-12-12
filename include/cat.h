#pragma once
#include <stdint.h>

class CFileLocation
{
public:
	uint32_t sector_offset;
	uint32_t size;

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

    void Init(CFileLocation* wac_file_desc0, CFileLocation* wal_file_desc1);
    void Reload(); // todo
};

#include <cat.h>

#include <iostream>

/* CFileLocation class methods */

void CFileLocation::Clear()
{
	memset(this, 0, sizeof(this));
}

/* CWalCatalog class methods */

/* Gets the wac and wal size/sector offset from the ISO and stores it in the wac struct */
void CWalCatalog::Init(CFileLocation* wac_file_desc0, CFileLocation* wal_file_desc1)
{
    this->wac_sector_offset = wac_file_desc0->sector_offset;
    this->wac_size = wac_file_desc0->size;
    this->wal_sector_offset = wal_file_desc1->sector_offset;
    this->wal_size = wal_file_desc1->size;
    Reload();
    return;
}

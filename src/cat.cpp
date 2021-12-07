#include <cat.h>

/* CFileLocation class methods */

void CFileLocation::Clear(CFileLocation* fl)
{
	memset(fl, 0, 8);
}

/* CWalCatalog class methods */

void CWalCatalog::Init(FileLocation* wac_file_desc0, FileLocation* wal_file_desc1)
{
    this->wac_sector_offset = wac_file_desc0->sector_offset;
    this->wac_size = wac_file_desc0->size;
    this->wal_sector_offset = wal_file_desc1->sector_offset;
    this->wal_size = wal_file_desc1->size;
    Reload();
    return;
}

void CWalCatalog::Reload()
{

}

#include <WalCatalog.h>

void Init(CWalCatalog *wac, CFileLocation* wac_file_desc0, CFileLocation* wal_file_desc1)
{
    wac->wac_sector_offset = wac_file_desc0->sector_offset;
    wac->wac_size = wac_file_desc0->size;
    wac->wal_sector_offset = wal_file_desc1->sector_offset;
    wac->wal_size = wal_file_desc1->size;
    Reload(wac);
    return;
}

void Reload(CWalCatalog* wac)
{

}
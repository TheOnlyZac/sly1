#include <WalCatalog.h>

void CWalCatalog::Init(FileLocation* wac_file_desc0, FileLocation* wal_file_desc1)
{
    wac_sector_offset = wac_file_desc0->sector_offset;
    wac_size = wac_file_desc0->size;
    wal_sector_offset = wal_file_desc1->sector_offset;
    wal_size = wal_file_desc1->size;
    Reload();
    return;
}

void CWalCatalog::Reload()
{

}

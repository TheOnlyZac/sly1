#include <cat.h>
#include <cstring>
#include <iostream>


/* CFileLocation class methods */

void CFileLocation::Clear()
{
	memset(this, 0, sizeof(this));
}

/* CWalCatalog class methods */

/* Store the WAC and WAL size/sector offset from the ISO */
void CWalCatalog::Init(CFileLocation* pflWac, CFileLocation* pflWal)
{
    this->wac_sector_offset = pflWac->m_fcl.isector;
    this->wac_size = pflWac->m_fcl.cb;
    this->wal_sector_offset = pflWal->m_fcl.isector;
    this->wal_size = pflWal->m_fcl.cb;
    Reload();
}

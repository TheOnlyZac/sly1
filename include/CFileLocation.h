#ifndef FILELOCATION
#define FILELOCATION
#include <iostream>

struct CFileLocation
{
    uint32_t sector_offset;
    uint32_t size;
};

static CFileLocation fl0;
static CFileLocation fl1;
void Clear(CFileLocation* fl);
#endif
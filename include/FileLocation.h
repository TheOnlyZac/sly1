#ifndef FILELOCATION
#define FILELOCATION
#include <iostream>

class CFileLocation
{
    public:

    struct CFileLocationStruct
    {
        uint32_t sector_offset;
        uint32_t size;
    };

    void Clear(CFileLocationStruct* fl);
};
#endif
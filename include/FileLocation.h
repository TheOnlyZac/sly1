#pragma once

#include <iostream>

class FileLocation
{
public:
    struct CFileLocation
    {
        uint32_t sector_offset;
        uint32_t size;
    };

    void Clear(CFileLocation* fl);
};
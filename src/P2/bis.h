#pragma once
#include <bas.h>
#include <prog.h>
#include <iostream>
#include <stdint.h>

typedef unsigned char byte;

// todo: rewrite class with correct fields and types
class CBinaryInputStream
{
public:
    uint32_t field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xc;
    uint32_t size;
    uint32_t size_2;
    uint32_t stream_pos;
    int stream_size;
    BYTE* ptr_data_origin;
    uint32_t size_3;
    uint32_t flags;
    BYTE* size_of_70002000_segment;
    int* level_id;
    int field_0x34;
    int field_0x38;
    uint32_t field_0x3c;
    int sector_size;
    int field_0x44;
    uint32_t lsn_to_read;
    uint32_t field_0x4c;
    BYTE* field_0x50;
    uint32_t sector_offset;
    uint32_t field_0x58;
    uint32_t field_0x5c;
    uint32_t field_0x60;
    uint32_t field_0x64;
    uint32_t g_fCdAvailable;

    uint32_t FOpenSector(uint32_t isector, uint32_t cb);
    void OpenMemory(int cb, void* pv);
    void Close();
    void DecrementCdReadLimit(int cb);
    void Read(int cb, uint64_t pv); // todo: verify param types
    void Align(int n);
    byte U8Read();
    uint16_t U16Read();
    uint32_t U32Read();
    int8_t S8Read();
    int16_t S16Read();
    int32_t S32Read();
    float F32Read();
    void ReadStringSw(char** pachz);
};

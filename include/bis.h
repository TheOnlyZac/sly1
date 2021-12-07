#pragma once

#include <prog.h>

#include <iostream>

typedef unsigned char byte;

class CBinaryInputStream
{
public:
    uint32_t field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xc;
    uint32_t size; /* Created by retype action */
    uint32_t size_2;
    uint32_t stream_pos;
    int stream_size;
    byte* ptr_data_origin;
    uint32_t size_3;
    uint32_t flags;
    byte* size_of_70002000_segment;
    int* level_id;
    int field_0x34;
    int field_0x38;
    uint32_t field_0x3c;
    int sector_size;
    int field_0x44;
    uint32_t lsn_to_read;
    uint32_t field_0x4c;
    byte* field_0x50;
    uint32_t sector_offset;
    uint32_t field_0x58;
    uint32_t field_0x5c;
    uint32_t field_0x60;
    uint32_t field_0x64;
    uint32_t g_fCdAvailable;

    uint32_t FOpenSector(uint32_t sector_offset, uint32_t size);
    void OpenMemory(int param_1, void* param_2);
    void Close();
    void DecrementCdReadLimit(int param_1);
    void Read(int count, void* dst);
    void Align(int alignment);
    byte U8Read();
    uint16_t U16Read();
    uint32_t U32Read();
    int8_t S8Read();
    int16_t S16Read();
    int32_t S32Read();
    float F32Read();
    void ReadStringSw(char* dst);
};

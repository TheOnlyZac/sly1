#include <iostream>

typedef unsigned char byte;

class CBinaryInputStream
{
    public:
    struct CProg
    {
        int field_0x0;
        int field_0x4;
        int field_0x8;
        int field_0xc;
        int field_0x10;
        byte field_0x14;
        byte field_0x15;
        byte field_0x16;
        byte field_0x17;
        byte field_0x18;
        byte field_0x19;
        byte field_0x1a;
        byte field_0x1b;
        byte field_0x1c;
        byte field_0x1d;
        byte field_0x1e;
        byte field_0x1f;
        byte field_0x20;
        byte field_0x21;
        byte field_0x22;
    };

    struct CBinaryInputStreamStruct
    {
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
    };

    static CBinaryInputStreamStruct bs;

    uint32_t FOpenSector(CBinaryInputStreamStruct* bs, uint32_t sector_offset, uint32_t size);
    void OpenMemory(CBinaryInputStreamStruct* bs, int param_1, void* param_2);
    void Close(CBinaryInputStreamStruct* bs);
    void DecrementCdReadLimit(CBinaryInputStreamStruct* bs, int param_1);
    void Read(CBinaryInputStreamStruct* bs, int count, void* dst);
    void Align(CBinaryInputStreamStruct* bs, int alignment);
    byte U8Read(CBinaryInputStreamStruct* bs);
    uint16_t U16Read(CBinaryInputStreamStruct* bs);
    uint32_t U32Read(CBinaryInputStreamStruct* bs);
    int8_t S8Read(CBinaryInputStreamStruct* bs);
    int16_t S16Read(CBinaryInputStreamStruct* bs);
    int32_t S32Read(CBinaryInputStreamStruct* bs);
    float F32Read(CBinaryInputStreamStruct* bs);
    void ReadStringSw(CBinaryInputStreamStruct* bs, char* dst);
};
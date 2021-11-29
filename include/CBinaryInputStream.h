#include <iostream>

typedef unsigned char byte;
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

struct CBinaryInputStream 
{
    uint32_t field_0x0;
    int field_0x4;
    byte* field_0x8;
    int field_0xc;
    uint32_t size;
    uint32_t field_0x14;
    void* stream_pos;
    uint32_t stream_size;
    byte* field_0x20;
    int field_0x24;
    uint32_t field_0x28;
    int field_0x2c;
    struct CProg* field_0x30;
    byte field_0x34;
    byte field_0x35;
    byte field_0x36;
    byte field_0x37;
    byte field_0x38;
    byte field_0x39;
    byte field_0x3a;
    byte field_0x3b;
    byte field_0x3c;
    byte field_0x3d;
    byte field_0x3e;
    byte field_0x3f;
    byte field_0x40;
    byte field_0x41;
    byte field_0x42;
    byte field_0x43;
    uint32_t field_0x44;
    int field_0x48;
    void* field_0x4c;
    uint32_t field_0x50;
    byte* sector_offset;
    int field_0x58;
    uint32_t field_0x5c;
    int field_0x60;
    struct CProg* field_0x64;
};

static CBinaryInputStream bs;

uint32_t FOpenSector(CBinaryInputStream* bs, uint32_t sector_offset, uint32_t size);
void OpenMemory(CBinaryInputStream* bs, int param_1, void* param_2);
void Close(CBinaryInputStream* bs);
void DecrementCdReadLimit(CBinaryInputStream* bs, int param_1);
void Read(CBinaryInputStream* bs, int count, void* dst);
void Align(CBinaryInputStream* bs, int alignment);
byte U8Read(CBinaryInputStream* bs);
uint16_t U16Read(CBinaryInputStream* bs);
uint32_t U32Read(CBinaryInputStream *bs);
int8_t S8Read(CBinaryInputStream* bs);
int16_t S16Read(CBinaryInputStream* bs);
int32_t S32Read(CBinaryInputStream* bs);
float F32Read(CBinaryInputStream* bs);
void ReadStringSw(CBinaryInputStream* bs, char* dst);
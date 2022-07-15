#include <vec.h>
#include <iostream>

// todo: fix, replace, or remove struct
struct Entity
{
    int field_0x0;
    float field_0x4;
    int field_0x8;
    struct SW* entity_list_pointer;
    struct Entity* field_0x18;
    struct Entity* field_0x1c;
    int* field_0x2c;
    struct Entity* field_0x34;
    struct Entity* field_0x50;
    int field_0x54;
    uint32_t field_0x60;
    int field_0xac;
    struct VECTOR field_0xd0;
    struct VECTOR field_0xe0;
    struct VECTOR field_0xf0;
    struct VECTOR position;
    void (*update)(float); /* Entity update func */
    int field_0x148;
    int field_0x14c;
    struct VECTOR velocity; /* X Velocity */
    struct VECTOR field_0x160;
    struct VECTOR unk_vector3_0x170;
    struct VECTOR unk_vector3_0x180;
    struct astruct_14* unk_astruct14_0x1ec;
    struct astruct_15* unk_astruct15_0x1f0;
    int field_0x228;
    int field_0x284;
    int field_0x294;
    int field_0x298;
    uint64_t field_0x2c8;
    int field_0x2d0;
    uint32_t unk_flags_0x2e8;
    uint32_t field_0x2ec;
    int field_0x2f0;
    int field_0x2f4;
    int field_0x2f8;
    float field_0x2fc;
    uint32_t field_0x300;
    float gravity; /* Downward gravity force */
    struct Entity* next_entity_ptr;
    struct Entity* prev_entity_ptr;
    int field_0x4b8;
    uint64_t field_0x538;
    byte field_0x550;
    byte field_0x554;
    byte field_0x560;
    byte field_0x564;
    byte field_0x568;
    byte field_0x61c;
    int field_0x720;
    uint32_t field_0x72c;
    uint32_t field_0x748;
    int field_0x754;
    int field_0x7e0;
    uint32_t field_0xa60;
    uint32_t field_0xba4;
    uint32_t field_0xbf4;
    uint32_t field_0xbf8;
    uint32_t field_0xbfc;
    uint32_t field_0xc00;
};

// todo: investigate and rewrite struct
struct SW
{
        enum OID field_0x8;
        struct CFrame* field_0x30;
        int* field_0x48;
        int field_0x4d;
        int* field_0x4e;
        int field_0x53;
        int field_0x5c;
        uint32_t next_entity_offset;
        float field_0x71;
        struct XP* field_0x78;
        struct SLOTHEAP* field_0x1b78;
        struct LinkedListNode* field_0x1c2c;
        //struct DL field_0x1c90;
        float field_0x1e30;
        float field_0x1e34;
        int field_0x1e38;
        //MUSID field_0x1e3c;
};

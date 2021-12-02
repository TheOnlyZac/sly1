#include <bis.h>

uint32_t CBinaryInputStream::FOpenSector(CBinaryInputStream* bs, uint32_t sector_offset, uint32_t size)
{
    int iVar1;
    int iVar2;

    if (g_fCdAvailable == 0) 
    {
        return 0;
    }

    iVar2 = bs->field_0xc;
    bs->field_0x4 = 1;
    bs->sector_offset = (byte*)sector_offset;
    bs->field_0x4c = (void*)size;
    bs->field_0x20 = bs->field_0x8;
    bs->size = size;
    bs->size_2 = size;
    bs->field_0x44 = 0;
    bs->field_0x50 = 0;
    bs->field_0x48 = 0;
    if (iVar2 < 0) 
    {
        iVar2 = iVar2 + 0xfffff;
    }
    bs->field_0x5c = 0;
    iVar1 = 2;
    if (2 < iVar2 >> 0x14) 
    {
        iVar1 = iVar2 >> 0x14;
    }
    bs->field_0x60 = 0;
    bs->field_0x58 = iVar1;
    bs->field_0x64 = (CProg*)(iVar1 + -1);
    return 1;
}
void CBinaryInputStream::OpenMemory(CBinaryInputStream* bs, int size, void* pos)
{
    bs->stream_size = size;
    bs->field_0x4 = 2;
    bs->stream_pos = pos;
    return;
}

void CBinaryInputStream::Close(CBinaryInputStream* bs)
{
    if (bs->field_0x4 == 0) 
    {
        if (-1 < (long)*(int*)&bs->field_0x40) 
        {
            sceClose((long)*(int*)&bs->field_0x40);
        }
    }
    else 
    {
        if (bs->field_0x4 != 1) 
        {
            bs->field_0x2c = 0;
            goto LAB_0013a694;
        }
        if (bs->field_0x48 != 0) 
        {
            if ((bs->field_0x0 & 2) == 0) 
            {
                snd_StreamSafeCdBreak();
            }
            else {
                sceCdBreak();
            }
        }
    }
    bs->field_0x2c = 0;
    bs->field_0x4 = -1;
    bs->field_0x20 = (byte*)0x0;
    bs->field_0x18 = (void*)0x0;
    bs->field_0x24 = 0;
    bs->field_0x1c = 0;
    bs->field_0x28 = 0;
    return;
}
void CBinaryInputStream::DecrementCdReadLimit(CBinaryInputStream* bs, int param_1)
{
    bs->field_0x4c = (void*)((int)bs->field_0x4c - param_1);
    return;
}

void CBinaryInputStream::Read(CBinaryInputStream* bs, int count, void* dst)
{
    uint32_t uVar2;

    if (bs->stream_size > 0 && count > 0)
    {
        do 
        {
            uint32_t size = bs->stream_size;
            if (size == 0) 
            {
                if ((bs->field_0x0 & 4) == 0) 
                {
                    Pump(bs);
                    bs->stream_size = bs->field_0x24;
                    bs->stream_pos = bs->field_0x20;
                    bs->field_0x20 = bs->field_0x20 + bs->field_0x24;
                    bs->field_0x24 = 0;
                    size = bs->stream_size;
                }
                else 
                {
                    Decompress(bs);
                    size = bs->stream_size;
                }
                if (size == 0) 
                {
                    bs->stream_size = 0xffffffff;
                    return;
                }
            }
            uVar2 = count;
            if ((int)size <= count) 
            {
                uVar2 = size;
            }
            if (dst != (void*)0x0) 
            {
                CopyAb(dst, bs->stream_pos, uVar2);
                dst = (void*)((int)dst + uVar2);
            }
            count = count - uVar2;
            bs->stream_pos = (void*)((int)bs->stream_pos + uVar2);
            bs->stream_size = bs->stream_size - uVar2;
        } 
        while (0 < count);
    }
    return;
}

void CBinaryInputStream::Align(CBinaryInputStream* bs, int alignment)
{
    uint32_t pos = bs->stream_pos;
    uint32_t size = pos + alignment + -1 & -alignment;
    bs->stream_size = size;
    bs->stream_pos = bs->stream_pos - size - stream_pos;
    return;
}

byte CBinaryInputStream::U8Read(CBinaryInputStream* bs)
{
    byte value;
    if (bs->stream_size < 1)
    {
        Read(bs, 1, value);
    }
    else
    {
        value = (byte)*bs->stream_pos;
        bs->stream_size = bs->stream_size - 1;
        bs->stream_pos = bs->stream_pos + 1;
        return value;
    }
}

uint16_t CBinaryInputStream::U16Read(CBinaryInputStream* bs)
{
    uint16_t value;
    if (bs->stream_size < 2)
    {
        Read(bs, 2, value);
    }
    else
    {
        value = (uint16_t)*bs->stream_pos;
        bs->stream_size = bs->stream_size - 2;
        bs->stream_pos = bs->stream_pos + 2;
        return value;
    }
}

uint32_t CBinaryInputStream::U32Read(CBinaryInputStream* bs)
{
    uint32_t value;
    if (bs->stream_size < 4)
    {
        Read(bs, 4, value);
    }
    else
    {
        value = (uint32_t)*bs->stream_pos;
        bs->stream_size = bs->stream_size - 4;
        bs->stream_pos = bs->stream_pos + 4;
        return value;
    }
}

int8_t CBinaryInputStream::S8Read(CBinaryInputStream* bs)
{
    int8_t value;
    if (bs->stream_size < 1)
    {
        Read(bs, 1, value);
    }
    else
    {
        value = (int8_t)*bs->stream_pos;
        bs->stream_size = bs->stream_size - 1;
        bs->stream_pos = bs->stream_pos + 1;
        return value;
    }
}

int16_t CBinaryInputStream::S16Read(CBinaryInputStream* bs)
{
    int16_t value;
    if (bs->stream_size < 2)
    {
        Read(bs, 2, value);
    }
    else
    {
        value = (int16_t)*bs->stream_pos;
        bs->stream_size = bs->stream_size - 2;
        bs->stream_pos = bs->stream_pos + 2;
        return value;
    }
    return value;
}

int32_t CBinaryInputStream::S32Read(CBinaryInputStream* bs)
{
    int32_t value;
    if (bs->stream_size < 4)
    {
        Read(bs, 4, value);
    }
    else
    {
        value = (int32_t)*bs->stream_pos;
        bs->stream_size = bs->stream_size - 4;
        bs->stream_pos = bs->stream_pos + 4;
        return value;
    }
    return value;
}

float CBinaryInputStream::F32Read(CBinaryInputStream* bs)
{
    float value;
    if (bs->stream_size < 4)
    {
        Read(bs, 4, value);
    }
    else
    {
        value = (float)*bs->stream_pos;
        bs->stream_size = bs->stream_size - 4;
        bs->stream_pos = bs->stream_pos + 4;
        return value;
    }
    return value;
}

void CBinaryInputStream::ReadStringSw(CBinaryInputStream* bs, char *dst0)
{
    int string_count = U16Read(bs);
    char* dst1 = (char*)PvAllocSwImpl(string_count + 1);
    Read(bs, string_count, dst1);
    dst1[string_count] = '\0';
    *dst0 = dst1;
    return;
}
#include <bis.h>

/* CBinaryInputStream class methods */

uint32_t CBinaryInputStream::FOpenSector(uint32_t sector_offset, uint32_t size)
{
    int iVar1;
    int iVar2;

    if (g_fCdAvailable == 0)
    {
        return 0;
    }

    iVar2 = this->field_0xc;
    this->field_0x4 = 1;
    this->sector_offset = sector_offset;
    this->field_0x4c = size;
    //this->ptr_data_origin = this->field_0x8;
    this->size = size;
    this->size_2 = size;
    this->field_0x44 = 0;
    this->field_0x50 = 0;
    this->lsn_to_read = 0;
    if (iVar2 < 0)
    {
        iVar2 = iVar2 + 0xfffff;
    }
    this->field_0x5c = 0;
    iVar1 = 2;
    if (2 < iVar2 >> 0x14)
    {
        iVar1 = iVar2 >> 0x14;
    }
    this->field_0x60 = 0;
    this->field_0x58 = iVar1;
    this->field_0x64 = (iVar1 + -1);
    return 1;
}

void CBinaryInputStream::OpenMemory(int size, void* pos)
{
    this->stream_size = size;
    this->field_0x4 = 2;
    //this->stream_pos = pos;
    return;
}

void CBinaryInputStream::Close()
{
    if (this->field_0x4 == 0)
    {
        if (-1 < (long)*(int*)&this->sector_size)
        {
            //sceClose((long)*(int*)&this->sector_size);
        }
    }
    else
    {
        if (this->field_0x4 != 1)
        {
            this->size_of_70002000_segment = 0;
            //goto LAB_0013a694;
        }
        if (this->lsn_to_read != 0)
        {
            if ((this->field_0x0 & 2) == 0)
            {
                //snd_StreamSafeCdBreak();
            }
            else {
                //sceCdBreak();
            }
        }
    }
    this->size_of_70002000_segment = 0;
    this->field_0x4 = -1;
    this->ptr_data_origin = (byte*)0x0;
    this->stream_pos = 0x0;
    this->size_3 = 0;
    this->stream_size = 0;
    this->flags = 0;
    return;
}

void CBinaryInputStream::DecrementCdReadLimit(int param_1)
{
    this->field_0x4c = this->field_0x4c - param_1;
    return;
}

void CBinaryInputStream::Read(int count, uint64_t dst)
{
    uint32_t uVar2;

    if (this->stream_size > 0 && count > 0)
    {
        do
        {
            uint32_t size = this->stream_size;
            if (size == 0)
            {
                if ((this->field_0x0 & 4) == 0)
                {
                    //Pump(this);
                    this->stream_size = this->size_3;
                    //this->stream_pos = this->ptr_data_origin;
                    this->ptr_data_origin = this->ptr_data_origin + this->size_3;
                    this->size_3 = 0;
                    size = this->stream_size;
                }
                else
                {
                    //Decompress(this);
                    size = this->stream_size;
                }
                if (size == 0)
                {
                    this->stream_size = 0xffffffff;
                    return;
                }
            }
            uVar2 = count;
            if ((int)size <= count)
            {
                uVar2 = size;
            }
            if (dst != 0x0)
            {
                //CopyAb(dst, this->stream_pos, uVar2);
                dst = dst + uVar2;
            }
            count = count - uVar2;
            this->stream_pos = this->stream_pos + uVar2;
            this->stream_size = this->stream_size - uVar2;
        } while (0 < count);
    }
    return;
}

void CBinaryInputStream::Align(int alignment)
{
    uint32_t pos = this->stream_pos;
    uint32_t size = pos + alignment + -1 & -alignment;
    this->stream_size = size;
    this->stream_pos = this->stream_pos - size - stream_pos;
    return;
}

byte CBinaryInputStream::U8Read()
{
    byte value;
    if (this->stream_size < 1)
    {
        Read(1, value);
    }
    else
    {
        value = this->stream_pos;
        this->stream_size = this->stream_size - 1;
        this->stream_pos = this->stream_pos + 1;
        return value;
    }
}

uint16_t CBinaryInputStream::U16Read()
{
    uint16_t value;
    if (this->stream_size < 2)
    {
        Read(2, value);
    }
    else
    {
        value = this->stream_pos;
        this->stream_size = this->stream_size - 2;
        this->stream_pos = this->stream_pos + 2;
        return value;
    }
}

uint32_t CBinaryInputStream::U32Read()
{
    uint32_t value;
    if (this->stream_size < 4)
    {
        Read(4, value);
    }
    else
    {
        value = this->stream_pos;
        this->stream_size = this->stream_size - 4;
        this->stream_pos = this->stream_pos + 4;
        return value;
    }
}

int8_t CBinaryInputStream::S8Read()
{
    int8_t value;
    if (this->stream_size < 1)
    {
        Read(1, value);
    }
    else
    {
        value = this->stream_pos;
        this->stream_size = this->stream_size - 1;
        this->stream_pos = this->stream_pos + 1;
        return value;
    }
}

int16_t CBinaryInputStream::S16Read()
{
    int16_t value;
    if (this->stream_size < 2)
    {
        Read(2, value);
    }
    else
    {
        value = this->stream_pos;
        this->stream_size = this->stream_size - 2;
        this->stream_pos = this->stream_pos + 2;
        return value;
    }
    return value;
}

int32_t CBinaryInputStream::S32Read()
{
    int32_t value;
    if (this->stream_size < 4)
    {
        Read(4, value);
    }
    else
    {
        value = this->stream_pos;
        this->stream_size = this->stream_size - 4;
        this->stream_pos = this->stream_pos + 4;
        return value;
    }
    return value;
}

float CBinaryInputStream::F32Read()
{
    float value;
    if (this->stream_size < 4)
    {
        Read(4, value);
    }
    else
    {
        value = this->stream_pos;
        this->stream_size = this->stream_size - 4;
        this->stream_pos = this->stream_pos + 4;
        return value;
    }
    return value;
}

void CBinaryInputStream::ReadStringSw(char* dst0)
{
    int string_count = U16Read();
    //char* dst1 = (char*)PvAllocSwImpl(string_count + 1);
    //Read(string_count, dst1);
    //dst1[string_count] = '\0';
    //*dst0 = dst1;
    return;
}

/* CBinaryAsyncStream class methods */

/* Constructor */
CBinaryAsyncStream::CBinaryAsyncStream(void* pvSpool)
{
    this->m_isector = 0;
    this->m_abSpool = (BYTE*)((int)pvSpool + 0x3fU & 0xffffffc0);
    this->m_fd = -1;
    this->m_pbSpooling = NULL;
    this->m_pb = NULL;
    this->m_cbFile = 0;
    this->m_cbUnspooled = 0;
    this->m_cbSpooling = 0;
    this->m_ibCur = 0;
    this->m_cb = 0;
}

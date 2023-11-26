#include <bis.h>

CBinaryInputStream::CBinaryInputStream(std::string fileName)
{
    file.open(fileName, std::ios::binary);
}

int CBinaryInputStream::FOpenFile(CFileLocation* pfl)
{
    int isFileOpen = 0;

    if (g_fCdAvailable != 0)
        isFileOpen = FOpenSector(pfl->m_fcl.isector, pfl->m_fcl.cb);

    return isFileOpen;
}

int CBinaryInputStream::FOpenSector(uint32_t isector, uint32_t cb)
{
    int iVar1;
    int iVar2;

    if (g_fCdAvailable == 0)
        return 0;

    iVar2 = m_cbSpool;
    m_bisk = BISK::Cd;
    m_isector = isector;
    m_cbAsyncRemaining = cb;
    m_pbRaw = m_abSpool;
    m_cbFile = cb;
    m_cbRemaining = cb;
    m_cbAsyncComplete = 0;
    m_cbPartialRead = 0;
    m_cbAsyncRequest = 0;

    if (iVar2 < 0)
        iVar2 = iVar2 + 0xfffff;

    m_cbufFill = 0;
    iVar1 = 2;

    if (2 < iVar2 >> 0x14)
        iVar1 = iVar2 >> 0x14;

    m_ibufMic = 0;
    m_cbuf = iVar1;
    m_ibufMac = iVar1 + -1;
    return 1;
}

void CBinaryInputStream::OpenMemory(int cb, void* pv)
{
    m_cb = cb;
    m_bisk = BISK::Mem;
    m_pb = (byte*)pv;
}

void CBinaryInputStream::DecrementCdReadLimit(int cb)
{
    m_cbAsyncRemaining = m_cbAsyncRemaining - cb;
}

void CBinaryInputStream::Read(int cb, void *pv)
{
    uint32_t uVar1;
    uint32_t cb_00;

    if ((-1 < m_cb) && (0 < cb)) {

        for (int i = 0; i < cb; i++)
        {
            uVar1 = m_cb;
            if (uVar1 == 0) {
                if ((m_grfbis & 4U) == 0) {
                    //Pump();
                    m_cb = m_cbRaw;
                    m_pb = m_pbRaw;
                    m_pbRaw = m_pbRaw + m_cbRaw;
                    m_cbRaw = 0;
                    uVar1 = m_cb;
                }
                else {
                    //Decompress();
                    uVar1 = m_cb;
                }
                if (uVar1 == 0) {
                    m_cb = -1;
                    return;
                }
            }
            cb_00 = cb;
            if ((int)uVar1 <= cb) {
                cb_00 = uVar1;
            }
            if (pv != 0x0) {
                // CopyAb(pv, m_pb, cb_00);
                pv = (void *)(pv + cb_00);
            }

            m_pb = m_pb + cb_00;
            m_cb = m_cb - cb_00;
        }
    }
}

void CBinaryInputStream::Read_Modified(int cb, void* pv)
{

}

void CBinaryInputStream::Align(int n)
{
    byte* pbOld;
    byte* pbNew;

    pbOld = m_pb;
    pbNew = reinterpret_cast<byte*>((reinterpret_cast<uintptr_t>(pbOld) + n - 1) & -n);
    m_pb = pbNew;
    m_cb = m_cb - (pbNew - pbOld);
}

void CBinaryInputStream::Align_Modified(int n)
{
    std::ifstream::pos_type pos = file.tellg();

    if (pos % n != 0)
        pos += (n - (pos % n));

    file.seekg(pos, std::ios_base::beg);
}

byte CBinaryInputStream::U8Read()
{
    byte value{};

    if (m_cb < 1)
        Read(1, &value);

    else {
        value = *m_pb;
        m_cb = m_cb + -1;
        m_pb = m_pb + 1;
    }

    return value;
}

byte CBinaryInputStream::U8Read_Modified()
{
    byte temp;
    file.read(reinterpret_cast<char*> (&temp), sizeof(byte));
    return temp;
}

uint16_t CBinaryInputStream::U16Read()
{
    uint16_t value{};

    if (m_cb < 2)
        Read(2, &value);

    else {
        value = *(uint16_t*)m_pb;
        m_cb = m_cb - 2;
        m_pb = reinterpret_cast<byte*>(reinterpret_cast<uintptr_t>(m_pb) + 2);
    }
    return value;
}

uint16_t CBinaryInputStream::U16Read_Modified()
{
    uint16_t temp;
    file.read(reinterpret_cast<char*> (&temp), sizeof(uint16_t));
    return temp;
}

uint32_t CBinaryInputStream::U32Read()
{
    byte bVar1;
    byte bVar2;
    byte bVar3;
    byte bVar4;
    byte* pbVar5;

    uint32_t value{};
    if (m_cb < 4)
        Read(4, &value);

    else {
        pbVar5 = m_pb;
        bVar1 = pbVar5[1];
        bVar2 = *pbVar5;
        bVar3 = pbVar5[2];
        bVar4 = pbVar5[3];
        m_cb = m_cb + -4;
        m_pb = pbVar5 + 4;
        value = (uint32_t)bVar2 + (uint32_t)bVar1 * 0x100 + (uint32_t)bVar3 * 0x10000 + (uint32_t)bVar4 * 0x1000000;
    }
    return value;
}

uint32_t CBinaryInputStream::U32Read_Modified()
{
    uint32_t temp;
    file.read(reinterpret_cast<char*> (&temp), sizeof(uint32_t));
    return temp;
}

int8_t CBinaryInputStream::S8Read()
{
    int8_t value{};

    if (m_cb < 1)
        Read(1, &value);

    else {
        value = *m_pb;
        m_cb = m_cb + -1;
        m_pb = m_pb + 1;
    }
    return value;
}

int8_t CBinaryInputStream::S8Read_Modified()
{
    int8_t temp;
    file.read(reinterpret_cast<char*> (&temp), sizeof(int8_t));
    return temp;
}

int16_t CBinaryInputStream::S16Read()
{
    byte bVar1;
    byte bVar2;
    byte* pbVar3;
    int16_t value{};

    if (m_cb < 2) {
        Read(2, &value);
    }
    else {
        pbVar3 = m_pb;
        bVar1 = pbVar3[1];
        bVar2 = *pbVar3;
        m_cb = m_cb + -2;
        m_pb = pbVar3 + 2;
        value = (uint16_t)bVar2 | (uint16_t)(((uint32_t)bVar1 << 0x18) >> 0x10);
    }
    return value;
}

int16_t CBinaryInputStream::S16Read_Modified()
{
    int16_t temp;
    file.read(reinterpret_cast<char*> (&temp), sizeof(int16_t));
    return temp;
}

int32_t CBinaryInputStream::S32Read()
{
    byte bVar1;
    byte bVar2;
    byte bVar3;
    byte bVar4;
    byte* pbVar5;
    int32_t value{};

    if (m_cb < 4)
        Read(4, &value);

    else {
        pbVar5 = m_pb;
        bVar2 = pbVar5[1];
        bVar3 = *pbVar5;
        bVar4 = pbVar5[2];
        bVar1 = pbVar5[3];
        m_cb = m_cb + -4;
        m_pb = pbVar5 + 4;
        value = (uint32_t)bVar3 + (uint32_t)bVar2 * 0x100 + (uint32_t)bVar4 * 0x10000 + (char)bVar1 * 0x1000000;
    }
    return value;
}

int32_t CBinaryInputStream::S32Read_Modified()
{
    int32_t temp;
    file.read(reinterpret_cast<char*> (&temp), sizeof(int32_t));
    return temp;
}

float CBinaryInputStream::F32Read()
{
    byte bVar1;
    byte bVar2;
    byte bVar3;
    byte bVar4;
    byte* pbVar5;
    float value{};

    if (m_cb < 4)
        Read(4, &value);

    else {
        pbVar5 = m_pb;
        bVar1 = pbVar5[1];
        bVar2 = *pbVar5;
        bVar3 = pbVar5[2];
        bVar4 = pbVar5[3];
        m_cb = m_cb + -4;
        value = (float)((uint32_t)bVar2 + (uint32_t)bVar1 * 0x100 + (uint32_t)bVar3 * 0x10000 + (uint32_t)bVar4 * 0x1000000)
            ;
        m_pb = pbVar5 + 4;
    }
    return value;
}

float CBinaryInputStream::F32Read_Modified()
{
    float temp;
    file.read(reinterpret_cast<char*> (&temp), sizeof(float));
    return temp;
}

void CBinaryInputStream::ReadStringSw(char** pachz)
{
    int string_count = U16Read();
    //char* dst1 = (char*)PvAllocSwImpl(string_count + 1);
    //Read(string_count, dst1);
    //dst1[string_count] = '\0';
    //*pachz = dst1;
}

void CBinaryInputStream::Close()
{
    if (m_bisk == BISK::Host) {
        if (-1 < m_fd) {
            //sceClose();
        }
    }
    else {
        if (m_bisk != BISK::Cd) {
            m_cbSpillOver = 0;
            m_bisk = BISK::Nil;
            m_pbRaw = 0x0;
            m_pb = 0x0;
            m_cbRaw = 0;
            m_cb = 0;
            m_grfDecomp = 0;
            return;
        }
        if (m_cbAsyncRequest != 0) {
            if ((m_grfbis & 2U) == 0) {
                //snd_StreamSafeCdBreak();
            }
            else {
                //sceCdBreak();
            }
        }
    }

    m_cbSpillOver = 0;
    m_bisk = BISK::Nil;
    m_pbRaw = 0x0;
    m_pb = 0x0;
    m_cbRaw = 0;
    m_cb = 0;
    m_grfDecomp = 0;
    return;
}

void CBinaryInputStream::Close_Modified()
{
    file.clear();
    file.close();
}

CBinaryInputStream::~CBinaryInputStream()
{
    Close();
    Close_Modified();
}

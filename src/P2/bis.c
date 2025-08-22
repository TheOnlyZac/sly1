#include <bis.h>
#include <989snd.h>
#include <lib/libkernl/filestub.h>
#include <sdk/libcdvd.h>
#include <memory.h>

INCLUDE_ASM(const s32, "P2/bis", __18CBinaryInputStreamiPvi);

INCLUDE_ASM(const s32, "P2/bis", DESTRUCTOR__CBinaryInputStream);
#ifdef SKIP_ASM
CBinaryInputStream::~CBinaryInputStream()
{
    Close();
}
#endif

int CBinaryInputStream::FOpenSector(uint isector, uint cb)
{
    int cbSpool = m_cbSpool;

    m_bisk = BISK_Cd;
    m_cbAsyncRequest = isector;
    m_cbFile = cb;
    m_cbRemaining = cb;
    m_fd = cb;
    m_pbRaw = m_abSpool;
    *(uint *)&m_tickWait = 0;
    m_cbAsyncComplete = 0;
    *(uint *)((int)&m_tickWait + 4) = 0;

    if (cbSpool < 0)
    {
        cbSpool += 0xfffff;
    }

    m_cbPartialRead = 0;

    int cbAsyncRemaining = 2;
    int shr = 20;
    if ((cbSpool >> shr) > cbAsyncRemaining)
    {
        cbAsyncRemaining = cbSpool >> shr;
    }

    m_isector = 0;
    m_cbAsyncRemaining = cbAsyncRemaining;
    m_cbuf = cbAsyncRemaining - 1;

    return 1;
}

void CBinaryInputStream::OpenMemory(int cb, void *pv)
{
    m_bisk = BISK_Mem;
    m_pb = (byte *)pv;
    m_cb = cb;
}

int CBinaryInputStream::FOpenFile(CFileLocation *pfl)
{
    return FOpenSector(pfl->m_fcl.isector, pfl->m_fcl.cb);
}

void CBinaryInputStream::Close()
{
    switch (m_bisk)
    {
        case BISK_Host:
        {
            // NOTE: This is m_fd if m_tickWait is removed.
            if (*(int *)((uint8_t *)&m_tickWait - 0x4) >= 0)
                sceClose(*(int *)((uint8_t *)&m_tickWait - 0x4));
            break;
        }
        case BISK_Cd:
        {
            // NOTE: This is m_cbAsyncComplete if m_tickWait is removed.
            if (STRUCT_OFFSET(this, 0x3c, int))
            {
                if (m_grfbis & 0x2)
                {
                    sceCdBreak();
                }
                else
                {
                    snd_StreamSafeCdBreak();
                }
            }
            break;
        }
    }

    m_bisk = BISK_Nil;
    m_pbRaw = 0;
    m_pb = 0;
    m_cbRaw = 0;
    m_cb = 0;
    m_grfDecomp = 0;
    m_cbSpillOver = 0;
}

void CBinaryInputStream::DecrementCdReadLimit(int cb)
{
    m_fd = m_fd - cb;
}

INCLUDE_ASM(const s32, "P2/bis", PumpCd__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", PumpHost__18CBinaryInputStream);

void CBinaryInputStream::Pump()
{
    switch (m_bisk)
    {
        case BISK_Host:
            PumpHost();
            break;
        case BISK_Cd:
            PumpCd();
            break;
        default:
            break;
    }

    // TODO: This code matches perfectly, but it could look much better.
    int iVar1 = m_cbRemaining - STRUCT_OFFSET(this, 0x24, int);
    int zero = 0;
    int remain = (iVar1 > zero) ? iVar1 : 0;

    m_cbRemaining = remain;

    if(m_pprog)
    {
        m_pprog->SetRemain(remain);
    }
}

INCLUDE_ASM(const s32, "P2/bis", Decompress__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", Read__18CBinaryInputStreamiPv);
#ifdef SKIP_ASM
/**
 * @brief Reads a certain number of bytes from the stream.
 *
 * @param cb Count of bytes to read.
 * @param pv Pointer to the memory destination.
 *
 * @todo  74.27% matched
 */
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
                    Decompress();
                    Pump();
                    m_cb = m_cbRaw;
                    m_pb = m_pbRaw;
                    m_pbRaw = m_pbRaw + m_cbRaw;
                    m_cbRaw = 0;
                    uVar1 = m_cb;
                }
                else {
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
            if (pv != nullptr) {
                byte* pb = reinterpret_cast<byte*>(pv);
                CopyAb(pb, m_pb, cb_00);
                pv = reinterpret_cast<void*>(pb + cb_00);
            }

            m_pb = m_pb + cb_00;
            m_cb = m_cb - cb_00;
        }
    }
}
#endif

void CBinaryInputStream::Align(int n)
{
    int pbAligned = ((int)m_pb + (n - 1)) & -n;
    m_cb -= (pbAligned - (int)m_pb);
    m_pb = (byte*)pbAligned;
}

uchar CBinaryInputStream::U8Read()
{

    if (m_cb >= 1)
    {
        uchar b = *m_pb;
        m_pb += 1;
        m_cb -= 1;
        return b;
    }
    else
    {
        uchar b;
        Read(1, &b);
        return b;
    }
}

ushort CBinaryInputStream::U16Read()
{
    if (m_cb >= 2)
    {
        ushort u = m_pb[0];
        ushort v = m_pb[1];
        m_pb += 2;
        m_cb -= 2;
        return (v << 8) | u;
    }
    else
    {
        ushort v;
        Read(2, &v);
        return v;
    }
}

uint CBinaryInputStream::U32Read()
{
    if (m_cb >= 4)
    {
        uint u = m_pb[0];
        uint v = m_pb[1];
        uint w = m_pb[2];
        uint x = m_pb[3];
        m_pb += 4;
        m_cb -= 4;
        return u + (v * 0x100) + (w * 0x10000) + (x * 0x1000000);
    }
    else
    {
        uint v;
        Read(4, &v);
        return v;
    }
}

INCLUDE_ASM(const s32, "P2/bis", func_00137CB8);

char CBinaryInputStream::S8Read()
{

    if (m_cb >= 1)
    {
        char b = *m_pb;
        m_pb += 1;
        m_cb -= 1;
        return b;
    }
    else
    {
        char b;
        Read(1, &b);
        return b;
    }
}

short CBinaryInputStream::S16Read()
{
    if (m_cb >= 2)
    {
        short v = m_pb[1] << 8;
        v |= m_pb[0];
        m_pb += 2;
        m_cb -= 2;
        return v;
    }
    else
    {
        short v;
        Read(2, &v);
        return v;
    }
}

int CBinaryInputStream::S32Read()
{
    if (m_cb >= 4)
    {
        int u = m_pb[0];
        int v = m_pb[1];
        int w = m_pb[2];
        char x = m_pb[3];
        m_pb += 4;
        m_cb -= 4;
        return u + (v << 8) + (w << 16) + (x << 24);
    }
    else
    {
        int v;
        Read(4, &v);
        return v;
    }
}
INCLUDE_ASM(const s32, "P2/bis", func_00137DF0);

float CBinaryInputStream::F32Read()
{
    if (m_cb >= 4)
    {
        int g;
        g = (m_pb[0] + (m_pb[1] << 8) + (m_pb[2] << 16) + (m_pb[3] << 24));
        m_pb += 4;
        m_cb -= 4;
        return *(float*)&g;
    }
    else
    {
        float g;
        Read(4, &g);
        return g;
    }
}

void CBinaryInputStream::ReadVector(VECTOR *pvec)
{
    Read(sizeof(VECTOR), pvec);
}

void CBinaryInputStream::ReadVector4(VECTOR4 *pvec)
{
    Read(sizeof(VECTOR4), pvec);
}

void CBinaryInputStream::ReadMatrix(MATRIX3 *pmat) {
    int size = sizeof(pmat->mat[0]);
    Read(size, &pmat->mat[0]);
    Read(size, &pmat->mat[1][1]);
    Read(size, &pmat->mat[2][2]);
}

INCLUDE_ASM(const s32, "P2/bis", ReadMatrix4__18CBinaryInputStreamP7MATRIX4);

INCLUDE_ASM(const s32, "P2/bis", ReadGeom__18CBinaryInputStreamP4GEOM);

INCLUDE_ASM(const s32, "P2/bis", ReadBspc__18CBinaryInputStreamP4GEOMP4BSPC);

INCLUDE_ASM(const s32, "P2/bis", ReadVbsp__18CBinaryInputStreamPiPP4VBSP);

void CBinaryInputStream::ReadStringSw(char **pachz)
{
    uint16_t length = U16Read();
    char *buffer = (char *)PvAllocSwImpl((int)length + 1);
    Read((int)length, buffer);
    buffer[length] = 0;
    *pachz = buffer;
}

INCLUDE_ASM(const s32, "P2/bis", func_00138510);
INCLUDE_ASM(const s32, "P2/bis", func_00138550);

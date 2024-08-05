#include <bis.h>
#include <989snd.h>

INCLUDE_ASM(const s32, "P2/bis", __18CBinaryInputStreamiPvi);

INCLUDE_ASM(const s32, "P2/bis", DESTRUCTOR__CBinaryInputStream);

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
    return FOpenSector(pfl->fcl.isector, pfl->fcl.cb);
}

INCLUDE_ASM(const s32, "P2/bis", Close__18CBinaryInputStream);

void CBinaryInputStream::DecrementCdReadLimit(int cb)
{
    m_fd = m_fd - cb;
}

INCLUDE_ASM(const s32, "P2/bis", PumpCd__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", PumpHost__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", Pump__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", Decompress__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", Read__18CBinaryInputStreamiPv);

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

short CBinaryInputStream::S16Read(void)
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

INCLUDE_ASM(const s32, "P2/bis", ReadMatrix__18CBinaryInputStreamP7MATRIX3);

INCLUDE_ASM(const s32, "P2/bis", ReadMatrix4__18CBinaryInputStreamP7MATRIX4);

INCLUDE_ASM(const s32, "P2/bis", ReadGeom__18CBinaryInputStreamP4GEOM);

INCLUDE_ASM(const s32, "P2/bis", ReadBspc__18CBinaryInputStreamP4GEOMP4BSPC);

INCLUDE_ASM(const s32, "P2/bis", ReadVbsp__18CBinaryInputStreamPiPP4VBSP);

INCLUDE_ASM(const s32, "P2/bis", ReadStringSw__18CBinaryInputStreamPPc);
INCLUDE_ASM(const s32, "P2/bis", func_00138510);
INCLUDE_ASM(const s32, "P2/bis", func_00138550);

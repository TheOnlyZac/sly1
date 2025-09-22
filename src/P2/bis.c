#include <bis.h>
#include <memory.h>
#include <989snd.h>
#include <sdk/libcdvd.h>
#include <lib/libkernl/filestub.h>

INCLUDE_ASM("asm/nonmatchings/P2/bis", __18CBinaryInputStreamPvii);
#ifdef SKIP_ASM
/**
 * @todo 92.85% match. Class fields might be incorrect,
 * but they seem to be used correctly elsewhere?
 * https://decomp.me/scratch/CpeOx
 */
CBinaryInputStream::CBinaryInputStream(void *pvSpool, int cbSpool, GRFBIS grfbis)
{
    int aligned = (cbSpool + 0x3f) & ~0x3f;
    int padding = (aligned - cbSpool);

    m_bisk = BISK_Nil;
    m_grfbis = grfbis;

    m_abSpool = (byte *)pvSpool - padding;
    m_cbSpool = aligned;

    // m_pbRaw = 0;
    m_pb = 0;
    m_cbRaw = 0;
    m_cb = 0;
    m_pprog = 0;
    m_grfDecomp = 0;
    m_cbSpillOver = 0;
    m_cbFile = 0;
}
#endif

CBinaryInputStream::~CBinaryInputStream()
{
    Close();
}

int CBinaryInputStream::FOpenSector(uint isector, uint cb)
{
    m_bisk = BISK_Cd;
    m_cbAsyncRequest = isector;
    m_cbFile = cb;
    m_cbRemaining = cb;
    m_fd = cb;
    m_pbRaw = m_abSpool;
    *(uint *)&m_tickWait = 0;
    m_cbAsyncComplete = 0;
    *(uint *)((int)&m_tickWait + 4) = 0;

    int cbSpool = m_cbSpool;
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
            if (*(int *)((uchar *)&m_tickWait - 0x4) >= 0)
                sceClose(*(int *)((uchar *)&m_tickWait - 0x4));
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
    m_fd -= cb;
}

INCLUDE_ASM("asm/nonmatchings/P2/bis", PumpCd__18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/bis", PumpHost__18CBinaryInputStream);

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

    if (m_pprog)
    {
        m_pprog->SetRemain(remain);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/bis", Decompress__18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/bis", Read__18CBinaryInputStreamiPv);
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
    uint uVar1;
    uint cb_00;

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
    m_pb = (byte *)pbAligned;
}

uchar CBinaryInputStream::U8Read()
{
    if (m_cb >= 1)
    {
        uchar b = *m_pb;
        m_pb++;
        m_cb--;
        return b;
    }

    uchar b;
    Read(sizeof(uchar), &b);
    return b;
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

    ushort v;
    Read(sizeof(ushort), &v);
    return v;
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

    uint v;
    Read(sizeof(uint), &v);
    return v;
}

INCLUDE_ASM("asm/nonmatchings/P2/bis", junk_00137CB8);

char CBinaryInputStream::S8Read()
{
    if (m_cb >= 1)
    {
        char b = *m_pb;
        m_pb += 1;
        m_cb -= 1;
        return b;
    }

    char b;
    Read(sizeof(char), &b);
    return b;
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

    short v;
    Read(sizeof(short), &v);
    return v;
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

    int v;
    Read(sizeof(int), &v);
    return v;
}

INCLUDE_ASM("asm/nonmatchings/P2/bis", junk_00137DF0);

float CBinaryInputStream::F32Read()
{
    if (m_cb >= 4)
    {
        int g = (m_pb[0] + (m_pb[1] << 8) + (m_pb[2] << 16) + (m_pb[3] << 24));
        m_pb += 4;
        m_cb -= 4;
        return *(float *)&g;
    }

    float g;
    Read(sizeof(float), &g);
    return g;
}

void CBinaryInputStream::ReadVector(VECTOR *pvec)
{
    Read(sizeof(VECTOR), pvec);
}

void CBinaryInputStream::ReadVector4(VECTOR4 *pvec)
{
    Read(sizeof(VECTOR4), pvec);
}

void CBinaryInputStream::ReadMatrix(MATRIX3 *pmat)
{
    int size = sizeof(pmat->mat[0]);
    Read(size, &pmat->mat[0]);
    Read(size, &pmat->mat[1][1]);
    Read(size, &pmat->mat[2][2]);
}

void CBinaryInputStream::ReadMatrix4(MATRIX4 *pmat)
{
    // TODO: This might be possible to clean up, but I wasn't able to.
    // The compiler seems to insist that must we have pointer to each row. -545u
    float *row0 = &pmat->mat[0][0];
    float *row1 = &pmat->mat[1][0];
    float *row2 = &pmat->mat[2][0];
    float *row3 = &pmat->mat[3][0];

    const int cbRow = sizeof(float) * 3;
    Read(cbRow, row0);
    Read(cbRow, row1);
    Read(cbRow, row2);
    Read(cbRow, row3);

    row0[3] = 0.0f;
    row1[3] = 0.0f;
    row2[3] = 0.0f;
    row3[3] = 1.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/bis", ReadGeom__18CBinaryInputStreamP4GEOM);

INCLUDE_ASM("asm/nonmatchings/P2/bis", ReadBspc__18CBinaryInputStreamP4GEOMP4BSPC);

INCLUDE_ASM("asm/nonmatchings/P2/bis", ReadVbsp__18CBinaryInputStreamPiPP4VBSP);

void CBinaryInputStream::ReadStringSw(char **pachz)
{
    ushort length = U16Read();
    char *buffer = (char *)PvAllocSwImpl((int)length + 1);
    Read((int)length, buffer);
    buffer[length] = 0;
    *pachz = buffer;
}

INCLUDE_ASM("asm/nonmatchings/P2/bis", junk_00138510);

void CBinaryInputStream::Unknown1()
{
    ushort size = U16Read();
    Read(size, (void *)nullptr);
}

void CBinaryInputStream::Unknown2(void **ppv)
{
    uint data[8];
    Read(0x20, &data);

    if (data[1] != data[7])
    {
        *ppv = PvAllocSwCopyImpl(0x20, data);
        return;
    }

    *ppv = (void *)nullptr;
}

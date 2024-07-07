#include <bis.h>

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

    if (cbSpool < 0) {
        cbSpool += 0xfffff;
    }

    m_cbPartialRead = 0;

    int cbAsyncRemaining = 2;
    int shr = 20;
    if ((cbSpool >> shr) > cbAsyncRemaining) {
        cbAsyncRemaining = cbSpool >> shr;
    }

    m_isector = 0;
    m_cbAsyncRemaining = cbAsyncRemaining;
    m_cbuf = cbAsyncRemaining - 1;

    return 1;
}

INCLUDE_ASM(const s32, "P2/bis", OpenMemory__18CBinaryInputStreamiPv);

INCLUDE_ASM(const s32, "P2/bis", FOpenFile__18CBinaryInputStreamP13CFileLocation);

INCLUDE_ASM(const s32, "P2/bis", Close__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", DecrementCdReadLimit__18CBinaryInputStreami);

INCLUDE_ASM(const s32, "P2/bis", PumpCd__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", PumpHost__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", Pump__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", Decompress__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", Read__18CBinaryInputStreamiPv);

INCLUDE_ASM(const s32, "P2/bis", Align__18CBinaryInputStreami);

INCLUDE_ASM(const s32, "P2/bis", U8Read__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", U16Read__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", U32Read__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", func_00137CB8);

INCLUDE_ASM(const s32, "P2/bis", S8Read__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", S16Read__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", S32Read__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", func_00137DF0);

INCLUDE_ASM(const s32, "P2/bis", F32Read__18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/bis", ReadVector__18CBinaryInputStreamP6VECTOR);

INCLUDE_ASM(const s32, "P2/bis", ReadVector4__18CBinaryInputStreamP7VECTOR4);

INCLUDE_ASM(const s32, "P2/bis", ReadMatrix__18CBinaryInputStreamP7MATRIX3);

INCLUDE_ASM(const s32, "P2/bis", ReadMatrix4__18CBinaryInputStreamP7MATRIX4);

INCLUDE_ASM(const s32, "P2/bis", ReadGeom__18CBinaryInputStreamP4GEOM);

INCLUDE_ASM(const s32, "P2/bis", ReadBspc__18CBinaryInputStreamP4GEOMP4BSPC);

INCLUDE_ASM(const s32, "P2/bis", ReadVbsp__18CBinaryInputStreamPiPP4VBSP);

INCLUDE_ASM(const s32, "P2/bis", ReadStringSw__18CBinaryInputStreamPPc);

INCLUDE_ASM(const s32, "P2/bis", func_00138510);

INCLUDE_ASM(const s32, "P2/bis", func_00138550);

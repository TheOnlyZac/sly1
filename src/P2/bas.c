#include <bas.h>
#include <sdk/libcdvd.h>
#include <lib/libkernl/filestub.h>

// INCLUDE_ASM(const s32, "P2/bas", __18CBinaryAsyncStreamPvi);
CBinaryAsyncStream::CBinaryAsyncStream(void *pvSpool)
{
    m_isector = 0;
    m_abSpool = (byte *)(((int)pvSpool + 0x3f) & ~0x3f);
    m_fd = -1;
    m_pbSpooling = 0;
    m_pb = 0;
    m_cbFile = 0;
    m_cbUnspooled = 0;
    m_cbSpooling = 0;
    m_ibCur = 0;
    m_cb = 0;
}

CBinaryAsyncStream::~CBinaryAsyncStream()
{
    Close();
}

bool CBinaryAsyncStream::FOpenFile(CFileLocation *pfl)
{
    return FOpenSector(pfl->m_fcl.isector, pfl->m_fcl.cb);
}

INCLUDE_ASM(const s32, "P2/bas", junk_0012FD98);

bool CBinaryAsyncStream::FOpenSector(u32 isector, u32 cb)
{
    m_isector = isector;
    m_cbFile = cb;
    m_cbUnspooled = cb;
    m_bask = BASK_Cd;
    m_cb = 0;
    m_pb = m_abSpool;
    m_ibCur = 0;
    StartSpooling();
    return true;
}

void CBinaryAsyncStream::Close()
{
    switch(m_bask)
    {
        case BASK_Host:
        {
            if(m_fd > -1)
            {
                sceClose(m_fd);
            }
            m_fd = -1;
            break;
        }
        case BASK_Cd:
        {
            if(FSpooling())
            {
                sceCdSync(0);
                FinishSpooling();
            }
            m_isector = 0;
            break;
        }
    }
    
    m_bask = BASK_Nil;
}

INCLUDE_ASM(const s32, "P2/bas", StartSpooling__18CBinaryAsyncStream);

bool CBinaryAsyncStream::FSpooling()
{
    return m_cbSpooling != 0;
}

INCLUDE_ASM(const s32, "P2/bas", FSpoolingComplete__18CBinaryAsyncStream);

INCLUDE_ASM(const s32, "P2/bas", FinishSpooling__18CBinaryAsyncStream);

void CBinaryAsyncStream::Spool()
{
    switch (m_bask)
    {
        case BASK_Host:
        {
            StartSpooling();
            FinishSpooling();
            break;
        }
        case BASK_Cd:
        {
            FinishSpooling();
            StartSpooling();
            break;
        }
    }
}

void CBinaryAsyncStream::Skip(int cb)
{
    m_ibCur += cb;
}

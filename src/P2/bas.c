#include <bas.h>
#include <cd.h>
#include <sdk/libcdvd.h>
#include <lib/libkernl/filestub.h>

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

JUNK_ADDIU(30);

bool CBinaryAsyncStream::FOpenSector(uint isector, uint cb)
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
    switch (m_bask)
    {
        case BASK_Host:
        {
            if (m_fd > -1)
            {
                sceClose(m_fd);
            }
            m_fd = -1;
            break;
        }
        case BASK_Cd:
        {
            if (FSpooling())
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

void CBinaryAsyncStream::StartSpooling()
{
    if (!FSpooling() && m_cbUnspooled != 0)
    {
        byte *pv = m_abSpool;
        int cb = 0x4000;

        if (m_cbUnspooled < cb)
        {
            cb = m_cbUnspooled;
        }

        if (m_pb == pv)
        {
            pv += 0x4000;
        }

        m_pbSpooling = pv;
        m_cbSpooling = cb;

        switch (m_bask)
        {
            case BASK_Host:
            {
                sceRead(m_fd, pv, cb);
                break;
            }
            case BASK_Cd:
            {
                ReadCdDirect(m_isector, (m_cbSpooling + 0x7ffu) >> 0x0b, pv);
                break;
            }
        }
    }
}

bool CBinaryAsyncStream::FSpooling()
{
    return m_cbSpooling != 0;
}

bool CBinaryAsyncStream::FSpoolingComplete()
{
    int status = 0;
    bool fComplete = false;

    if (m_cb == m_ibCur && FSpooling())
    {
        switch (m_bask)
        {
            case BASK_Host:
            {
                int fExecuting;
                status = sceIoctl(m_fd, 1, &fExecuting);
                fComplete = (fExecuting == 0);
                break;
            }
            case BASK_Cd:
            {
                fComplete = (sceCdSync(1) == 0);
                if (fComplete)
                {
                    status = sceCdGetError();
                }
                break;
            }
        }
    }

    if (status)
    {
        m_cbSpooling = 0;
        m_pbSpooling = 0;
        fComplete = false;
    }

    return fComplete;
}

void CBinaryAsyncStream::FinishSpooling()
{
    if (FSpoolingComplete())
    {
        if (m_bask == BASK_Cd)
        {
            int n;
            if (m_cbSpooling <= -1)
            {
                n = m_cbSpooling + 0x7ffu;
            }
            else
            {
                n = m_cbSpooling;
            }

            m_isector += n >> 0x0b;
        }

        int cb = m_cbSpooling;

        m_cbUnspooled -= cb;
        m_pb = m_pbSpooling;
        m_cb = cb;

        m_cbSpooling = 0;
        m_pbSpooling = 0;
        m_ibCur = 0;
    }
}

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

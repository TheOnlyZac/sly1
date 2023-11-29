#include "cat.h"
#include <cstring>

//todo move to util header
#ifdef _MSC_VER
    #define STRICMP _stricmp
#else
    #include <strings.h>
    #define STRICMP strcasecmp
#endif

void CFileLocation::Clear()
{
    memset(this, 0, 8);
}

void CWalCatalog::Init(CFileLocation* pflWac, CFileLocation* pflWal)
{
    m_flWac.m_fcl.isector = pflWac->m_fcl.isector;
    m_flWac.m_fcl.cb = pflWac->m_fcl.cb;
    m_flWal.m_fcl.isector = pflWac->m_fcl.isector;
    m_flWal.m_fcl.cb = pflWal->m_fcl.cb;
}

int CWalCatalog::FFindFile(char* pchzKey, FK fk, CFileLocation* pflResult)
{
    WALE* pWVar1;
    WALE* pWVar3;
    WALE* pwale;
    int iVar2;
    int iVar4;
    char achzKey[128]; // Buffer used to reference the file its looking for.

    //! There is a mistake here, nothing is passed to the format string
    sprintf(achzKey, "%s\\%s"); // Storing the file that its looking for in achzKey buffer.
    pWVar3 = m_awale;

    while ((pwale == nullptr, iVar4 < m_cwale && (iVar2 = STRICMP(pWVar3->pchzKey, achzKey), pwale = pWVar3, iVar2 != 0))) {
        pWVar3 += 1;
        iVar4 += 1;
    }

    if (pwale == 0x0) {
        iVar4 = 0;
        pWVar3 = m_awale;

        while ((pWVar1 = pwale, iVar4 < m_cwale && (iVar2 = STRICMP(pWVar3->pchzKey, pchzKey), pWVar1 = pWVar3, iVar2 != 0))) {
            pWVar3 = pWVar3 + 1;
            iVar4 = iVar4 + 1;
        }

        pwale = pWVar1;
        if (pwale == 0x0)
            return (int)(pwale != 0x0);
    }

    if (pflResult != 0x0)
        BuildFl(pwale, pflResult);

    return (int)(pwale != 0x0);
}

int CWalCatalog::FDefaultWorld(char* pchzResult, CFileLocation* pflResult)
{
    int isFileFound;

    if (m_cpchz == 0)
        isFileFound = 0;

    else {
        strcpy(pchzResult, m_apchz[0]);
        isFileFound = FFindFile(pchzResult, FK_BrxWorld, pflResult);
    }

    return isFileFound;
}

void CWalCatalog::BuildFl(WALE* pwale, CFileLocation* pflResult)
{
    m_awale->pchzKey = pwale->pchzKey;
    m_awale->pfcl->isector = pflResult->m_fcl.isector;
    m_awale->pfcl->cb = pflResult->m_fcl.cb;
}

void CWalCatalog::Reload()
{

}

void CCatalog::Init()
{

}

int CCatalog::FFindFile(char* pchzKey, FK fk, CFileLocation* pflResult)
{
    return 0;
}

int CCatalog::FDefaultWorld(char* pchzResult, CFileLocation* pflResult)
{
    int isDefaultWorldFound = m_wcatCd.FDefaultWorld(pchzResult, pflResult);
    return isDefaultWorldFound;
}

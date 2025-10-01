#include <sce/memset.h>
#include <transition.h>
#include <chkpnt.h>
#include <phasemem.h>
#include <sw.h>
#include <joy.h>
#include <brx.h>
#include <sound.h>

CTransition::CTransition()
{
    m_pchzWorld = (char*)nullptr;
    grftrans = FTRANS_None;
    m_oidWarp = OID_Nil;
    m_oidWarpContext = OID_Nil;
    memset(m_achzWorldCur, 0, 0x20);
}

void CTransition::Set(char *pchzWorld, OID oidWarp, OID oidWarpContext, GRFTRANS grftrans)
{
    if (m_fPending == false)
    {
        this->m_fPending = true;
        this->m_pchzWorld = pchzWorld;
        this->m_oidWarp = oidWarp;
        this->m_oidWarpContext = oidWarpContext;
        this->grftrans = grftrans;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/transition", Execute__11CTransition);
#ifdef SKIP_ASM
/**
 * @todo 15.19% matched.
 *
 * Some functions called in this function are not implemented yet.
 */
void CTransition::Execute()
{
    CFileLocation fileLocation;
    LevelTableStruct levelInfo = {};

    SetPhase(PHASE_Load);
    // func_0018d410();

    if (levelInfo.fileLocation.m_fcl.cb != 0)
    {
        // fileLocation.Clear();

        // Decrypting the sector offsets and file size
        uint cb = levelInfo.fileLocation.m_fcl.cb ^ levelInfo.level_name;
        uint isector = levelInfo.fileLocation.m_fcl.isector ^ levelInfo.for_size;
        fileLocation.m_fcl.cb = cb;
        fileLocation.m_fcl.isector = isector;

        // Set up progress bar (temp, this was copied from Startup)
        int nRemain = cb;
        int rgbaComplete = 0x007f0000; // blue
        int rgbaRemain = 0x003f3f3f; // gray
        int rgbaWarning = 0x00003f3f; // yellow
        int rgbaTrouble = 0x0000003f; // red
        CProg prog = CProg((RGBA *)&rgbaComplete, (RGBA *)&rgbaRemain, (RGBA *)&rgbaWarning, (RGBA *)&rgbaTrouble);

        if (cb == 0)
        {
            MvgkUnknown1(MVGK_Music);
            SetMvgkRvol(MVGK_Music, 1.0f);
            ClearPhase(PHASE_None);
            levelInfo.fileLocation.m_fcl.isector = 0;
            return;
        }

        DeleteSw(g_psw);
        g_psw = 0;
        // SetupBulkDataFromBrx()
        ResetClock(&g_clock, 0.0);
        AddGrfusr(0x80);
        // SetupGame(levelInfo.level_id);
        g_psw = (SW *)PloNew(CID_SW, 0, 0, OID__WORLD, -1);
    }
}
#endif // SKIP_ASM

void ResetWorld(FTRANS ftrans)
{
    SetMvgkUvol(0.0f);

    GRFTRANS grftrans;
    switch (ftrans)
    {
    case FTRANS_None:
        grftrans = FTRANS_None;
        break;
    case FTRANS_Checkpoint:
        ReturnChkmgrToCheckpoint(&g_chkmgr);
        return;
    case FTRANS_RetryWorld:
        grftrans = FTRANS_RetryWorld;
        break;
    case (FTRANS_Checkpoint | FTRANS_RetryWorld):
        // Transitions with the Sly Cooper logo wipe
        grftrans = 4;
        break;
    }

    g_transition.Set(g_transition.m_achzWorldCur, OID_Nil, OID_Nil, grftrans);
}

INCLUDE_ASM("asm/nonmatchings/P2/transition", transition__static_initialization_and_destruction_0);

INCLUDE_ASM("asm/nonmatchings/P2/transition", _GLOBAL_$I$g_transition);

/**
 * @file transition.cpp
 *
 * @brief Implements for the transition system.
*/
#include <transition.h>

void::CTransition::ResetWorld(FTRANS ftrans)
{
    //989snd_related__(0.0);
    if (ftrans == FTRANS_Checkpoint) {
        //ReturnChkmgrToCheckpoint(&g_chkmgr);
    }
    else {
        if (ftrans < 2) {
            if (ftrans == GRFTRANS_None) {
                grftrans = 0;
                /* Reload with no transition */
            }
        }
        else if (ftrans == FTRANS_RetryWorld) {
            grftrans = 2;
        }
        else if (ftrans == (FTRANS_Checkpoint | FTRANS_RetryWorld)) {
            /* Transition with the Sly Cooper logo wipe */
            grftrans = 4;
        }
        Set(g_transition.m_achzWorldCur, OID_Unknown, OID_Unknown, grftrans);
    }
}

void CTransition::Set(char* pchzWorld, OID oidWarp, OID oidWarpContext, GRFTRANS grftrans)
{
	if (m_fPending == 0) {
		grftrans = grftrans;
		m_fPending = 1;
		m_pchzWorld = pchzWorld;
		m_oidWarp = oidWarp;
		m_oidWarpContext = oidWarpContext;
	}
}

void CTransition::Execute()
{
    CFileLocation fileLocation;
    LevelTableStruct levelInfo{};

    SetPhase(PHASE_Load);
    if (levelInfo.fileLocation.m_fcl.cb != 0)
    {
        fileLocation.Clear();

        // Decrypting the sector offsets and file size
        fileLocation.m_fcl.cb = levelInfo.fileLocation.m_fcl.cb ^ levelInfo.level_name;
        fileLocation.m_fcl.isector = levelInfo.fileLocation.m_fcl.isector ^ levelInfo.for_size;

        if (fileLocation.m_fcl.cb == 0)
        {
            //FUN_001C06D8();
            //SetMvgkRvol();//
            ClearPhase(PHASE_Load);
            levelInfo.fileLocation.m_fcl.isector = 0;
            return;
        }

        DeleteSw(g_psw);
        g_psw = 0;
        //SetupBulkDataFromBrx()
        ResetClock(&g_clock, 0.0);
        AddGrfusr(0x80);
        //SetupGame(levelInfo.level_id);
        g_psw = PloNew(CID_SW, 0, 0, OID__WORLD, -1);

    }
}


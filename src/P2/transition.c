#include <sce/memset.h>
#include <transition.h>
#include <chkpnt.h>

extern void SetMvgkRvol(float); // todo: replace with header file/declaration

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

INCLUDE_ASM(const s32, "P2/transition", Execute__11CTransition);

void ResetWorld(FTRANS ftrans)
{
    GRFTRANS grftrans;

    SetMvgkRvol(0.0f);
    switch (ftrans)
    {
        case FTRANS_None:
            /* Reload with no transition */
            grftrans = FTRANS_None;
            break;

        case FTRANS_Checkpoint:
            ReturnChkmgrToCheckpoint(&g_chkmgr);
            return;

        case FTRANS_RetryWorld:
            grftrans = FTRANS_RetryWorld;
            break;

        case (FTRANS_Checkpoint | FTRANS_RetryWorld):
            /* Transition with the Sly Cooper logo wipe */
            grftrans = 4;
            break;
    }

    g_transition.Set(g_transition.m_achzWorldCur, OID_Nil, OID_Nil, grftrans);
}

INCLUDE_ASM(const s32, "P2/transition", transition__static_initialization_and_destruction_0);

INCLUDE_ASM(const s32, "P2/transition", _GLOBAL_$I$g_transition);

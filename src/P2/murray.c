#include <murray.h>
#include <stepguard.h>
#include <lo.h>
#include <oid.h>
#include <vec.h>
#include <xform.h>
#include <game.h>
#include <cid.h>
#include <rwm.h>
#include <mq.h>

void InitMurray(MURRAY *pmurray)
{
    InitStepguard(pmurray);
    STRUCT_OFFSET(pmurray, 0xbd4, int) = 0; // pmurray->fAutoFadeDying
    STRUCT_OFFSET(pmurray, 0xbd0, float) = 0.0f; // pmurray->uFling
}

void PostMurrayLoad(MURRAY *pmurray)
{
    PostStepguardLoad(pmurray);

    SnipAloObjects(pmurray, 2, D_00269B60);

    STRUCT_OFFSET(pmurray, 0x5f0, ASEG *) = PasegFindStepguard(pmurray, OID_EF);
    STRUCT_OFFSET(pmurray, 0xc38, ASEG *) = PasegFindStepguard(pmurray, OID_16C);
    STRUCT_OFFSET(pmurray, 0xc3c, ASEG *) = PasegFindStepguard(pmurray, OID_16D);
    STRUCT_OFFSET(pmurray, 0xc40, ASEG *) = PasegFindStepguard(pmurray, OID_16A);
    STRUCT_OFFSET(pmurray, 0xc44, ASEG *) = PasegFindStepguard(pmurray, OID_16B);
}

void OnMurrayEnteringSgs(MURRAY *pmurray, SGS sgsPrev, ASEG *pasegTargetOverride) 
{
    SGS postSGS;
    SGG *murraySgg;
    ASEG *localAseg = pasegTargetOverride;

    SGS preSGS = STRUCT_OFFSET(pmurray, 0x724, SGS);
    switch (preSGS) 
    {                               /* irregular */
    case SGS_ReturnToPatrol:
        STRUCT_OFFSET(pmurray, 0xC28, XFM *) = 0;
        STRUCT_OFFSET(pmurray, 0xC10, int) = 0;
        break;
    case SGS_Stun:
        if (STRUCT_OFFSET(pmurray, 0xC30, int) == 4) 
        {
            localAseg = STRUCT_OFFSET(pmurray, 0xC44, ASEG *);
        } else 
        {
            localAseg = STRUCT_OFFSET(pmurray, 0xC3C, ASEG *);
        }
        break;
    case SGS_Dying:
        if (STRUCT_OFFSET(pmurray, 0xC30, int) == 4) 
        {
            localAseg = STRUCT_OFFSET(pmurray, 0xC40, ASEG *);
        } else 
        {
            localAseg = STRUCT_OFFSET(pmurray, 0xC38, ASEG *);
        }
        murraySgg = STRUCT_OFFSET(pmurray, 0x720, SGG *);
        if (murraySgg != 0) 
        {
            RemoveSggGuard(murraySgg, pmurray);
        }
        break;
    }
    OnStepguardEnteringSgs(pmurray, sgsPrev, localAseg);
    postSGS = STRUCT_OFFSET(pmurray, 0x724, SGS);
    if ((postSGS == SGS_Dying) || (postSGS == SGS_Stun)) 
    {
        STRUCT_OFFSET(pmurray, 0xC04, int) = 0;
    }
}

void OnMurrayExitingSgs(MURRAY *pmurray, SGS sgs) 
{
    void** tempFunction; //used as a pointer to a function

    OnStepguardExitingSgs(pmurray, sgs);
    SGS murraySGS = STRUCT_OFFSET(pmurray, 0x724, SGS); // pmurray->sgs
    switch (murraySGS) 
    {                         
        case SGS_Stun:
            tempFunction = STRUCT_OFFSET(pmurray, 0xC2C, void **);
            if (tempFunction != NULL) 
            {
                typedef void (*VFn)(void**);
                STRUCT_OFFSET((*tempFunction), 0x150, VFn)(tempFunction);
            }
            break;
        case SGS_LostPlayer:
            if (STRUCT_OFFSET(pmurray, 0x600, int) == 1) 
            {
                typedef void (*VFn2)(MURRAY*,int);
                STRUCT_OFFSET(STRUCT_OFFSET(pmurray, 0x0, int), 0x14C, VFn2)(pmurray, 0);
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/murray", UpdateMurrayGoal__FP6MURRAYi);

INCLUDE_ASM("asm/nonmatchings/P2/murray", UpdateMurraySgs__FP6MURRAY);

int FUN_001903f0(MURRAY *pmurray, int i) 
{
    if ((g_grfcht & 1) || (IsSwHandsOff__FP2SW(STRUCT_OFFSET(pmurray, 0x14, SW *)) != 0)) 
    {
        return 1;
    }
    return FUN_001c9a48(pmurray, i);
}

int FUN_00190450(MURRAY *pmurray, ZPR *pzpr) 
{
    SO *so;
    
    typedef int (*VFn)(MURRAY*, SO*);
    if (STRUCT_OFFSET(STRUCT_OFFSET(pmurray, 0x0, MURRAY *), 0x13c, VFn)(pmurray, (STRUCT_OFFSET(pzpr, 0x0, SO *)))) 
    {
         return 0;
    }
        
    STRUCT_OFFSET(pmurray, 0xC34, int) = 0;
    STRUCT_OFFSET(pmurray, 0xC30, int) = (int) STRUCT_OFFSET(pzpr, 0x0, int);
    if (STRUCT_OFFSET(pzpr, 0x0, int) == 0) 
    {
        so = STRUCT_OFFSET(pzpr, 0x4, SO *);
        if (so != 0) 
        {
            if (FIsRwmAmmo(STRUCT_OFFSET(STRUCT_OFFSET(pmurray, 0xC2C, MURRAY *), 0x618, RWM *), so) != 0) 
            {
                STRUCT_OFFSET(pmurray,0xC34,int) = 1;
            }
        }
    }
    return FTakeStepguardDamage(pmurray, pzpr);
}

int FAbsorbMurrayWkr(MURRAY *pmurray, WKR *pwkr) 
{
    if (FCharmAvailable__Fv() == 0) 
    {
        STRUCT_OFFSET(pmurray, 0xA68, int) = 0;
    } 
    else if (STRUCT_OFFSET(pmurray,0xC34,int) == 0) 
    {
        STRUCT_OFFSET(pmurray,0xA68, int) = 1;
    } 
    else 
    {
        STRUCT_OFFSET(pmurray, 0xA68, int) = 0;
    }

    int absorbed = FAbsorbStepguardWkr__FP9STEPGUARDP3WKR(pmurray, pwkr);
    if (absorbed == 0) 
    {
        return 0;    
    }

    struct 
    {
        MURRAY* pmurray; // 0x0($29)
        int wkr_val;   // 0x4($29)
    } stack_args;

    stack_args.pmurray = pmurray;
    stack_args.wkr_val = STRUCT_OFFSET(pwkr,0x0,int);
        
    typedef void (*VFn)(MURRAY*, int, typeof(stack_args)*);
    VFn tester = STRUCT_OFFSET(STRUCT_OFFSET(pmurray,0x0,int), 0x48, VFn);
    tester(pmurray, 0x17, &stack_args);
    return 1;
}

/**
 * @todo 100% match. Register allocation is different, but the logic is the same.
 */
INCLUDE_ASM("asm/nonmatchings/P2/murray", FDetectMurray__FP6MURRAY);
#ifdef SKIP_ASM
int FDetectMurray(MURRAY *pmurray)
{    
    if (STRUCT_OFFSET(pmurray, 0xC28, int) != 0)
    {
        int i = 0;
        for (; i < STRUCT_OFFSET(pmurray, 0xC10, int); i++)
        {
            ALO *paloEnemy = STRUCT_OFFSET_INDEX(pmurray, 0xC14, ALO*, i);    
            CID type;
    
            if (!FIsBasicDerivedFrom(paloEnemy, CID_STEPGUARD)
                || ((type = STRUCT_OFFSET(paloEnemy, 0x724, CID)), type != CID_UBG)
                    && (FIsBasicDerivedFrom(paloEnemy, CID_SMARTGUARD)
                        || type != CID_GOMER))
            {
                if (FIsLoInWorld(paloEnemy))
                {
                    if (i >= STRUCT_OFFSET(pmurray, 0xC10, int))
                        break;
                    return 1;
                }
            }
        }
        
        STRUCT_OFFSET(pmurray, 0xC28, XFM *) = 0;
    }
    return 0;
}
#endif

int FCanMurrayAttack(MURRAY *pmurray)
{
    return false;
}

int AddMurrayEnemy(MURRAY *pmurray, ALO *paloEnemy) 
{
    int arraySize;

    if ((paloEnemy != 0) && (FIsLoInWorld__FP2LO(paloEnemy) != 0)) 
    {
        if ((FIsBasicDerivedFrom__FP5BASIC3CID(paloEnemy, CID_STEPGUARD) == 0) 
                || (STRUCT_OFFSET(paloEnemy, 0x724, SGS) != SGS_Dying)) 
        {
            arraySize = STRUCT_OFFSET(pmurray, 0xC10, int);
            if (arraySize < 4U) 
            {
                int tempForCompile = (4 * arraySize);
                *(ALO **)((unsigned char *)(tempForCompile + 0xC14) + (unsigned int)pmurray) = paloEnemy; // had to do it like this to match
                STRUCT_OFFSET(pmurray, 0xC10, int) = arraySize + 1;
                return 1;
            }
        }
    }
    return 0;
}

void SetMurrayPursueXfm(MURRAY *pmurray, XFM *pxfm)
{
    STRUCT_OFFSET(pmurray, 0xc28, XFM *) = pxfm; // pmurray->pxfmPursue
}

void SetMurrayPatrolXfm(MURRAY *pmurray, XFM *pxfm)
{
    STRUCT_OFFSET(pmurray, 0xc24, XFM *) = pxfm; // pmurray->pxfmPatrol
}

void CollectMurrayPrize(MURRAY *pmurray, PCK pck, ALO *palo)
{
    CollectPoPrize(pmurray, pck, palo);
    if (pck == PCK_Key)
    {
        SetStepguardSgs(pmurray, SGS_LostPlayer, STRUCT_OFFSET(pmurray, 0x5f0, ASEG *)); // pmurray->pasegCelebrateKey
    }
}

int CheckMurrayStunOrDying(MURRAY *pmurray) 
{
    SGS sgs = STRUCT_OFFSET(pmurray, 0x724, SGS); // pmurray->sgs
    switch (sgs) 
    {
        case SGS_Stun:   
            return 1;
        case SGS_Dying:     
            return 2;
        default:            
            return 0;
    }
}

void HandleMurrayMessage(MURRAY *pmurray, MSGID msgid, void* pv) 
{
    HandleStepguardMessage(pmurray, msgid, pv);
    if (msgid == MSGID_label) 
    {
        //pmurray->pasegaSgs
        if (STRUCT_OFFSET(pv, 0x0, ASEGA *) == STRUCT_OFFSET(pmurray, 0x7E0, ASEGA *)) 
        {
            if (STRUCT_OFFSET(pv, 0x8, int) == 1338) 
            {
                reload_post_death();
            }
        }
    }
}

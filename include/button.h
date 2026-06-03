/**
 * @file button.h
 *
 * @brief Button.
 */
#ifndef BUTTON_H
#define BUTTON_H

#include "common.h"
#include <oid.h>
#include <so.h>
#include <rs.h>

// Forward.
struct ASEG;
struct DIALOG;

/**
 * @brief Unknown.
 */
enum IASH
{
    IASH_On = 0,
    IASH_Off = 1,
    IASH_Max = 2
};

/**
 * @brief Unknown.
 */
struct ASH
{
    int coid;
    OID aoid[16];
    int cpaseg;
    ASEG *apaseg[16];
};

/**
 * @brief Button state.
 */
enum BUTTONS
{
    BUTTONS_Nil = -1,
    BUTTONS_NoContact = 0,
    BUTTONS_Contact = 1,
    BUTTONS_Pushed = 2,
    BUTTONS_Disabled = 3,
    BUTTONS_Reset = 4,
    BUTTONS_Max = 5
};

/**
 * @brief Button.
 *
 * @todo Migrated from May 19 prototype. May be incorrect.
 */
struct BTN
{
    /* 0x00 */ int unknown; // TODO: VTBTN
    /* 0x04 */ ALO *paloOwner;
    /* 0x08 */ ASH aash[2];
    float svtAnimation;
    /* 0x11c */ int fCheckpointed;
    /* 0x120 */ int ichkPushed;
    float tButtons;
    float dtRepush;
    BUTTONS buttons;
    int fEnabled;
    int fSilent;
    int fReapplyAseg;
    int fManualReset;
    /* 0x140 */ OID oidDialog;
    DIALOG *pdialog;
    int crsmg;
    RSMG arsmg[8];
};

/**
 * @class VOL_BUTTON
 * @brief Volume button.
 */
struct VOLBTN : public SO
{
    // ...
    /* 0x550 */ int coidPush;
    /* 0x554 */ OID aoidPush[8];
    //...
    /* 0x5c0 */ BTN btn;
    // ...
    /* 0x790 */ int fSendChangeEvents;
    // ...
};

/**
 * @class BUTTON
 * @brief Button.
 */
struct BUTTON : public SO
{
    /* 0x550 */ STRUCT_PADDING(1); // TODO: Probably BTNT.
    /* 0x554 */ BTN btn;
    /* 0x720 */ int coidPush;
    /* 0x724 */ OID aoidPush[8];
    /* 0x744 */ int coidNoPush;
    /* 0x748 */ OID aoidNoPush[8];
    /* 0x768 */ int ccidPush;
    /* 0x76c */ CID acidPush[8];
    /* 0x78c */ int ccidNoPush;
    /* 0x790 */ CID acidNoPush[8];
    // ...
};

void PostAshLoad(SW *psw, ASH *pash, ALO *paloOwner);

int FFoundAshAseg(ASH *pash, ASEG *paseg);

int FAddAshAseg(ASH *pash, ASEG *paseg);

int FAddAshOid(ASH *pash, OID oid);

void InitBtn(BTN *pbtn);

void LoadBtn(BTN *pbtn, ALO *paloOwner);

void PostBtnLoad(BTN *pbtn);

void RestoreBtnFromCheckpointCallback(BTN *pbtn, MSGID msgid, void *pv);

void SetBtnRsmg(BTN *pbtn, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal);

void SetBtnButtons(BTN *pbtn, BUTTONS buttons);

int FAddRsmg(RSMG *arsmg, int crsmgMax, int *pcrsmg, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal);

void TriggerRsmg(SW *psw, int crsmg, RSMG *arsmg, LO *ploContext, int fTrigger);

void RunBtnAsegs(BTN *pbtn, IASH asht, int fSeekToEnd, int fUnknown);

void TriggerBtn(BTN *pbtn, int fSeekToEnd, int fChkTrigger);

void UntriggerBtn(BTN *pbtn, int fSeekToEnd);

void InitButton(BUTTON *pbutton);

void LoadButtonFromBrx(BUTTON *pbutton, CBinaryInputStream *pbis);

void InsertButtonPos(BUTTON *pbutton, PNT *ppnt, VECTOR *ppos);

void InsertButtonMat(BUTTON *pbutton, XFM *pxfm, MATRIX3 *pmat);

void PostButtonLoad(BUTTON *pbutton);

void CloneButton(BUTTON *pbutton, BUTTON *pbuttonBase);

void SetButtonButtons(BUTTON *pbutton, BUTTONS buttons);

int FCheckButtonObject(BUTTON *pbutton, SO *psoOther);

int IposFindButtonClosest(BUTTON *pbutton, float *psDist);

int ImatFindButtonClosest(BUTTON *pbutton, float *prad);

void PresetButtonAccel(BUTTON *pbutton, float dt);

void UpdateButtonInternalXps(BUTTON *pbutton);

void UpdateButton(BUTTON *pbutton, float dt);

int FAbsorbButtonWkr(BUTTON *pbutton, WKR *pwkr);

void InitVolbtn(VOLBTN *pvolbtn);

void LoadVolbtnFromBrx(VOLBTN *pvolbtn, CBinaryInputStream *pbis);

void PostVolbtnLoad(VOLBTN *pvolbtn);

void CloneVolbtn(VOLBTN *pvolbtn, VOLBTN *pvolbtnBase);

void SetVolbtnButtons(VOLBTN *pvolbtn, BUTTONS buttons);

void UpdateVolbtn(VOLBTN *pvolbtn, float dt);

int FGetVolbtnPushObjectsWithinList(VOLBTN *pvolbtn, void *pvstate);

void AddBtnAseg(BTN *pbtn, ALO *palo, OID oid);

void AddButtonAseg(BUTTON *pbutton, OID oid);

void AddVolbtnAseg(VOLBTN *pvolbtn, OID oid);

void AddBtnOffAseg(BTN *pbtn, ALO *palo, OID oid);

void AddButtonOffAseg(BUTTON *pbutton, OID oid);

void AddVolbtnOffAseg(VOLBTN *pvolbtn, OID oid);

void AddButtonPushObject(BUTTON *pbutton, OID oid);

void AddButtonNoPushObject(BUTTON *pbutton, OID oid);

void AddButtonPushClass(BUTTON *pbutton, CID cid);

void AddButtonNoPushClass(BUTTON *pbutton, CID cid);

void AddVolbtnPushObject(VOLBTN *pvolbtn, OID oid);

void SetButtonRsmg(BUTTON *pbutton, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal);

void SetVolbtnRsmg(VOLBTN *pvolbtn, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal);

#endif // BUTTON_H

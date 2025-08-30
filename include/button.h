/**
 * @file button.h
 *
 * @brief Button.
 */
#ifndef BUTTON_H
#define BUTTON_H

#include <anim.h>
#include <oid.h>
#include <so.h>
#include <rs.h>

/**
 * @brief Button State (?).
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
 * @todo Migrated from May 19 prototype. May be incorrect.
 */
struct BTN
{
    int unknown;
    ALO *paloOwner;
    ASH aash[2];
    float svtAnimation;
    int fCheckpointed;
    int ichkPushed;
    float tButtons;
    float dtRepush;
    BUTTONS buttons;
    int fEnabled;
    int fSilent;
    int fReapplyAseg;
    int fManualReset;
    OID oidDialog;
    // DIALOG *pdialog;
    int crsmg;
    RSMG arsmg[8];
};

/**
 * @brief Unknown.
 */
struct VOLBTN
{
    // ...
};

/**
 * @brief Button.
 */
struct BUTTON : public SO
{
    BTN btn;
    // ...
};

/*
void PostAshLoad(SW *psw, ASH *pash, ALO *paloOwner);

int FFoundAshAseg(ASH *pash, ASEG *paseg);

int FAddAshAseg(ASH *pash, ASEG *paseg);

int FAddAshOid(ASH *pash, OID oid);
*/

void InitBtn(BTN *pbtn);

void LoadBtn(BTN *pbtn, ALO *paloOwner);

void PostBtnLoad(BTN *pbtn);

// void RestoreBtnFromCheckpointCallback(BTN *pbtn, MSGID msgid, void *pv);

void SetBtnRsmg(BTN *pbtn, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal);

void SetBtnButtons(BTN *pbtn, BUTTONS buttons);

int FAddRsmg(RSMG *arsmg, int crsmgMax, int *pcrsmg, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal);

/*
void TriggerRsmg(SW *psw, int crsmg, RSMG *arsmg, LO *ploContext, int fTrigger);

void RunBtnAsegs(BTN *pbtn, IASH asht, int fSeekToEnd);

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
*/

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

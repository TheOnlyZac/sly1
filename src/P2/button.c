#include <button.h>
#include <chkpnt.h>

INCLUDE_ASM("asm/nonmatchings/P2/button", PostAshLoad__FP2SWP3ASHP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/button", FFoundAshAseg__FP3ASHP4ASEG);

int FAddAshAseg(ASH *pash, ASEG * paseg)
{
    int c = STRUCT_OFFSET(pash, 0x44, int);
    ASEG * *a = &STRUCT_OFFSET(pash, 0x48, ASEG *);
    a[c] = paseg;
    c = c + 1;
    STRUCT_OFFSET(pash, 0x44, int) = c;
    return c < 16;
}

int FAddAshOid(ASH *pash, OID oid)
{
    int c = STRUCT_OFFSET(pash, 0x0, int);
    OID *a = &STRUCT_OFFSET(pash, 0x4, OID);
    a[c] = oid;
    c = c + 1;
    STRUCT_OFFSET(pash, 0x0, int) = c;
    return c < 16;
}

void InitBtn(BTN *pbtn)
{
    STRUCT_OFFSET(pbtn, 0x120, int) = IchkAllocChkmgr(&g_chkmgr); // pbtn->ichkPushed
    STRUCT_OFFSET(pbtn, 0x140, OID) = OID_Nil; // pbtn->oidDialog
}

INCLUDE_ASM("asm/nonmatchings/P2/button", LoadBtn__FP3BTNP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/button", PostBtnLoad__FP3BTN);

void RestoreBtnFromCheckpointCallback(BTN *pbtn, MSGID msgid, void *pv)
{
    if (msgid == MSGID_callback)
    {
        PostSwCallback(pbtn->paloOwner->psw, (PFNMQ)RestoreBtnFromCheckpointCallback, pbtn,
                       MSGID_button_trigger, NULL);
    }
    else
    {
        TriggerBtn(pbtn, 1, 1);
    }
}

void SetBtnRsmg(BTN *pbtn, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal)
{
    FAddRsmg(pbtn->arsmg, 8, &pbtn->crsmg, fOnTrigger, oidRoot, oidSM, oidGoal);
}

INCLUDE_ASM("asm/nonmatchings/P2/button", SetBtnButtons__FP3BTN7BUTTONS);

INCLUDE_ASM("asm/nonmatchings/P2/button", FAddRsmg__FP4RSMGiPii3OIDN24);

INCLUDE_ASM("asm/nonmatchings/P2/button", TriggerRsmg__FP2SWiP4RSMGP2LOi);

INCLUDE_ASM("asm/nonmatchings/P2/button", RunBtnAsegs__FP3BTN4IASHii);

void TriggerBtn(BTN *pbtn, int fSeekToEnd, int fChkTrigger)
{
    if (fChkTrigger)
        HandleLoSpliceEvent(pbtn->paloOwner, 0x16, 0, NULL);
    else
        HandleLoSpliceEvent(pbtn->paloOwner, 2, 0, NULL);

    if (!STRUCT_OFFSET(pbtn, 0x134, int) && !fChkTrigger) // pbtn->fSilent
    {
        float sStart = 3000.0f;
        float sFull = 300.0f;
        float uVolAtSource = 1.0f;
        StartSound(SFXID_Click1, NULL, pbtn->paloOwner, NULL, sStart, sFull, uVolAtSource, 0.0f,
                   0.0f, NULL, NULL);
    }

    RunBtnAsegs(pbtn, IASH_On, fSeekToEnd, fChkTrigger);

    if (!STRUCT_OFFSET(pbtn, 0x13C, int)) // pbtn->fManualReset
        SetBtnButtons(pbtn, BUTTONS_Pushed);

    if (STRUCT_OFFSET(pbtn, 0x11C, int))                           // pbtn->fCheckpointed
        SetChkmgrIchk(&g_chkmgr, STRUCT_OFFSET(pbtn, 0x120, int)); // pbtn->ichkPushed

    pbtn->paloOwner->pvtlo->pfnSendLoMessage(pbtn->paloOwner, MSGID_button_trigger, pbtn);
}

void UntriggerBtn(BTN *pbtn, int fSeekToEnd)
{
    HandleLoSpliceEvent(pbtn->paloOwner, 3, 0, NULL); // untrigger event
    RunBtnAsegs(pbtn, IASH_Off, fSeekToEnd, 0);
    pbtn->paloOwner->pvtlo->pfnSendLoMessage(pbtn->paloOwner, MSGID_button_untrigger, pbtn);
}

void InitButton(BUTTON *pbutton)
{
    InitSo(pbutton);
    InitBtn(&STRUCT_OFFSET(pbutton, 0x554, BTN)); // pbutton->btn
}

void LoadButtonFromBrx(BUTTON *pbutton, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(pbutton, pbis);
    LoadBtn(&STRUCT_OFFSET(pbutton, 0x554, BTN), pbutton); // pbutton->btn
}

INCLUDE_ASM("asm/nonmatchings/P2/button", InsertButtonPos__FP6BUTTONP3PNTP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/button", InsertButtonMat__FP6BUTTONP3XFMP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/button", PostButtonLoad__FP6BUTTON);

void CloneButton(BUTTON *pbutton, BUTTON *pbuttonBase)
{
    int ichkPushed = STRUCT_OFFSET(pbutton, 0x554, BTN).ichkPushed;
    CloneSo(pbutton, pbuttonBase);
    STRUCT_OFFSET(pbutton, 0x554, BTN).ichkPushed = ichkPushed;
    STRUCT_OFFSET(pbutton, 0x554, BTN).paloOwner = (ALO *)pbutton;
}

void SetButtonButtons(BUTTON *pbutton, BUTTONS buttons)
{
    SetBtnButtons(&STRUCT_OFFSET(pbutton, 0x554, BTN), buttons);
}

INCLUDE_ASM("asm/nonmatchings/P2/button", FCheckButtonObject__FP6BUTTONP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/button", IposFindButtonClosest__FP6BUTTONPf);

INCLUDE_ASM("asm/nonmatchings/P2/button", ImatFindButtonClosest__FP6BUTTONPf);

INCLUDE_ASM("asm/nonmatchings/P2/button", PresetButtonAccel__FP6BUTTONf);

INCLUDE_ASM("asm/nonmatchings/P2/button", UpdateButtonInternalXps__FP6BUTTON);

INCLUDE_ASM("asm/nonmatchings/P2/button", UpdateButton__FP6BUTTONf);

INCLUDE_ASM("asm/nonmatchings/P2/button", FAbsorbButtonWkr__FP6BUTTONP3WKR);

void InitVolbtn(VOLBTN *pvolbtn)
{
    InitSo(pvolbtn);
    InitBtn(&STRUCT_OFFSET(pvolbtn, 0x5c0, BTN)); // pvolbtn->btn
    STRUCT_OFFSET(pvolbtn, 0x538, ulong) |= 0x80000000000; // pvolbtn->bspcCamera.absp
    SetSoConstraints(pvolbtn, CT_Locked, NULL, CT_Locked, NULL);
}

void LoadVolbtnFromBrx(VOLBTN *pvolbtn, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(pvolbtn, pbis);
    LoadBtn(&STRUCT_OFFSET(pvolbtn, 0x5c0, BTN), pvolbtn); // pvolbtn->btn
    if (STRUCT_OFFSET(pvolbtn, 0x790, int) != 0) // pvolbtn->fSendChangeEvents
    {
       STRUCT_OFFSET(pvolbtn, 0x5c0, BTN).fManualReset = 1; // // pvolbtn->btn
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/button", PostVolbtnLoad__FP6VOLBTN);

void CloneVolbtn(VOLBTN *pvolbtn, VOLBTN *pvolbtnBase)
{
    int ichkPushed = STRUCT_OFFSET(pvolbtn, 0x5c0, BTN).ichkPushed; // pvolbtn->btn
    CloneSo(pvolbtn, pvolbtnBase);
    STRUCT_OFFSET(pvolbtn, 0x5c0, BTN).ichkPushed = ichkPushed; // pvolbtn->btn
    STRUCT_OFFSET(pvolbtn, 0x5c0, BTN).paloOwner = (ALO *)pvolbtn; // pvolbtn->btn
}

void SetVolbtnButtons(VOLBTN *pvolbtn, BUTTONS buttons)
{
    SetBtnButtons(&STRUCT_OFFSET(pvolbtn, 0x5c0, BTN), buttons); // pvolbtn->btn
}

INCLUDE_ASM("asm/nonmatchings/P2/button", UpdateVolbtn__FP6VOLBTNf);

INCLUDE_ASM("asm/nonmatchings/P2/button", FGetVolbtnPushObjectsWithinList__FP6VOLBTNPv);

void AddBtnAseg(BTN *pbtn, ALO *palo, OID oid)
{
    FAddAshOid(pbtn->aash, oid);
}

void AddButtonAseg(BUTTON *pbutton, OID oid)
{
    AddBtnAseg(&STRUCT_OFFSET(pbutton, 0x554, BTN), pbutton, oid); // pbutton->btn
}

void AddVolbtnAseg(VOLBTN *pvolbtn, OID oid)
{
    AddBtnAseg(&STRUCT_OFFSET(pvolbtn, 0x5c0, BTN), pvolbtn, oid); // pvolbtn->btn
}

void AddBtnOffAseg(BTN *pbtn, ALO *palo, OID oid)
{
    FAddAshOid(&pbtn->aash[1], oid);
}

void AddButtonOffAseg(BUTTON *pbutton, OID oid)
{
    AddBtnOffAseg(&STRUCT_OFFSET(pbutton, 0x554, BTN), pbutton, oid); // pbutton->btn
}

void AddVolbtnOffAseg(VOLBTN *pvolbtn, OID oid)
{
    AddBtnOffAseg(&STRUCT_OFFSET(pvolbtn, 0x5c0, BTN), pvolbtn, oid); // pvolbtn->btn
}

void AddButtonPushObject(BUTTON *pbutton, OID oid)
{
    int coidPush = STRUCT_OFFSET(pbutton, 0x720, int);        // pbutton->coidPush
    STRUCT_OFFSET_INDEX(pbutton, 0x724, OID, coidPush) = oid; // pbutton->aoidPush[coidPush]
    STRUCT_OFFSET(pbutton, 0x720, int) = coidPush + 1;        // pbutton->coidPush
}

void AddButtonNoPushObject(BUTTON *pbutton, OID oid)
{
    int coidNoPush = STRUCT_OFFSET(pbutton, 0x744, int);        // pbutton->coidNoPush
    STRUCT_OFFSET_INDEX(pbutton, 0x748, OID, coidNoPush) = oid; // pbutton->aoidNoPush[coidNoPush]
    STRUCT_OFFSET(pbutton, 0x744, int) = coidNoPush + 1;        // pbutton->coidNoPush
}

void AddButtonPushClass(BUTTON *pbutton, CID cid)
{
    int ccidPush = STRUCT_OFFSET(pbutton, 0x768, int);        // pbutton->ccidPush
    STRUCT_OFFSET_INDEX(pbutton, 0x76c, CID, ccidPush) = cid; // pbutton->acidPush[ccidPush]
    STRUCT_OFFSET(pbutton, 0x768, int) = ccidPush + 1;        // pbutton->ccidPush
}

void AddButtonNoPushClass(BUTTON *pbutton, CID cid)
{
    int ccidNoPush = STRUCT_OFFSET(pbutton, 0x78c, int);        // pbutton->ccidNoPush
    STRUCT_OFFSET_INDEX(pbutton, 0x790, CID, ccidNoPush) = cid; // pbutton->acidNoPush[ccidNoPush]
    STRUCT_OFFSET(pbutton, 0x78c, int) = ccidNoPush + 1;        // pbutton->ccidNoPush
}

void AddVolbtnPushObject(VOLBTN *pvolbtn, OID oid)
{
    int coidPush = STRUCT_OFFSET(pvolbtn, 0x550, int);        // pvolbtn->coidPush
    STRUCT_OFFSET_INDEX(pvolbtn, 0x554, OID, coidPush) = oid; // pvolbtn->aoidPush[coidPush]
    STRUCT_OFFSET(pvolbtn, 0x550, int) = coidPush + 1;        // pvolbtn->coidPush
}

void SetButtonRsmg(BUTTON *pbutton, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal)
{
    SetBtnRsmg(&STRUCT_OFFSET(pbutton, 0x554, BTN), fOnTrigger, oidRoot, oidSM, oidGoal); // pbutton->btn
}

void SetVolbtnRsmg(VOLBTN *pvolbtn, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal)
{
    SetBtnRsmg(&STRUCT_OFFSET(pvolbtn, 0x5c0, BTN), fOnTrigger, oidRoot, oidSM, oidGoal); // pvolbtn->btn
}

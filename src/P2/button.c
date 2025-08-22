#include <button.h>
#include <chkpnt.h>

INCLUDE_ASM(const s32, "P2/button", PostAshLoad__FP2SWP3ASHP3ALO);

INCLUDE_ASM(const s32, "P2/button", FFoundAshAseg__FP3ASHP4ASEG);

INCLUDE_ASM(const s32, "P2/button", FAddAshAseg__FP3ASHP4ASEG);

INCLUDE_ASM(const s32, "P2/button", FAddAshOid__FP3ASH3OID);

void InitBtn(BTN *pbtn)
{
    STRUCT_OFFSET(pbtn, 0x120, int) = IchkAllocChkmgr(&g_chkmgr);
    STRUCT_OFFSET(pbtn, 0x140, OID) = OID_Nil;
}

INCLUDE_ASM(const s32, "P2/button", LoadBtn__FP3BTNP3ALO);

INCLUDE_ASM(const s32, "P2/button", PostBtnLoad__FP3BTN);

INCLUDE_ASM(const s32, "P2/button", RestoreBtnFromCheckpointCallback__FP3BTN5MSGIDPv);

INCLUDE_ASM(const s32, "P2/button", SetBtnRsmg__FP3BTNi3OIDN22);

INCLUDE_ASM(const s32, "P2/button", SetBtnButtons__FP3BTN7BUTTONS);

INCLUDE_ASM(const s32, "P2/button", FAddRsmg__FP4RSMGiPii3OIDN24);

INCLUDE_ASM(const s32, "P2/button", TriggerRsmg__FP2SWiP4RSMGP2LOi);

INCLUDE_ASM(const s32, "P2/button", RunBtnAsegs__FP3BTN4IASHi);

INCLUDE_ASM(const s32, "P2/button", TriggerBtn__FP3BTNii);

INCLUDE_ASM(const s32, "P2/button", UntriggerBtn__FP3BTNi);

INCLUDE_ASM(const s32, "P2/button", InitButton__FP6BUTTON);

INCLUDE_ASM(const s32, "P2/button", LoadButtonFromBrx__FP6BUTTONP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/button", InsertButtonPos__FP6BUTTONP3PNTP6VECTOR);

INCLUDE_ASM(const s32, "P2/button", InsertButtonMat__FP6BUTTONP3XFMP7MATRIX3);

INCLUDE_ASM(const s32, "P2/button", PostButtonLoad__FP6BUTTON);

INCLUDE_ASM(const s32, "P2/button", CloneButton__FP6BUTTONT0);

INCLUDE_ASM(const s32, "P2/button", SetButtonButtons__FP6BUTTON7BUTTONS);

INCLUDE_ASM(const s32, "P2/button", FCheckButtonObject__FP6BUTTONP2SO);

INCLUDE_ASM(const s32, "P2/button", IposFindButtonClosest__FP6BUTTONPf);

INCLUDE_ASM(const s32, "P2/button", ImatFindButtonClosest__FP6BUTTONPf);

INCLUDE_ASM(const s32, "P2/button", PresetButtonAccel__FP6BUTTONf);

INCLUDE_ASM(const s32, "P2/button", UpdateButtonInternalXps__FP6BUTTON);

INCLUDE_ASM(const s32, "P2/button", UpdateButton__FP6BUTTONf);

INCLUDE_ASM(const s32, "P2/button", FAbsorbButtonWkr__FP6BUTTONP3WKR);

INCLUDE_ASM(const s32, "P2/button", InitVolbtn__FP6VOLBTN);

INCLUDE_ASM(const s32, "P2/button", LoadVolbtnFromBrx__FP6VOLBTNP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/button", PostVolbtnLoad__FP6VOLBTN);

INCLUDE_ASM(const s32, "P2/button", CloneVolbtn__FP6VOLBTNT0);

INCLUDE_ASM(const s32, "P2/button", SetVolbtnButtons__FP6VOLBTN7BUTTONS);

INCLUDE_ASM(const s32, "P2/button", UpdateVolbtn__FP6VOLBTNf);

INCLUDE_ASM(const s32, "P2/button", FGetVolbtnPushObjectsWithinList__FP6VOLBTNPv);

INCLUDE_ASM(const s32, "P2/button", AddBtnAseg__FP3BTNP3ALO3OID);

INCLUDE_ASM(const s32, "P2/button", AddButtonAseg__FP6BUTTON3OID);

INCLUDE_ASM(const s32, "P2/button", AddVolbtnAseg__FP6VOLBTN3OID);

INCLUDE_ASM(const s32, "P2/button", AddBtnOffAseg__FP3BTNP3ALO3OID);

INCLUDE_ASM(const s32, "P2/button", AddButtonOffAseg__FP6BUTTON3OID);

INCLUDE_ASM(const s32, "P2/button", AddVolbtnOffAseg__FP6VOLBTN3OID);

INCLUDE_ASM(const s32, "P2/button", AddButtonPushObject__FP6BUTTON3OID);

INCLUDE_ASM(const s32, "P2/button", AddButtonNoPushObject__FP6BUTTON3OID);

INCLUDE_ASM(const s32, "P2/button", AddButtonPushClass__FP6BUTTON3CID);

INCLUDE_ASM(const s32, "P2/button", AddButtonNoPushClass__FP6BUTTON3CID);

INCLUDE_ASM(const s32, "P2/button", AddVolbtnPushObject__FP6VOLBTN3OID);

INCLUDE_ASM(const s32, "P2/button", SetButtonRsmg__FP6BUTTONi3OIDN22);

INCLUDE_ASM(const s32, "P2/button", SetVolbtnRsmg__FP6VOLBTNi3OIDN22);

INCLUDE_ASM(const s32, "P2/button", FUN_00140790__Fv);

INCLUDE_ASM(const s32, "P2/button", FUN_001407A0);

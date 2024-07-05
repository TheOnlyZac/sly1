#include <screen.h>

INCLUDE_ASM(const s32, "P2/screen", StartupScreen__Fv);

INCLUDE_ASM(const s32, "P2/screen", PostBlotsLoad__Fv);

INCLUDE_ASM(const s32, "P2/screen", UpdateBlots__Fv);

INCLUDE_ASM(const s32, "P2/screen", ForceHideBlots__Fv);

INCLUDE_ASM(const s32, "P2/screen", ResetBlots__Fv);

INCLUDE_ASM(const s32, "P2/screen", RenderBlots__Fv);

INCLUDE_ASM(const s32, "P2/screen", DrawBlots__Fv);

INCLUDE_ASM(const s32, "P2/screen", InitBlot__FP4BLOT5BLOTK);

INCLUDE_ASM(const s32, "P2/screen", PostBlotLoad__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", UpdateBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", SetBlotAchzDraw__FP4BLOTPc);

INCLUDE_ASM(const s32, "P2/screen", SetBlotRgba__FP4BLOTUi);

INCLUDE_ASM(const s32, "P2/screen", SetBlotFontScale__FP4BLOTf);

INCLUDE_ASM(const s32, "P2/screen", DrawBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", func_001AA890);

INCLUDE_ASM(const s32, "P2/screen", DtAppearBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", DtVisibleBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", DtDisappearBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", SetBlotDtAppear__FP4BLOTf);

INCLUDE_ASM(const s32, "P2/screen", SetBlotDtVisible__FP4BLOTf);

INCLUDE_ASM(const s32, "P2/screen", SetBlotDtDisappear__FP4BLOTf);

INCLUDE_ASM(const s32, "P2/screen", OnBlotReset__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", ShowBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", HideBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", SetBlotBlots__FP4BLOT5BLOTS);

INCLUDE_ASM(const s32, "P2/screen", FIncludeBlotForPeg__FP4BLOTT0);

INCLUDE_ASM(const s32, "P2/screen", ResizeBlot__FP4BLOTff);

INCLUDE_ASM(const s32, "P2/screen", RepositionBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", RepositionBlotDependents__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", SetBlotClock__FP4BLOTPf);

INCLUDE_ASM(const s32, "P2/screen", PostCtrLoad__FP3CTR);

INCLUDE_ASM(const s32, "P2/screen", UpdateCtr__FP3CTR);

INCLUDE_ASM(const s32, "P2/screen", DrawCtr__FP3CTR);

INCLUDE_ASM(const s32, "P2/screen", RebuildCtrAchzDraw__FP3CTR);

INCLUDE_ASM(const s32, "P2/screen", DtVisibleCtr__FP3CTR);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ab600);

INCLUDE_ASM(const s32, "P2/screen", UpdateTimer__FP5TIMER);

INCLUDE_ASM(const s32, "P2/screen", DrawTimer__FP5TIMER);

INCLUDE_ASM(const s32, "P2/screen", SetTimer__FP5TIMERf);

INCLUDE_ASM(const s32, "P2/screen", SetTimerSpeed__FP5TIMERf);

INCLUDE_ASM(const s32, "P2/screen", SetTimerExpire__FP5TIMERfPFP5TIMER9TIMERNOTK_v);

INCLUDE_ASM(const s32, "P2/screen", StartTimer__FP5TIMER);

INCLUDE_ASM(const s32, "P2/screen", StopTimer__FP5TIMER);

INCLUDE_ASM(const s32, "P2/screen", RebuildTimerAchzDraw__FP5TIMERf);

INCLUDE_ASM(const s32, "P2/screen", SetTimerTimers__FP5TIMER6TIMERS);

INCLUDE_ASM(const s32, "P2/screen", DtVisibleTrunkctr__FP8TRUNKCTR);

INCLUDE_ASM(const s32, "P2/screen", DtVisibleCrusherctr__FP10CRUSHERCTR);

INCLUDE_ASM(const s32, "P2/screen", func_001ABE60);

INCLUDE_ASM(const s32, "P2/screen", FUN_001abe70);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac060);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac0e8);

INCLUDE_ASM(const s32, "P2/screen", PostNoteLoad__FP4NOTE);

INCLUDE_ASM(const s32, "P2/screen", SetNoteAchzDraw__FP4NOTEPc);

INCLUDE_ASM(const s32, "P2/screen", DrawNote__FP4NOTE);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac888);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac910);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac990);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac9e0);

INCLUDE_ASM(const s32, "P2/screen", FUN_001aca30);

INCLUDE_ASM(const s32, "P2/screen", FUN_001aca68);

INCLUDE_ASM(const s32, "P2/screen", DrawTitle__FP5TITLE);

INCLUDE_ASM(const s32, "P2/screen", PostTotalsLoad__FP6TOTALS);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ace38);

INCLUDE_ASM(const s32, "P2/screen", FUN_001acee0);

INCLUDE_ASM(const s32, "P2/screen", render_level_info_from_id);

INCLUDE_ASM(const s32, "P2/screen", render_level_info);

INCLUDE_ASM(const s32, "P2/screen", render_hideout_world_info);

INCLUDE_ASM(const s32, "P2/screen", SetTotalsBlots__FP6TOTALS5BLOTS);

INCLUDE_ASM(const s32, "P2/screen", ShowTotalsQMARK);

INCLUDE_ASM(const s32, "P2/screen", HideTotalsQMARK);

INCLUDE_ASM(const s32, "P2/screen", DrawTotals__FP6TOTALS);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ad6a8);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ad718);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ad7b0);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ad940);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ad970);

INCLUDE_ASM(const s32, "P2/screen", DrawLetterbox__FP9LETTERBOX);

INCLUDE_ASM(const s32, "P2/screen", FUN_001adc60);

INCLUDE_ASM(const s32, "P2/screen", DrawLogo__FP4LOGO);

INCLUDE_ASM(const s32, "P2/screen", FUN_001adf28);

INCLUDE_ASM(const s32, "P2/screen", FUN_001adff0);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ae130);

INCLUDE_ASM(const s32, "P2/screen", UpdateAttract__FP7ATTRACT);

INCLUDE_ASM(const s32, "P2/screen", func_001AE220);

INCLUDE_ASM(const s32, "P2/screen", DrawLineScreen__FUiUiUiUiUiUiG4RGBAi);

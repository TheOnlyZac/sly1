#include <dart.h>
#include <emitter.h>

extern SNIP s_asnipDart[];

void InitDart(DART *pdart)
{
    InitSo(pdart);
    SetDartDarts(pdart, DARTS_Nil);
}

INCLUDE_ASM("asm/nonmatchings/P2/dart", OnDartAdd__FP4DART);

void RemoveDart(DART *pdart)
{
    RemoveLo(pdart);
    AppendDlEntry(&pdart->psw->dlDartFree, pdart);
    SetDartDarts(pdart, DARTS_AvailToFire);
}

void CloneDart(DART *pdart, DART *pdartBase)
{
    DLE dleDartFree = STRUCT_OFFSET(pdart, 0x56c, DLE); // pdart->dleDartFree
    CloneSo(pdart, pdartBase);
    STRUCT_OFFSET(pdart, 0x56c, DLE) = dleDartFree; // pdart->dleDartFree
}

void LoadDartFromBrx(DART *pdart, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(pdart, pbis);
    InferExpl(&STRUCT_OFFSET(pdart, 0x58c, EXPL *), pdart); // pdart->pexpl
}

void HandleDartMessage(DART *pdart, MSGID msgid, void *pv)
{
    HandleAloMessage(pdart, msgid, pv);
    // pdart->pasegaSticking
    if (msgid == MSGID_asega_retracted && (ASEGA *)pv == STRUCT_OFFSET(pdart, 0x578, ASEGA *))
    {
        STRUCT_OFFSET(pdart, 0x578, ASEGA *) = (ASEGA *)nullptr;
        SetDartDarts(pdart, DARTS_Stuck);
    }
}

void PostDartLoad(DART *pdart)
{
    PostAloLoad(pdart);
    SnipAloObjects(pdart, 1, s_asnipDart);
}

INCLUDE_ASM("asm/nonmatchings/P2/dart", UpdateDart__FP4DARTf);

INCLUDE_ASM("asm/nonmatchings/P2/dart", SetDartDarts__FP4DART5DARTS);

INCLUDE_ASM("asm/nonmatchings/P2/dart", ApplyDartThrow__FP4DARTP2PO);

INCLUDE_ASM("asm/nonmatchings/P2/dart", UpdateDartAirborne__FP4DARTf);

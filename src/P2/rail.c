#include <rail.h>
#include <find.h>
#include <sw.h>

extern float D_0024C8C4;

void InitRail(RAIL *prail)
{
    InitLo(prail);
    prail->unk1 = D_0024C8C4;
    prail->oid = OID_Nil;
}

void OnRailAdd(RAIL *prail)
{
    OnLoAdd(prail);
    AppendDlEntry(&prail->psw->dlRail, prail);
}

void OnRailRemove(RAIL *prail)
{
    OnLoRemove(prail);
    RemoveDlEntry(&prail->psw->dlRail, prail);
}

void PostLoadRail(RAIL *prail)
{
    PostLoLoad(prail);
    if (prail->oid != OID_Nil)
    {
        // TODO: Check if the field at 0x58 is LO or something that inherits from it.
        prail->plo = PloFindSwObject(prail->psw, 4, prail->oid, prail);
    }
}

void CloneRail(RAIL *prail, RAIL *prailBase)
{
    DLE dleRail = prail->dleRail;
    CloneLo(prail, prailBase);
    prail->dleRail = dleRail;
}

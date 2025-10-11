#include <landing.h>
#include <sw.h>

void OnLandingAdd(LANDING *planding)
{
    OnLoAdd(planding);
    AppendDlEntry(&planding->psw->dlLanding, planding);
}

void OnLandingRemove(LANDING *planding)
{
    OnLoRemove(planding);
    RemoveDlEntry(&planding->psw->dlLanding, planding);
}

void CloneLanding(LANDING *planding, LANDING *plandingBase)
{
    DLE dleLanding = planding->dleLanding;
    CloneLo(planding, plandingBase);
    planding->dleLanding = dleLanding;
}

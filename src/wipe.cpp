#include <wipe.h>

// First parameter is ptr to enc level file info second paramter unk third is warp type
void WipeToWorldWarp(LevelLoadData* pchzWorld, OID oidWarp, WIPEK wipek)
{
	trans.fSet = 1;
	trans.grftrans = 0;
	trans.pchzWorld = pchzWorld;
	trans.oidWarp = (int)oidWarp;
	ActivateWipe(&g_pwipe, &trans, wipek);
	return;
}

void ActivateWipe(WIPE* pwipe, TRANS* ptrans, WIPEK wipek)
{

}
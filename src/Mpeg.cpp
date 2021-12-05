#include <CMpeg.h>

void CMpeg::Execute(CutsceneManager* cutscene_manager)
{
    OID* cutscene;
    OID* second_cutscene;

    /* Store values from cutscene mgr */
    second_cutscene = cutscene_manager->second_cutscene;
    cutscene = cutscene_manager->name;
    /* Reset cutscene mgr values to Null */
    cutscene_manager->name = (OID*)0x0;
    cutscene_manager->second_cutscene = (OID*)0x0;
    play_cutscene ? (cutscene_manager, cutscene);
    /* If a second cutscene is speficied, play it immediately
       after the first one */
    if (second_cutscene != (OID*)0x0) {
        play_cutscene ? (cutscene_manager, second_cutscene);
    }
    return;
}
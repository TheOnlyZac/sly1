#include <MPeg.h>

void CMpeg::Execute()
{
    OID* cutscene;
    OID* second_cutscene;

    /* Store values from cutscene mgr */
    second_cutscene = this->second_cutscene;
    cutscene = this->name;
    /* Reset cutscene mgr values to Null */
    this->name = (OID*)0x0;
    this->second_cutscene = (OID*)0x0;
    /* todo: define function
    play_cutscene(this, cutscene); */
    /* If a second cutscene is speficied, play it immediately
       after the first one */
    if (second_cutscene != (OID*)0x0) {
        /* todo: define function
        play_cutscene(this, second_cutscene); */
    }
    return;
}

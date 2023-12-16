/**
 * @file mpeg.cpp
 *
 * @brief Implements MPEG video and audio playback.
*/
#include <mpeg.h>
#include <bis.h>
#include <phasemem.h>
#include <clock.h>
#include <joy.h>
#include <wipe.h>
#include <cd.h>
#include <sound.h>

void CMpeg::ExecuteOids()
{
    OID oid1 = this->oid_1;
    OID oid2 = this->oid_2;

    this->oid_1 = OID_Unknown;
    this->oid_2 = OID_Unknown;

    Execute(&oid1); // execute 1st mpeg
    if (oid2 != OID_Unknown)
    {
        Execute(&oid2); // execute 2nd mpeg
    }
}

void CMpeg::Execute(OID* oid)
{
    char* pchzKey;
    int fmpegIsEnd;
    FGS fgs;
    bool foidValid;

    // Update the phase and set the cutscene pchz

    SetPhase(PHASE_Mpeg);

    /* todo: define function
    pchzKey = (char*)get_cutscene_pchz_from_oid(oid);
    this->m_pchzPss = pchzKey; */

    // Setup binary async stream and file location
    CBinaryAsyncStream bas(&g_phasemem);
    CFileLocation fileLocation;
    fileLocation.Clear();

    if (oid == NULL)
    {
        foidValid = false;
    }
    else
    {
        fileLocation.m_fcl.cb = (int)oid[1] ^ (int)oid[7];
        fileLocation.m_fcl.isector = *(int*)*oid ^ (int)oid[5];
        foidValid = fileLocation.m_fcl.cb != 0;
    }
    if ((foidValid) /*todo &&
        (fmpegIsEnd = FUN_0012fd78(&bas, &fileLocation), fmpegIsEnd != 0) */)
    {
        // Start the mpeg, then loop until it ends
        Start();
        while (fmpegIsEnd = sceMpegIsEnd(&this->m_scempeg), fmpegIsEnd == 0)
        {
            MarkClockTickRealOnly(&g_clock);
            UpdateJoy(&g_joy);

            /* todo: define global variables
            if (oid == &g_oid_unknown ? ) {
                foidValid = true;
            }
            else {
                foidValid = false;
                if (oid != NULL) {
                    foidVvalid = (oid[2] ^ oid[6]) == (OID_00248498 ^ OID_002484a8);
                }
            } */

            if (this->m_pchzPss < (char*)0x10) {
                fgs = static_cast<FGS>(1 << ((intptr_t)this->m_pchzPss & 0x1f));
            }
            else {
                fgs = static_cast<FGS>(0);
            }

            if ((g_pgsCur->fgs & fgs) != 0 /* || foidValid && DAT_00269b4c != 0 */) {
                fmpegIsEnd = FCatchWipeButtonTrans(g_pwipe, &g_joy, WIPES_Black);
                if (fmpegIsEnd != 0) break;

                // Allow the cutscene to be skipped by pressing certain joy buttons
                if ((g_joy.grfbtnPressed &
                    (PAD_L2 | PAD_R2 | PAD_L1 | PAD_R1 | PAD_TRIANGLE | PAD_SELECT | PAD_START)) !=
                    _NOT_PRESSED) {
                    SetJoyBtnHandled(&g_joy, PAD_L2 | PAD_R2 | PAD_L1 | PAD_R1 | PAD_TRIANGLE |
                        PAD_SELECT | PAD_START);
                    break;
                }
            }

            UpdateCd();
            if (g_cds != CDS_Ready) break;
            Update(); // update the mpeg
        }

        foidValid = true;
        /* todo: define globals
        if ((oid != &g_oid_unknown ? ) && (foidValid = false, oid != NULL)) {
            foidValid = (oid[2] ^ oid[6]) == (OID_00248498 ^ OID_002484a8);
        }
        if (foidValid) {
            DAT_00269b4c = 1;
        } */

        // Finish the mpeg and close the binary async stream
        Finish();
        bas.Close();
    }
    else {
        // Play thud sound if an invalid or null cutscene attempted to play
        StartSound(SFXID_Nil, NULL, NULL, NULL, 3000, 300, 1, 0, 0, NULL, NULL); //todo sfxid for thud sound
    }

    // Clear the game phase (bas is destroyed automatically)
    ClearPhase(PHASE_Mpeg);
}

void CMpeg::Start()
{

}

void CMpeg::Update()
{

}

void CMpeg::Finish()
{

}

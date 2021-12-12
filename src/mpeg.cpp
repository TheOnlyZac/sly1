#include <cat.h>
#include <clock.h>
#include <gs.h>
#include <joy.h>
#include <mpeg.h>

unsigned int g_phasemem{}; // todo: what data type is this

/* Executes the mpegs stored as OIDs on the mpeg struct. (name is made-up) */
void CMpeg::ExecuteOids()
{
    OID oid1 = this->oid_1;
    OID oid2 = this->oid_2;

    this->oid_1 = OID::Unknown;
    this->oid_2 = OID::Unknown;

    Execute(&oid1); // execute 1st mpeg
    if (oid2 != OID::Unknown)
    {
        Execute(&oid2); // execute 2nd mpeg
    }
}

/* Execute (play) the mpeg with the given oid. */
void CMpeg::Execute(OID* oid)
{
    char* pchzKey;
    int fmpegIsEnd;
    FGS fgs;
    CFileLocation fileLocation;
    bool foidValid;

    // Update the global game phase and get the pchz key for the cutscene

    /* todo: define function and PHASE enum
    SetPhase(PHASE::Mpeg); */

    /* todo: define function
    pchzKey = (char*)get_cutscene_pchz_from_oid(oid);
    this->m_pchzPss = pchzKey; */

    // Setup binary async stream and file location
    CBinaryAsyncStream bas(&g_phasemem);
    fileLocation.Clear();

    if (oid == NULL)
    {
        foidValid = false;
    }
    else
    {
        fileLocation.size = (int)oid[1] ^ (int)oid[7];
        fileLocation.sector_offset = *(int*)*oid ^ (int)oid[5];
        foidValid = fileLocation.size != 0;
    }
    if ((foidValid) /*todo &&
        (fmpegIsEnd = FUN_0012fd78(&bas, &fileLocation), fmpegIsEnd != 0) */)
    {
        // Start the mpeg, and begin the while loop that repeats until it's done
        Start();
        while (/*todo fmpegIsEnd = sceMpegIsEnd(&this->m_scempeg), */ fmpegIsEnd == 0)
        {
            // Update clock and handle joy inputs during mpeg
            MarkClockTickRealOnly(&g_clock);
            /* todo: define joy.c function
            UpdateJoy(&g_joy); */

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
                fgs = static_cast<FGS>(1 << ((unsigned int )this->m_pchzPss & 0x1f));
            }
            else {
                fgs = static_cast<FGS>(0);
            }

            /* todo: define global vars, functions, and PadButtons enum
            if ((g_pgsCur->fgs & fgs) != 0 || foidValid && DAT_00269b4c != 0) {
                fmpegIsEnd = FCatchWipeButtonTrans((WIPE*)&g_pwipe, &g_joy, WIPES_Black);
                if (fmpegIsEnd != 0) break;
                // Allow the cutscene to be skipped by pressing certain joy buttons
                if ((g_joy.grfbtnPressed &
                    (PAD_L2 | PAD_R2 | PAD_L1 | PAD_R1 | PAD_TRIANGLE | PAD_SELECT | PAD_START)) !=
                    _NOT_PRESSED) {
                    SetJoyBtnHandled(&g_joy, PAD_L2 | PAD_R2 | PAD_L1 | PAD_R1 | PAD_TRIANGLE |
                        PAD_SELECT | PAD_START);
                    break;
                }
            } */

            /* todo: define functions and global variables
            UpdateCd();
            if (g_cds != CDS::Ready) break; */
            Update();
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
        /* todo: define StartSound function and SFXID enum
        StartSound(SFXID::thud7, NULL, NULL, NULL, 3000.0, 300.0, 1.0, 0.0, 0.0, NULL, NULL); */
    }

    // Clear the game phase (bas is destroyed automatically)
    /* todo: define function
    ClearPhase(PHASE::Mpeg); */
}

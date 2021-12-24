#include <transition.h>
#include <clock.h>

void CTransition::Set(char* pchzWorld, OID oidWarp, OID oidWarpContext, GRFTRANS grftrans)
{
	if (this->m_fPending == 0) {
		this->grftrans = grftrans;
		this->m_fPending = 1;
		this->m_pchzWorld = pchzWorld;
		this->m_oidWarp = oidWarp;
		this->m_oidWarpContext = oidWarpContext;
	}
	return;
}


void CTransition::Execute()
{
	LevelTableStruct* lld;
	LevelTableStruct* search_data;
	LevelTableStruct* ciphers;
	CFileLocation fileLocation;
	lsn_and_unk_ciphers_t* lsn_enc_size_enc;
	/* todo: define function
	SetPhase(2); */
	if ((lld->lsn_and_size_ciphers).size_enc != 0)
	{
		fileLocation.Clear();
		//Loading the encrypted seor offsets and sizes in variables to be decrypted
		uint32_t *enc_file_table = NULL;
		uint32_t off = lld->lsn_and_size_ciphers.size_enc;
		enc_file_table = (uint32_t*)off;
		uint32_t enc_bytes0 = *enc_file_table;
		enc_file_table = enc_file_table + 4;
		uint32_t enc_bytes1 = *enc_file_table;
		enc_file_table = enc_file_table + 4;
		uint32_t enc_bytes2 = *enc_file_table;
		enc_file_table = enc_file_table + 4;
		uint32_t enc_bytes3 = *enc_file_table;
		enc_file_table = enc_file_table + 4;
		uint32_t enc_bytes4 = *enc_file_table;
		enc_file_table = enc_file_table + 4;
		uint32_t enc_bytes5 = *enc_file_table;
		enc_file_table = enc_file_table + 4;
		uint32_t enc_bytes6 = *enc_file_table;
		enc_file_table = enc_file_table + 4;
		uint32_t enc_bytes7 = *enc_file_table;
		lld->lsn_and_size_ciphers.size_enc = 0;
		uint32_t size = enc_bytes1 ^ enc_bytes7;
		fileLocation = *(CFileLocation*)(enc_bytes0 ^ enc_bytes5);

		if (size != 0)
		{
			search_data = (LevelTableStruct*)lld->for_lsn;
			bool unk_0 = 1;
			if (ciphers != search_data && search_data != 0)
			{
				uint32_t unk_1 = enc_bytes6 ^ enc_bytes2;
				uint32_t unk_2 = lld->for_size ^ lld->lsn_and_size_ciphers.lsn_enc;
			}
			uint32_t *unk_ptr0 = NULL;
			uint32_t *unk_ptr1 = NULL;
			uint32_t *unk_ptr2 = NULL;
			uint32_t unk_2 = 0x03F3F3F;
			uint32_t unk_3 = 0x340C00;
			uint32_t unk_4 = 0x2C3B00;
			unk_ptr0 = (uint32_t*)unk_2;
			unk_ptr1 = (uint32_t*)unk_3;
			unk_ptr2 = (uint32_t*)unk_4;
			//gcc2_compiled(&ciphers->level_id, 0x3F3F, 0x3F, 0x3F00, unk_2);
			//gcc2_compiled(bs, &unk_ptr1, &unk_ptr2, 6);
			
			if (ciphers->level_id != 0)
			{
				//CProg::Begin(ciphers->level_id);
			}

			int always_1 = 0;
			//always_1 = init_packed_data_stuff(bs, &fileLocation)

			if (always_1 == 0)
			{
				//Func_1372E0(CBinaryInputStream *bs, 2);
			}
			else
			{
				//reset_engine_values((EntityList*)g_psw);
				//Func_1db928();
				ResetClock(&g_clock, 0.0);
				//AddGrfusr(0x80);
				//load_level(search_data, )
				//g_psw = PloNew(0x6C, 0x0, 0x0, OID_WORLD, -1);
				//SetMvgkRvol(0.0, 10, 0);
				//PostGlobalsetLoad(bs, ciphers)
				if (ciphers->level_id != 0)
				{
					//CProg::End(ciphers->level_id);
				}

			}    
				//if (g_pgsCur->grfgs != 0 && unk_idk_maybe_savedata != 0 && unk_idk_maybe_savedata + 0x19d8 != g_pgsCur->gameworldCur || unk_idk_maybe_savedata +0x19dc != g_pgsCur->worldlevelCur)
				//{
					//save_related(&g_astruct_4);
				//}

			//FUN_001372e0(bs, 2);
		}

		//ResetCM(g_pcm, 1)
		//UpdateSounds();
		//SetMvgkRvol(1.0,10,0);
		//TeleportSwPlayer(g_psw, lld->search_val, lld ->field_0xc);
		OnDifficultyInitialTeleport(&g_difficulty);
		uint32_t* unk_ptr3 = NULL;
		uint32_t* unk_ptr4 = NULL;
		uint32_t unk_5 = 0x02623d8;
		uint32_t unk_6 = 0x026fa90;
		unk_ptr3 = (uint32_t*)unk_5;
		unk_ptr4 = (uint32_t*)unk_6;
		//FUN_00160ce8(unk_ptr3);
		//FUN_0016b520(unk_ptr4);
		//RecalcSwXpAll(g_psw, 0);
		//UpdateCmLast(g_pcm, 0, g_clock.ui_animation_timer);
		//if (lld->field_0x10 & 0x10 != 0) 
		//{
			//lives_blot.field_0x0 + 0x38;
		//}
		SetClockRate(1.0);
	}

	//FUN_001c06d8();
	//SetMvgkRvol(&g_psw->field_0x1d61, 1, 1);
	//ClearPhase();
	//(lld->lsn_and_size_ciphers).lsn_enc = 0;
	return;
}


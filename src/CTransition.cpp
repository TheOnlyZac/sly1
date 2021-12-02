#include <CTransition.h>


void CTransition::Set(CTransition0* ct, OID* load_data, int param_2, int load_mod, int load_flags)
{
    if (ct->field_0x0 == 0)
    {
        ct->field_0x10 = load_flags;
        ct->field_0x0 = 1;
        ct->level_file_info = (char*)load_data;
        ct->field_0x8 = param_2;
        ct->field_0xc = load_mod;
    }
}
void CTransition::Execute(LevelLoadManager* level_mgr)
{
	LevelLoadData* search_data;
	LevelLoadData* ciphers;
	lsn_and_unk_t* lsn_and_size;
	lsn_and_unk_ciphers_t* lsn_enc_size_enc;
	bool unk_0;
	//SetPhase(2);
	if ((search_data->lsn_and_size_ciphers).size_enc != 0)
	{
		//CFileLocation::Clear(&lsn_and_size);
		//Loading the encrypted sector offsets and sizes in variables to be decrypted
		uint32_t *enc_file_table = NULL;
		uint32_t off = search_data->lsn_and_size_ciphers.size_enc;
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
		search_data->lsn_and_size_ciphers.size_enc = 0;
		uint32_t size = enc_bytes1 ^ enc_bytes7;
		lsn_and_size = (lsn_and_unk_t*)(enc_bytes0 ^ enc_bytes5);
		if (size != 0)
		{
			unk_0 = 1;
			
		}
	}
}
#include <iostream>
#include <CFileLocation.h>
typedef unsigned char    byte;
typedef struct LevelLoadManager LevelLoadManager, * PLevelLoadManager;
typedef struct LevelLoadData LevelLoadData, * PLevelLoadData;
typedef struct lsn_and_unk_ciphers_t lsn_and_unk_ciphers_t, * Plsn_and_unk_ciphers_t;
typedef struct CTransition CTransition, * PCTransition;
typedef struct lsn_and_unk_t lsn_and_unk_t, * Plsn_and_unk_t;

class CTransition
{
	public:

        typedef enum OID 
        {
            OID__WORLD = 3,
            OID_bentley = 6,
            OID__CAMERA = 4,
            OID_murray = 7,
            OID__MERGED_STATICS = 1,
            OID_rat = 617,
            OID_Unknown = 0,
            OID_jt = 5,
            OID__VISIBILITY_MAP = 2
        } OID;

        struct CTransition0
        { /* PlaceHolder Class Structure */
            uint32_t field_0x0;
            char* level_file_info;
            int field_0x8;
            int field_0xc;
            uint32_t field_0x10;
        };

        typedef enum FLS 
        { /* Level State Flags */
            FLS_BossDefeated = 16,
            FLS_Tertiary = 8,
            FLS_Visited = 1,
            FLS_KeyCollected = 2,
            FLS_Secondary = 4
        } FLS;

        struct lsn_and_unk_ciphers_t
        {
            uint32_t lsn_enc;
            uint32_t size_enc;
        };

        struct LevelLoadData 
        {
            struct lsn_and_unk_ciphers_t lsn_and_size_ciphers; /* Ciphers for lsn and size */
            uint32_t search_val;
            uint32_t field_0xc;
            uint32_t field_0x10;
            uint32_t for_lsn;
            uint32_t search_cipher; /* Cipher for search val */
            uint32_t for_size;
            uint32_t level_id; /* Level ID */
            void* level_name; /* Pointer to name string */
            enum FLS tasks; /* Tasks to complete (visited, key, vault, mts) */
        };

        struct LevelLoadManager 
        {
            uint32_t should_load_level;
            struct LevelLoadData* load_data;
            uint32_t load_flags;
            uint32_t load_mod_flags;
            struct LevelLoadData level;
        };

        struct lsn_and_unk_t
        {
            uint32_t lsn;
            uint32_t size;
        };
        void Set(CTransition0* ct, OID* load_data, int param_2, int load_mod, int load_flags);
		void Execute(LevelLoadManager* level_mgr);
};
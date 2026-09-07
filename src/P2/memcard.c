#include <memcard.h>
#include <thread.h>
#include <sdk/ee/libmc.h>
#include <sdk/ee/eekernel.h>
#include <sce/memset.h>

extern SAVE g_save;
extern MEMCARD g_memcard;

extern void *DAT_002bea10;

void StartupMemcard()
{
	sceMcInit();
	InitMemcard(&g_memcard);
	InitSave(&g_save, 0, 0);
}

void InitMemcard(MEMCARD *pmemcard)
{
	pmemcard->semaId = SemaCreate(1, 1);
	pmemcard->threadId = -1;
	pmemcard->field_0x10 = 0x22;
}

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018b600__Fv);

/**
 * @todo 82.93% match. Setting struct fields in wrong order?
 */
INCLUDE_ASM("asm/nonmatchings/P2/memcard", CreateMemcardThread__FP7MEMCARDii);
#ifdef SKIP_ASM
void CreateMemcardThread(MEMCARD *pmemcard, int unk1, int unk2)
{
	SetMemcardThreadHighPrio(pmemcard);
	pmemcard->field_0x08 = unk1;
	pmemcard->field_0x0c = unk2;
	pmemcard->field_0x10 = 0x20;
	
	ThreadParam threadParam;
	memset(&threadParam, 0, sizeof(ThreadParam));
	threadParam.entry = FUN_0018b600;
	threadParam.gpReg = &_gpReg;
	threadParam.stack = DAT_002bea10;
	threadParam.stackSize = 0x4000;
	threadParam.initPriority = 3;
	
	g_athread.sema = CreateThread(&threadParam);
	pmemcard->threadId = g_athread.sema;
	StartThread(pmemcard->threadId, *(int *)pmemcard);
}
#endif // SKIP_ASM

void SetMemcardThreadHighPrio(MEMCARD *pmemcard)
{
	if (FMemcardThreadValid(&g_memcard))
	{
		ChangeThreadPriority(pmemcard->threadId, 1);
	}
	
	WaitSema(pmemcard->semaId);
	SignalSema(pmemcard->semaId);
}

int FMemcardThreadValid(MEMCARD *pmemcard)
{
	return pmemcard->threadId != -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018b780);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018b910__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018b930__Fi);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018b988);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018bc90);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018bd00);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", InitSave__FP4SAVEii);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", UpdateSave__FP4SAVE);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", CompareSaves__FP4SAVET0);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c028);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c178_FP4SAVEi);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c1a8);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c1e8);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c250);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c420);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c568);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c638);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c770);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c7f8__FP4SAVE);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c888);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c9c0);

JUNK_ADDIU(10);
JUNK_ADDIU(10);
JUNK_ADDIU(b0);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018ca10);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", load_sly_icon_from_disc);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", load_file_from_disc);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018cdd8);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018cfc0);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d028);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d0a0);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d168);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d1f8);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d228);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d268);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d2b0);

JUNK_ADDIU(10);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d2e8);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d328);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d368);

JUNK_ADDIU(10);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", Clear__13CFileLocation);

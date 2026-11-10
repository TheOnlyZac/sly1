#include <memcard.h>
#include <thread.h>
#include <sdk/ee/libmc.h>
#include <sdk/ee/eekernel.h>
#include <sce/memset.h>
#include <clock.h>
#include <cat.h>
#include <game.h>

// libmc functions, names unknown (guessed signatures)
extern "C"
{
int func_00209CB8(int port, int slot, int *ptype, int *pfree, int *pformat); // sceMcGetInfo (guess)
int func_00209B80(int mode, int *pcmd, int *presult); // sceMcSync (guess)
int func_00209FA8(int port, int slot);
int func_002096E8(int port, int slot, int x);
int func_002095B0(int port, int slot, char *pchz, int mode); // sceMcOpen (guess)
int func_00209720(int fd); // sceMcClose (guess)
int func_00209870(int fd, void *pv, int cb); // sceMcRead (guess)
int func_00209990(int fd, void *pv, int cb); // sceMcWrite (guess)
}

extern SAVE g_save;
extern MEMCARD g_memcard;

extern void *DAT_002bea10;
extern "C" void func_001F6A30();
extern "C" int FUN_00160650(GS *pgs);

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

void FUN_0018b600()
{
	WaitSema(g_memcard.semaId);
	g_memcard.field_0x10 = ((int (*)(int))g_memcard.field_0x08)(g_memcard.field_0x0c);
	g_athread.sema = -1;
	g_memcard.threadId = -1;
	g_memcard.field_0x0c = 0;
	g_memcard.field_0x08 = 0;
	SignalSema(g_memcard.semaId);
	func_001F6A30();
}

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
	threadParam.entry = (void (*)(void *))FUN_0018b600;
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

int FUN_0018b910(int n)
{
	if (n == 0)
		return 0x1d;
	if (n > 0)
		return 0x1e;
	return 0x1f;
}

int FUN_0018b930(int n)
{
	switch (n)
	{
	case 0:
		return 0x20;
	case 1:
		return 0x21;
	case -1:
		return 0x22;
	}
	return 0x1f;
}

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018b988__Fii);

int FUN_0018bc90(int a, int b, int *pout)
{
	int cmd;
	int result;
	int r = FUN_0018b930(func_00209B80(a, &cmd, &result));
	if (pout)
		*pout = result;
	if (r == 0x21)
		r = FUN_0018b988(b, result);
	return r;
}

int FUN_0018bd00(int a, int b, int *pc)
{
	int r = FUN_0018b910(a);
	if (r == 0x1d)
		r = FUN_0018bc90(0, b, pc);
	return r;
}

void InitSave(SAVE *psave, int unk1, int unk2)
{
	memset(psave, 0, 0x4f50);
	psave->field_0x0c = -1;
	psave->mode = 0;
	FUN_0018c178(psave, 0);
	psave->port = unk1;
	psave->slot = unk2;
	STRUCT_OFFSET(psave, 0x4f48, int) = 0;
	STRUCT_OFFSET(psave, 0x4f44, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/memcard", UpdateSave__FP4SAVE);

int CompareSaves(SAVE *psave1, SAVE *psave2)
{
	int d = psave1->unk_0x54 - psave2->unk_0x54;
	if (d != 0)
		return d;
	d = psave1->unk_0x52 - psave2->unk_0x52;
	if (d != 0)
		return d;
	d = psave1->unk_0x53 - psave2->unk_0x53;
	if (d != 0)
		return d;
	d = psave1->unk_0x56 - psave2->unk_0x56;
	if (d != 0)
		return d;
	d = psave1->unk_0x57 - psave2->unk_0x57;
	if (d != 0)
		return d;
	return psave1->unk_0x58 - psave2->unk_0x58;
}

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c028);

void FUN_0018c178(SAVE *psave, int state)
{
	if (state != psave->state)
	{
		if (state == 2)
			STRUCT_OFFSET(psave, 0x4f44, int) = 0;
		psave->state = state;
		psave->tState = g_clock.tReal;
	}
}

int FUN_0018c1a8(SAVE *psave)
{
	int r = FUN_0018d1f8(psave);
	if (r)
		psave->mode = 2;
	else
		psave->mode = 3;
	return r;
}

int FUN_0018c1e8(SAVE *psave)
{
	CFileLocation cfl;
	int f;
	if (psave == 0)
		f = 0;
	else
	{
		cfl.m_fcl.cb = psave->port ^ STRUCT_OFFSET(psave, 0x1c, uint);
		cfl.m_fcl.isector = psave->field_0x00 ^ psave->mode;
		f = cfl.m_fcl.cb != 0;
	}
	int r = 0;
	if (f)
		r = FUN_001407A0(&cfl.m_fcl.isector);
	return r;
}

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c250);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c420);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c568);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c638);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c770);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c7f8__FP4SAVE);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018c888__FP4SAVEPciT1Pi);

int FUN_0018c9c0(SAVE *psave, char *pchz, char *pbHdr)
{
	int x;
	int r = FUN_0018c888(psave, pchz, 1, pbHdr, &x);
	if (r != 0)
		return r;
	return (x == 1) ? 0 : 0xe;
}

JUNK_ADDIU(10);
JUNK_ADDIU(10);
JUNK_ADDIU(b0);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018ca10);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", load_sly_icon_from_disc);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", load_file_from_disc);

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018cdd8);

int FUN_0018cfc0(SAVE *psave, char *pchz, GS *pgs)
{
	pgs->gsv = 0x12;
	pgs->cbThis = 0x1a00;
	pgs->nChecksum = FUN_00160650(pgs);
	return FUN_0018d368(psave, pchz, pgs, 0x1a00);
}

int FUN_0018d028(SAVE *psave, char *pchz, GS *pgs, char *pbHdr)
{
	char abHdr[0x60];
	InitGameState(pgs);
	if (pbHdr == 0)
		pbHdr = abHdr;
	int r = FUN_0018cfc0(psave, pchz, pgs);
	if (r == 0)
		r = FUN_0018c9c0(psave, pchz, pbHdr);
	return r;
}

INCLUDE_ASM("asm/nonmatchings/P2/memcard", FUN_0018d0a0);

int FUN_0018d168(SAVE *psave, int *pcb)
{
	int r = FUN_0018bd00(func_00209CB8(psave->port, psave->slot, &psave->mcType, &psave->mcFree, &psave->mcFormat), 1, 0);
	switch (r)
	{
	case 9:
		r = 0;
		break;
	case 10:
		r = 12;
		break;
	}
	if (r == 0)
		*pcb = psave->mcFree << 10;
	else
		*pcb = 0;
	return r;
}

int FUN_0018d1f8(SAVE *psave)
{
	return FUN_0018bd00(func_00209FA8(psave->port, psave->slot), 0x10, 0);
}

int FUN_0018d228(SAVE *psave, int b)
{
	int r = FUN_0018bd00(func_002096E8(psave->port, psave->slot, b), 0xb, 0);
	return r == 0x18 ? 0 : r;
}

int FUN_0018d268(SAVE *psave, char *pchz, int mode, int *pfd)
{
	return FUN_0018bd00(func_002095B0(psave->port, psave->slot, pchz, mode), 2, pfd);
}

int FUN_0018d2b0(SAVE *psave, int fd)
{
	return FUN_0018bd00(func_00209720(fd), 3, 0);
}

JUNK_NOP();
JUNK_ADDIU(10);

int FUN_0018d2e8(SAVE *psave, int fd, void *pv, int cb, int *pc)
{
	return FUN_0018bd00(func_00209870(fd, pv, cb), 5, pc);
}

int FUN_0018d328(SAVE *psave, int fd, void *pv, int cb, int *pc)
{
	return FUN_0018bd00(func_00209990(fd, pv, cb), 6, pc);
}

int FUN_0018d368(SAVE *psave, char *pchz, void *pv, int cb)
{
	int fd = -1;
	int cbWritten;
	int r = FUN_0018d268(psave, pchz, 0x202, &fd);
	if (r != 0)
		return r;
	r = FUN_0018d328(psave, fd, pv, cb, &cbWritten);
	if (r == 0)
		r = (cbWritten == cb) ? 0 : 7;
	FUN_0018d2b0(psave, fd);
	return r;
}

JUNK_ADDIU(10);

void CFileLocation::Clear()
{
	memset(&m_fcl, 0, sizeof(FCL));
}

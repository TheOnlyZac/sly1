#include <memcard.h>
#include <thread.h>
#include <sdk/ee/libmc.h>
#include <sdk/ee/eekernel.h>
#include <sce/memset.h>
#include <clock.h>
#include <cat.h>
#include <game.h>
#include <text.h>
#include <rumble.h>
#include <bis.h>
#include <prompt.h>
#include <memory.h>

// libmc functions, names unknown (guessed signatures)
extern "C"
{
int func_00209CB8(int port, int slot, int *ptype, int *pfree, int *pformat); // sceMcGetInfo (guess)
int func_00209E48(int port, int slot, char *pchz, int mode, int cMax, sceMcTblGetDir *ptbl); // sceMcGetDir (guess)
int func_0020A078(int port, int slot, char *pchz);
int func_00209B80(int mode, int *pcmd, int *presult); // sceMcSync (guess)
int func_00209FA8(int port, int slot);
int func_002096E8(int port, int slot, char *pchz);
int func_002095B0(int port, int slot, char *pchz, int mode); // sceMcOpen (guess)
int func_00209720(int fd); // sceMcClose (guess)
int func_00209870(int fd, void *pv, int cb); // sceMcRead (guess)
int func_00209990(int fd, void *pv, int cb); // sceMcWrite (guess)
}

extern char D_00248470[];
extern PROMPT D_0026FF68;
extern SAVE g_save;
extern MEMCARD g_memcard;

extern char D_002BEA10[]; // thread stack buffer (guess)
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

void CreateMemcardThread(MEMCARD *pmemcard, int unk1, int unk2)
{
	SetMemcardThreadHighPrio(pmemcard);
	pmemcard->field_0x08 = unk1;
	pmemcard->field_0x0c = unk2;
	pmemcard->field_0x10 = 0x20;
	
	ThreadParam threadParam;
	memset(&threadParam, 0, sizeof(ThreadParam));
	threadParam.entry = (void (*)(void *))FUN_0018b600;
	threadParam.stack = D_002BEA10;
	threadParam.gpReg = &_gpReg;
	threadParam.stackSize = 0x4000;
	threadParam.initPriority = 3;
	
	g_athread.sema = pmemcard->threadId = CreateThread(&threadParam);
	StartThread(pmemcard->threadId, (unsigned long)pmemcard);
}

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

void FUN_0018b780(sceMcTblGetDir *pdir, SAVEDIRENT *pent)
{
	memset(pent, 0, sizeof(SAVEDIRENT));
	strcpy(pent->achzName, (char *)pdir->EntryName);
	pent->cb = pdir->FileSizeByte;
	if (pdir->AttrFile & 0x1)
		pent->grf |= 0x1;
	if (pdir->AttrFile & 0x2)
		pent->grf |= 0x2;
	if (pdir->AttrFile & 0x4)
		pent->grf |= 0x4;
	if (pdir->AttrFile & 0x8)
		pent->grf |= 0x8;
	if (pdir->AttrFile & 0x20)
		pent->grf |= 0x10;
	if (pdir->AttrFile & 0x80)
		pent->grf |= 0x20;
	if (pdir->AttrFile & 0x800)
		pent->grf |= 0x40;
	if (pdir->AttrFile & 0x1000)
		pent->grf |= 0x80;
	pent->dt.bCreateMonth = pdir->_Create.Month;
	pent->dt.bCreateDay = pdir->_Create.Day;
	pent->dt.wCreateYear = pdir->_Create.Year;
	pent->dt.bCreateHour = pdir->_Create.Hour;
	pent->dt.bCreateMin = pdir->_Create.Min;
	pent->dt.bCreateSec = pdir->_Create.Sec;
	pent->dt.bModifyMonth = pdir->_Modify.Month;
	pent->dt.bModifyDay = pdir->_Modify.Day;
	pent->dt.wModifyYear = pdir->_Modify.Year;
	pent->dt.bModifyHour = pdir->_Modify.Hour;
	pent->dt.bModifyMin = pdir->_Modify.Min;
	pent->dt.bModifySec = pdir->_Modify.Sec;
}

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
#ifdef SKIP_ASM
int FUN_0018b988(int cmd, int r)
{
	switch (cmd)
	{
	case 1:
		switch (r)
		{
		case 0: return 0;
		case -1: return 9;
		case -2: return 0xa;
		case -5: return 0xb;
		}
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 2:
		switch (r)
		{
		case -3: return 1;
		case -4: return 0xd;
		case -5: return 6;
		case -7: return 0x19;
		case -2: return 0xc;
		}
		if (r >= 0)
			return 0;
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 4:
		switch (r)
		{
		case -4: return 0x10;
		case -2: return 0xc;
		}
		if (r >= 0)
			return 0;
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 5:
		switch (r)
		{
		case -4: return 0x10;
		case -2: return 0xc;
		case -5: return 0x11;
		}
		if (r >= 0)
			return 0;
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 6:
		switch (r)
		{
		case -5: return 0x12;
		case -8: return 0x1a;
		case -4: return 0x10;
		case -3: return 1;
		case -2: return 0xc;
		}
		if (r >= 0)
			return 0;
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 3:
	case 10:
		switch (r)
		{
		case 0: return 0;
		case -2: return 0xc;
		case -4: return 0x10;
		}
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 11:
		switch (r)
		{
		case 0: return 0;
		case -3: return 1;
		case -4: return 0x18;
		case -2: return 0xc;
		}
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 12:
		switch (r)
		{
		case 0: return 0;
		case -2: return 0xc;
		case -4: return 0x15;
		}
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 13:
		switch (r)
		{
		case -2: return 0xc;
		case -4: return 0x15;
		}
		if (r >= 0)
			return 0;
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 14:
		switch (r)
		{
		case 0: return 0;
		case -2: return 0xc;
		case -4: return 0x16;
		}
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 15:
		switch (r)
		{
		case 0: return 0;
		case -4: return 0xe;
		case -5: return 0x13;
		case -6: return 0x17;
		case -2: return 0xc;
		}
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 16:
		if (r == 0)
			return 0;
		if (r < 0)
			return 4;
		return 0x1f;
	case 17:
		if (r == 0)
			return 0;
		if (r < 0)
			return 5;
		return 0x1f;
	case 18:
		if (r == -2)
			return 0xc;
		if (r >= 0)
			return 0;
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 19:
		switch (r)
		{
		case 0: return 0;
		case -2: return 0xc;
		case -4: return 0x16;
		}
		if (r < -9)
			return 0xb;
		return 0x1f;
	case 20:
		switch (r)
		{
		case 0: return 0;
		case -403: return 0x23;
		}
		return 0x1f;
	case 21:
		if (r >= 0)
			return 0;
		if (r + 100 < 100u)
			return 0x1f;
		if (r < -99)
			return 0x1e;
		return 0x1f;
	}
	return 0x1f;
}
#endif // SKIP_ASM

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
	psave->state = -1;
	psave->mode = 0;
	FUN_0018c178(psave, 0);
	psave->port = unk1;
	psave->slot = unk2;
	STRUCT_OFFSET(psave, 0x4f48, int) = 0;
	STRUCT_OFFSET(psave, 0x4f44, int) = 0;
}

void UpdateSave(SAVE *psave)
{
	if (FMemcardThreadValid(&g_memcard))
		return;
	if (psave->state == psave->mode)
	{
		if (psave->tRetry <= g_clock.tReal)
			CreateMemcardThread(&g_memcard, (int)FUN_0018d0a0, (int)psave);
	}
	else
		FUN_0018c028(psave, psave->mode);
	if (FMemcardThreadValid(&g_memcard))
		return;
	if (psave->substate != 1)
		return;
	if (g_clock.tReal - psave->tState >= 0.3f)
	{
		if (STRUCT_OFFSET(psave, 0x4f44, int) != 0)
		{
			if (psave->state != 5)
				SetPrompt(&D_0026FF68, (PRP)1, (PRK)0x15);
		}
		else
		{
			PROMPT *pprompt = &D_0026FF68;
			if (STRUCT_OFFSET(pprompt, 0x25c, int) != 0 && STRUCT_OFFSET(pprompt, 0x268, int) == 0x11)
			{
				if (psave->state != 5)
					SetPrompt(&D_0026FF68, (PRP)1, (PRK)0x20);
				return;
			}
			switch (psave->state)
			{
			case 1:
				SetPrompt(&D_0026FF68, (PRP)1, (PRK)3);
				break;
			case 2:
				SetPrompt(&D_0026FF68, (PRP)1, (PRK)4);
				break;
			case 3:
				SetPrompt(&D_0026FF68, (PRP)1, (PRK)7);
				break;
			case 4:
				SetPrompt(&D_0026FF68, (PRP)1, (PRK)10);
				break;
			}
		}
	}
}

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

void FUN_0018c028(SAVE *psave, int state)
{
	if (state != psave->state)
	{
		if (psave->state == 5)
			STRUCT_OFFSET(psave, 0x4f48, int) = 0;
		switch (state)
		{
		case 0:
		case 1:
			CreateMemcardThread(&g_memcard, (int)FUN_0018d0a0, (int)psave);
			break;
		case 3:
			CreateMemcardThread(&g_memcard, (int)FUN_0018c420, (int)psave);
			break;
		case 5:
		{
			SAVESLOT *pslot;
			char *pbHdr = (char *)psave + 0x1a30;
			pslot = STRUCT_OFFSET(psave, 0x4f48, SAVESLOT *) = (SAVESLOT *)((char *)psave + 0x30);
			for (int i = 2; i >= 0; pbHdr += 0x1a5c, i--, pslot++)
			{
				if (pslot->gs.dt != 0.0f)
				{
					if (CompareSaves((SAVE *)((char *)STRUCT_OFFSET(psave, 0x4f48, SAVESLOT *) + 0x1a00), (SAVE *)pbHdr) < 0)
						STRUCT_OFFSET(psave, 0x4f48, SAVESLOT *) = pslot;
				}
				else
					InitGameState(&pslot->gs);
			}
			break;
		}
		}
		psave->state = state;
		psave->tState = g_clock.tReal;
	}
}

void FUN_0018c178(SAVE *psave, int state)
{
	if (state != psave->substate)
	{
		if (state == 2)
			STRUCT_OFFSET(psave, 0x4f44, int) = 0;
		psave->substate = state;
		psave->tSubstate = g_clock.tReal;
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

int FUN_0018c250(SAVE *psave)
{
	char abBuf[0x50];
	int n;
	int c;
	int cb;
	int r = FUN_0018bd00(func_0020A078(psave->port, psave->slot, "/"), 0x12, &n);
	if (r != 0)
		return r;
	c = (n == 0) ? 2 : 1;
	cb = FUN_0018c1e8((SAVE *)D_00248470);
	c += 5;
	c += (cb + 0x3ff) / 0x400;
	c += 0x15;
	if (psave->mcFree < c)
		return 1;
	r = FUN_0018d228(psave, "/BASCUS-97198YAOTWTD!");
	if (r == 0)
	{
		r = FUN_0018d368(psave, "/BASCUS-97198YAOTWTD!/BASCUS-97198YAOTWTD!", (void *)"Sly Cooper", 10);
		if (r == 0)
		{
			r = FUN_0018ca10(psave, "/BASCUS-97198YAOTWTD!", (void *)"Sly Cooper");
			if (r == 0)
			{
				r = load_sly_icon_from_disc(psave, "/BASCUS-97198YAOTWTD!");
				if (r == 0)
				{
					SAVESLOT *aslot = (SAVESLOT *)((char *)psave + 0x30);
					for (int i = 0; i < 3; i++)
					{
						sprintf(abBuf, "/%s/%s%d", "BASCUS-97198YAOTWTD!", "save", i + 1);
						r = FUN_0018d028(psave, abBuf, &aslot[i].gs, (char *)aslot[i].unk_0x1a00);
						if (r != 0)
							goto done;
					}
					if (psave->mode < 5)
						psave->mode = 5;
				}
			}
		}
	}
done:
	return r;
}

/**
 * @note (guess) The original asm tests r in the loop but never stores the result
 * of FUN_0018cdd8, so the return value of that call is dropped here too.
 */
int FUN_0018c420(SAVE *psave)
{
	char abBuf[0x50];
	int cEnt;
	int cb;
	int r = FUN_0018bd00(func_00209E48(psave->port, psave->slot, "/BASCUS-97198YAOTWTD!", 0, -1, 0), 0xd, &cEnt);
	if (cEnt <= 0)
	{
		FUN_0018d168(psave, &cb);
		if (cb <= 0xc3ff)
			psave->mode = 4;
		return 0xe;
	}
	for (int i = 0; r == 0 && i < 3; i++)
	{
		sprintf(abBuf, "/%s/%s%d", "BASCUS-97198YAOTWTD!", "save", i + 1);
		FUN_0018cdd8(psave, abBuf, &((SAVESLOT *)((char *)psave + 0x30))[i].gs, (char *)((SAVESLOT *)((char *)psave + 0x30))[i].unk_0x1a00);
	}
	if (r == 0)
	{
		if (psave->mode < 5)
			psave->mode = 5;
	}
	return r;
}

int FUN_0018c568(SAVE *psave)
{
	if (STRUCT_OFFSET(psave, 0x4f44, GS *) == 0)
		return 0x2c;
	*g_pgsCur = *STRUCT_OFFSET(psave, 0x4f44, GS *);
	RumbleUnknown2(g_pgsCur);
	return 0;
}

int FUN_0018c638(SAVE *psave)
{
	char abBuf[0x50];
	if (STRUCT_OFFSET(psave, 0x4f44, GS *) == 0)
		return 0x2c;
	RumbleUnknown2(g_pgsCur);
	*STRUCT_OFFSET(psave, 0x4f44, GS *) = *g_pgsCur;
	int i = ((SAVESLOT *)STRUCT_OFFSET(psave, 0x4f44, GS *) - (SAVESLOT *)((char *)psave + 0x30)) + 1;
	sprintf(abBuf, "/%s/%s%d", "BASCUS-97198YAOTWTD!", "save", i);
	return FUN_0018cfc0(psave, abBuf, STRUCT_OFFSET(psave, 0x4f44, GS *));
}

int FUN_0018c770(SAVE *psave)
{
	char abBuf[0x50];
	if (STRUCT_OFFSET(psave, 0x4f4c, GS *) == 0)
		return 0x2c;
	int i = ((SAVESLOT *)STRUCT_OFFSET(psave, 0x4f4c, GS *) - (SAVESLOT *)((char *)psave + 0x30)) + 1;
	sprintf(abBuf, "/%s/%s%d", "BASCUS-97198YAOTWTD!", "save", i);
	return FUN_0018d028(psave, abBuf, STRUCT_OFFSET(psave, 0x4f4c, GS *), (char *)STRUCT_OFFSET(psave, 0x4f4c, GS *) + 0x1a00);
}

struct UW
{
	int w;
} __attribute__((packed));
struct VTUNK
{
	char unk_0x00[0x38];
	void (*pfn)(void *);
};
struct OBJUNK
{
	VTUNK *pvt;
	char unk_0x04[0x25c];
};
extern OBJUNK D_00273EB0;

void FUN_0018c7f8(SAVE *psave)
{
	if (STRUCT_OFFSET(psave, 0x4f44, int) != 0)
	{
		if ((g_pgsCur->grfgs & 0x100) == 0)
		{
			PROMPT *pprompt = &D_0026FF68;
			STRUCT_OFFSET(pprompt, 0x27c, int) = -1;
			SetPrompt(pprompt, (PRP)1, (PRK)0x14);
		}
		else
		{
			CreateMemcardThread(&g_memcard, (int)FUN_0018c638, (int)psave);
			OBJUNK *pobj = &D_00273EB0;
			((UW *)((char *)pobj + 0x260))->w = 0;
			pobj->pvt->pfn(pobj);
		}
	}
}

extern char D_002BE9C0[];
extern sceMcTblGetDir D_002BE540[];

int FUN_0018c888(SAVE *psave, char *pchz, int cMax, char *pbHdr, int *pc)
{
	if (cMax >= 0x13)
		return 0x25;
	int mode;
	if (pchz != 0)
	{
		if (strlen(pchz) > 0x40)
			return 0xd;
		strcpy(D_002BE9C0, pchz);
		mode = 0;
	}
	else
	{
		mode = 1;
		pchz = D_002BE9C0;
	}
	sceMcTblGetDir *pdir = D_002BE540;
	memset(pdir, 0, 0x480);
	int r = FUN_0018bd00(func_00209E48(psave->port, psave->slot, pchz, mode, cMax, pdir), 0xd, pc);
	if (r != 0)
		return r;
	int i = 0;
	if (i < *pc)
	{
		char *pent = pbHdr;
		do
		{
			FUN_0018b780(pdir, (SAVEDIRENT *)pent);
			i++;
			pent += 0x5c;
			pdir++;
		} while (i < *pc);
	}
	return 0;
}

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

// These two strings are read through the symbol in the original (not constant folded),
// so they are emitted by hand in rodata order instead of being literals.
extern char D_0024B3D0[];
extern char D_0024B3D8[];
asm(".section .rodata\n"
    ".align 3\n"
    ".globl D_0024B3D0\n"
    "D_0024B3D0: .asciz \"PS2D\"\n"
    ".align 3\n"
    ".globl D_0024B3D8\n"
    "D_0024B3D8: .asciz \"sly.ico\"\n"
    ".section .text\n");
extern "C" void FUN_001b5c40(char *pchzSrc, char *pchzDst);
struct S8
{
	char ach[8];
};

int FUN_0018ca10(SAVE *psave, char *pchz, void *pv)
{
	sceMcIconSys icon;
	char abName[0x50];
	memset(&icon, 0, sizeof(sceMcIconSys));
	*(int *)icon.Head = *(int *)D_0024B3D0;
	icon.Head[4] = D_0024B3D0[4];
	icon.OffsLF = 0x20;
	icon.TransRate = 0x60;
	icon.BgColor[0][0] = 0;
	icon.BgColor[0][1] = 0x87;
	icon.BgColor[0][2] = 0xff;
	icon.BgColor[1][0] = 0;
	icon.BgColor[1][1] = 0x29;
	icon.BgColor[1][2] = 0x6f;
	icon.BgColor[2][0] = 0;
	icon.BgColor[2][1] = 0x29;
	icon.BgColor[2][2] = 0x6f;
	icon.BgColor[3][0] = 0;
	icon.BgColor[3][1] = 0x87;
	icon.BgColor[3][2] = 0xff;
	icon.LightDir[0][0] = 0.0f;
	icon.LightDir[0][1] = 0.5f;
	icon.LightDir[0][2] = -0.5f;
	icon.LightDir[1][0] = 0.5f;
	icon.LightDir[1][1] = -0.4f;
	icon.LightDir[1][2] = 0.1f;
	icon.LightDir[2][0] = -0.5f;
	icon.LightDir[2][1] = 0.5f;
	icon.LightDir[2][2] = 0.5f;
	icon.LightColor[0][0] = 0.14f;
	icon.LightColor[0][1] = 0.03f;
	icon.LightColor[0][2] = 0.48f;
	icon.LightColor[1][0] = 0.33f;
	icon.LightColor[1][1] = 0.0f;
	icon.LightColor[1][2] = 0.33f;
	icon.LightColor[2][0] = 0.14f;
	icon.LightColor[2][1] = 0.14f;
	icon.LightColor[2][2] = 0.38f;
	icon.Ambient[0] = 0.5f;
	icon.Ambient[1] = 0.5f;
	icon.Ambient[2] = 0.5f;
	FUN_001b5c40((char *)pv, (char *)icon.TitleName);
	*(S8 *)icon.FnameView = *(S8 *)D_0024B3D8;
	*(S8 *)icon.FnameCopy = *(S8 *)D_0024B3D8;
	*(S8 *)icon.FnameDel = *(S8 *)D_0024B3D8;
	sprintf(abName, "%s/%s", pchz, "icon.sys");
	return FUN_0018d368(psave, abName, &icon, 0x3c4);
}

int load_sly_icon_from_disc(SAVE *psave, char *pchz)
{
	return load_file_from_disc(psave, pchz, (SAVE *)D_00248470, D_0024B3D8);
}

int load_file_from_disc(SAVE *psave, char *pchzA, SAVE *pcipher, char *pchzB)
{
	char abName[0x50];
	int fd;
	int cbWritten;
	InitStackImpl();
	fd = -1;
	// @todo (guess) args are in the order the asm passes them, they do not match bis.h
	CBinaryInputStream bis((void *)0x8040, (int)PvAllocStackImpl(0x8040), 0);
	sprintf(abName, "%s/%s", pchzA, pchzB);
	int r = FUN_0018d268(psave, abName, 0x202, &fd);
	if (r == 0)
	{
		CFileLocation cfl;
		int f;
		if (pcipher == 0)
			f = 0;
		else
		{
			cfl.m_fcl.cb = pcipher->port ^ STRUCT_OFFSET(pcipher, 0x1c, uint);
			cfl.m_fcl.isector = pcipher->field_0x00 ^ pcipher->mode;
			f = cfl.m_fcl.cb != 0;
		}
		if (f == 0 || !bis.FOpenFile(&cfl))
			r = 0x27;
		else
		{
			int cbLeft = bis.m_cbFile;
			if (cbLeft > 0)
			{
				char abBuf[0x1000];
				do
				{
					int cb = 0x1000;
					if (cbLeft <= 0xfff)
						cb = cbLeft;
					bis.Read(cb, abBuf);
					r = FUN_0018d328(psave, fd, abBuf, cb, &cbWritten);
					if (r != 0)
						goto done;
					if (cbWritten != cb)
					{
						r = 7;
						goto done;
					}
					cbLeft -= cbWritten;
				} while (cbLeft > 0);
			}
			r = 0;
		}
done:
		bis.Close();
		int rc = FUN_0018d2b0(psave, fd);
		if (r == 0)
			r = rc;
		FreeStackImpl();
	}
	return r;
}

int FUN_0018cdd8(SAVE *psave, char *pchz, GS *pgs, char *pbHdr)
{
	SAVEDIRENT dirent;
	GS gs;
	int fd = -1;
	int cbRead;
	if (pbHdr == 0)
		pbHdr = (char *)&dirent;
	memset(pbHdr, 0, 0x5c);
	InitGameState(pgs);
	int r = FUN_0018c9c0(psave, pchz, pbHdr);
	if (r != 0)
		return r;
	SAVEDIRENT *pent = (SAVEDIRENT *)pbHdr;
	if ((pent->grf & 0xd4) != 4)
		return 0x14;
	int cb = pent->cb;
	if (cb != 0x1a00)
		return 0x1c;
	r = FUN_0018d268(psave, pchz, 1, &fd);
	if (r != 0)
		return r;
	r = FUN_0018d2e8(psave, fd, &gs, 0x1a00, &cbRead);
	if (r != 0)
	{
		FUN_0018d2b0(psave, fd);
		return r;
	}
	if (r == 0)
	{
		if (cbRead != cb)
			r = 8;
		else if (gs.gsv != 0x12)
			r = 0x1c;
		else if (gs.cbThis != cbRead)
			r = 0x1c;
		else if (gs.nChecksum != FUN_00160650(&gs))
			r = 0x1b;
		else
		{
			*pgs = gs;
			r = 0;
		}
	}
	FUN_0018d2b0(psave, fd);
	return r;
}

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

int FUN_0018d0a0(SAVE *psave)
{
	int r = FUN_0018bd00(func_00209CB8(psave->port, psave->slot, &psave->mcType, &psave->mcFree, &psave->mcFormat), 1, 0);
	switch (r)
	{
	case 9:
	case 11:
		psave->mode = 1;
		r = 0xb;
		break;
	case 10:
	case 12:
		psave->mode = 2;
		r = 0xc;
		break;
	case 0:
		if (psave->mcFormat != 0)
		{
			if (psave->mode < 3)
				psave->mode = 3;
		}
		else
			psave->mode = 2;
		break;
	}
	psave->tRetry = g_clock.tReal + 0.3f;
	return r;
}

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

int FUN_0018d228(SAVE *psave, char *pchz)
{
	int r = FUN_0018bd00(func_002096E8(psave->port, psave->slot, pchz), 0xb, 0);
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

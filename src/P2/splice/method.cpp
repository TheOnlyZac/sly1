#include "common.h"
#include <sce/memset.h>
#include <splice/method.h>
#include <splice/splotheap.h>

// todo: matches but blocked by reference in 001c15d8
INCLUDE_ASM(const s32, "P2/splice/method", PmethodNew__Fv);
// static CMethod* PMethodNew()
// {
//     CMethod* method = (CMethod*)g_splotheapMethod.PvAllocClear();
//     memset(method, 0, sizeof(CMethod));
//     return method;
// }

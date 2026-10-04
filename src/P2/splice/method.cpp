#include <sce/memset.h>
#include <splice/method.h>
#include <splice/spliceutils.h>

CMethod *PmethodNew()
{
    CMethod *method = (CMethod *)g_splotheapMethod.PvAllocClear();
    memset(method, 0, sizeof(CMethod));
    return method;
}

#include <proxy.h>
#include <sw.h>

void InitProxy(PROXY *pproxy)
{
    InitAlo(pproxy);
    AppendDlEntry(&pproxy->psw->dlProxy, pproxy);
}

INCLUDE_ASM("asm/nonmatchings/P2/proxy", LoadProxyFromBrx__FP5PROXYP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/proxy", CloneProxy__FP5PROXYT0);

void PostProxyLoad(PROXY *pproxy)
{
    PostAloLoad(pproxy);
    pproxy->pvtlo->pfnRemoveLo(pproxy);
}

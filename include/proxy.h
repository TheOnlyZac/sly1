/**
 * @file proxy.h
 */
#ifndef PROXY_H
#define PROXY_H

#include "common.h"
#include <alo.h>
#include <bis.h>
#include <dl.h>

/**
 * @brief Unknown.
 *
 * @todo Does this inherit from a base struct?
 */
struct PROXY
{
    DL dlProxyRoot;
    DLE dleProxy;
    undefined4 unk_0x8;
    undefined4 unk_0xC;
    undefined4 unk_0x10;
};

void InitProxy(PROXY *pproxy);

void LoadProxyFromBrx(PROXY *pproxy, CBinaryInputStream *pbis);

void CloneProxy(PROXY *pproxy, PROXY *pproxyBase);

void PostProxyLoad(PROXY *pproxy);

#endif // PROXY_H

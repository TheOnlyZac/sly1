#ifndef SIFRPC_H_
#define SIFRPC_H_

extern "C" {

typedef void (*sceSifEndFunc)(void*);
typedef void* (*sceSifRpcFunc)(unsigned, void*, int);

struct _sif_rpc_data { // 0x10
    /* 0x0 */ void* paddr;
    /* 0x4 */ unsigned int pid;
    /* 0x8 */ int tid;
    /* 0xc */ unsigned int mode;
};
typedef _sif_rpc_data sceSifRpcData;

struct _sif_client_data { // 0x28
    /* 0x00 */ struct _sif_rpc_data rpcd;
    /* 0x10 */ unsigned int command;
    /* 0x14 */ void* buff;
    /* 0x18 */ void* cbuff;
    /* 0x1c */ sceSifEndFunc func;
    /* 0x20 */ void* para;
    /* 0x24 */ struct _sif_serve_data* serve;
};
typedef _sif_client_data sceSifClientData;

struct _sif_serve_data { // 0x44
    /* 0x00 */ unsigned int command;
    /* 0x04 */ sceSifRpcFunc func;
    /* 0x08 */ void* buff;
    /* 0x0c */ int size;
    /* 0x10 */ sceSifRpcFunc cfunc;
    /* 0x14 */ void* cbuff;
    /* 0x18 */ int csize;
    /* 0x1c */ sceSifClientData* client;
    /* 0x20 */ void* paddr;
    /* 0x24 */ unsigned int fno;
    /* 0x28 */ void* receive;
    /* 0x2c */ int rsize;
    /* 0x30 */ int rmode;
    /* 0x34 */ unsigned int rid;
    /* 0x38 */ struct _sif_serve_data* link;
    /* 0x3c */ struct _sif_serve_data* next;
    /* 0x40 */ struct _sif_queue_data* base;
};
typedef _sif_serve_data sceSifServeData;

struct _sif_queue_data { // 0x18
    /* 0x00 */ int key;
    /* 0x04 */ int active;
    /* 0x08 */ struct _sif_serve_data* link;
    /* 0x0c */ struct _sif_serve_data* start;
    /* 0x10 */ struct _sif_serve_data* end;
    /* 0x14 */ struct _sif_queue_data* next;
};
typedef _sif_queue_data sceSifQueueData;

void sceSifInitRpc(unsigned int mode);
int sceSifBindRpc(sceSifClientData*, unsigned int, unsigned int);
int sceSifCallRpc(sceSifClientData*, unsigned int, unsigned int, void*, int, void*, int, sceSifEndFunc, void*);
int sceSifCheckStatRpc(sceSifRpcData*);
}

#endif // SIFRPC_H_

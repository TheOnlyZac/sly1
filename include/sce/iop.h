#ifndef IOP_H
#define IOP_H

extern "C"
{
int sceSifLoadFileReset();
int sceSifLoadModule(const char *, int, int);
int sceSifRebootIop(void *);
int sceSifSyncIop();
};

#endif // IOP_H
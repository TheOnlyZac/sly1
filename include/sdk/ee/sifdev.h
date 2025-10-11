#ifndef SIFDEV_H
#define SIFDEV_H

extern "C"
{
int sceSifLoadFileReset();
int sceSifLoadModule(const char *filename, int args, const char *argp);
int sceSifRebootIop(const char *img);
int sceSifSyncIop(void);
};

#endif // SIFDEV_H

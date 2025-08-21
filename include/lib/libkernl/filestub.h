/**
 * @file include/lib/libkernl/filestub.h
 * @note src/lib/libkernl/filestub.c
 */
#ifndef FILESTUB_H
#define FILESTUB_H

extern "C"
{
    int sceClose(int fd);
	void sceRead(int fd, void *pv, int cb);
};

#endif // FILESTUB_H

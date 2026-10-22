#ifndef SIF_H
#define SIF_H

extern "C"
{

struct sceSifDmaData
{
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
};

int sceSifDmaStat();

int sceSifSetDma();

};

#endif // SIF_H
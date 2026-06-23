/**
 * @file gifs.h
 */
#ifndef GIFS_H
#define GIFS_H

#include <dmas.h>

/**
 * @brief Unknown. Constructs primitives for rendering?
 * @note "unsigned long" isn't the same as "ulong".
 */
struct GIFS : public DMAS
{
    /* 0x1c */ QW *m_pqwPrim;
    /* 0x20 */ uint m_creg;
    /* 0x24 */ uint m_cregAll;

    GIFS();

    void AddPrimEnd();
    void EndPrim(int fEOP);
    void CheckReg(int fExpectPack, int regExpect);
    void AddPrimBulk(int prim, int c, int creg, unsigned long regs, QW **paqwBulk);
    void AddPrimPack(int prim, int creg, unsigned long regs);
    void PackRGBA(uint rgba);
    void PackUV(int u, int v);
    void PackSTQ(float s, float t, float q);
    void PackXYZ(int x, int y, int z);
    void PackXYZF(int x, int y, int z, int fog);
    void PackXYZFNoKick(int x, int y, int z, int fog);
    void PackAD(long int a, long int d);
    void AddPrimList(int creg, ulong regs);
    void ListRGBAQ(uint rgba, float q);
    void ListUV(int u, int v);
    void ListXYZF(int x, int y, int z, int fog);
    void AddImage(int cqw);
};

#endif // GIFS_H

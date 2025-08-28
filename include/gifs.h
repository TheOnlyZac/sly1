/**
 * @file gifs.h
 */
#ifndef GIFS_H
#define GIFS_H

#include <dmas.h>

/**
 * @brief Unknown. Constructs primitives for rendering? 
 */
struct GIFS : DMAS
{
    QW *m_pqwPrim;
    uint m_creg;
    uint m_cregAll;

    GIFS();

    void AddPrimEnd();
    void EndPrim(int fEOP);
    void CheckReg(int fExpectPack, int regExpect);
    void AddPrimBulk(int prim, int c, int creg, ulong regs, QW **paqwBulk);
    void AddPrimPack(int prim, int creg, ulong regs);
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

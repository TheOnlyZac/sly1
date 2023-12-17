/**
 * @file prog.h
 *
 * @brief Declares the prog class.
*/
#ifndef PROG_H
#define PROG_H

#include <game.h>
#include <font.h>

typedef bool BOOL; // todo: move to util header

/**
 * @Brief Progress
*/
class CProg
{
public:
	BOOL m_fActive;
	int m_nMax;
	int m_nTarget;
	int m_nRemain;
	int m_cRetry;
	RGBA m_rgbaComplete;
	RGBA m_rgbaRemain;
	RGBA m_rgbaWarning;
	RGBA m_rgbaTrouble;

	void Begin();
	void SetRemain(int nRemain);
	void Draw();
	void End();
};

#endif // PROG_H

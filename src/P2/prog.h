#pragma once
#include <game.h>
#include <font.h>

typedef bool BOOL; // todo: move this to the appropriate file

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

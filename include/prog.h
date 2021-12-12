#pragma once

typedef bool BOOL; // todo: move this to the appropriate file;
typedef unsigned int RGBA; // todo: define struct

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
};

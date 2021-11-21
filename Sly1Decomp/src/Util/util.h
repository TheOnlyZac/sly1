#pragma once

struct LM
{
	float gMin, gMax;
	//float u4ag;

	inline LM(float min = 0, float max = 1)
	{
		gMin = min;
		gMax = max;
	}
};

inline LM g_lmZeroOne(0, 1);

float GLimitLm(LM* plm, float g);


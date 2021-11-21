#pragma once

struct LM
{
	float gMin, gMax;
	//float u4ag;

	inline LM(float min, float max)
	{
		gMin = min;
		gMax = max;
	}
};

float GLimitLm(LM* plm, float g);


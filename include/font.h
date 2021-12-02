#pragma once

class CTextBox
{
	float m_x;
	float m_y;
	float m_dx;
	float m_dy;
	/* RGBA m_rgba; todo */
	/* JH m_jh; todo */
	char padding[3];
	/* JV m_jv; todo */

public:
	void SetPos(float x, float y);

};
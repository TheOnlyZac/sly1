#pragma once

enum class JH : int
{
	JH_Left = 0x0,
	JH_Center = 0x1,
	JH_Right = 0x2,
	JH_Max = 0x3
};

enum class JV : int
{
	JH_Top = 0x0,
	JH_Center = 0x1,
	JH_Bottom = 0x2,
	JH_Max = 0x3
};

struct RGBA {
    unsigned char ab[1];
    char bGreen;
    char bBlue;
    char bAlpha;
    char u1bRed;
};

class CTextBox
{
private:
	float m_x; // x pos
	float m_y; // y pos
	float m_dx; // x size
	float m_dy; // y size
	RGBA m_rgba; // text color
	JH m_jh; // horizontal justification
	JV m_jv; // vertical justification

public:
	void SetPos(float x, float y);
	void SetSize(float dx, float dy);
	void SetTextColor(RGBA rgba);
	void SetHorizontalJust(JH jh);
	void SetVerticalJust(JV jv);
};
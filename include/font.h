#pragma once

/* Horizontal Justification */
enum class JH : int
{
	JH_Left = 0x0,
	JH_Center = 0x1,
	JH_Right = 0x2,
	JH_Max = 0x3
};

/* Vertical Justification */
enum class JV : int
{
	JH_Top = 0x0,
	JH_Center = 0x1,
	JH_Bottom = 0x2,
	JH_Max = 0x3
};

/* Red, Green, Blue, Alpha color values */
struct RGBA {
    char bRed;
    char bGreen;
    char bBlue;
    char bAlpha;
};

/* Unknown, used by CFont class */
struct SFR
{
	float rx;
	float ry;
};

struct CFont
{
protected:
	int m_dxCharUnscaled;
	int m_dxSpaceUnscaled;
	int m_dyUnscaled;
	int m_csfr;
	struct SFR m_asfr[4];
	int m_fGstest;
	int field_0x34; // unknown
	u64 m_gstest;
	u32 m_z;

private:
	float m_rxScale;
	float m_ryScale;
	//__vtbl_ptr_type * vf5078; // todo
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
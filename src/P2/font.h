#pragma once

typedef char BYTE;

/* Horizontal Justification */
enum class JH : int
{
	Left = 0x0,
	Center = 0x1,
	Right = 0x2,
	Max = 0x3
};

/* Vertical Justification */
enum class JV : int
{
	Top = 0x0,
	Center = 0x1,
	Bottom = 0x2,
	Max = 0x3
};

/* Red, Green, Blue, Alpha color values */
struct RGBA {
    BYTE bRed;
    BYTE bGreen;
	BYTE bBlue;
	BYTE bAlpha;
};

/* Unknown, possibly ScaleFactorRatio 
(used by CFont class, probably to scale fonts) */
struct SFR
{
	float rx;
	float ry;
};

typedef struct _vtbl_ptr_type;
class CFont
{
protected:
	int m_dxCharUnscaled;
	int m_dxSpaceUnscaled;
	int m_dyUnscaled;
	int m_csfr;
	struct SFR m_asfr[4]; // 4 different scale factors, each to be used in a different situation?
	int m_fGstest;
	int field_0x34; // unknown
	/* todo: figure out these types
	u64 m_gstest;
	u32 m_z; */

private:
	float m_rxScale;
	float m_ryScale;
	_vtbl_ptr_type* vf5078;
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

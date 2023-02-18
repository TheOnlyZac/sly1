#include <font.h>

/* Set text bos position */
void CTextBox::SetPos(float x, float y)
{
	this->m_x = x;
	this->m_y = y;
}

/* Set text box size */
void CTextBox::SetSize(float dx, float dy)
{
	this->m_dx = dx;
	this->m_dy = dy;
}

/* Set text box text color */
void CTextBox::SetTextColor(RGBA rgba)
{
	this->m_rgba = rgba;
}

/* Set text bos horizontal justification */
void CTextBox::SetHorizontalJust(JH jh)
{
	this->m_jh = jh;
}

/* Set text box vertical justification */
void CTextBox::SetVerticalJust(JV jv)
{
	this->m_jv = jv;
}

/**
 * @file font.cpp
 *
 * @brief Defines functions for manipulating fonts.
*/
#include <font.h>

void CTextBox::SetPos(float x, float y)
{
	this->m_x = x;
	this->m_y = y;
}

void CTextBox::SetSize(float dx, float dy)
{
	this->m_dx = dx;
	this->m_dy = dy;
}

void CTextBox::SetTextColor(RGBA rgba)
{
	this->m_rgba = rgba;
}

void CTextBox::SetHorizontalJust(JH jh)
{
	this->m_jh = jh;
}

void CTextBox::SetVerticalJust(JV jv)
{
	this->m_jv = jv;
}

#include <CTextBox.h>

void CTextBox::SetHorizontalJust(CTextBox* tb, uint32_t param_1)
{
	*(uint32_t*)(tb + 0x14) = param_1;
}
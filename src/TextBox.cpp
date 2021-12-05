#include <TextBox.h>

void TextBox::SetHorizontalJust(CTextBox* tb, uint32_t param_1)
{
	*(uint32_t*)(tb + 0x14) = param_1;
}
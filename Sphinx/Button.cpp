#include "Button.h"

Sphinx::Forms::CButton::CButton() : TextAlign(ContentAlignment::MiddleCenter)
{
	BackColor = CSystemColors::ButtonFace;
	Size = D3DXVECTOR2(75.0f, 23.0f);
}

void Sphinx::Forms::CButton::Render(CRenderer* pRenderer)
{
	if (Parent == NULL || !Visible)
		return;

	D3DXVECTOR2 pos = GetAbsolutePos();

	RECT rect = {
		(LONG)pos.x + Padding.left + 5,
		(LONG)pos.y + Padding.top + 3,
		(LONG)(pos.x + Size.x) - Padding.right - 5,
		(LONG)(pos.y + Size.y) - Padding.bottom - 5
	};

	DWORD dwFormat = (DWORD)TextAlign;

	if (RightToLeft)
		dwFormat |= DT_RTLREADING;

	pRenderer->DrawBorder(pos.x, pos.y, Size.x, Size.y, CSystemColors::ButtonBorder);
	pRenderer->DrawFilledRect(pos.x + 1.0f, pos.y + 1.0f, Size.x - 2.0f, Size.y - 2.0f, BackColor);
	pRenderer->DrawText(Font, 0, 0, &rect, dwFormat, ForeColor, Text.c_str());
}
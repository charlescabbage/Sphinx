#include "Label.h"

Sphinx::Forms::CLabel::CLabel() : TextAlign(ContentAlignment::TopLeft)
{
	Size = D3DXVECTOR2(100.0f, 23.0f);
}

void Sphinx::Forms::CLabel::Render(CRenderer* pRenderer)
{
	if (Parent == NULL || !Visible)
		return;

	RECT rect;
	D3DXVECTOR2 pos = GetAbsolutePos();
	DWORD dwFormat = (DWORD)TextAlign;

	if (RightToLeft)
		dwFormat |= DT_RTLREADING;

	pRenderer->CalcTextRect(Font, &rect, dwFormat, Text.c_str());

	float width = (float)(rect.right - rect.left);
	float height = (float)(rect.bottom - rect.top);

	Size.x = (float)(width + Padding.right + 5);
	Size.y = (float)(height + Padding.bottom + 1);

	rect.left = (LONG)pos.x + Padding.left + 5;
	rect.top = (LONG)pos.y + Padding.top + 1;
	rect.right = (LONG)(pos.x + Size.x);
	rect.bottom = (LONG)(pos.y + Size.y);

	if (BackColor != Parent->BackColor)
	{
		pRenderer->DrawFilledRect(pos.x, pos.y,
			Size.x + Padding.left + 5,
			Size.y + Padding.top + 3,
			BackColor);
	}

	pRenderer->DrawText(Font, 0, 0, &rect, dwFormat, ForeColor, Text.c_str());
}
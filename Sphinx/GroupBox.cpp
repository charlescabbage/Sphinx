#include "GroupBox.h"

Sphinx::Forms::CGroupBox::CGroupBox()
{
	Size = D3DXVECTOR2(200.0f, 100.0f);
}

void Sphinx::Forms::CGroupBox::Render(CRenderer* pRenderer)
{
	if (Parent == NULL || !Visible)
		return;

	D3DXVECTOR2 pos = GetAbsolutePos();
	DWORD dwFormat = DT_LEFT | DT_NOCLIP;

	if (RightToLeft)
		dwFormat |= DT_RTLREADING;

	RECT rect;
	pRenderer->CalcTextRect(Font, &rect, dwFormat, Text.c_str());

	float width = (float)(rect.right - rect.left);
	float height = (float)(rect.bottom - rect.top);

	D3DXVECTOR2 box[6] = {
		{ pos.x + 6.0f, pos.y },
		{ pos.x, pos.y },
		{ pos.x, pos.y + Size.y - 1.0f },
		{ pos.x + Size.x, pos.y + Size.y - 1.0f },
		{ pos.x + Size.x, pos.y },
		{ pos.x + width + 11.0f, pos.y },
	};

	if (RightToLeft)
	{
		box[0].x = pos.x + Size.x - width - 11.0f;
		box[5].x = pos.x + Size.x - 7.0f;
	}

	pRenderer->Draw(box, 6, 1.0f, CSystemColors::GroupBoxBorder);

	rect.left = (LONG)(box[0].x + 4.0f);
	rect.top = (LONG)pos.y - Font->Desc.Height / 2;
	rect.right = (LONG)(rect.left + width);
	rect.bottom = (LONG)(rect.right + height);

	pRenderer->DrawText(Font, 0, 0, &rect, dwFormat, ForeColor, Text.c_str());

	// child controls
	for (auto& c : Controls->Collection)
	{
		c->DoEvents();
		c->Render(pRenderer);
	}
}
#include "RadioButton.h"

Sphinx::Forms::CRadioButton::CRadioButton() : 
CheckAlign(ContentAlignment::MiddleLeft),
Checked(false)
{
	Size = D3DXVECTOR2(104.0f, 24.0f);
}

void Sphinx::Forms::CRadioButton::Render(CRenderer* pRenderer)
{
	if (Parent == NULL || !Visible)
		return;

	RECT rect;
	D3DXVECTOR2 pos = GetAbsolutePos();

	//pRenderer->DrawBorder(pos.x, pos.y, Size.x, Size.y, CSystemColors::CheckBoxBorder);

	pRenderer->CalcTextRect(Font, &rect, (DWORD)CheckAlign, Text.c_str());

	Size.x = (float)(rect.right - rect.left + 20);
	Size.y = (float)(rect.bottom - rect.top + 3);

	rect.left = (LONG)pos.x;
	rect.top = (LONG)pos.y;
	rect.right = (LONG)(pos.x + Size.x);
	rect.bottom = (LONG)(pos.y + Size.y);

	switch (CheckAlign)
	{
	case ContentAlignment::TopLeft:
		rect.left += 16;
		break;
	case ContentAlignment::TopCenter:
		pos.x += (Size.x / 2.0f - 6.0f);
		break;
	case ContentAlignment::TopRight:
		pos.x += (Size.x - 12.0f);
		rect.right -= 16;
		break;
	case ContentAlignment::MiddleLeft:
		pos.y += (Size.y / 2.0f - 6.0f);
		rect.left += 16;
		break;
	case ContentAlignment::MiddleCenter:
		pos.x += (Size.x / 2.0f - 6.0f);
		pos.y += (Size.y / 2.0f - 6.0f);
		break;
	case ContentAlignment::MiddleRight:
		pos.x += (Size.x - 12.0f);
		pos.y += (Size.y / 2.0f - 6.0f);
		rect.right -= 16;
		break;
	case ContentAlignment::BottomLeft:
		pos.y += (Size.y - 12.0f);
		rect.left += 16;
		break;
	case ContentAlignment::BottomCenter:
		pos.x += (Size.x / 2.0f - 6.0f);
		pos.y += (Size.y - 12.0f);
		break;
	case ContentAlignment::BottomRight:
		pos.x += (Size.x - 12.0f);
		pos.y += (Size.y - 12.0f);
		rect.right -= 16;
		break;
	}

	/*
	pRenderer->DrawBorder((float)rect.left,
		(float)rect.top,
		(float)(rect.right - rect.left),
		(float)(rect.bottom - rect.top),
		CSystemColors::CheckBoxBorder);
	*/

	pRenderer->DrawFilledCircle(pos, 6.0f, 12, FALSE, CSystemColors::RadioButtonArea);
	pRenderer->DrawCircle(pos, 6.0f, 12, 0, 1.0f, FALSE, CSystemColors::RadioButtonBorder);
	pRenderer->DrawText(Font, (int)pos.x, (int)pos.y, &rect, (DWORD)CheckAlign, ForeColor, Text.c_str());

	if (Checked)
		pRenderer->DrawFilledCircle(D3DXVECTOR2(pos.x + 3.0f, pos.y + 3.0f), 3.0f, 5, FALSE, CSystemColors::RadioButtonCheck);
}
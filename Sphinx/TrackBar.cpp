#include "TrackBar.h"
#include "Form.h"

Sphinx::Forms::CTrackBar::CTrackBar() :
Orientation(Orientation::Horizontal),
LargeChange(5),
Maximum(10),
Minimum(0),
SmallChange(1),
Value(Minimum)
{
	if (Orientation == Orientation::Vertical)
		Size = D3DXVECTOR2(21.0f, 104.0f);
	else
		Size = D3DXVECTOR2(104.0f, 21.0f);
}

void Sphinx::Forms::CTrackBar::Render(CRenderer* pRenderer)
{
	if (Parent == NULL || !Visible)
		return;

	GetDIMPos(&MousePosition);

	D3DXVECTOR2 pos = GetAbsolutePos();

	if (bMouseDown && DIMPress(DIM_LEFT))
	{
		bMouseDown = true;

		int newValue;

		if (Orientation == Orientation::Vertical)
			newValue = (int)(Maximum + ((Minimum - Maximum) * ((MousePosition.y - pos.y) / Size.y)));
		else
			newValue = (int)(Minimum + ((Maximum - Minimum) * ((MousePosition.x - pos.x) / Size.x)));

		if (newValue < Minimum)
			newValue = Minimum;
		if (newValue > Maximum)
			newValue = Maximum;

		if (newValue != Value)
		{
			Value = newValue;
			ValueChanged(NULL);
		}
	}
	else
	{
		bMouseDown = false;
	}

	if (static_cast<CForm*>(TopLevelControl)->ActiveControl == this)
	{
		if (DIKPress(Orientation == Orientation::Vertical ? DIK_UP : DIK_RIGHT))
			Value += SmallChange;
		else if (DIKPress(Orientation == Orientation::Vertical ? DIK_DOWN : DIK_LEFT))
			Value -= SmallChange;
	}

	if (Value < Minimum)
		Value = Minimum;
	if (Value > Maximum)
		Value = Maximum;

	if (Orientation == Orientation::Vertical)
	{
		float x = pos.x + floor(Size.x / 2.0f) - 1.0f;

		pRenderer->DrawBorder(x, pos.y, 4.0f, Size.y, CSystemColors::TrackBarBorder);
		pRenderer->DrawFilledRect(x + 1.0f, pos.y + 1.0f, 2.0f, Size.y - 2.0f, CSystemColors::TrackBarArea);
		pRenderer->DrawFilledRect(pos.x, pos.y + 1.0f + ((Size.y - 12.0f) / (Minimum - Maximum) * (Value - Maximum)), Size.x, 10.0f, CSystemColors::TrackBarSlider);
	}
	else
	{
		float y = pos.y + floor(Size.y / 2.0f) - 1.0f;

		pRenderer->DrawBorder(pos.x, y, Size.x, 4.0f, CSystemColors::TrackBarBorder);
		pRenderer->DrawFilledRect(pos.x + 1.0f, y + 1.0f, Size.x - 2.0f, 2.0f, CSystemColors::TrackBarArea);
		pRenderer->DrawFilledRect(pos.x + 1.0f + ((Size.x - 12.0f) / (Maximum - Minimum) * (Value - Minimum)), pos.y, 10.0f, Size.y, CSystemColors::TrackBarSlider);
	}
}
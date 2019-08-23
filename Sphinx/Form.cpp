#include "Form.h"

Sphinx::Forms::CForm::CForm() :
FormBorderStyle(FormBorderStyle::Sizable),
StartPosition(FormStartPosition::DefaultLocation),
WindowState(FormWindowState::Normal),
AcceptButton(NULL),
CancelButton(NULL),
Owner(NULL),
ActiveControl(NULL),
ActiveForm(NULL),
ControlBox(true),
MaximizeBox(true),
MinimizeBox(true),
Opacity(100.0),
ShowIcon(true),
TopLevel(true),
TopMost(false)
{
	TopLevelControl = static_cast<CControl*>(this);
	Size = D3DXVECTOR2(300.0f, 300.0f);
}

void Sphinx::Forms::CForm::Render(CRenderer* pRenderer)
{
	if (!Visible)
		return;

	GetDIMPos(&MousePosition);

	if (ControlBox)
	{
		MouseOverCaption = (MousePosition.x > Location.x &&
			MousePosition.y > Location.y &&
			MousePosition.x < Location.x + Size.x - 44.0f &&
			MousePosition.y < Location.y + 23.0f);

		MouseOverControlBox =
			(MousePosition.x > Location.x + Size.x - (MaximizeBox || MinimizeBox ? 134.0f : 44.0f) &&
			MousePosition.y > Location.y + 1.0f &&
			MousePosition.x < Location.x + Size.x - 1.0f &&
			MousePosition.y < Location.y + 23.0f);

		MouseOverClose = (MouseOverControlBox &&
			MousePosition.x > Location.x + Size.x - 44.0f &&
			MousePosition.x < Location.x + Size.x - 1.0f);

		if (MaximizeBox || MinimizeBox)
		{
			MouseOverCaption &= (MousePosition.x < Location.x + Size.x - 134.0f);

			MouseOverMax = (MouseOverControlBox &&
				MousePosition.x > Location.x + Size.x - 89.0f &&
				MousePosition.x < Location.x + Size.x - 46.0f);

			MouseOverMin = (MouseOverControlBox &&
				MousePosition.x > Location.x + Size.x - 134.0f &&
				MousePosition.x < Location.x + Size.x - 91.0f);
		}
	}

	if (DIMDown(DIM_LEFT))
	{
		if (MouseOverCaption)
		{
			MouseDownCaption = true;
			MousePositionCaption.x = MousePosition.x - (LONG)Location.x;
			MousePositionCaption.y = MousePosition.y - (LONG)Location.y;
		}

		if (MouseOver())
			ActiveForm = this;
		else
			ActiveForm = NULL;
	}

	if (MouseDownCaption && DIMPress(DIM_LEFT))
	{
		Location.x = (FLOAT)(MousePosition.x - MousePositionCaption.x);
		Location.y = (FLOAT)(MousePosition.y - MousePositionCaption.y);
	}
	else
	{
		MouseDownCaption = false;
	}

	// client area
	pRenderer->DrawFilledRect(Location.x + 1.0f, Location.y + 22.0f, Size.x - 2.0f, Size.y - 23.0f, BackColor);

	// child controls
	for (auto& c : Controls->Collection)
	{
		c->DoEvents();
		c->Render(pRenderer);
	}

	// border
	pRenderer->DrawBorder(Location.x, Location.y, Size.x, Size.y, CSystemColors::WindowFrame);

	// caption bar
	pRenderer->DrawFilledRect(Location.x + 1.0f, Location.y + 1.0f, Size.x - 2.0f, 22.0f,
		ActiveForm == this ? CSystemColors::ActiveCaption : CSystemColors::InactiveCaption);

	// caption
	pRenderer->DrawText(Font, (int)Location.x + 14, (int)Location.y + 12, NULL, DT_VCENTER | DT_NOCLIP,
		ActiveForm == this ? CSystemColors::ActiveCaptionText : CSystemColors::InactiveCaptionText, Text.c_str());

	if (ControlBox)
	{
		if (MaximizeBox || MinimizeBox)
		{
			if (MouseOverMax)
				pRenderer->DrawFilledRect(Location.x + Size.x - 89.0f, Location.y + 1.0f, 44.0f, 21.0f, D3DCOLOR_XRGB(229, 229, 229));

			pRenderer->DrawBorder(Location.x + Size.x - 72.0f, Location.y + 7.0f,
				10.0f, 10.0f, ActiveForm == this && MaximizeBox ? ForeColor : D3DCOLOR_XRGB(153, 153, 153));

			if (MouseOverMin)
				pRenderer->DrawFilledRect(Location.x + Size.x - 134.0f, Location.y + 1.0f, 44.0f, 21.0f, D3DCOLOR_XRGB(229, 229, 229));

			pRenderer->DrawLine(D3DXVECTOR2(Location.x + Size.x - 117.0f, Location.y + 11.0f),
				D3DXVECTOR2(Location.x + Size.x - 107.0f, Location.y + 11.0f),
				1.0f, ActiveForm == this && MinimizeBox ? ForeColor : D3DCOLOR_XRGB(153, 153, 153));
		}

		if (MouseOverClose)
			pRenderer->DrawFilledRect(Location.x + Size.x - 44.0f, Location.y + 1.0f, 44.0f, 21.0f, CSystemColors::ControlBoxClose);

		pRenderer->DrawLine(D3DXVECTOR2(Location.x + Size.x - 27.0f, Location.y + 6.0f),
			D3DXVECTOR2(Location.x + Size.x - 18.0f, Location.y + 15.0f),
			1.0f, ActiveForm == this ? MouseOverClose ? WHITE(255) : ForeColor : D3DCOLOR_XRGB(153, 153, 153));
		pRenderer->DrawLine(D3DXVECTOR2(Location.x + Size.x - 27.0f, Location.y + 15.0f),
			D3DXVECTOR2(Location.x + Size.x - 18.0f, Location.y + 6.0f),
			1.0f, ActiveForm == this ? MouseOverClose ? WHITE(255) : ForeColor : D3DCOLOR_XRGB(153, 153, 153));
	}
}

void Sphinx::Forms::CForm::AddOwnedForm(CForm* ownedForm)
{
	OwnedForms.push_back(ownedForm);
}

void Sphinx::Forms::CForm::RemoveOwnedForm(CForm* ownedForm)
{
	int i = 0, size = OwnedForms.size();

	for (; i < size; i++)
	{
		if (OwnedForms[i] == ownedForm)
		{
			OwnedForms.erase(OwnedForms.begin() + i);
			break;
		}
	}
}
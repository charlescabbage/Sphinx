#include "Control.h"
#include "CheckBox.h"
#include "Form.h"
#include "RadioButton.h"
#include "TabPage.h"

Sphinx::Forms::CControl::CControl() :
Controls(new CControlCollection(this)),
TopLevelControl(NULL),
Parent(NULL),
BackColor(CSystemColors::Control),
Font(new CFont("Microsoft Sans Serif", 15, FW_NORMAL, FALSE)),
ForeColor(CSystemColors::ControlText),
RightToLeft(false),
Enabled(true),
Visible(true),
Location({ 0.0f, 0.0f }),
MaximumSize({ 0.0f, 0.0f }),
MinimumSize({ 0.0f, 0.0f }),
Padding({ 0, 0, 0, 0 }),
MouseButtons(MouseButtons::None),
MousePosition({ 0, 0 })
{
}

Sphinx::Forms::CControl::~CControl()
{
	delete Controls;
	delete Font;
}

bool Sphinx::Forms::CControl::MouseOver()
{
	D3DXVECTOR2 pos = GetAbsolutePos();

	int x = (int)pos.x;
	int y = (int)pos.y;
	int w = x + (int)Size.x;
	int h = y + (int)Size.y;

	return (MousePosition.x > x && MousePosition.y > y && MousePosition.x < w && MousePosition.y < h);
}

D3DXVECTOR2 Sphinx::Forms::CControl::GetAbsolutePos()
{
	D3DXVECTOR2 pos = Location;
	CControl* control = Parent;

	if (control)
	{
		while (control)
		{
			if (CControl* tab = dynamic_cast<CTabPage*>(control))
				pos += D3DXVECTOR2(1.0f, tab->Font->Desc.Height + 12.0f);

			pos += control->Location;

			control = control->Parent;
		}

		pos.x += 1.0f;
		pos.y += 23.0f;
	}

	return pos;
}

void Sphinx::Forms::CControl::BringToBack()
{
	if (!Parent)
		return;

	Parent->Controls->Remove(this);
	Parent->Controls->Insert(0, this);
}

void Sphinx::Forms::CControl::BringToFront()
{
	if (!Parent)
		return;

	Parent->Controls->Remove(this);
	Parent->Controls->Add(this);
}

void Sphinx::Forms::CControl::SetBounds(float x, float y, float width, float height)
{
	Location = D3DXVECTOR2(x, y);
	Size = D3DXVECTOR2(width, height);
}

void Sphinx::Forms::CControl::DoEvents()
{
	GetDIMPos(&MousePosition);

	if (!bMouseOver && MouseOver())
	{
		bMouseOver = true;
		MouseEnter(NULL);
	}
	else if (bMouseOver && !MouseOver())
	{
		bMouseOver = false;
		MouseLeave(NULL);
	}

	CControl*& control = static_cast<CForm*>(TopLevelControl)->ActiveControl;

	if (!bMouseDown && DIMDown(DIM_LEFT) && bMouseOver) // any button
	{
		if (DIMDown(DIM_LEFT) && control != this)
		{
			if (control)
				control->LeaveFocus(NULL);

			control = this;
			GotFocus(NULL);
		}

		bMouseDown = true;
		MouseDown(NULL);
	}

	if (bMouseDown && DIMUp(DIM_LEFT)) // any button
	{
		bMouseDown = false;
		MouseUp(NULL);

		if (bMouseOver)
		{
			MouseClick(NULL);

			if (DIMDoubleClick(DIM_LEFT)) // any button
			{
				MouseDoubleClick(NULL);
			}

			if (DIMUp(DIM_LEFT))
			{
				if (CCheckBox* checkBox = dynamic_cast<CCheckBox*>(this))
				{
					checkBox->Checked = !checkBox->Checked;
					checkBox->CheckChanged(NULL);
				}

				if (CRadioButton* radioButton = dynamic_cast<CRadioButton*>(this))
				{
					for (auto& c : Parent->Controls->Collection)
					{
						CRadioButton* rb = dynamic_cast<CRadioButton*>(c);

						if (rb && rb->Checked)
						{
							rb->Checked = false;
							rb->CheckChanged(NULL);
							break;
						}
					}

					radioButton->Checked = true;
					radioButton->CheckChanged(NULL);
				}
			}
		}
	}

	/*
	if (control == this)
	{
	if (DIKDown())
	KeyDown(NULL);

	if (DIKPress())
	KeyPress(NULL);

	if (DIKUp())
	KeyUp(NULL);
	}
	*/
}

Sphinx::Forms::CControl::CControlCollection::CControlCollection(CControl* owner) : Owner(owner)
{
}

void UpdateTopLevelControl(Sphinx::Forms::CControl* control, Sphinx::Forms::CControl* toplevel)
{
	for (auto& c : control->Controls->Collection)
	{
		c->TopLevelControl = toplevel;
		UpdateTopLevelControl(c, toplevel);
	}
}

void Sphinx::Forms::CControl::CControlCollection::Add(Sphinx::Forms::CControl* control)
{
	Collection.push_back(control);
	control->Parent = Owner;

	CControl* toplevel = control->Parent;

	while (toplevel->Parent)
		toplevel = toplevel->Parent;

	control->TopLevelControl = toplevel;

	UpdateTopLevelControl(control, toplevel);
}

Sphinx::Forms::CControl* Sphinx::Forms::CControl::CControlCollection::At(int index)
{
	return Collection.at(index);
}

void Sphinx::Forms::CControl::CControlCollection::Clear()
{
	Collection.clear();
}

bool Sphinx::Forms::CControl::CControlCollection::Contains(Sphinx::Forms::CControl* control)
{
	if (IndexOf(control) >= 0)
		return true;

	return false;
}

int Sphinx::Forms::CControl::CControlCollection::Count()
{
	return Collection.size();
}

int Sphinx::Forms::CControl::CControlCollection::IndexOf(Sphinx::Forms::CControl* control)
{
	int i = 0, size = Collection.size();

	for (; i < size; i++)
	{
		if (Collection[i] == control)
			return i;
	}

	return -1;
}

void Sphinx::Forms::CControl::CControlCollection::Insert(int index, Sphinx::Forms::CControl* control)
{
	Collection.insert(Collection.begin() + index, control);
}

void Sphinx::Forms::CControl::CControlCollection::Remove(Sphinx::Forms::CControl* control)
{
	RemoveAt(IndexOf(control));
}

void Sphinx::Forms::CControl::CControlCollection::RemoveAt(int index)
{
	Collection.erase(Collection.begin() + index);
}
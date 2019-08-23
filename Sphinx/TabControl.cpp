#include "TabControl.h"

Sphinx::Forms::CTabControl::CTabControl() : SelectedIndex(0)
{
	BackColor = CSystemColors::Window;
	Size = D3DXVECTOR2(200.0f, 100.0f);
}

void Sphinx::Forms::CTabControl::Render(CRenderer* pRenderer)
{
	if (Parent == NULL || !Visible)
		return;

	D3DXVECTOR2 pos = GetAbsolutePos();
	int nTabPages = Controls->Count();

	if (nTabPages > 0)
	{
		int tabIndex = 0;
		float xTabPage = 0.0f;
		float xBound = pos.x + Size.x;

		for (auto& c : Controls->Collection) // Draw each tab
		{
			RECT rect;
			float width;
			float height;

			// Calculate the rectangle
			pRenderer->CalcTextRect(Font, &rect, DT_VCENTER, c->Text.c_str());

			width = (float)(rect.right - rect.left) + 15.0f;
			height = (float)(rect.bottom - rect.top) + 8.0f;

			if (DIMDown(DIM_LEFT))
			{
				if (MousePosition.x > pos.x + xTabPage &&
					MousePosition.y > pos.y &&
					MousePosition.x < pos.x + width + xTabPage + 2.0f &&
					MousePosition.y < pos.y + height + 3.0f)
				{
					SelectedIndex = tabIndex;
				}
			}

			// Don't draw the tab if it exceeded the number of allowed tabs that would fit within the width of the TabControl
			if (pos.x + xTabPage + width > xBound)
				continue;

			// Raise the tab if it is selected otherwise lower it
			if (SelectedIndex == tabIndex)
			{
				pRenderer->DrawFilledRect(pos.x + xTabPage + 1.0f, pos.y + 1.0f, width, height + 3.0f, c->BackColor);
				pRenderer->DrawText(Font, (int)(pos.x + xTabPage) + 9, (int)(pos.y + (height + 3.0f) / 2.0f), NULL, DT_VCENTER | DT_NOCLIP, c->ForeColor, c->Text.c_str());

				D3DXVECTOR2 border[10] = {
					{ pos.x + xTabPage + width + 1.0f, pos.y + 1.0f },
					{ pos.x + xTabPage + width + 1.0f, pos.y },
					{ pos.x + xTabPage, pos.y },
					{ pos.x + xTabPage, pos.y + height + 3.0f },
					{ pos.x, pos.y + height + 3.0f },
					{ pos.x, pos.y + Size.y },
					{ pos.x + Size.x, pos.y + Size.y },
					{ pos.x + Size.x, pos.y + height + 3.0f },
					{ pos.x + xTabPage + width + 1.0f, pos.y + height + 3.0f },
					{ pos.x + xTabPage + width + 1.0f, pos.y + 2.0f }
				};

				pRenderer->Draw(border, tabIndex == nTabPages - 1 ? 10 : 9, 1.0f, CSystemColors::TabBorder);
				pRenderer->DrawFilledRect(pos.x + 1.0f, pos.y + height + 4.0f, Size.x - 1.0f, Size.y - height - 4.0f, c->BackColor);
			}
			else
			{
				pRenderer->DrawFilledRect(pos.x + xTabPage + 1.0f, pos.y + 3.0f, width, height, CSystemColors::Control);
				pRenderer->DrawText(Font, (int)(pos.x + xTabPage) + 9, (int)(pos.y + height / 2.0f) + 3, NULL, DT_VCENTER | DT_NOCLIP, c->ForeColor, c->Text.c_str());

				D3DXVECTOR2 border[4] = {
					{ pos.x + xTabPage, pos.y + height + 2.0f },
					{ pos.x + xTabPage, pos.y + 2.0f },
					{ pos.x + xTabPage + width, pos.y + 2.0f },
					{ pos.x + xTabPage + width, pos.y + height + 2.0f }
				};

				pRenderer->Draw(border, tabIndex == nTabPages - 1 ? 4 : 3, 1.0f, CSystemColors::TabBorder);
			}

			// Proceed to the next tab
			xTabPage += width + 1.0f;
			tabIndex++;
		}

		// Draw all the child controls within the tab page
		Controls->At(SelectedIndex)->Render(pRenderer);
	}
	else // Just draw an empty white rectangle if there are no tab pages
	{
		pRenderer->DrawBorder(pos.x, pos.y, Size.x, Size.y, CSystemColors::TabBorder);
		pRenderer->DrawFilledRect(pos.x + 1.0f, pos.y + 1.0f, Size.x - 2.0f, Size.y - 2.0f, BackColor);
	}
}
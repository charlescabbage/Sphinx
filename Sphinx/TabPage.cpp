#include "TabPage.h"

Sphinx::Forms::CTabPage::CTabPage()
{
	BackColor = CSystemColors::Window;
	Size = D3DXVECTOR2(200.0f, 100.0f);
}

void Sphinx::Forms::CTabPage::Render(CRenderer* pRenderer)
{
	if (Parent == NULL || !Visible)
		return;

	// child controls
	for (auto& c : Controls->Collection)
	{
		c->DoEvents();
		c->Render(pRenderer);
	}
}
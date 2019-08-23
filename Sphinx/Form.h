#ifndef FORM_H
#define FORM_H

#pragma once

#include "Control.h"
#include "Button.h"

namespace Sphinx
{
	namespace Forms
	{
		// Represents a window or dialog box that makes up an application's user interface.
		class CForm : public CControl
		{
		public:
			CForm();

			virtual void Render(CRenderer* pRenderer);
			virtual void AddOwnedForm(CForm* ownedForm);
			virtual void RemoveOwnedForm(CForm* ownedForm);

			FormBorderStyle FormBorderStyle;
			FormStartPosition StartPosition;
			FormWindowState WindowState;
			CButton* AcceptButton;
			CButton* CancelButton;
			std::vector<CForm*> OwnedForms;
			CControl* ActiveControl;
			CForm* ActiveForm;
			CForm* Owner;
			bool ControlBox;
			bool MaximizeBox;
			bool MinimizeBox;
			double Opacity;
			bool ShowIcon;
			bool TopLevel;
			bool TopMost;

		private:
			bool MouseOverMin;
			bool MouseOverMax;
			bool MouseOverClose;
			bool MouseOverControlBox;
			bool MouseOverCaption;
			bool MouseDownCaption;
			POINT MousePositionCaption;
		};
	}
}

#endif
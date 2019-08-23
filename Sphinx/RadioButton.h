#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#pragma once

#include "Control.h"

namespace Sphinx
{
	namespace Forms
	{
		// Enables the user to select a single option from a group of choices when paired with other RadioButton controls.
		class CRadioButton : public CControl
		{
		public:
			CRadioButton();

			virtual void Render(CRenderer* pRenderer);

			ContentAlignment CheckAlign;
			bool Checked;

			IEvent<void*> CheckChanged;
		};
	}
}

#endif
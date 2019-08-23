#ifndef CHECKBOX_H
#define CHECKBOX_H

#pragma once

#include "Control.h"

namespace Sphinx
{
	namespace Forms
	{
		// Represents a check box control.
		class CCheckBox : public CControl
		{
		public:
			CCheckBox();

			virtual void Render(CRenderer* pRenderer);

			ContentAlignment CheckAlign;
			bool Checked;

			IEvent<void*> CheckChanged;
		};
	}
}

#endif
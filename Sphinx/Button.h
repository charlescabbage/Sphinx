#ifndef BUTTON_H
#define BUTTON_H

#pragma once

#include "Control.h"

namespace Sphinx
{
	namespace Forms
	{
		// Represents a button control.
		class CButton : public CControl
		{
		public:
			CButton();

			virtual void Render(CRenderer* pRenderer);

			ContentAlignment TextAlign;
		};
	}
}

#endif
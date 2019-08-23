#ifndef GROUPBOX_H
#define GROUPBOX_H

#pragma once

#include "Control.h"

namespace Sphinx
{
	namespace Forms
	{
		// Represents a control that displays a frame around a group of controls with an optional caption.
		class CGroupBox : public CControl
		{
		public:
			CGroupBox();

			virtual void Render(CRenderer* pRenderer);
		};
	}
}

#endif
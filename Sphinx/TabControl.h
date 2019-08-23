#ifndef TABCONTROL_H
#define TABCONTROL_H

#pragma once

#include "Control.h"

namespace Sphinx
{
	namespace Forms
	{
		// Manages a related set of tab pages.
		class CTabControl : public CControl
		{
		public:
			CTabControl();

			virtual void Render(CRenderer* pRenderer);

			int SelectedIndex;
		};
	}
}

#endif
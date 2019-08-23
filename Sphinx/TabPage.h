#ifndef TABPAGE_H
#define TABPAGE_H

#pragma once

#include "Control.h"

namespace Sphinx
{
	namespace Forms
	{
		// Represents a single tab page in a TabControl.
		class CTabPage : public CControl
		{
		public:
			CTabPage();

			virtual void Render(CRenderer* pRenderer);
		};
	}
}

#endif
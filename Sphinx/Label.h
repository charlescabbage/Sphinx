#ifndef LABEL_H
#define LABEL_H

#pragma once

#include "Control.h"

namespace Sphinx
{
	namespace Forms
	{
		// Represents a standard label.
		class CLabel : public CControl
		{
		public:
			CLabel();

			virtual void Render(CRenderer* pRenderer);

			ContentAlignment TextAlign;
		};
	}
}

#endif
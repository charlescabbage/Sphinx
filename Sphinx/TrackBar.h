#ifndef TRACKBAR_H
#define TRACKBAR_H

#pragma once

#include "Control.h"

namespace Sphinx
{
	namespace Forms
	{
		// Represents a standard track bar.
		class CTrackBar : public CControl
		{
		public:
			CTrackBar();

			virtual void Render(CRenderer* pRenderer);

			IEvent<void*> ValueChanged;

			Orientation Orientation;
			int LargeChange; // on mouse click
			int Maximum;
			int Minimum;
			int SmallChange; // on arrow key press
			int Value;
		};
	}
}

#endif
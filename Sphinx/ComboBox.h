#ifndef COMBOBOX_H
#define COMBOBOX_H

#pragma once

#include "Control.h"

namespace Sphinx
{
	namespace Forms
	{
		// Represents a combo box control.
		class CComboBox : public CControl
		{
		public:
			CComboBox();

			ComboBoxStyle DropDownStyle;
		};
	}
}

#endif
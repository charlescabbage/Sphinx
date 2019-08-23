#ifndef CONTROL_H
#define CONTROL_H

#pragma once

#include "Drawing.h"
#include "Input.h"
#include "Events.h"

namespace Sphinx
{
	namespace Forms
	{
		// Specifies the ComboBox style.
		enum class ComboBoxStyle
		{
			Simple,
			DropDown,
			DropDownList
		};

		// Specifies alignment of content on the drawing surface.
		enum class ContentAlignment
		{
			TopLeft = DT_TOP | DT_LEFT,
			TopCenter = DT_TOP | DT_CENTER,
			TopRight = DT_TOP | DT_RIGHT,
			MiddleLeft = DT_VCENTER | DT_LEFT,
			MiddleCenter = DT_VCENTER | DT_CENTER,
			MiddleRight = DT_VCENTER | DT_RIGHT,
			BottomLeft = DT_BOTTOM | DT_LEFT,
			BottomCenter = DT_BOTTOM | DT_CENTER,
			BottomRight = DT_BOTTOM | DT_RIGHT
		};

		// Specifies the position and manner in which a control is docked.
		enum class DockStyle
		{
			None,
			Top,
			Bottom,
			Left,
			Right,
			Fill
		};

		// Specifies the border style for a form.
		enum class FormBorderStyle
		{
			None,
			FixedSingle,
			Fixed3D,
			FixedDialog,
			Sizable,
			FixedToolWindow,
			SizableToolWindow
		};

		// Specifies the initial position of a form.
		enum class FormStartPosition
		{
			Manual,
			CenterScreen,
			DefaultLocation,
			DefaultBounds,
			CenterParent
		};

		// Specifies how a form window is displayed.
		enum class FormWindowState
		{
			Normal,
			Minimized,
			Maximized
		};

		// Specifies constants that define which mouse button was pressed.
		enum class MouseButtons
		{
			None,
			Left,
			Right,
			Middle,
		};

		// Specifies the orientation of controls or elements of controls.
		enum class Orientation
		{
			Horizontal,
			Vertical
		};

		// Defines the base class for controls, which are components with visual representation.
		class CControl
		{
		public:
			// Represents a collection of Sphinx::Forms::Control objects.
			class CControlCollection;

		public:
			CControl();
			virtual ~CControl();

			virtual bool MouseOver();
			virtual D3DXVECTOR2 GetAbsolutePos();
			virtual void DoEvents();
			virtual void Render(CRenderer* pRenderer) {}
			virtual void BringToBack();
			virtual void BringToFront();
			virtual void SetBounds(float x, float y, float width, float height);

			CControlCollection* Controls;
			CControl* TopLevelControl;
			CControl* Parent;
			D3DCOLOR BackColor;
			CFont* Font;
			D3DCOLOR ForeColor;
			bool RightToLeft;
			std::string Text;
			bool Enabled;
			bool Visible;
			D3DXVECTOR2 Location;
			D3DXVECTOR2 MaximumSize;
			D3DXVECTOR2 MinimumSize;
			RECT Padding;
			D3DXVECTOR2 Size;
			MouseButtons MouseButtons;
			POINT MousePosition;

			IEvent<void*> GotFocus;
			IEvent<void*> LeaveFocus;
			IEvent<void*> MouseEnter;
			IEvent<void*> MouseLeave;
			IEvent<void*> MouseClick;
			IEvent<void*> MouseDoubleClick;
			IEvent<void*> MouseDown;
			IEvent<void*> MouseUp;
			IEvent<void*> KeyDown;
			IEvent<void*> KeyPress;
			IEvent<void*> KeyUp;

		protected:
			bool bMouseOver;
			bool bMouseDown;
		};

		class CControl::CControlCollection
		{
		public:
			CControlCollection(CControl* owner);

			void Add(CControl* control);
			CControl* At(int index);
			void Clear();
			bool Contains(CControl* control);
			int Count();
			int IndexOf(CControl* control);
			void Insert(int index, CControl* control);
			void Remove(CControl* control);
			void RemoveAt(int index);

			CControl* const Owner;
			std::vector<CControl*> Collection;
		};
	}
}

#endif
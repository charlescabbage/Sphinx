#ifndef INPUT_H
#define INPUT_H

#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <Windows.h>
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

typedef struct _BUTTONDATA
{
	bool down;
	bool press;
	bool up;
	bool doubleClick;
	DWORD dwTime;

} BUTTONDATA, *LPBUTTONDATA;

typedef struct _DIKEYBOARD
{
	BYTE state[256];
	BUTTONDATA buttons[256];

} DIKEYBOARD, *LPDIKEYBOARD;

typedef struct _DIMOUSE
{
	POINT cursor;
	DIMOUSESTATE state;
	BUTTONDATA buttons[4];

} DIMOUSE, *LPDIMOUSE;

#define DIM_LEFT	0
#define DIM_RIGHT	1
#define DIM_MIDDLE	2

class CInput
{
public:
	static CInput* Instance();

	BOOL IsInitialized();

	HRESULT Initialize(HWND hWnd);
	void Shutdown();

	HRESULT UpdateKeyboard();
	HRESULT UpdateMouse();

	bool _DIKDown(int dKey);
	bool _DIKPress(int dKey);
	bool _DIKUp(int dKey);

	bool _DIMDown(int dKey);
	bool _DIMPress(int dKey);
	bool _DIMUp(int dKey);
	bool _DIMDoubleClick(int dKey);
	void _GetDIMPos(LPPOINT lpPoint);

private:
	CInput() {};
	CInput(const CInput&) {};
	CInput& operator = (const CInput&) {};
	static CInput* m_pInstance;

	HWND m_hWnd;

	LPDIRECTINPUT8 m_pDI;
	LPDIRECTINPUTDEVICE8 m_pMouse;
	LPDIRECTINPUTDEVICE8 m_pKeyboard;

	DIKEYBOARD m_Keyboard;
	DIMOUSE m_Mouse;

	bool m_KeyDown;
	bool m_KeyPress;
	bool m_KeyUp;
	bool m_MouseDown;
	bool m_MousePress;
	bool m_MouseUp;
	bool m_MouseDoubleClick;
};

#define DIKDown(dKey)			CInput::Instance()->_DIKDown(dKey)
#define DIKPress(dKey)			CInput::Instance()->_DIKPress(dKey)
#define DIKUp(dKey)				CInput::Instance()->_DIKUp(dKey)

#define DIMDown(dKey)			CInput::Instance()->_DIMDown(dKey)
#define DIMPress(dKey)			CInput::Instance()->_DIMPress(dKey)
#define DIMUp(dKey)				CInput::Instance()->_DIMUp(dKey)
#define DIMDoubleClick(dKey)	CInput::Instance()->_DIMDoubleClick(dKey)
#define GetDIMPos(lpPoint)		CInput::Instance()->_GetDIMPos(lpPoint)

#endif
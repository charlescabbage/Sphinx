#include "Input.h"

CInput* CInput::m_pInstance = NULL;

CInput* CInput::Instance()
{
	if (!m_pInstance)
		m_pInstance = new CInput();

	return m_pInstance;
}

BOOL CInput::IsInitialized()
{
	if (m_hWnd)
		return true;

	return false;
}

HRESULT CInput::Initialize(HWND hWnd)
{
	HRESULT hr;

	m_hWnd = hWnd;

	// create the direct input object
	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL);
	if (FAILED(hr))
		return hr;

	// create mouse
	hr = m_pDI->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
	if (FAILED(hr))
		return hr;

	hr = m_pMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
		return hr;

	hr = m_pMouse->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
		return hr;

	hr = m_pMouse->Acquire();
	if (FAILED(hr))
		return hr;

	// create keyboard
	hr = m_pDI->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
	if (FAILED(hr))
		return hr;

	hr = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
		return hr;

	hr = m_pKeyboard->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
		return hr;

	hr = m_pKeyboard->Acquire();
	if (FAILED(hr))
		return hr;

	return S_OK;
}

void CInput::Shutdown()
{
	if (m_pDI)
	{
		if (m_pMouse)
		{
			try
			{
				m_pMouse->Unacquire();
				m_pMouse->Release();
				m_pMouse = NULL;
			}
			catch (...) {}
		}

		if (m_pKeyboard)
		{
			try
			{
				m_pKeyboard->Unacquire();
				m_pKeyboard->Release();
				m_pKeyboard = NULL;
			}
			catch (...) {}
		}

		try
		{
			m_pDI->Release();
			m_pDI = NULL;
		}
		catch (...) {}
	}
}

HRESULT CInput::UpdateKeyboard()
{
	HRESULT hr;

	hr = m_pKeyboard->GetDeviceState((sizeof(BYTE) << 8), &m_Keyboard.state);
	if (FAILED(hr))
	{
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
			m_pKeyboard->Acquire();
		else
			return hr;
	}

	for (int i = 0; i < 256; i++)
	{
		m_Keyboard.buttons[i].down = false;
		m_Keyboard.buttons[i].up = false;

		if (m_Keyboard.state[i] && !m_Keyboard.buttons[i].press)
		{
			m_Keyboard.buttons[i].down = true;
			m_Keyboard.buttons[i].press = true;
			m_KeyDown = true;
			m_KeyPress = true;
		}

		if (!m_Keyboard.state[i] && m_Keyboard.buttons[i].press)
		{
			m_Keyboard.buttons[i].up = true;
			m_Keyboard.buttons[i].press = false;
			m_KeyUp = true;
		}
	}

	return S_OK;
}

HRESULT CInput::UpdateMouse()
{
	RECT rect;
	POINT cursor;
	HRESULT hr;

	hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_Mouse.state);
	if (FAILED(hr))
	{
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
			m_pMouse->Acquire();
		else
			return hr;
	}

	GetCursorPos(&cursor);
	ScreenToClient(m_hWnd, &cursor);
	GetClientRect(m_hWnd, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	if (cursor.x < 0)
		cursor.x = 0;
	if (cursor.y < 0)
		cursor.y = 0;
	if (cursor.x > width)
		cursor.x = width;
	if (cursor.y > height)
		cursor.y = height;

	m_Mouse.cursor = cursor;

	DWORD dwTime = timeGetTime();

	m_MouseDown = false;
	m_MousePress = false;
	m_MouseUp = false;
	m_MouseDoubleClick = false;

	for (int i = 0; i < 4; i++)
	{
		m_Mouse.buttons[i].down = false;
		m_Mouse.buttons[i].up = false;

		if (m_Mouse.state.rgbButtons[i] && !m_Mouse.buttons[i].press)
		{
			m_Mouse.buttons[i].down = true;
			m_Mouse.buttons[i].press = true;
			m_MouseDown = true;
			m_MousePress = true;
		}

		if (!m_Mouse.state.rgbButtons[i] && m_Mouse.buttons[i].press)
		{
			m_Mouse.buttons[i].up = true;
			m_Mouse.buttons[i].press = false;
			m_MouseUp = true;

			if (!m_Mouse.buttons[i].doubleClick && (dwTime - m_Mouse.buttons[i].dwTime) <= GetDoubleClickTime())
			{
				m_Mouse.buttons[i].doubleClick = true;
				m_MouseDoubleClick = true;
			}
			else
			{
				m_Mouse.buttons[i].doubleClick = false;
			}

			m_Mouse.buttons[i].dwTime = dwTime;
		}
	}

	return S_OK;
}

bool CInput::_DIKDown(int dKey)
{
	return m_Keyboard.buttons[dKey].down;
}

bool CInput::_DIKPress(int dKey)
{
	return m_Keyboard.buttons[dKey].press;
}

bool CInput::_DIKUp(int dKey)
{
	return m_Keyboard.buttons[dKey].up;
}

bool CInput::_DIMDown(int dKey)
{
	return m_Mouse.buttons[dKey].down;
}

bool CInput::_DIMPress(int dKey)
{
	return m_Mouse.buttons[dKey].press;
}

bool CInput::_DIMUp(int dKey)
{
	return m_Mouse.buttons[dKey].up;
}

bool CInput::_DIMDoubleClick(int dKey)
{
	return m_Mouse.buttons[dKey].doubleClick;
}

void CInput::_GetDIMPos(LPPOINT lpPoint)
{
	*lpPoint = m_Mouse.cursor;
}
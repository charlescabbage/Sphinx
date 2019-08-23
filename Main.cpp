#include "MyForm.h"

#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib,"winmm.lib")

using namespace Project1;

LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;
CRenderer* pRenderer;
CFont* pFont;
MyForm* pMyForm;

DWORD dwFrames;
DWORD dwCurrentTime;
DWORD dwLastUpdateTime;
DWORD dwElapsedTime;
TCHAR szFPS[32];
TCHAR szActiveControl[32];

// this is the function used to render a single frame
void render_frame()
{
	dwFrames++;
	dwCurrentTime = timeGetTime();
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 1000)
	{
		sprintf_s(szFPS, "FPS : %u", (UINT)(dwFrames * 1000.0 / dwElapsedTime));
		dwFrames = 0;
		dwLastUpdateTime = dwCurrentTime;
	}

	CControl::CControlCollection* controls = pMyForm->Controls->At(0)->Controls->At(0)->Controls->At(1)->Controls;

	CTrackBar* trackBar1 = static_cast<CTrackBar*>(controls->At(0));
	CTrackBar* trackBar2 = static_cast<CTrackBar*>(controls->At(1));
	CTrackBar* trackBar3 = static_cast<CTrackBar*>(controls->At(2));

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(trackBar1->Value, trackBar2->Value, trackBar3->Value), 1.0f, 0);
	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(trackBar1->Value, trackBar2->Value, trackBar3->Value), 1.0f, 0);

	d3ddev->BeginScene();

	pRenderer->Create(d3ddev);
	pRenderer->Begin();

	pMyForm->Render(pRenderer);

	pRenderer->DrawText(pFont, 10, 10, NULL, NULL, YELLOW(255), szFPS);

	POINT point;
	GetDIMPos(&point);

	pRenderer->DrawText(pFont, 10, 30, NULL, NULL, YELLOW(255), "CursorPos : {X=%d,Y=%d}", point.x, point.y);

	if (pMyForm->ActiveControl)
		sprintf_s(szActiveControl, pMyForm->ActiveControl->Text.c_str());
	else
		sprintf_s(szActiveControl, "NULL");

	pRenderer->DrawText(pFont, 10, 50, NULL, NULL, YELLOW(255), "ActiveControl : %s", szActiveControl);

	pRenderer->DrawText(pFont, 10, 70, NULL, NULL, YELLOW(255), "trackBar->Value : %d, %d, %d", trackBar1->Value, trackBar2->Value, trackBar3->Value);

	pRenderer->End();
	pRenderer->Release();

	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

// this function initializes and prepares Direct3D for use
void initD3D(HWND hwnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	RECT rect;
	GetClientRect(hwnd, &rect);

	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = rect.right - rect.left;
	d3dpp.BackBufferHeight = rect.bottom - rect.top;
	d3dpp.EnableAutoDepthStencil = true;        // Manage SetDepthStencil for us
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// 16-bit pixel format for the z-buffer

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

	d3ddev->SetRenderState(D3DRS_LIGHTING, false);    		// turn off the 3D lighting
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// both sides of the triangles
	d3ddev->SetRenderState(D3DRS_ZENABLE, true);			// turn on the z-buffer
}

// this is the function that cleans up Direct3D and COM
void cleanD3D()
{
	d3ddev->Release();		// close and release the 3D device
	d3d->Release();			// close and release Direct3D
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd;
	WNDCLASSEX wc;
	MSG msg;

	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszClassName = "WindowClass";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(0, "WindowClass", "Sphinx GUI", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 600, NULL, NULL, hInstance, NULL);

	// set up and initialize Direct3D
	initD3D(hwnd);

	CInput::Instance()->Initialize(hwnd);

	pRenderer = new CRenderer();
	pMyForm = new MyForm(pRenderer);
	pFont = new CFont("Microsoft Sans Serift", 15, FW_BOLD, FALSE);
	pRenderer->AddFont(pFont);

	// enter the main loop
	do {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		CInput::Instance()->UpdateMouse();
		CInput::Instance()->UpdateKeyboard();

		render_frame();

	} while (msg.message != WM_QUIT);

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}
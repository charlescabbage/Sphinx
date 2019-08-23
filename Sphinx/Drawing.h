#ifndef DRAWING_H
#define DRAWING_H

#pragma once

#include <Windows.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <d3dx9.h>

#pragma comment(lib, "d3dx9.lib")

// Classes declared in this file

class CFont;
class CRenderer;
class CSystemColors;

typedef struct _CUSTOMVERTEX
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
	FLOAT rhw;
	D3DCOLOR color;

} CUSTOMVERTEX, *LPCUSTOMVERTEX;

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	VOID AddFont(CFont* pFont);
	VOID RemoveFont(CFont* pFont);
	VOID RemoveFontAt(INT index);
	VOID ClearFonts();

	VOID Create(LPDIRECT3DDEVICE9 pDevice);

	VOID Begin();
	VOID End();

	VOID OnLostDevice();
	VOID OnResetDevice();

	VOID GetDevice(LPDIRECT3DDEVICE9 pDevice) { pDevice = m_pDevice; }
	VOID GetViewport(D3DVIEWPORT9* pViewport) { *pViewport = m_Viewport; }

	VOID Draw(CONST D3DXVECTOR2* pVertexList, DWORD dwVertexListCount, FLOAT Width, D3DCOLOR Color);
	VOID DrawLine(D3DXVECTOR2 Start, D3DXVECTOR2 End, FLOAT Width, D3DCOLOR Color);
	VOID DrawBorder(FLOAT x, FLOAT y, FLOAT Width, FLOAT Height, D3DCOLOR Color);
	VOID DrawRect(FLOAT x, FLOAT y, FLOAT Width, FLOAT Height, FLOAT Thickness, D3DCOLOR Color);
	VOID DrawFilledRect(FLOAT x, FLOAT y, FLOAT Width, FLOAT Height, D3DCOLOR Color);
	VOID DrawCircle(D3DXVECTOR2 Location, FLOAT Radius, INT Sides, INT Spaces, FLOAT Width, BOOL Center, D3DCOLOR Color);
	VOID DrawFilledCircle(D3DXVECTOR2 Location, FLOAT Radius, INT Sides, BOOL Center, D3DCOLOR Color);
	INT DrawText(CFont* pFont, INT x, INT y, LPRECT pRect, DWORD Format, D3DCOLOR Color, LPCSTR pText, ...);

	INT CalcTextRect(CFont* pFont, LPRECT pRect, DWORD Format, LPCSTR pText, ...);

	VOID Release();

private:
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXLINE m_pLine;
	std::vector<CFont*> m_Fonts;

	LPDIRECT3DPIXELSHADER9 m_pShader;
	DWORD m_CullMode;
	DWORD m_AlphaBlend;
	DWORD m_SrcBlend;
	DWORD m_DestBlend;
	DWORD m_FVF;

	D3DVIEWPORT9 m_Viewport;
};

// Defines a particular format for text, including font face, size, and style attributes.
class CFont
{
public:
	CFont(LPCSTR pFaceName, INT Height, UINT Weight, BOOL Italic);
	~CFont();

	BOOL Created();
	HRESULT Create(LPDIRECT3DDEVICE9 pDevice);
	HRESULT OnLostDevice();
	HRESULT OnResetDevice();
	VOID Release();

	D3DXFONT_DESC Desc;
	LPD3DXFONT pFont;
};

// Basic colors

#define BLACK(a)	D3DCOLOR_ARGB(a, 0, 0, 0)
#define WHITE(a)	D3DCOLOR_ARGB(a, 255, 255, 255)
#define RED(a)		D3DCOLOR_ARGB(a, 255, 0, 0)
#define LIME(a)		D3DCOLOR_ARGB(a, 0, 255, 0)
#define BLUE(a)		D3DCOLOR_ARGB(a, 0, 0, 255)
#define YELLOW(a)	D3DCOLOR_ARGB(a, 255, 255, 0)
#define CYAN(a)		D3DCOLOR_ARGB(a, 0, 255, 255)
#define MAGENTA(a)	D3DCOLOR_ARGB(a, 255, 0, 255)
#define SILVER(a)	D3DCOLOR_ARGB(a, 192, 192, 192)
#define GRAY(a)		D3DCOLOR_ARGB(a, 128, 128, 128)
#define MAROON(a)	D3DCOLOR_ARGB(a, 128, 0, 0)
#define OLIVE(a)	D3DCOLOR_ARGB(a, 128, 128, 0)
#define GREEN(a)	D3DCOLOR_ARGB(a, 0, 128, 0)
#define PURPLE(a)	D3DCOLOR_ARGB(a, 128, 0, 128)
#define TEAL(a)		D3DCOLOR_ARGB(a, 0, 128, 128)
#define NAVY(a)		D3DCOLOR_ARGB(a, 0, 0, 128)

// Each property of the SystemColors class is a D3DCOLOR that is the color of a display element.
class CSystemColors
{
public:
	static CONST D3DCOLOR ActiveBorder = D3DCOLOR_XRGB(180, 180, 180);
	static CONST D3DCOLOR ActiveCaption = D3DCOLOR_XRGB(255, 255, 255);
	static CONST D3DCOLOR ActiveCaptionText = D3DCOLOR_XRGB(0, 0, 0);
	static CONST D3DCOLOR AppWorkSpace = D3DCOLOR_XRGB(171, 171, 171);
	static CONST D3DCOLOR ButtonBorder = D3DCOLOR_XRGB(173, 173, 173);
	static CONST D3DCOLOR ButtonFace = D3DCOLOR_XRGB(225, 225, 225);
	static CONST D3DCOLOR CheckBoxArea = D3DCOLOR_XRGB(255, 255, 255);
	static CONST D3DCOLOR CheckBoxBorder = D3DCOLOR_XRGB(51, 51, 51);
	static CONST D3DCOLOR CheckBoxCheck = D3DCOLOR_XRGB(51, 51, 51);
	static CONST D3DCOLOR ComboBoxBorder = D3DCOLOR_XRGB(173, 173, 173);
	static CONST D3DCOLOR Control = D3DCOLOR_XRGB(240, 240, 240);
	static CONST D3DCOLOR ControlBoxClose = D3DCOLOR_XRGB(232, 17, 35);
	static CONST D3DCOLOR ControlDark = D3DCOLOR_XRGB(160, 160, 160);
	static CONST D3DCOLOR ControlDarkDark = D3DCOLOR_XRGB(105, 105, 105);
	static CONST D3DCOLOR ControlLight = D3DCOLOR_XRGB(227, 227, 227);
	static CONST D3DCOLOR ControlLightLight = D3DCOLOR_XRGB(255, 255, 255);
	static CONST D3DCOLOR ControlText = D3DCOLOR_XRGB(0, 0, 0);
	static CONST D3DCOLOR Desktop = D3DCOLOR_XRGB(0, 0, 0);
	static CONST D3DCOLOR GradientActiveCaption = D3DCOLOR_XRGB(185, 209, 234);
	static CONST D3DCOLOR GradientInactiveCaption = D3DCOLOR_XRGB(215, 228, 242);
	static CONST D3DCOLOR GrayText = D3DCOLOR_XRGB(109, 109, 109);
	static CONST D3DCOLOR GroupBoxBorder = D3DCOLOR_XRGB(220, 220, 220);
	static CONST D3DCOLOR HighLight = D3DCOLOR_XRGB(51, 153, 255);
	static CONST D3DCOLOR HighLightText = D3DCOLOR_XRGB(255, 255, 255);
	static CONST D3DCOLOR HotTrack = D3DCOLOR_XRGB(0, 102, 204);
	static CONST D3DCOLOR InactiveBorder = D3DCOLOR_XRGB(244, 247, 252);
	static CONST D3DCOLOR InactiveCaption = D3DCOLOR_XRGB(255, 255, 255);
	static CONST D3DCOLOR InactiveCaptionText = D3DCOLOR_XRGB(169, 169, 169);
	static CONST D3DCOLOR Info = D3DCOLOR_XRGB(255, 255, 225);
	static CONST D3DCOLOR InfoText = D3DCOLOR_XRGB(0, 0, 0);
	static CONST D3DCOLOR Menu = D3DCOLOR_XRGB(240, 240, 240);
	static CONST D3DCOLOR MenuBar = D3DCOLOR_XRGB(240, 240, 240);
	static CONST D3DCOLOR MenuText = D3DCOLOR_XRGB(0, 0, 0);
	static CONST D3DCOLOR RadioButtonArea = D3DCOLOR_XRGB(255, 255, 255);
	static CONST D3DCOLOR RadioButtonBorder = D3DCOLOR_XRGB(51, 51, 51);
	static CONST D3DCOLOR RadioButtonCheck = D3DCOLOR_XRGB(51, 51, 51);
	static CONST D3DCOLOR ScrollBar = D3DCOLOR_XRGB(200, 200, 200);
	static CONST D3DCOLOR TabBorder = D3DCOLOR_XRGB(217, 217, 217);
	static CONST D3DCOLOR TrackBarArea = D3DCOLOR_XRGB(231, 234, 234);
	static CONST D3DCOLOR TrackBarBorder = D3DCOLOR_XRGB(214, 214, 214);
	static CONST D3DCOLOR TrackBarSlider = D3DCOLOR_XRGB(0, 122, 217);
	static CONST D3DCOLOR Window = D3DCOLOR_XRGB(255, 255, 255);
	static CONST D3DCOLOR WindowFrame = D3DCOLOR_XRGB(24, 131, 215);
	static CONST D3DCOLOR WindowText = D3DCOLOR_XRGB(0, 0, 0);
};

#endif
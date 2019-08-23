#include "Drawing.h"

CFont::CFont(LPCSTR pFaceName, INT Height, UINT Weight, BOOL Italic) : pFont(NULL)
{
	Desc.Height = Height;
	Desc.Width = 0;
	Desc.Weight = Weight;
	Desc.MipLevels = 0;
	Desc.Italic = Italic;
	Desc.CharSet = DEFAULT_CHARSET;
	Desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	Desc.Quality = DEFAULT_QUALITY;
	Desc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	strcpy_s(Desc.FaceName, pFaceName);
}

CFont::~CFont()
{
	delete pFont;
}

HRESULT CFont::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return D3DXCreateFontIndirect(pDevice, &Desc, &pFont);
}

HRESULT CFont::OnLostDevice()
{
	return pFont->OnLostDevice();
}

HRESULT CFont::OnResetDevice()
{
	return pFont->OnResetDevice();
}

VOID CFont::Release()
{
	pFont->Release();
	pFont = NULL;
}

BOOL CFont::Created()
{
	if (!pFont)
		return FALSE;

	return TRUE;
}

CRenderer::CRenderer() : m_pDevice(NULL), m_pLine(NULL), m_pShader(NULL)
{
}

CRenderer::~CRenderer()
{
	ClearFonts();

	// This would mean deleting the game's device as well.
	// delete m_pDevice;

	delete m_pLine;
	delete m_pShader;
}

VOID CRenderer::AddFont(CFont* pFont)
{
	m_Fonts.push_back(pFont);
}

VOID CRenderer::RemoveFont(CFont* pFont)
{
	m_Fonts.erase(std::remove(m_Fonts.begin(), m_Fonts.end(), pFont), m_Fonts.end());
}

VOID CRenderer::RemoveFontAt(INT index)
{
	m_Fonts.erase(m_Fonts.begin() + index);
}

VOID CRenderer::ClearFonts()
{
	for (auto& f : m_Fonts)
		delete f;

	m_Fonts.clear();
}

VOID CRenderer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;

	m_pDevice->GetViewport(&m_Viewport);

	if (!m_pLine)
		D3DXCreateLine(m_pDevice, &m_pLine);

	for (auto& f : m_Fonts)
	{
		if (!f->Created())
			f->Create(m_pDevice);
	}
}

VOID CRenderer::Begin()
{
	m_pDevice->GetPixelShader(&m_pShader);
	m_pDevice->GetRenderState(D3DRS_CULLMODE, &m_CullMode);
	m_pDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &m_AlphaBlend);
	m_pDevice->GetRenderState(D3DRS_SRCBLEND, &m_SrcBlend);
	m_pDevice->GetRenderState(D3DRS_DESTBLEND, &m_DestBlend);
	m_pDevice->GetFVF(&m_FVF);

	m_pDevice->SetPixelShader(NULL);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pDevice->SetFVF(CUSTOMFVF);
}

VOID CRenderer::End()
{
	m_pDevice->SetPixelShader(m_pShader);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, m_CullMode);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, m_AlphaBlend);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, m_SrcBlend);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, m_DestBlend);
	m_pDevice->SetFVF(m_FVF);
}

VOID CRenderer::OnLostDevice()
{
	if (m_pLine)
		m_pLine->OnLostDevice();

	for (auto& f : m_Fonts)
	{
		if (f->Created())
			f->OnLostDevice();
	}
}

VOID CRenderer::OnResetDevice()
{
	if (m_pLine)
		m_pLine->OnResetDevice();

	for (auto& f : m_Fonts)
	{
		if (f->Created())
			f->OnResetDevice();
	}
}

VOID CRenderer::Draw(const D3DXVECTOR2* pVertexList, DWORD dwVertexListCount, FLOAT Width, D3DCOLOR Color)
{
	m_pLine->SetWidth(Width);
	m_pLine->Begin();
	m_pLine->Draw(pVertexList, dwVertexListCount, Color);
	m_pLine->End();
}

VOID CRenderer::DrawLine(D3DXVECTOR2 Start, D3DXVECTOR2 End, FLOAT Width, D3DCOLOR Color)
{
	D3DXVECTOR2 vLine[2] = { Start, End };
	Draw(vLine, 2, Width, Color);
}

VOID CRenderer::DrawBorder(FLOAT x, FLOAT y, FLOAT Width, FLOAT Height, D3DCOLOR Color)
{
	CUSTOMVERTEX border[5] = {
		{ x, y, 0.0f, 1.0f, Color },
		{ x + Width - 1.0f, y, 0.0f, 1.0f, Color },
		{ x + Width - 1.0f, y + Height - 1.0f, 0.0f, 1.0f, Color },
		{ x, y + Height - 1.0f, 0.0f, 1.0f, Color },
		{ x, y + 1.0f, 0.0f, 1.0f, Color }
	};

	m_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, border, sizeof(CUSTOMVERTEX));
}

VOID CRenderer::DrawRect(FLOAT x, FLOAT y, FLOAT Width, FLOAT Height, FLOAT Thickness, D3DCOLOR Color)
{
	DrawFilledRect(x, y + Thickness, Thickness, Height - (Thickness * 2.0f), Color);
	DrawFilledRect(x, y, Width, Thickness, Color);
	DrawFilledRect(x + Width - Thickness, y + Thickness, Thickness, Height - (Thickness * 2.0f), Color);
	DrawFilledRect(x, y + Height - Thickness, Width, Thickness, Color);
}

VOID CRenderer::DrawFilledRect(FLOAT x, FLOAT y, FLOAT Width, FLOAT Height, D3DCOLOR Color)
{
	CUSTOMVERTEX qV[4] = {
		{ x, y + Height, 0.0f, 1.0f, Color },
		{ x, y, 0.0f, 1.0f, Color },
		{ x + Width, y + Height, 0.0f, 1.0f, Color },
		{ x + Width, y, 0.0f, 1.0f, Color }
	};

	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, qV, sizeof(CUSTOMVERTEX));
}

VOID CRenderer::DrawCircle(D3DXVECTOR2 Location, FLOAT Radius, INT Sides, INT Spaces, FLOAT Width, BOOL Center, D3DCOLOR Color)
{
	int skip = 0;
	float angle = D3DX_PI * 2 / Sides;
	float _cos = cos(angle);
	float _sin = sin(angle);
	float x1 = Radius, y1 = 0.0f, x2, y2;

	if (!Center)
	{
		Location.x += Radius;
		Location.y += Radius;
	}

	for (int i = 0; i < Sides; i++)
	{
		x2 = _cos * x1 - _sin * y1 + Location.x;
		y2 = _sin * x1 + _cos * y1 + Location.y;
		x1 += Location.x;
		y1 += Location.y;

		if (skip == 0)
			DrawLine(D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2), Width, Color);

		x1 = x2 - Location.x;
		y1 = y2 - Location.y;

		if (Spaces > 0)
		{
			if (skip != Spaces - 1)
				skip++;
			else
				skip = 0;
		}
	}
}

VOID CRenderer::DrawFilledCircle(D3DXVECTOR2 Location, FLOAT Radius, INT Sides, BOOL Center, D3DCOLOR Color)
{
	float angle = D3DX_PI * 2 / Sides;
	float _cos = cos(angle);
	float _sin = sin(angle);
	float x1 = Radius, y1 = 0, x2, y2;

	CUSTOMVERTEX* pVertex = new CUSTOMVERTEX[Sides * 3 + 3];

	if (!Center)
	{
		Location.x += Radius;
		Location.y += Radius;
	}

	for (int i = 0; i <= Sides * 3; i += 3)
	{
		x2 = _cos * x1 - _sin * y1 + Location.x;
		y2 = _sin * x1 + _cos * y1 + Location.y;
		x1 += Location.x;
		y1 += Location.y;

		pVertex[i] = { Location.x, Location.y, 0.0f, 1.0f, Color };
		pVertex[i + 1] = { x1, y1, 0.0f, 1.0f, Color };
		pVertex[i + 2] = { x2, y2, 0.0f, 1.0f, Color };

		x1 = x2 - Location.x;
		y1 = y2 - Location.y;
	}

	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, Sides * 3, pVertex, sizeof(CUSTOMVERTEX));

	delete[] pVertex;
}

INT CRenderer::DrawText(CFont* pFont, INT x, INT y, LPRECT pRect, DWORD Format, D3DCOLOR Color, LPCSTR pText, ...)
{
	va_list args;
	char szBuffer[1024];

	va_start(args, pText);
	vsprintf_s(szBuffer, pText, args);
	va_end(args);

	if (pRect)
		return pFont->pFont->DrawText(NULL, szBuffer, -1, pRect, Format, Color);

	RECT rect = { x, y, x, y };

	return pFont->pFont->DrawText(NULL, szBuffer, -1, &rect, Format | DT_NOCLIP, Color);
}

INT CRenderer::CalcTextRect(CFont* pFont, LPRECT pRect, DWORD Format, LPCSTR pText, ...)
{
	va_list args;
	char szBuffer[1024];

	va_start(args, pText);
	vsprintf_s(szBuffer, pText, args);
	va_end(args);

	return pFont->pFont->DrawText(NULL, szBuffer, -1, pRect, Format | DT_CALCRECT, NULL);
}

VOID CRenderer::Release()
{
	if (m_pLine)
	{
		m_pLine->Release();
		m_pLine = NULL;
	}

	for (auto& f : m_Fonts)
	{
		if (f->Created())
			f->Release();
	}
}
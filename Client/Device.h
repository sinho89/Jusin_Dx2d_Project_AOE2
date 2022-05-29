#pragma once

class CDevice
{
	DECLARE_SINGLETON(CDevice)
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;
	LPD3DXSPRITE		m_pSprite;
	LPD3DXFONT			m_pFont;
	LPD3DXLINE			m_pLine;
public:
	HRESULT				InitD3D(void);
	LPDIRECT3DDEVICE9	GetDevice(void);
	LPD3DXSPRITE		GetSprite(void);
	LPD3DXFONT			GetFont(void);
	LPD3DXLINE			GetLine(void);
	void				SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	void				Render_Begin(void);
	void				Render_End(void);
	void				Render_End(HWND	_hWnd);
	void				Release(void);
private:
	CDevice(void){;}
public:
	~CDevice(void);
};

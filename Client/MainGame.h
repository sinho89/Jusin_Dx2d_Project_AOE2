#pragma once

class CDevice;
class CMainGame
{
private:
	CDevice*	m_pDevice;
	float		m_fTime;
	int			m_iFps;
	TCHAR		m_szBuf[MAX_PATH];
	D3DXMATRIX	matTransFPS;
public:
	HRESULT	Initialize(void);
	int		Update(void);
	void	Render(void);
	void	Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};

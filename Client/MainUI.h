#pragma once
#include "obj.h"

class CMainUI :
	public CObj
{
private:
	const TEXINFO*	pMainUITex;
	const TEXINFO*	pMiniViewTex;
	const TEXINFO*	pMiniMapTex[4];
	const TEXINFO*	pTexInfo[80];
	const TEXINFO*  pIconTex[9];


public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	void BuildProfilRender();
	void ProfilRender();
	bool MiniMapRenderCheck();
	void MiniMapRender();
public:
	CMainUI(void);
	virtual ~CMainUI(void);
};

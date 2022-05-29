#pragma once
#include "obj.h"

class CMiniMap :
	public CObj
{
private:
	unordered_map<int, TILE*>*				m_pmapTile;	
	list<CObj*>*							m_pUnit;
	list<CObj*>*							m_pBuild;
private:
	const TEXINFO*	pMiniViewTex;
	const TEXINFO*	pMiniMapTex[4];
	const TEXINFO*	pTexInfo[80];
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void MoveMinimap(void);
public:
	void InitRender(void);
public:
	CMiniMap(void);
	virtual ~CMiniMap(void);
};

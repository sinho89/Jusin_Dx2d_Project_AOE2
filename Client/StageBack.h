#pragma once
#include "obj.h"

class CStageBack :
	public CObj
{
private:
	TILE	m_tTile;
	int		m_iTime;
	bool	m_bDrawCheck;
	bool	m_bDrawNum;
	const TEXINFO*	pTexInfo[80];
	bool	m_bTestKey1;
	bool	m_bTestKey2;
	bool	m_bTestKey3;
	bool	m_bTestKey4;
	bool	m_bTestKey5;
	bool	m_bTestKey6;
	FRAME	m_tTimeFrame;
private:
	unordered_map<int, TILE*>	m_DrawTileMap;
public:
	unordered_map<int, TILE*>&	GetDrawTile()
	{
		return m_DrawTileMap; 
	}
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void LoadTile(void);
	void CheckDrawTile(void);
public:
	CStageBack(void);
	virtual ~CStageBack(void);
};

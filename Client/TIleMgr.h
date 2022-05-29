#pragma once

class CTileMgr
{
	DECLARE_SINGLETON(CTileMgr)
public:
	static bool	FogTileCheck;
private:
	unordered_map<int, TILE*>	m_TileMap;
	unordered_map<int, TILE*>	m_FogCheckTile;
public:
	unordered_map<int, TILE*>&	GetTile()
	{
		return m_TileMap;
	}
	unordered_map<int, TILE*>&	GetFogTile()
	{
		return m_FogCheckTile;
	}
public:
	void			SetFindCheck();
	int				GetTileIndex(const D3DXVECTOR3&	vPos);
	bool			Picking(const D3DXVECTOR3& vPos, const int& iIndex);	//직선의 방정식..
private:
	CTileMgr(void);
public:
	~CTileMgr(void);
};

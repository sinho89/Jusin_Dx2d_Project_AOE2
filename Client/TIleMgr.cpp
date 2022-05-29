#include "StdAfx.h"
#include "TileMgr.h"

IMPLEMENT_SINGLETON(CTileMgr)

bool	CTileMgr::FogTileCheck = false;

CTileMgr::CTileMgr(void)
{
}

CTileMgr::~CTileMgr(void)
{
	unordered_map<int, TILE*>::iterator iter = m_TileMap.begin();
	unordered_map<int, TILE*>::iterator iter_end = m_TileMap.end();

	for(iter; iter != iter_end; ++iter)
		SAFE_DELETE(iter->second);
	m_TileMap.clear();
}

void CTileMgr::SetFindCheck()
{
	unordered_map<int, TILE*>::iterator iter = m_TileMap.begin();
	unordered_map<int, TILE*>::iterator iter_end = m_TileMap.end();

	for(iter; iter != iter_end; ++iter)
		iter->second->m_BuildType = BT_FINDSTART;
}
int CTileMgr::GetTileIndex( const D3DXVECTOR3& vPos )
{
	for(size_t i = 0; i < m_TileMap.size(); ++i)
	{
		if(Picking(vPos, i))
		{
			return i;
		}
	}
	return -1;
}

bool CTileMgr::Picking( const D3DXVECTOR3& vPos, const int& iIndex )
{
	if(iIndex >= 2500 || iIndex < 0)
		return false;

	float fGradient = (TILESIZEY / 2.f) / (TILESIZEX / 2.f);

	//마름모 각 꼭지점 4개를 만들어라...
	D3DXVECTOR3	vPoint[4] = 
	{
		D3DXVECTOR3(m_TileMap[iIndex]->vPos.x, m_TileMap[iIndex]->vPos.y - TILESIZEY / 2.f, 0),
		D3DXVECTOR3(m_TileMap[iIndex]->vPos.x + TILESIZEX / 2.f, m_TileMap[iIndex]->vPos.y, 0),
		D3DXVECTOR3(m_TileMap[iIndex]->vPos.x, m_TileMap[iIndex]->vPos.y + TILESIZEY / 2.f, 0),
		D3DXVECTOR3(m_TileMap[iIndex]->vPos.x - TILESIZEX / 2.f, m_TileMap[iIndex]->vPos.y, 0),
	};


	float fB[4] = 
	{
		//y절편 구해라.....
		vPoint[0].y - fGradient * vPoint[0].x,
		vPoint[1].y + fGradient * vPoint[1].x,
		vPoint[2].y - fGradient * vPoint[2].x,
		vPoint[3].y + fGradient * vPoint[3].x,
	};

	//직선의 방정식은 y = ax + b

	//y - ax - b = 0	: 직선과 동일선상...
	//y - ax - b < 0	: 직선보다 아래에 있는점...
	//y - ax - b > 0	: 직선보다 위에 있는 애다....


	//(0,0) 기준으로 지나가는 선이라고 가정하고...
	if(vPos.y - fGradient * vPos.x - fB[0] > 0 &&
		vPos.y + fGradient * vPos.x - fB[1] < 0 &&
		vPos.y - fGradient * vPos.x - fB[2] < 0 &&
		vPos.y + fGradient * vPos.x - fB[3] > 0)
	{
		return true;
	}

	return false;
}

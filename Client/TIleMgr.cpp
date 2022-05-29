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

	//������ �� ������ 4���� ������...
	D3DXVECTOR3	vPoint[4] = 
	{
		D3DXVECTOR3(m_TileMap[iIndex]->vPos.x, m_TileMap[iIndex]->vPos.y - TILESIZEY / 2.f, 0),
		D3DXVECTOR3(m_TileMap[iIndex]->vPos.x + TILESIZEX / 2.f, m_TileMap[iIndex]->vPos.y, 0),
		D3DXVECTOR3(m_TileMap[iIndex]->vPos.x, m_TileMap[iIndex]->vPos.y + TILESIZEY / 2.f, 0),
		D3DXVECTOR3(m_TileMap[iIndex]->vPos.x - TILESIZEX / 2.f, m_TileMap[iIndex]->vPos.y, 0),
	};


	float fB[4] = 
	{
		//y���� ���ض�.....
		vPoint[0].y - fGradient * vPoint[0].x,
		vPoint[1].y + fGradient * vPoint[1].x,
		vPoint[2].y - fGradient * vPoint[2].x,
		vPoint[3].y + fGradient * vPoint[3].x,
	};

	//������ �������� y = ax + b

	//y - ax - b = 0	: ������ ���ϼ���...
	//y - ax - b < 0	: �������� �Ʒ��� �ִ���...
	//y - ax - b > 0	: �������� ���� �ִ� �ִ�....


	//(0,0) �������� �������� ���̶�� �����ϰ�...
	if(vPos.y - fGradient * vPos.x - fB[0] > 0 &&
		vPos.y + fGradient * vPos.x - fB[1] < 0 &&
		vPos.y - fGradient * vPos.x - fB[2] < 0 &&
		vPos.y + fGradient * vPos.x - fB[3] > 0)
	{
		return true;
	}

	return false;
}

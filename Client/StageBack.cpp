#include "StdAfx.h"
#include "StageBack.h"
#include "TileMgr.h"
#include "MouseMgr.h"
#include "TextureMgr.h"
#include "TImeMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "GallyShip.h"
#include "DestroyShip.h"
#include "FireShip.h"
#include "CannonShip.h"
#include "Soldier.h"
#include "Port.h"

CStageBack::CStageBack(void)
:m_bDrawCheck(false)
,m_bDrawNum(false)
,m_iTime(0)
{
}

CStageBack::~CStageBack(void)
{
	Release();
}

HRESULT CStageBack::Initialize( void )
{
	LoadTile();
	
	for(int i = 0; i < 80; ++i)
		pTexInfo[i] = CTextureMgr::GetInstance()->GetTexture(L"Tile", L"Tile", i);
	
	CheckDrawTile();


	m_bTestKey1 = false;
	m_bTestKey2  = false;
	m_bTestKey3  = false;
	m_bTestKey4  = false;
	m_bTestKey5	= false;
	m_bTestKey6 = false;

	m_tFrame = FRAME(60.f, 7.f, 69.f, 60.f);

	m_tTimeFrame = FRAME(0.f, 10.f, 200.f, 0.f);

	return S_OK;
}

int CStageBack::Update( void )
{
	D3DXVECTOR3 vMouse = CMouseMgr::GetMousePos();

	if(GetAsyncKeyState('T') & 0x8000)
	{
		if(m_bDrawNum == true)
			return 0;
		m_bDrawNum = true;
	}
	else
		m_bDrawNum = false;

	if(vMouse.x > WINCX - 30)
	{
		CObj::m_vScroll.x -= 500 * GETTIME;
		m_bDrawCheck = true;
	}
	if(vMouse.x< 0 + 30)
	{
		CObj::m_vScroll.x += 500 * GETTIME;
		m_bDrawCheck = true;
	}
	if(vMouse.y > WINCY - 50)
	{
		CObj::m_vScroll.y -= 500 * GETTIME;
		m_bDrawCheck = true;
	}
	if(vMouse.y < 0 + 30)
	{
		CObj::m_vScroll.y += 500 * GETTIME;
		m_bDrawCheck = true;
	}

	if(m_bDrawCheck == true)
	{
		CheckDrawTile();
		m_bDrawCheck = false;
	}

	vMouse.x -= CObj::m_vScroll.x;
	vMouse.y -= CObj::m_vScroll.y;


	m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tFrame.fFrame = m_tFrame.fOriFrame;
	}


	m_tTimeFrame.fFrame += m_tTimeFrame.fCount * GETTIME;
	if(m_tTimeFrame.fFrame > m_tTimeFrame.fMax)
	{
		if(CObj::m_bWarStart == true)
			CObj::m_bWarStart = false;
		m_tTimeFrame.fFrame = m_tTimeFrame.fOriFrame;
	}
	/*for(int i = 0, j = m_DrawTileMap.size(); i != j; ++i)
	{
		if(m_DrawTileMap[i]->byDrawID >= 60)
		{
			if(m_tFrame.fFrame > m_tFrame.fMax)
			{
				m_tFrame.fFrame = m_tFrame.fOriFrame;
			}
		}
	}*/

	if(GetAsyncKeyState('1') & 0x8000)
	{
		if(m_bTestKey1 == true)
			return 1;
		m_bTestKey1 = true;

		CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CGallyShip>::CreateObject(vMouse
			, CTileMgr::GetInstance()->GetTile()[960]->vPos, UT_GALLYSHIP, PT_ENEMY, 0));

	}
	else
		m_bTestKey1 = false;

	if(GetAsyncKeyState('2') & 0x8000)
	{
		if(m_bTestKey2 == true)
			return 1;
		m_bTestKey2 = true;

		CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CDestroyShip>::CreateObject(vMouse
			, CTileMgr::GetInstance()->GetTile()[960]->vPos, UT_DESTROYSHIP, PT_ENEMY, 0));

	}
	else
		m_bTestKey2 = false;

	if(GetAsyncKeyState('3') & 0x8000)
	{
		if(m_bTestKey3 == true)
			return 1;
		m_bTestKey3 = true;

		CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CFireShip>::CreateObject(vMouse
			, CTileMgr::GetInstance()->GetTile()[960]->vPos, UT_FIRESHIP, PT_ENEMY, 0));

	}
	else
		m_bTestKey3 = false;

	if(GetAsyncKeyState('4') & 0x8000)
	{
		if(m_bTestKey4 == true)
			return 1;
		m_bTestKey4 = true;

		CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CCannonShip>::CreateObject(vMouse
			, CTileMgr::GetInstance()->GetTile()[960]->vPos, UT_CANNONSHIP, PT_ENEMY, 0));

	}
	else
		m_bTestKey4 = false;

	if(GetAsyncKeyState('5') & 0x8000)
	{
		if(m_bTestKey5 == true)
			return 1;
		m_bTestKey5 = true;

		CObjMgr::GetInstance()->AddObject(L"Build", SORT_OBJECT, CFactory<CPort>::CreateObject(CTileMgr::GetInstance()->GetTile()[1730]->vPos, BT_PORT, PT_ENEMY, 0));


	}
	else
		m_bTestKey5 = false;


	return 0;
}

void CStageBack::Render( void )
{
	for(int i = 0, j = m_DrawTileMap.size(); i != j; ++i)
	{
		if(pTexInfo[m_DrawTileMap[i]->byDrawID] == NULL)
			return;
		
		if(m_DrawTileMap[i]->m_GroundType == GT_SEA)
		{
			if(pTexInfo[int(m_tFrame.fFrame)] == NULL)
				return;

			float fX = pTexInfo[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
			float fY = pTexInfo[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, m_DrawTileMap[i]->vPos.x, m_DrawTileMap[i]->vPos.y, 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			if(m_DrawTileMap[i]->byOption == 0 && m_DrawTileMap[i]->m_UnitType != UT_FOG)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[int(m_tFrame.fFrame)]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
					NULL,
					D3DCOLOR_ARGB(0, 255, 255, 255));
			}
			else if( m_DrawTileMap[i]->byOption == 1)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[int(m_tFrame.fFrame)]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else if(m_DrawTileMap[i]->byOption == 0 && m_DrawTileMap[i]->m_UnitType == UT_FOG)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[int(m_tFrame.fFrame)]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
					NULL,
					D3DCOLOR_ARGB(128, 255, 255, 255));
			}


		}
		else
		{
			float fX = pTexInfo[m_DrawTileMap[i]->byDrawID]->ImgInfo.Width / 2.f;
			float fY = pTexInfo[m_DrawTileMap[i]->byDrawID]->ImgInfo.Height / 2.f;

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, m_DrawTileMap[i]->vPos.x, m_DrawTileMap[i]->vPos.y, 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			if(m_DrawTileMap[i]->byOption == 0 && m_DrawTileMap[i]->m_UnitType != UT_FOG)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[m_DrawTileMap[i]->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
					NULL,
					D3DCOLOR_ARGB(0, 255, 255, 255));
			}
			else if( m_DrawTileMap[i]->byOption == 1)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[m_DrawTileMap[i]->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else if(m_DrawTileMap[i]->byOption == 0 && m_DrawTileMap[i]->m_UnitType == UT_FOG)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[m_DrawTileMap[i]->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
					NULL,
					D3DCOLOR_ARGB(128, 255, 255, 255));
			}

		}
		
	}

	if(m_bDrawNum == true)
	{
		for(int i = 0; i < TILECNTY; ++i)
		{
			for(int j = 0; j < TILECNTX; ++j)
			{
				int iIndex = i * TILECNTX + j;

				//폰트를 여기서 출력한다...
				TCHAR	szBuf[128] = L"";
				wsprintf(szBuf, L"%d", iIndex);

				D3DXMATRIX	matTrans;
				D3DXMatrixTranslation(&matTrans, CTileMgr::GetInstance()->GetTile()[iIndex]->vPos.x + CObj::m_vScroll.x, CTileMgr::GetInstance()->GetTile()[iIndex]->vPos.y + CObj::m_vScroll.y, 0.f);
				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				switch(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType)
				{
				case GT_GROUND:
					CDevice::GetInstance()->GetFont()->DrawTextW(
						CDevice::GetInstance()->GetSprite(),
						szBuf, lstrlen(szBuf), NULL, NULL,
						D3DCOLOR_ARGB(255, 0, 0, 0));
					break;
				case GT_SEA:
					CDevice::GetInstance()->GetFont()->DrawTextW(
						CDevice::GetInstance()->GetSprite(),
						szBuf, lstrlen(szBuf), NULL, NULL,
						D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case GT_UNIT:
					CDevice::GetInstance()->GetFont()->DrawTextW(
						CDevice::GetInstance()->GetSprite(),
						szBuf, lstrlen(szBuf), NULL, NULL,
						D3DCOLOR_ARGB(255, 0, 255, 255));
					break;
				case GT_EMPTY:
					CDevice::GetInstance()->GetFont()->DrawTextW(
						CDevice::GetInstance()->GetSprite(),
						szBuf, lstrlen(szBuf), NULL, NULL,
						D3DCOLOR_ARGB(255, 255, 0, 0));
					break;
				case GT_BUILD:
					CDevice::GetInstance()->GetFont()->DrawTextW(
						CDevice::GetInstance()->GetSprite(),
						szBuf, lstrlen(szBuf), NULL, NULL,
						D3DCOLOR_ARGB(255, 128, 128, 0));

					break;
				}
				switch(CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType)
				{
				case RT_TREE:
					CDevice::GetInstance()->GetFont()->DrawTextW(
						CDevice::GetInstance()->GetSprite(),
						szBuf, lstrlen(szBuf), NULL, NULL,
						D3DCOLOR_ARGB(255, 0, 255, 0));
					break;
				case RT_FISH:
					CDevice::GetInstance()->GetFont()->DrawTextW(
						CDevice::GetInstance()->GetSprite(),
						szBuf, lstrlen(szBuf), NULL, NULL,
						D3DCOLOR_ARGB(255, 0, 0, 255));
					break;
				case RT_STONE:
					CDevice::GetInstance()->GetFont()->DrawTextW(
						CDevice::GetInstance()->GetSprite(),
						szBuf, lstrlen(szBuf), NULL, NULL,
						D3DCOLOR_ARGB(255, 128, 128, 128));
					break;
				case RT_GOLD:
					CDevice::GetInstance()->GetFont()->DrawTextW(
						CDevice::GetInstance()->GetSprite(),
						szBuf, lstrlen(szBuf), NULL, NULL,
						D3DCOLOR_ARGB(255, 255, 255, 0));
					break;
				case RT_CHERRY:
					CDevice::GetInstance()->GetFont()->DrawTextW(
						CDevice::GetInstance()->GetSprite(),
						szBuf, lstrlen(szBuf), NULL, NULL,
						D3DCOLOR_ARGB(255, 255, 0, 255));
					break;
				}
			}
		}
	}
}

void CStageBack::Release( void )
{

}

void CStageBack::LoadTile( void )
{
	int k = 0;

	for(int i = 0; i < TILECNTY; ++i)
	{
		for(int j = 0; j < TILECNTX; ++j)
		{
			int iIndex = i * TILECNTX + j;

			TILE*	pTile = new TILE;

			pTile->vPos.x = float(TILESIZEX / 2 * ( j - i ) + ((TILESIZEX * TILECNTX) / 2.f));
			pTile->vPos.y = float(TILESIZEY / 2 * ( j + i ));
			pTile->vPos.z = 0.f;

			pTile->vSize = D3DXVECTOR3(float(TILESIZEX), float(TILESIZEY), 0.f);
			pTile->byOption = 0;

			if(iIndex >= 0 + k && iIndex < 20 + k && i < 15)
			{
				if(i == 14 || iIndex % (20 + k - 1) == 0 && iIndex != 0)
				{
					pTile->byDrawID = 45;
					pTile->m_GroundType = GT_GROUND;
				}
				else
				{
					pTile->byDrawID = 16;
					pTile->m_GroundType = GT_GROUND;
				}
			}

			else if(i >= TILECNTX - 15 && iIndex > 20 + k)
			{
				if(i == TILECNTX - 15 || iIndex == (20 + k + 1))
				{
					pTile->byDrawID = 45;
					pTile->m_GroundType = GT_GROUND;

				}
				else
				{
					pTile->byDrawID = 16;
					pTile->m_GroundType = GT_GROUND;
				}
			}
			else
			{
				pTile->byDrawID = 60;
				pTile->m_GroundType = GT_SEA;
			}
			pTile->m_eType = RT_NONE;
			pTile->m_BuildType = BT_end;
			pTile->m_UnitType = UT_end;
			pTile->byOriID = pTile->byDrawID;

			pTile->wstrObjKey = L"Tile";
			pTile->wstrStateKey = L"Tile";

			CTileMgr::GetInstance()->GetTile().insert(make_pair(iIndex, pTile));
		}

		k += TILECNTX;
	}
}

void CStageBack::CheckDrawTile( void )
{

	m_DrawTileMap.clear();

	int iCnt = 0;	
	
	float fRight = -CObj::m_vScroll.x + WINCX + TILESIZEX - 30;
	float fDown  = -CObj::m_vScroll.y + WINCY - TILESIZEY - 10;
	float fLeft  = -CObj::m_vScroll.x - TILESIZEX + 30;
	float fUp	 = -CObj::m_vScroll.y - TILESIZEY + 10;

	for(int i = 0; i < TILECNTY; ++i)
	{
		for(int j = 0; j < TILECNTX; ++j)
		{
			int iIndex = j + i * TILECNTX;

			if(iIndex > 2500 || iIndex < 0)
				return;

			if(CTileMgr::GetInstance()->GetTile()[iIndex]->vPos.x < fRight && CTileMgr::GetInstance()->GetTile()[iIndex]->vPos.y < fDown
				&&CTileMgr::GetInstance()->GetTile()[iIndex]->vPos.x > fLeft &&CTileMgr::GetInstance()->GetTile()[iIndex]->vPos.y > fUp)
			{
				m_DrawTileMap.insert(make_pair(iCnt, CTileMgr::GetInstance()->GetTile()[iIndex]));
				++iCnt;
			}
		}
	}
}

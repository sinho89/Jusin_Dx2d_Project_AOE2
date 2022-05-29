#include "StdAfx.h"
#include "MiniMap.h"
#include "TileMgr.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "StageBack.h"
#include "MouseMgr.h"
CMiniMap::CMiniMap(void)
{
}

CMiniMap::~CMiniMap(void)
{
}

HRESULT CMiniMap::Initialize( void )
{

	for(int i = 0; i < 80; ++i)
		pTexInfo[i] = CTextureMgr::GetInstance()->GetTexture(L"Tile", L"Tile", i);

	pMiniViewTex = CTextureMgr::GetInstance()->GetTexture(L"MiniView", L"MiniView", 0);

	for(int i = 0; i < 4; ++i)
	{
		pMiniMapTex[i] = CTextureMgr::GetInstance()->GetTexture(L"MiniMap", L"MiniMap", i);
	}
	
	m_pmapTile = &CTileMgr::GetInstance()->GetTile();

	return S_OK;
}

int CMiniMap::Update( void )
{
	m_pUnit = &CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT);
	m_pBuild = &CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT);
	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if(CMouseMgr::GetMousePos().x > 511.f && CMouseMgr::GetMousePos().x < 778.f &&
			CMouseMgr::GetMousePos().y > 485.f && CMouseMgr::GetMousePos().y < 600.f)
		{
			MoveMinimap();
		}
	}
	return 0;
}

void CMiniMap::Render( void )
{
	unordered_map<int, TILE*>::iterator iter;

	for(int i = 0; i < TILECNTY; ++i)
	{
		for(int j = 0; j < TILECNTX; ++j)
		{
			int iIndex = i * TILECNTX + j;

			iter = m_pmapTile->find(iIndex);

			if(pTexInfo[iter->second->byDrawID] == NULL)
				return;

			float fX = pTexInfo[iter->second->byDrawID]->ImgInfo.Width / 2.f;
			float fY = pTexInfo[iter->second->byDrawID]->ImgInfo.Height / 2.f;

			D3DXMATRIX	matTrans;
			D3DXMATRIX	matScale;
			D3DXMatrixTranslation(&matTrans, (iter->second->vPos.x + 9300) * 0.055 , (iter->second->vPos.y + 8475) * 0.055, 0.f);
			D3DXMatrixScaling(&matScale, 0.055f, 0.055f, 0.f);

			D3DXMATRIX	matWorld;

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			if(iter->second->byOption == 0 && iter->second->m_UnitType != UT_FOG)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[iter->second->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(0, 255, 255, 255));
			}
			if( iter->second->byOption == 1)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[iter->second->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			if(iter->second->byOption == 0 && iter->second->m_UnitType == UT_FOG)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[iter->second->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(128, 255, 255, 255));
			}
		}
	}

	list<CObj*>::iterator Unit_iter = m_pUnit->begin();
	list<CObj*>::iterator Unit_iter_end = m_pUnit->end();


	for(; Unit_iter != Unit_iter_end; ++Unit_iter)
	{
			if((*Unit_iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
			{
				D3DXMATRIX	matTrans;
				D3DXMatrixTranslation(&matTrans, ((*Unit_iter)->GetInfo()->vPos.x + 10120) * 0.055, ((*Unit_iter)->GetInfo()->vPos.y + 8880) * 0.055, 0.f);
				
				m_tInfo.matWorld = matTrans;

				CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

				CDevice::GetInstance()->GetSprite()->Draw(pMiniMapTex[0]->pTexture,
					NULL,
					&D3DXVECTOR3(TILESIZEX/2.f, TILESIZEY/2.f, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));	
			}
			if((*Unit_iter)->GetInfo()->m_ePlayerType == PT_ENEMY && (*Unit_iter)->GetInfo()->bView == true)
			{
				D3DXMATRIX	matTrans;
				D3DXMatrixTranslation(&matTrans, ((*Unit_iter)->GetInfo()->vPos.x + 10120) * 0.055, ((*Unit_iter)->GetInfo()->vPos.y + 8880) * 0.055, 0.f);

				m_tInfo.matWorld = matTrans;

				CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

				CDevice::GetInstance()->GetSprite()->Draw(pMiniMapTex[2]->pTexture,
					NULL,
					&D3DXVECTOR3(TILESIZEX/2.f, TILESIZEY/2.f, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));	
			}
		
	}

	list<CObj*>::iterator Build_iter = m_pBuild->begin();
	list<CObj*>::iterator Build_iter_end = m_pBuild->end();


	for(; Build_iter != Build_iter_end; ++Build_iter)
	{
		if((*Build_iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, ((*Build_iter)->GetInfo()->vPos.x + 10120) * 0.055, ((*Build_iter)->GetInfo()->vPos.y + 8880) * 0.055, 0.f);

			m_tInfo.matWorld = matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pMiniMapTex[1]->pTexture,
				NULL,
				&D3DXVECTOR3(TILESIZEX/2.f, TILESIZEY/2.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));	
		}
		if((*Build_iter)->GetInfo()->m_ePlayerType == PT_ENEMY && (*Build_iter)->GetInfo()->bView == true)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, ((*Build_iter)->GetInfo()->vPos.x + 10120) * 0.055, ((*Build_iter)->GetInfo()->vPos.y + 8880) * 0.055, 0.f);

			m_tInfo.matWorld = matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pMiniMapTex[3]->pTexture,
				NULL,
				&D3DXVECTOR3(TILESIZEX/2.f, TILESIZEY/2.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));	
		}
	}
}

void CMiniMap::Release( void )
{

}

void CMiniMap::InitRender()
{
	for(int i = 0; i < TILECNTY; ++i)
	{
		for(int j = 0; j < TILECNTX; ++j)
		{
			int iIndex = i * TILECNTX + j;

			if(pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID] == NULL)
				return;

			float fX = pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID]->ImgInfo.Width / 2.f;
			float fY = pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID]->ImgInfo.Height / 2.f;

			D3DXMATRIX	matTrans;
			D3DXMATRIX	matScale;
			D3DXMatrixTranslation(&matTrans, (CTileMgr::GetInstance()->GetTile()[iIndex]->vPos.x + 9300) * 0.055 , (CTileMgr::GetInstance()->GetTile()[iIndex]->vPos.y + 8475) * 0.055, 0.f);
			D3DXMatrixScaling(&matScale, 0.055f, 0.055f, 0.f);

			D3DXMATRIX	matWorld;

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);


			if(CTileMgr::GetInstance()->GetTile()[iIndex]->byOption == 0 && CTileMgr::GetInstance()->GetTile()[iIndex]->m_UnitType != UT_FOG)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(0, 255, 255, 255));
			}
			if( CTileMgr::GetInstance()->GetTile()[iIndex]->byOption == 1)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			if(CTileMgr::GetInstance()->GetTile()[iIndex]->byOption == 0 && CTileMgr::GetInstance()->GetTile()[iIndex]->m_UnitType == UT_FOG)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(128, 255, 255, 255));
			}
		}
	}
}

void CMiniMap::MoveMinimap( void )
{
	
	float fMiniMap_X = CMouseMgr::GetMousePos().x - 511.f;
	float fMiniMap_Y = CMouseMgr::GetMousePos().y - 465.f;

	m_vScroll.x = (fMiniMap_X-10.f) * -14.28571428571429f;
	m_vScroll.y = (fMiniMap_Y-15.f) * -14.28571428571429f;

	if(m_vScroll.x > 0)
		m_vScroll.x = 0;

	if(m_vScroll.x < -3040.f)
		m_vScroll.x = -3040.f;

	if(m_vScroll.y > 0)
		m_vScroll.y = 0;

	if(m_vScroll.y < -1320.f)
		m_vScroll.y = -1320.f;
	
}

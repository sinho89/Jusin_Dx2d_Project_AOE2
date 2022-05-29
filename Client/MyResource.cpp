#include "StdAfx.h"
#include "MyResource.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "TImeMgr.h"
CMyResource::CMyResource(void)
:m_iFishNum(0)
,m_iTime(0)
{
}

CMyResource::~CMyResource(void)
{
	Release();
}

HRESULT CMyResource::Initialize( void )
{
	//m_tInfo.bAlive = true;
	m_iTime = 0;
	m_bFogColl = false;
	switch(m_tInfo.m_eResourceType)
	{
	case RT_CHERRY:
		m_tInfo.wstrObjKey = L"Cherry";
		for(int i = 0; i < 4; ++i)
			pCherryTex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, i);
		break;
	case RT_TREE:
		m_tInfo.vPos.y -= 70.f;
		m_tInfo.wstrObjKey = L"Tree";
		for(int i = 0; i < 10; ++i)
		{
			pTreeTex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, i);
			pTreeShadowTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Tree_Shadow", L"Tree_Shadow", i);
		}
		for(int i = 0; i < 5; ++i)
			pChoppingTreeTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Chopping_Tree", L"Chopping_Tree", i);
		break;
	case RT_FISH:
		m_iFishNum = rand() % 2;
		if(m_iFishNum == 0)
		{
			m_tInfo.wstrObjKey = L"Marlin";
			for(int i = 0; i < 49; ++i)
				pFishTex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, i);
		}
		else
		{
			m_tInfo.wstrObjKey = L"ChamChi";
			for(int i = 0; i < 49; ++i)
				pChamChiTex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, i);
		}
		m_tFrame = FRAME(0.f, 15.f, 49.f, 0.f);
		break;
	case RT_GOLD:
		m_tInfo.wstrObjKey = L"Gold";
		for(int i = 0; i < 7; ++i)
			pGoldTex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, i);
		break;
	case RT_STONE:
		m_tInfo.wstrObjKey = L"Rock";
		for(int i = 0; i < 7; ++i)
			pRockTex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, i);
		break;
	}

	m_tInfo.fCollRange = 25.f;

	return S_OK;
}

int CMyResource::Update( void )
{

	D3DXMATRIX	matTrans;

	if(m_tInfo.m_eResourceType == RT_FISH)
	{
		if(m_bFogColl == false && m_tInfo.bView == true)
		{
			m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
			if(m_tFrame.fFrame > m_tFrame.fMax)
			{
				m_tFrame.fFrame = m_tFrame.fOriFrame;
			}
		}
	}
	if(m_tInfo.m_eResourceType == RT_TREE)
	{
		if(m_tInfo.iHp <= 199)
		{
			m_tInfo.wstrObjKey = L"Chopping_Tree";
		}
	}

	if(m_tInfo.bView == false)
	{
		if(CTileMgr::GetInstance()->GetTile()[m_tInfo.iIndex]->byOption == 1)
		{
			m_tInfo.bView = true;
			m_bFogColl= false;
		}
	}

	if(m_tInfo.bView == true)
	{
		if(m_tInfo.iIndex != -1)
		{
			if(CTileMgr::GetInstance()->GetTile()[m_tInfo.iIndex]->byOption == 0)
			{
				m_bFogColl = true;
			}
			else
				m_bFogColl = false;
		}
	}

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	return 0;
}

void CMyResource::Render( void )
{
	if(m_tInfo.bView == false)
		return;
	int iAlpha = 0;
	if(m_bFogColl == false)
		iAlpha = 255;
	else if(m_bFogColl == true)
		iAlpha = 128;

	if(m_tInfo.wstrObjKey == L"Tree")
	{
		if(pTreeShadowTex[m_tInfo.byDrawID] == NULL)
			return;

		float fX = pTreeShadowTex[m_tInfo.byDrawID]->ImgInfo.Width / 2.f + 30.f;
		float fY = pTreeShadowTex[m_tInfo.byDrawID]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTreeShadowTex[m_tInfo.byDrawID]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(100, 0, 0, 0));

		if(pTreeTex[m_tInfo.byDrawID] == NULL)
			return;

		fX = pTreeTex[m_tInfo.byDrawID]->ImgInfo.Width / 2.f;
		fY = pTreeTex[m_tInfo.byDrawID]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTreeTex[m_tInfo.byDrawID]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(m_tInfo.wstrObjKey == L"Chopping_Tree")
	{
		if(pChoppingTreeTex[3] == NULL)
			return;

		float fX = pChoppingTreeTex[3]->ImgInfo.Width / 2.f;
		float fY = pChoppingTreeTex[3]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pChoppingTreeTex[3]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y - 70, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if(m_tInfo.wstrObjKey == L"Rock")
	{
		if(pRockTex[m_tInfo.byDrawID] == NULL)
			return;

		float fX = pRockTex[m_tInfo.byDrawID]->ImgInfo.Width / 2.f;
		float fY = pRockTex[m_tInfo.byDrawID]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pRockTex[m_tInfo.byDrawID]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(iAlpha, 255, 255, 255));
	}
	else if(m_tInfo.wstrObjKey == L"Gold")
	{
		if(pGoldTex[m_tInfo.byDrawID] == NULL)
			return;

		float fX = pGoldTex[m_tInfo.byDrawID]->ImgInfo.Width / 2.f;
		float fY = pGoldTex[m_tInfo.byDrawID]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pGoldTex[m_tInfo.byDrawID]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if(m_tInfo.wstrObjKey == L"Cherry")
	{
		if(pCherryTex[m_tInfo.byDrawID] == NULL)
			return;

		float fX = pCherryTex[m_tInfo.byDrawID]->ImgInfo.Width / 2.f;
		float fY = pCherryTex[m_tInfo.byDrawID]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pCherryTex[m_tInfo.byDrawID]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if(m_tInfo.wstrObjKey == L"Marlin")
	{
		if(pFishTex[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pFishTex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pFishTex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pFishTex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if(m_tInfo.wstrObjKey == L"ChamChi")
	{
		if(pChamChiTex[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pChamChiTex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pChamChiTex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pChamChiTex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMyResource::Release( void )
{

}


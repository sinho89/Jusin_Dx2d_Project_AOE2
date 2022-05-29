#include "StdAfx.h"
#include "Town.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"
#include "Barracks.h"
#include "TIleMgr.h"
#include "TImeMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Broken.h"
#include "BrokenEffect.h"
#include "SoundMgr.h"
CTown::CTown(void)
{
}

CTown::~CTown(void)
{
}
HRESULT CTown::Initialize( void )
{
	m_tInfo.iSight = 500;


	pProfilTex = CTextureMgr::GetInstance()->GetTexture(L"BuildIcon", L"BuildIcon", 11);

	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		m_tInfo.wstrObjKey = L"PlayerTown";
		pTownTex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, m_tInfo.byDrawID);
		pTownTex2 = CTextureMgr::GetInstance()->GetTexture(L"PlayerTown2", L"PlayerTown2", 0);
		pTownTex3 = CTextureMgr::GetInstance()->GetTexture(L"PlayerTown3", L"PlayerTown3", 0);
		pTownTex4 = CTextureMgr::GetInstance()->GetTexture(L"PlayerTown4", L"PlayerTown4", 0);
		pSelectionLine = CTextureMgr::GetInstance()->GetTexture(L"Select", L"Select", 2);
		
	}
	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		m_tInfo.wstrObjKey = L"EnemyTown";
		pTownTex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, m_tInfo.byDrawID);
		pTownTex2 = CTextureMgr::GetInstance()->GetTexture(L"EnemyTown2", L"EnemyTown2", 0);
		pTownTex3 = CTextureMgr::GetInstance()->GetTexture(L"EnemyTown3", L"EnemyTown3", 0);
		pTownTex4 = CTextureMgr::GetInstance()->GetTexture(L"EnemyTown4", L"EnemyTown4", 0);
	}
	pTownShadowTex = CTextureMgr::GetInstance()->GetTexture(L"Town_Shadow", L"Town_Shadow", m_tInfo.byDrawID);
	pTownShadowTex2 = CTextureMgr::GetInstance()->GetTexture(L"Town_Shadow2", L"Town_Shadow2", m_tInfo.byDrawID);

	m_tInfo.vMakePos = D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 100.f, 0.f);
	m_tInfo.vWayPos = D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 100.f, 0.f);

	for(int i = 0; i < 20; ++i)
	{
		pSmallFire[i] = CTextureMgr::GetInstance()->GetTexture(L"Fire", L"Fire1", i);
		pMidFire[i] = CTextureMgr::GetInstance()->GetTexture(L"Fire", L"Fire2", i);
		pBigFire[i] = CTextureMgr::GetInstance()->GetTexture(L"Fire", L"Fire3", i);
	}

	m_tFrame = FRAME(0.f, 10.f, 19.f, 0.f);

	m_tInfo.fCollRange = 90.f;
	m_tInfo.iHp = 800;
	m_tInfo.iMaxHp = 800;
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		CCollisionMgr::GetInstance()->InitTileSightCollision(this);
	}
	return S_OK;
}

int CTown::Update( void )
{

	if(m_tInfo.iHp <= 0)
	{
		CSoundMgr::GetInstance()->GroundBoomSound(L"CannonShot.wav");
		CObjMgr::GetInstance()->AddObject(L"Broken", SORT_OBJECT, CFactory<CBroken>::CreateObject(m_tInfo.vPos, BST_MAX, BT_TOWN));
		CObjMgr::GetInstance()->AddObject(L"BrokenEffect", SORT_OBJECT, CFactory<CBrokenEffect>::CreateObject(m_tInfo.vPos));
		if(m_tInfo.m_ePlayerType == PT_ENEMY)
		{
			list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
			list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();
			for(; iter != iter_end; ++iter)
			{
				if((*iter)->GetInfo()->m_ePlayerType == PT_ENEMY)
					(*iter)->GetInfo()->iHp = 0;
			}


			CSoundMgr::GetInstance()->GroundBoomSound(L"End.wav");
		}
		m_tInfo.bAlive = false;
	}
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		CCollisionMgr::GetInstance()->TileSightCollision(this);
		m_tInfo.bView = true;
	}

	m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tFrame.fFrame = m_tFrame.fOriFrame;
	}

	CObj::SetWayPoint();
	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		CCollisionMgr::GetInstance()->EnemySightCollisoin(this);
	}

	return 0;
}

void CTown::Render( void )
{
	if(m_tInfo.bView == false)
		return;

	float fX;
	float fY; 

	
	if(m_tInfo.bSelection == true)
	{
		if(pSelectionLine == NULL)
			return;

		fX = pSelectionLine->ImgInfo.Width / 2.f - 10;
		fY = pSelectionLine->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pSelectionLine->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if((CObj::m_eAgeType == AT_DARK || CObj::m_eAgeType == AT_FEUDAL) && m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		if(pTownShadowTex == NULL)
			return;

		fX = pTownShadowTex->ImgInfo.Width / 2.f;
		fY = pTownShadowTex->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownShadowTex->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(100, 0, 0, 0));
	}

	if(CObj::m_eAgeType == AT_IMPERIAL && m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		if(pTownShadowTex2 == NULL)
			return;

		fX = pTownShadowTex2->ImgInfo.Width / 2.f;
		fY = pTownShadowTex2->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownShadowTex2->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(100, 0, 0, 0));
	}
	if(CObj::m_eAgeType == AT_DARK && m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		if(pTownTex == NULL)
			return;

		fX = pTownTex->ImgInfo.Width / 2.f - 10;
		fY = pTownTex->ImgInfo.Height / 2.f + 70;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownTex->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(CObj::m_eAgeType == AT_FEUDAL && m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		if(pTownTex2 == NULL)
			return;

		fX = pTownTex2->ImgInfo.Width / 2.f - 10;
		fY = pTownTex2->ImgInfo.Height / 2.f + 70;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownTex2->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(CObj::m_eAgeType == AT_IMPERIAL && m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		if(pTownTex3 == NULL)
			return;

		fX = pTownTex3->ImgInfo.Width / 2.f - 10;
		fY = pTownTex3->ImgInfo.Height / 2.f + 100;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownTex3->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(CObj::m_eAgeType == AT_CASTLE && m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		if(pTownTex4 == NULL)
			return;

		fX = pTownTex4->ImgInfo.Width / 2.f - 10;
		fY = pTownTex4->ImgInfo.Height / 2.f + 70;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownTex4->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if((CObj::m_eEnemyAgeType == AT_DARK || CObj::m_eEnemyAgeType == AT_FEUDAL) && m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		if(pTownShadowTex == NULL)
			return;

		fX = pTownShadowTex->ImgInfo.Width / 2.f;
		fY = pTownShadowTex->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownShadowTex->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(100, 0, 0, 0));
	}

	if(CObj::m_eEnemyAgeType == AT_IMPERIAL && m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		if(pTownShadowTex2 == NULL)
			return;

		fX = pTownShadowTex2->ImgInfo.Width / 2.f;
		fY = pTownShadowTex2->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownShadowTex2->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(100, 0, 0, 0));
	}
	if(CObj::m_eEnemyAgeType == AT_DARK && m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		if(pTownTex == NULL)
			return;

		fX = pTownTex->ImgInfo.Width / 2.f - 10;
		fY = pTownTex->ImgInfo.Height / 2.f + 70;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownTex->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(CObj::m_eEnemyAgeType == AT_FEUDAL && m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		if(pTownTex2 == NULL)
			return;

		fX = pTownTex2->ImgInfo.Width / 2.f - 10;
		fY = pTownTex2->ImgInfo.Height / 2.f + 70;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownTex2->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(CObj::m_eEnemyAgeType == AT_IMPERIAL && m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		if(pTownTex3 == NULL)
			return;

		fX = pTownTex3->ImgInfo.Width / 2.f - 10;
		fY = pTownTex3->ImgInfo.Height / 2.f + 100;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownTex3->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(CObj::m_eEnemyAgeType == AT_CASTLE && m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		if(pTownTex4 == NULL)
			return;

		fX = pTownTex4->ImgInfo.Width / 2.f - 10;
		fY = pTownTex4->ImgInfo.Height / 2.f + 70;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTownTex4->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	

}

void CTown::Release( void )
{

}
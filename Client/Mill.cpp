#include "StdAfx.h"
#include "Mill.h"
#include "TextureMgr.h"
#include "TImeMgr.h"
#include "CollisionMgr.h"
CMill::CMill(void)
{
}

CMill::~CMill(void)
{
}

HRESULT CMill::Initialize( void )
{
	pProfilTex = CTextureMgr::GetInstance()->GetTexture(L"BuildIcon", L"BuildIcon", 7);
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		m_tInfo.wstrObjKey = L"PlayerMill";
		for(int i = 0; i < 43; ++i)
			pMillTex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, i);
		for(int i = 0; i < 8; ++i)
			pMillTex2[i] = CTextureMgr::GetInstance()->GetTexture(L"PlayerMill2", L"PlayerMill2", i);
		for(int i = 0; i < 10; ++i)
			pMillTex3[i] = CTextureMgr::GetInstance()->GetTexture(L"PlayerMill3", L"PlayerMill3", i);
		pSelectionLine = CTextureMgr::GetInstance()->GetTexture(L"Select", L"Select", 3);
		

	}
	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		m_tInfo.wstrObjKey = L"EnemyMill";
		for(int i = 0; i < 43; ++i)
			pMillTex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, i);
	}

	m_iTime = 0;
	m_tInfo.byOriID = m_tInfo.byDrawID;

	m_tInfo.fCollRange = 60.f;

	m_tFrame = FRAME(0.f, 10.f, 42.f, 0.f);

	m_tInfo.iSight = 300;
	m_tInfo.iHp = 500;
	m_tInfo.iMaxHp = 500;

	return S_OK;
}

int CMill::Update( void )
{
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
		CCollisionMgr::GetInstance()->TileSightCollision(this);


	m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
	
	if(CObj::m_eAgeType == AT_DARK)
	{
		if(m_tFrame.fFrame > 42)
		{
			m_tFrame.fFrame = 0;
		}
	}
	if(CObj::m_eAgeType == AT_FEUDAL)
	{
		if(m_tFrame.fFrame > 7)
		{
			m_tFrame.fFrame = 0;
		}
	}
	if(CObj::m_eAgeType == AT_CASTLE || CObj::m_eAgeType == AT_IMPERIAL)
	{
		if(m_tFrame.fFrame > 9)
		{
			m_tFrame.fFrame = 0;
		}
	}

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	return 0;
}

void CMill::Render( void )
{
	if(m_tInfo.bSelection == true)
	{
		if(pSelectionLine == NULL)
			return;

		int fX = pSelectionLine->ImgInfo.Width / 2.f;
		int fY = pSelectionLine->ImgInfo.Height / 2.f - 20;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pSelectionLine->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(CObj::m_eAgeType == AT_DARK)
	{
		if(pMillTex[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pMillTex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pMillTex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pMillTex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(CObj::m_eAgeType == AT_FEUDAL)
	{
		if(m_tFrame.fFrame > 7)
		{
			m_tFrame.fFrame = 0;
		}

		if(pMillTex2[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pMillTex2[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pMillTex2[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f + 20;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pMillTex2[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(CObj::m_eAgeType == AT_CASTLE || CObj::m_eAgeType == AT_IMPERIAL)
	{
		if(m_tFrame.fFrame > 9)
		{
			m_tFrame.fFrame = 0;
		}

		if(pMillTex3[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pMillTex3[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pMillTex3[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f + 10;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pMillTex3[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMill::Release( void )
{

}

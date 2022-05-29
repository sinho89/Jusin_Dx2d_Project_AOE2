#include "StdAfx.h"
#include "Port.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Broken.h"
#include "BrokenEffect.h"
#include "TIleMgr.h"
#include "GallyShip.h"
#include "SoundMgr.h"
CPort::CPort(void)
{
}

CPort::~CPort(void)
{
}

HRESULT CPort::Initialize( void )
{
	m_tInfo.iSight = 300;
	pProfilTex = CTextureMgr::GetInstance()->GetTexture(L"BuildIcon", L"BuildIcon", 5);

	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		m_tInfo.wstrObjKey = L"PlayerPort";
		pPortTex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, m_tInfo.byDrawID);
		pPortTex2 = CTextureMgr::GetInstance()->GetTexture(L"PlayerPort2", L"PlayerPort2", m_tInfo.byDrawID);
		pPortTex3 = CTextureMgr::GetInstance()->GetTexture(L"PlayerPort3", L"PlayerPort3", m_tInfo.byDrawID);
		pPortTex4 = CTextureMgr::GetInstance()->GetTexture(L"PlayerPort4", L"PlayerPort4", m_tInfo.byDrawID);
		pPortShadowTex = CTextureMgr::GetInstance()->GetTexture(L"Port_Shadow", L"Port_Shadow", m_tInfo.byDrawID);
		pPortShadowTex2 = CTextureMgr::GetInstance()->GetTexture(L"Port_Shadow2", L"Port_Shadow2", m_tInfo.byDrawID);
		pPortShadowTex3 = CTextureMgr::GetInstance()->GetTexture(L"Port_Shadow3", L"Port_Shadow3", m_tInfo.byDrawID);
		pSelectionLine = CTextureMgr::GetInstance()->GetTexture(L"Select", L"Select", 3);
		CSoundMgr::GetInstance()->CreatePortSound(L"PortCreate.wav");

	}
	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		m_tInfo.wstrObjKey = L"EnemyPort";
		pPortTex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, m_tInfo.byDrawID);
		pPortShadowTex = CTextureMgr::GetInstance()->GetTexture(L"Port_Shadow", L"Port_Shadow", m_tInfo.byDrawID);
		pPortShadowTex2 = CTextureMgr::GetInstance()->GetTexture(L"Port_Shadow2", L"Port_Shadow2", m_tInfo.byDrawID);
		pPortShadowTex3 = CTextureMgr::GetInstance()->GetTexture(L"Port_Shadow3", L"Port_Shadow3", m_tInfo.byDrawID);
	}

	for(int i = 0; i < 60; ++i)
		pBirdTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Bird", L"Bird", i);

	m_iTime = 0;
	m_tInfo.byOriID = m_tInfo.byDrawID;

	m_tInfo.vMakePos = D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 100.f, 0.f);
	m_tInfo.vWayPos = D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 100.f, 0.f);

	m_tInfo.fCollRange = 60.f;
	m_tInfo.iHp = 500;
	m_tInfo.iMaxHp = 500;

	m_tFrame = FRAME(0.f, 20.f, 60.f, 0.f);
	m_tTime = FRAME(0.f, 10.f, 80.f, 0.f);
	return S_OK;
}

int CPort::Update( void )
{

	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		m_tTime.fFrame += m_tTime.fCount * GETTIME;
		if(m_tTime.fFrame > m_tTime.fMax)
		{
			D3DXVECTOR3 vCreate = m_tInfo.vPos;
			vCreate.y -= 80.f;
			CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CGallyShip>::CreateObject(vCreate
				, CTileMgr::GetInstance()->GetTile()[960]->vPos, UT_GALLYSHIP, PT_ENEMY, 0));
			m_tTime.fFrame = m_tTime.fOriFrame;
		}
	}
	if(m_tInfo.iHp <= 0)
	{
		CSoundMgr::GetInstance()->GroundBoomSound(L"CannonShot.wav");
		CObjMgr::GetInstance()->AddObject(L"Broken", SORT_FIRST, CFactory<CBroken>::CreateObject(m_tInfo.vPos, BST_MAX, BT_PORT));
		CObjMgr::GetInstance()->AddObject(L"BrokenEffect", SORT_OBJECT, CFactory<CBrokenEffect>::CreateObject(m_tInfo.vPos));
		m_tInfo.bAlive = false;
	}
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		CCollisionMgr::GetInstance()->TileSightCollision(this);
		m_tInfo.bView = true;
	}

	CObj::SetWayPoint();

	m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tFrame.fFrame = m_tFrame.fOriFrame;
	}


	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		CCollisionMgr::GetInstance()->EnemySightCollisoin(this);
	}
	return 0;
}

void CPort::Render( void )
{
	if(m_tInfo.bView == false)
		return;

	float fX = 0;
	float fY = 0;

	if(m_tInfo.bSelection == true)
	{
		if(pSelectionLine == NULL)
			return;

		fX = pSelectionLine->ImgInfo.Width / 2.f - 10;
		fY = pSelectionLine->ImgInfo.Height / 2.f - 25;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pSelectionLine->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(CObj::m_eAgeType == AT_DARK || m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		if(pPortShadowTex == NULL)
			return;

		fX = pPortShadowTex->ImgInfo.Width / 2.f + 13;
		fY = pPortShadowTex->ImgInfo.Height / 2.f - 35;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pPortShadowTex->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(125, 0, 0, 0));
	}

	if(CObj::m_eAgeType == AT_FEUDAL && m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		if(pPortShadowTex2 == NULL)
			return;

		fX = pPortShadowTex2->ImgInfo.Width / 2.f + 13;
		fY = pPortShadowTex2->ImgInfo.Height / 2.f - 35;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pPortShadowTex2->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(125, 0, 0, 0));
	}

	if(CObj::m_eAgeType == AT_IMPERIAL && m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		if(pPortShadowTex3 == NULL)
			return;

		fX = pPortShadowTex3->ImgInfo.Width / 2.f + 13;
		fY = pPortShadowTex3->ImgInfo.Height / 2.f - 35;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pPortShadowTex3->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(125, 0, 0, 0));
	}

	if(CObj::m_eAgeType == AT_DARK || m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		if(pPortTex == NULL)
			return;

		fX = pPortTex->ImgInfo.Width / 2.f;
		fY = pPortTex->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pPortTex->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

	}

	if(CObj::m_eAgeType == AT_FEUDAL && m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		if(pPortTex2 == NULL)
			return;

		fX = pPortTex2->ImgInfo.Width / 2.f;
		fY = pPortTex2->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pPortTex2->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

	}

	if((CObj::m_eAgeType == AT_CASTLE || CObj::m_eAgeType == AT_IMPERIAL) && m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		if(pPortTex4 == NULL)
			return;

		fX = pPortTex4->ImgInfo.Width / 2.f;
		fY = pPortTex4->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pPortTex4->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

	}

	if(pBirdTex[int(m_tFrame.fFrame)] == NULL)
		return;

	fX = pBirdTex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
	fY = pBirdTex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(pBirdTex[int(m_tFrame.fFrame)]->pTexture, 
		NULL,
		&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y + 150.f, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CPort::Release( void )
{

}

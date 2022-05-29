#include "StdAfx.h"
#include "Home.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
CHome::CHome(void)
{
}

CHome::~CHome(void)
{
}

HRESULT CHome::Initialize( void )
{
	pProfilTex = CTextureMgr::GetInstance()->GetTexture(L"BuildIcon", L"BuildIcon", 15);

	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		m_tInfo.wstrObjKey = L"PlayerHome";
		pHomeTex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, m_tInfo.byDrawID);
		pHomeTex2 = CTextureMgr::GetInstance()->GetTexture(L"PlayerHome2", L"PlayerHome2", m_tInfo.byDrawID);
		pHomeTex3 = CTextureMgr::GetInstance()->GetTexture(L"PlayerHome3", L"PlayerHome3", m_tInfo.byDrawID);
		CSoundMgr::GetInstance()->CreateHomeSound(L"HomeCreate.wav");
	}
	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		m_tInfo.wstrObjKey = L"EnemyHome";
		pHomeTex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, m_tInfo.byDrawID);
	}

	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"MainUI", SORT_UI).begin();

	pSelectionLine = CTextureMgr::GetInstance()->GetTexture(L"Select", L"Select", 4);
	(*iter)->GetInfo()->iUnitMaxCount += 5;

	m_tInfo.fCollRange = 60.f;

	m_tInfo.iSight = 300;
	m_tInfo.iHp = 500;
	m_tInfo.iMaxHp = 500;
	return S_OK;
}

int CHome::Update( void )
{
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
		CCollisionMgr::GetInstance()->TileSightCollision(this);

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	return 0;
}

void CHome::Render( void )
{
	if(m_tInfo.bSelection == true)
	{
		if(pSelectionLine == NULL)
			return;

		int fX = pSelectionLine->ImgInfo.Width / 2.f;
		int fY = pSelectionLine->ImgInfo.Height / 2.f - 10;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pSelectionLine->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(CObj::m_eAgeType == AT_DARK)
	{
		if(pHomeTex == NULL)
			return;

		float fX = pHomeTex->ImgInfo.Width / 2.f;
		float fY = pHomeTex->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pHomeTex->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(CObj::m_eAgeType == AT_FEUDAL)
	{
		if(pHomeTex2 == NULL)
			return;

		float fX = pHomeTex2->ImgInfo.Width / 2.f;
		float fY = pHomeTex2->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pHomeTex2->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(CObj::m_eAgeType == AT_IMPERIAL || CObj::m_eAgeType == AT_CASTLE)
	{
		if(pHomeTex3 == NULL)
			return;

		float fX = pHomeTex3->ImgInfo.Width / 2.f;
		float fY = pHomeTex3->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pHomeTex3->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CHome::Release( void )
{

}

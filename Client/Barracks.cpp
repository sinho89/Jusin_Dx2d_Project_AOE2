#include "StdAfx.h"
#include "Barracks.h"
#include "TextureMgr.h"
#include "TileMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
CBarracks::CBarracks(void)
{
}

CBarracks::~CBarracks(void)
{
}

HRESULT CBarracks::Initialize( void )
{
	pProfilTex = CTextureMgr::GetInstance()->GetTexture(L"BuildIcon", L"BuildIcon", 0);
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		m_tInfo.wstrObjKey = L"PlayerBarraks";
		pBarracksTex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, m_tInfo.byDrawID);
		pBarracksTex2 = CTextureMgr::GetInstance()->GetTexture(L"PlayerBarracks2", L"PlayerBarracks2", m_tInfo.byDrawID);
		pBarracksTex3 = CTextureMgr::GetInstance()->GetTexture(L"PlayerBarracks3", L"PlayerBarracks3", m_tInfo.byDrawID);
		pSelectionLine = CTextureMgr::GetInstance()->GetTexture(L"Select", L"Select", 2);
		CSoundMgr::GetInstance()->CreateBarrackSound(L"BarrackCreate.wav");
	}
	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		m_tInfo.wstrObjKey = L"EnemyBarracks";
		pBarracksTex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, m_tInfo.byDrawID);
	}

	m_tInfo.vMakePos = D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 100.f, 0.f);
	m_tInfo.vWayPos = D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 100.f, 0.f);

	m_tInfo.fCollRange = 90.f;

	m_tInfo.iSight = 400;
	m_tInfo.iHp = 1000;
	m_tInfo.iMaxHp = 1000;
	return S_OK;
}

int CBarracks::Update( void )
{
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		CCollisionMgr::GetInstance()->TileSightCollision(this);
		m_tInfo.bView = true;
	}

	CObj::SetWayPoint();

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	return 0;
}

void CBarracks::Render( void )
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
		if(pBarracksTex == NULL)
			return;

		float fX = pBarracksTex->ImgInfo.Width / 2.f;
		float fY = pBarracksTex->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBarracksTex->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(CObj::m_eAgeType == AT_FEUDAL)
	{
		if(pBarracksTex2 == NULL)
			return;

		float fX = pBarracksTex2->ImgInfo.Width / 2.f;
		float fY = pBarracksTex2->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBarracksTex2->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(CObj::m_eAgeType == AT_IMPERIAL || CObj::m_eAgeType == AT_CASTLE)
	{
		if(pBarracksTex3 == NULL)
			return;

		float fX = pBarracksTex3->ImgInfo.Width / 2.f;
		float fY = pBarracksTex3->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBarracksTex3->pTexture, 
			NULL,
			&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CBarracks::Release( void )
{

}

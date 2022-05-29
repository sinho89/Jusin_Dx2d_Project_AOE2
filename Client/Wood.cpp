#include "StdAfx.h"
#include "Wood.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"
CWood::CWood(void)
{
}

CWood::~CWood(void)
{
}

HRESULT CWood::Initialize( void )
{

	pProfilTex = CTextureMgr::GetInstance()->GetTexture(L"BuildIcon", L"BuildIcon", 20);
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		m_tInfo.wstrObjKey = L"PlayerLumberCamp";
		pWoodTex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, m_tInfo.byDrawID);
		pSelectionLine = CTextureMgr::GetInstance()->GetTexture(L"Select", L"Select", 3);
	}
	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		m_tInfo.wstrObjKey = L"EnemyLumberCamp";
		pWoodTex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, m_tInfo.byDrawID);
	}

	m_tInfo.fCollRange = 60.f;

	m_tInfo.iSight = 300;
	m_tInfo.iHp = 500;
	m_tInfo.iMaxHp = 500;
	return S_OK;
}

int CWood::Update( void )
{
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
		CCollisionMgr::GetInstance()->TileSightCollision(this);

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	return 0;
}

void CWood::Render( void )
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

	if(pWoodTex == NULL)
		return;

	float fX = pWoodTex->ImgInfo.Width / 2.f;
	float fY = pWoodTex->ImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(pWoodTex->pTexture, 
		NULL,
		&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CWood::Release( void )
{

}

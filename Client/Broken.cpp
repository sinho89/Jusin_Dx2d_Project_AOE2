#include "StdAfx.h"
#include "Broken.h"
#include "TextureMgr.h"
#include "TImeMgr.h"
CBroken::CBroken(void)
{
}

CBroken::~CBroken(void)
{
}

HRESULT CBroken::Initialize( void )
{
	m_tInfo.bView = false;

	for(int i = 0; i < 4; ++i)
		pBroken[i] = CTextureMgr::GetInstance()->GetTexture(L"Broken", L"Broken", i);

	switch(m_tInfo.m_eSizeType)
	{
	case BST_MIN:
		m_tInfo.byDrawID = 0;
		break;
	case BST_MID:
		m_tInfo.byDrawID = 1;
		break;
	case BST_MAX:
		m_tInfo.byDrawID = 2;
		break;
	case BST_PORT:
		m_tInfo.byDrawID = 1;
		break;
	}
	m_tFrame = FRAME(0.f, 10.f, 50.f, 0.f);

	m_tInfo.bAlive = true;

	return S_OK;
}

int CBroken::Update( void )
{
	m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tInfo.bAlive = false;
	}
	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	return 0;
}

void CBroken::Render( void )
{
	if(pBroken[m_tInfo.byDrawID] == NULL)
		return;

	float fX = pBroken[m_tInfo.byDrawID]->ImgInfo.Width / 2.f;
	float fY = pBroken[m_tInfo.byDrawID]->ImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(pBroken[m_tInfo.byDrawID]->pTexture, 
		NULL,
		&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBroken::Release( void )
{

}

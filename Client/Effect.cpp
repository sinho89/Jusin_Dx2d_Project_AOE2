#include "StdAfx.h"
#include "Effect.h"
#include "TextureMgr.h"
#include "TImeMgr.h"

CEffect::CEffect(void)
{
}

CEffect::~CEffect(void)
{
}

HRESULT CEffect::Initialize( void )
{

	for(int i = 0; i < 75; ++i)
		Effect[i] = CTextureMgr::GetInstance()->GetTexture(L"Ship_Move_Effect", L"Ship_Move_Effect", i);
	
	return S_OK;
}

int CEffect::Update( void )
{

	m_tFrame.fFrame += m_tFrame.fCount * GETTIME;

	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tInfo.bAlive = false;
		m_tFrame.fFrame = m_tFrame.fOriFrame;
	}

	CObj::SetMatrix();


	return 0;
}

void CEffect::Render( void )
{
	if(Effect[int(m_tFrame.fFrame)] == NULL)
		return;

	int fX = int(Effect[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
	int fY = int(Effect[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(Effect[int(m_tFrame.fFrame)]->pTexture, 
		NULL,
		&D3DXVECTOR3(fX, fY - 20, 0.f),
		NULL,
		D3DCOLOR_ARGB(200, 255, 255, 255));
}

void CEffect::Release( void )
{

}

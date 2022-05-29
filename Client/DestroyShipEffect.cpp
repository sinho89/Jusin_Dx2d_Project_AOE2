#include "StdAfx.h"
#include "DestroyShipEffect.h"
#include "TextureMgr.h"
#include "TImeMgr.h"
#include "SoundMgr.h"
CDestroyShipEffect::CDestroyShipEffect(void)
{
}

CDestroyShipEffect::~CDestroyShipEffect(void)
{
}

HRESULT CDestroyShipEffect::Initialize( void )
{
	for(int i = 0; i < 20; ++i)
		Effect[i] = CTextureMgr::GetInstance()->GetTexture(L"Boom5", L"Boom5", i);

	CSoundMgr::GetInstance()->CannonBoomSound(L"CannonShot.wav");

	m_tFrame = FRAME(0.f, 30.f, 20.f, 0.f);

	return S_OK;
}
int CDestroyShipEffect::Update( void )
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

void CDestroyShipEffect::Render( void )
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

void CDestroyShipEffect::Release( void )
{

}

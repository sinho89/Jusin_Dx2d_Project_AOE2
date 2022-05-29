#include "StdAfx.h"
#include "CannonBoom.h"
#include "TextureMgr.h"
#include "TImeMgr.h"
#include "SoundMgr.h"
CCannonBoom::CCannonBoom(void)
{
}

CCannonBoom::~CCannonBoom(void)
{
}

HRESULT CCannonBoom::Initialize( void )
{
	for(int i = 0; i < 10; ++i)
		Effect[i] = CTextureMgr::GetInstance()->GetTexture(L"Boom2", L"Boom2", i);
	for(int i = 0; i < 15; ++i)
		MissEffect[i] = CTextureMgr::GetInstance()->GetTexture(L"BoomMiss", L"BoomMiss", i);


	if(m_bShot == true)
	{
		CSoundMgr::GetInstance()->CannonBoomSound(L"CannonShot.wav");
		m_tFrame = FRAME(0.f, 30.f, 10.f, 0.f);

	}
	else if(m_bShot == false)
	{
		int iRand = rand()% 4;

		switch(iRand)
		{
		case 0:
			CSoundMgr::GetInstance()->CannonMissSound(L"CannonMiss1.wav");
			break;
		case 1:
			CSoundMgr::GetInstance()->CannonMissSound(L"CannonMiss2.wav");
			break;
		case 2:
			CSoundMgr::GetInstance()->CannonMissSound(L"CannonMiss3.wav");
			break;
		case 3:
			CSoundMgr::GetInstance()->CannonMissSound(L"CannonMiss4.wav");
			break;
		}
		m_tFrame = FRAME(0.f, 30.f, 15.f, 0.f);
	}

	return S_OK;
}
int CCannonBoom::Update( void )
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

void CCannonBoom::Render( void )
{

	if(m_bShot == true)
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
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	else if(m_bShot == false)
	{
		if(MissEffect[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(MissEffect[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(MissEffect[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(MissEffect[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY - 20, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CCannonBoom::Release( void )
{

}

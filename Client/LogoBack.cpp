#include "StdAfx.h"
#include "LogoBack.h"
#include "TImeMgr.h"
#include "TextureMgr.h"

CLogoBack::CLogoBack(void)
{
}

CLogoBack::~CLogoBack(void)
{
}

HRESULT CLogoBack::Initialize( void )
{
	m_tInfo.vPos = D3DXVECTOR3(float(WINCX / 2), float(WINCY / 2), 0.f);

	m_tInfo.wstrObjKey = L"LogoBack";
	m_tInfo.wstrStateKey = L"Loading";
	//_tcscpy_s(m_tInfo.szObjKey, sizeof(m_tInfo.szObjKey), L"LogoBack");
	//_tcscpy_s(m_tInfo.szStateKey, sizeof(m_tInfo.szStateKey), L"Loading");

	m_tFrame = FRAME(0.f, 2.f, 12.f, 0.f);

	return S_OK;
}

int CLogoBack::Update( void )
{
	m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tFrame.fFrame = m_tFrame.fMax - 1;
	}

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	return 0;
}

void CLogoBack::Render( void )
{
	const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrStateKey, (int)m_tFrame.fFrame);

	if(pTexInfo == NULL)
		return;

	float fX = pTexInfo->ImgInfo.Width / 2.f;
	float fY = pTexInfo->ImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, 
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CLogoBack::Release( void )
{

}
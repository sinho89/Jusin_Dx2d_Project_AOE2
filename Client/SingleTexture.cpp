#include "StdAfx.h"
#include "SingleTexture.h"
#include "Device.h"
#include "TextureMgr.h"

CSingleTexture::CSingleTexture(void)
{
	m_pTexInfo = NULL;
}

CSingleTexture::~CSingleTexture(void)
{
	Release();
}

HRESULT CSingleTexture::InsertTexture(const TCHAR* pPath,
									  const TCHAR* pStateKey,
									  const int& iCount)
{

	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	CTextureMgr::GetInstance()->GetCurrentPath() = pPath;

	if(FAILED(D3DXGetImageInfoFromFile(pPath, &m_pTexInfo->ImgInfo)))
	{
		MSG_BOX(L"D3DXGetImageInfoFromFile Failed");
		return E_FAIL;
	}

	if(FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice(),
		pPath,
		m_pTexInfo->ImgInfo.Width,
		m_pTexInfo->ImgInfo.Height,
		m_pTexInfo->ImgInfo.MipLevels,
		0,
		m_pTexInfo->ImgInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&m_pTexInfo->ImgInfo,
		NULL,
		&m_pTexInfo->pTexture)))
	{
		MSG_BOX(L"SingleTexeture Faile!");
		return E_FAIL;
	}

	return S_OK;
}

const TEXINFO* CSingleTexture::GetTexture(const TCHAR* pKey,
										  const int& iCount)
{
	return m_pTexInfo;
}

void CSingleTexture::Release(void)
{
	if(m_pTexInfo != NULL)
	{
		m_pTexInfo->pTexture->Release();
		delete m_pTexInfo;
		m_pTexInfo = NULL;
	}
}
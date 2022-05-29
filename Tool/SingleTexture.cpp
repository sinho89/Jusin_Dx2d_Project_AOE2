#include "StdAfx.h"
#include "SingleTexture.h"

CSingleTexture::CSingleTexture(void)
{
	m_pTexInfo = NULL;
}

CSingleTexture::~CSingleTexture(void)
{
	Release();
}

HRESULT CSingleTexture::InsertTexture(const TCHAR* pPath, const TCHAR* pStateKey /*= L""*/, const int& iCount /*= 0*/)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	if(FAILED(D3DXGetImageInfoFromFile(pPath, &m_pTexInfo->ImgInfo)))
	{
		MSG_BOX(L"D3DXGetImageInfoFromFile Failed");
		return E_FAIL;
	}

	if(FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice(),
		pPath,
		m_pTexInfo->ImgInfo.Width,	//가로
		m_pTexInfo->ImgInfo.Height,	//세로
		m_pTexInfo->ImgInfo.MipLevels,//확대 축소 이미지 레벨
		0,							//이미지 읽는 방식 설정...우리는 0
		m_pTexInfo->ImgInfo.Format,//이미지 포맷 형식
		D3DPOOL_MANAGED,			//현재 읽는 이미지들을 어떤 메모리에 보관할지...
		D3DX_DEFAULT,				//테두리 표현을 어떻게 할 것인가...
		D3DX_DEFAULT,				//확대 축소했을 때 어떻게 처리할지...
		D3DCOLOR_XRGB(255, 0, 255),						//제거할 이미지 색상...
		&m_pTexInfo->ImgInfo,		//이미지 정보를 어떻게 할지...
		NULL,						//8비트 미만의 이미지에 관련된 것...
		&m_pTexInfo->pTexture)))	//어디에다 로드한 이미지를 보관할 것인가...
	{
		MSG_BOX(L"SingleTexture Load Failed");
		return E_FAIL;
	}

	return S_OK;
}

const TEXINFO* CSingleTexture::GetTexture(const TCHAR* pKey /*= L""*/, const int& iCount /*= 0*/)
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

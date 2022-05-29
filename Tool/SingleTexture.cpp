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
		m_pTexInfo->ImgInfo.Width,	//����
		m_pTexInfo->ImgInfo.Height,	//����
		m_pTexInfo->ImgInfo.MipLevels,//Ȯ�� ��� �̹��� ����
		0,							//�̹��� �д� ��� ����...�츮�� 0
		m_pTexInfo->ImgInfo.Format,//�̹��� ���� ����
		D3DPOOL_MANAGED,			//���� �д� �̹������� � �޸𸮿� ��������...
		D3DX_DEFAULT,				//�׵θ� ǥ���� ��� �� ���ΰ�...
		D3DX_DEFAULT,				//Ȯ�� ������� �� ��� ó������...
		D3DCOLOR_XRGB(255, 0, 255),						//������ �̹��� ����...
		&m_pTexInfo->ImgInfo,		//�̹��� ������ ��� ����...
		NULL,						//8��Ʈ �̸��� �̹����� ���õ� ��...
		&m_pTexInfo->pTexture)))	//��𿡴� �ε��� �̹����� ������ ���ΰ�...
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

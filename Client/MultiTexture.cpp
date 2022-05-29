#include "StdAfx.h"
#include "MultiTexture.h"
#include "Device.h"
#include "TextureMgr.h"

CMultiTexture::CMultiTexture(void)
{
}

CMultiTexture::~CMultiTexture(void)
{
	Release();
}

HRESULT CMultiTexture::InsertTexture(const TCHAR* pPath,
									 const TCHAR* pStateKey,
									 const int& iCount)
{	
	TEXINFO*	pTexInfo = NULL;
	TCHAR	szPath[MAX_PATH] = L"";
	vector<TEXINFO*>	vecTexture;

	int iOne		= 0;
	int iTen		= 0;
	int iHundred	= 0;

	for(int i=0; i<iCount; ++i)
	{		
		if(iOne == 10)
		{
			++iTen;
			iOne = 0;
		}

		if(iTen == 10)
		{
			++iHundred;
			iTen = 0;
		}

		if(iCount >= 100)
		{
			wsprintf(szPath, pPath, iHundred, iTen, iOne);			
		}
		else if(100 > iCount && iCount > 10)
		{
			wsprintf(szPath, pPath, iTen, iOne);
		}
		else if(10 >= iCount && iCount >= 0)
		{
			wsprintf(szPath, pPath, iOne);
		}

		++iOne;

		pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		CTextureMgr::GetInstance()->GetCurrentPath() = szPath;

		if(FAILED(D3DXGetImageInfoFromFile(szPath, &pTexInfo->ImgInfo)))
		{
			MSG_BOX(szPath);
			return E_FAIL;
		}

		if(FAILED(D3DXCreateTextureFromFileEx(
			CDevice::GetInstance()->GetDevice(),
			szPath,
			pTexInfo->ImgInfo.Width,
			pTexInfo->ImgInfo.Height,
			pTexInfo->ImgInfo.MipLevels,
			0,
			pTexInfo->ImgInfo.Format,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 0, 255),
			&pTexInfo->ImgInfo,
			NULL,


			&pTexInfo->pTexture)))
		{
			MSG_BOX(szPath);
			return E_FAIL;
		}

		vecTexture.push_back(pTexInfo);
	}

	TCHAR*	pKey = new TCHAR[MAX_PATH];
	lstrcpy(pKey, pStateKey);

	m_MapMultiTexture.insert(make_pair(pKey, vecTexture));

	return S_OK;
}

const TEXINFO* CMultiTexture::GetTexture(const TCHAR* pKey,
										 const int& iCount)
{
	unordered_map<const TCHAR*, vector<TEXINFO*>>::iterator iter = m_MapMultiTexture.begin();
	unordered_map<const TCHAR*, vector<TEXINFO*>>::iterator iter_end = m_MapMultiTexture.end();

	iter = find_if(iter, iter_end, STRCOMPARE(pKey));

	//iter = m_MapMultiTexture.find(pKey);

	if(iter == m_MapMultiTexture.end())
		return NULL;

	return iter->second[iCount];
}

void CMultiTexture::Release(void)
{
	unordered_map<const TCHAR*, vector<TEXINFO*>>::iterator iter = m_MapMultiTexture.begin();
	unordered_map<const TCHAR*, vector<TEXINFO*>>::iterator iter_end = m_MapMultiTexture.end();

	for(iter; iter != iter_end; ++iter)
	{
		delete[] iter->first;

		for(size_t i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->pTexture->Release();
			delete iter->second[i];
		}
		iter->second.clear();
	}
	m_MapMultiTexture.clear();
}
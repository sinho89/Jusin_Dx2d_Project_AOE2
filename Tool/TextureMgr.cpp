#include "StdAfx.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::~CTextureMgr(void)
{
	Release();
}

HRESULT CTextureMgr::InsertTexture(const TCHAR* pFilePath, const TCHAR* pObjkey, 
								   eTextureType eType /*= TEX_SINGLE*/, 
								   const TCHAR* pStateKey /*= L""*/, 
								   const int& iCnt /*= 0*/)
{
	unordered_map<const TCHAR*, CTexture*>::iterator iter = 
		m_MaptTexture.begin();
	unordered_map<const TCHAR*, CTexture*>::iterator iter_end = 
		m_MaptTexture.end();

	iter = find_if(iter, iter_end, STRCOMPARE(pObjkey)); /*m_MaptTexture.find(pObjkey)*/;

	if(iter != iter_end && eType == TEX_SINGLE)
	{
		MSG_BOX(L"싱글 텍스쳐 중복키...");
		return E_FAIL;
	}

	CTexture* pTexture = NULL;
	switch(eType)
	{
	case TEX_SINGLE:
		pTexture = new CSingleTexture;
		break;
	case TEX_MULTI:
		pTexture = new CMultiTexture;
		break;
	}

	if(FAILED(pTexture->InsertTexture(pFilePath, pStateKey, iCnt)))
	{
		MSG_BOX(L"InsertTexture 실패");
		delete pTexture;
		return E_FAIL;
	}

	TCHAR*	pKey = new TCHAR[256];
	lstrcpy(pKey, pObjkey);

	m_MaptTexture.insert(make_pair(pKey, pTexture));

	return S_OK;
}

void CTextureMgr::Release(void)
{
	unordered_map<const TCHAR*, CTexture*>::iterator iter = m_MaptTexture.begin();
	unordered_map<const TCHAR*, CTexture*>::iterator iter_end = m_MaptTexture.end();

	for(iter; iter != iter_end; ++iter)
	{
		delete[] iter->first;
		delete iter->second;
	}
	m_MaptTexture.clear();
}


const	TEXINFO* CTextureMgr::GetTexture(const wstring& strObjkey, 
										 const wstring& strStateKey /*= L""*/, 
										 const int& iCnt /*= 0*/)
{
	unordered_map<const TCHAR*, CTexture*>::iterator iter = m_MaptTexture.begin();
	unordered_map<const TCHAR*, CTexture*>::iterator iter_end = m_MaptTexture.end();

	iter = find_if(iter, iter_end, STRCOMPARE(strObjkey.c_str()));

	if(iter == m_MaptTexture.end())
		return NULL;

	return iter->second->GetTexture(strStateKey.c_str(), iCnt);

}

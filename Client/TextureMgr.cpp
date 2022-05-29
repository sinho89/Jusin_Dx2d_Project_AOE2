#include "StdAfx.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr(void){}

CTextureMgr::~CTextureMgr(void)
{
	Release();
}

HRESULT CTextureMgr::InsertTexture(const TCHAR* pFilePath, const TCHAR* pObjkey, 
								   eTextureType eType, 
								   const TCHAR* pStateKey, 
								   const int& iCnt)
{
	unordered_map<const TCHAR*, CTexture*>::iterator iter = 
		m_MaptTexture.begin();
	unordered_map<const TCHAR*, CTexture*>::iterator iter_end = 
		m_MaptTexture.end();

	iter = find_if(iter, iter_end, STRCOMPARE(pObjkey));
	//iter = m_MaptTexture.find(pObjkey);


	if(iter == m_MaptTexture.end())
	{

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
	}
	else
	{
		if(eType == TEX_MULTI)
			iter->second->InsertTexture(pFilePath, pStateKey, iCnt);
	}	
	
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
	//iter = m_MaptTexture.find(strObjkey.c_str());

	if(iter == m_MaptTexture.end())
		return NULL;

	return iter->second->GetTexture(strStateKey.c_str(), iCnt);
}

//void CTextureMgr::ReleaseDynamicResource(void)
//{
//	unordered_map<const TCHAR*, CTexture*>::iterator iter = m_MaptTexture.begin();
//	unordered_map<const TCHAR*, CTexture*>::iterator iter_end = m_MaptTexture.end();
//
//	for(iter; iter != iter_end;)
//	{
//		if(iter->second->GetReleaseType() == RT_DYNAMIC)
//		{
//			delete iter->second;
//			delete [] iter->first;
//			iter = m_MaptTexture.erase(iter);
//		}
//		else
//			++iter;
//	}
//}

void CTextureMgr::ReadImagePath(wstring wstImgPath)
{
	wifstream	LoadFile;
	LoadFile.open(wstImgPath.c_str(), ios::in);

	TCHAR	szObjKey[MIN_STR] = L"";
	TCHAR	szStateKey[MIN_STR] = L"";
	TCHAR	szCount[MIN_STR] = L"";
	TCHAR	szImgPath[MIN_STR] = L"";

	wstring wstrCombine = L"";

	while(!LoadFile.eof())
	{
		LoadFile.getline(szObjKey, MIN_STR, '|');
		LoadFile.getline(szCount, MIN_STR, '|');
		LoadFile.getline(szStateKey, MIN_STR, '|');
		LoadFile.getline(szImgPath, MAX_PATH);

		wstrCombine = wstring(szObjKey) + L"|";
		wstrCombine += wstring(szCount) + L"|";
		wstrCombine += wstring(szStateKey) + L"|";
		wstrCombine += wstring(szImgPath);

		int iCount = _ttoi(szCount);

		if(FAILED(InsertTexture(szImgPath, szObjKey, TEX_MULTI, szStateKey, iCount)))
		{
			MSG_BOX((wstImgPath + L"로드 실패").c_str());
		}
	}

	LoadFile.close();
}

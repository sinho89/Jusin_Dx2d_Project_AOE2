#pragma once

class CTexture;

class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

private:
	unordered_map<const TCHAR*, CTexture*>	m_MaptTexture;
	wstring									m_strCurrentPath;
	
public:
	wstring&	GetCurrentPath(void)
	{
		return m_strCurrentPath;
	}

public:
	HRESULT	InsertTexture(const TCHAR* pFilePath,
		const TCHAR* pObjkey, eTextureType eType = TEX_SINGLE,
		const TCHAR* pStateKey = L"", const int& iCnt = 0);

	const	TEXINFO* GetTexture(const wstring& strObjkey,
		const wstring& strStateKey = L"",
		const int& iCnt = 0);

	void	Release(void);

	//void	ReleaseDynamicResource(void);
	void	ReadImagePath(wstring wstImgPath);

private:
	CTextureMgr(void);
public:
	~CTextureMgr(void);
};

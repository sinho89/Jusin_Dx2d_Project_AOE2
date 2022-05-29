#pragma once
#include "texture.h"

class CSingleTexture :
	public CTexture
{
private:
	TEXINFO*	m_pTexInfo;

public:
	virtual HRESULT InsertTexture(const TCHAR* pPath,
		const TCHAR* pStateKey = L"",
		const int& iCount = 0);

	virtual const TEXINFO* GetTexture(const TCHAR* pKey = L"",
		const int& iCount = 0);

	virtual void Release(void);
public:
	CSingleTexture(void);
	virtual ~CSingleTexture(void);
};

#pragma once
#include "obj.h"

class CBrokenEffect :
	public CObj
{
private:
	const TEXINFO* Effect[20];
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CBrokenEffect(void);
	CBrokenEffect(D3DXVECTOR3 _vPos)
	{
		m_tInfo.vPos = _vPos;
	};
	virtual ~CBrokenEffect(void);
};

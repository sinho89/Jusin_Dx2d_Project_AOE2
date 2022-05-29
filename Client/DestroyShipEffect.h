#pragma once
#include "obj.h"

class CDestroyShipEffect :
	public CObj
{
private:
	const TEXINFO* Effect[20];
	int m_iTime;
	int m_iMaxTime;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CDestroyShipEffect(void);
	CDestroyShipEffect(D3DXVECTOR3 _vPos)
	{
		m_tInfo.vPos = _vPos;
	};
	virtual ~CDestroyShipEffect(void);
};

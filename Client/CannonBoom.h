#pragma once
#include "obj.h"

class CCannonBoom :
	public CObj
{
private:
	const TEXINFO* Effect[10];
	const TEXINFO* MissEffect[15];
	int m_iTime;
	int m_iMaxTime;
	bool	m_bShot;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CCannonBoom(void);
	CCannonBoom(D3DXVECTOR3 _vPos, bool _bShot)
	{
		m_tInfo.vPos = _vPos;
		m_bShot = _bShot;
	};
	virtual ~CCannonBoom(void);
};

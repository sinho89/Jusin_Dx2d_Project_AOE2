#pragma once
#include "obj.h"

class CBroken :
	public CObj
{
private:
	const TEXINFO* pBroken[4];
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CBroken(void);
	CBroken(D3DXVECTOR3 _vPos, eBUILD_SIZE_TYPE _SizeType, eBuildType _BuildType)
	{
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eSizeType = _SizeType;
		m_tInfo.m_eBuildType = _BuildType;
		m_tInfo.m_eObjType = OT_NONE;
	}
	virtual ~CBroken(void);
};

#pragma once
#include "obj.h"

class CSequence :
	public CObj
{
private:
	const TEXINFO*	m_SequenceTex[3];

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CSequence(void);
	CSequence(D3DXVECTOR3 _vPos, eBUILD_SIZE_TYPE _SizeType, eBuildType _BuildType)
	{
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eSizeType = _SizeType;
		m_tInfo.m_eBuildType = _BuildType;
		m_tInfo.m_eObjType = OT_NONE;
	}
	virtual ~CSequence(void);
};

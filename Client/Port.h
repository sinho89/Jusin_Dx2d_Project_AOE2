#pragma once
#include "obj.h"

class CPort :
	public CObj
{
private:
	const TEXINFO*	pPortTex;
	const TEXINFO*	pPortTex2;
	const TEXINFO*	pPortTex3;
	const TEXINFO*	pPortTex4;
	const TEXINFO*	pPortShadowTex;
	const TEXINFO*	pPortShadowTex2;
	const TEXINFO*	pPortShadowTex3;
	const TEXINFO*	pBirdTex[60];
	const TEXINFO*  pSelectionLine;
	const TEXINFO*	pSmallFire[20];
	const TEXINFO*	pMidFire[20];
	const TEXINFO*	pBigFire[20];

	FRAME	m_tFireFrame;
	FRAME	m_tTime;
	int m_iTime;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CPort(void);
	CPort(D3DXVECTOR3 _vPos, eBuildType _Type, ePlayerType _TeamType, BYTE _byDrawID)
	{
		m_tInfo.vPos			= _vPos;
		m_tInfo.m_eBuildType	= _Type;
		m_tInfo.m_ePlayerType	= _TeamType;
		m_tInfo.byDrawID		= _byDrawID;
		m_tInfo.m_eObjType		= OT_BUILD;
		m_tInfo.m_eSaveType		= SRT_PORT;
		m_tInfo.m_eBuildType	= BT_PORT;
		m_tInfo.m_eSizeType		= BST_MID;
		//m_tTile.vPos = rTile.vPos;
	};
	virtual ~CPort(void);
};

#pragma once
#include "obj.h"

class CTown :
	public CObj
{
private:
	const TEXINFO*	pTownTex;
	const TEXINFO*	pTownTex2;
	const TEXINFO*	pTownTex3;
	const TEXINFO*	pTownTex4;
	const TEXINFO*	pTownShadowTex;
	const TEXINFO*	pTownShadowTex2;
	const TEXINFO*	pSelectionLine;
	const TEXINFO*	pSmallFire[20];
	const TEXINFO*	pMidFire[20];
	const TEXINFO*	pBigFire[20];
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CTown(void);
	CTown(D3DXVECTOR3 _vPos, eBuildType _Type, ePlayerType _TeamType, BYTE _byDrawID)
	{
		m_tInfo.vPos			= _vPos;
		m_tInfo.m_eBuildType	= _Type;
		m_tInfo.m_ePlayerType	= _TeamType;
		m_tInfo.byDrawID		= _byDrawID;
		m_tInfo.m_eObjType		= OT_BUILD;
		m_tInfo.m_eSaveType		= SRT_EVERYTHING;
		m_tInfo.m_eBuildType	= BT_TOWN;
		m_tInfo.m_eSizeType = BST_MAX;
		//m_tTile.vPos = rTile.vPos;

	};
	virtual ~CTown(void);
};

#pragma once
#include "obj.h"

class CMine :
	public CObj
{
private:
	const TEXINFO*	pMineTex;
	const TEXINFO*	pSelectionLine;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CMine(void);
	CMine(D3DXVECTOR3 _vPos, eBuildType _Type, ePlayerType _TeamType, BYTE _byDrawID)
	{
		m_tInfo.vPos			= _vPos;
		m_tInfo.m_eBuildType	= _Type;
		m_tInfo.m_ePlayerType	= _TeamType;
		m_tInfo.byDrawID		= _byDrawID;
		m_tInfo.m_eObjType		= OT_BUILD;
		m_tInfo.m_eSaveType		= SRT_MINE;
		m_tInfo.m_eBuildType	= BT_MINE;
		m_tInfo.m_eSizeType		= BST_MID;
		//m_tTile.vPos = rTile.vPos;

	};
	virtual ~CMine(void);
};

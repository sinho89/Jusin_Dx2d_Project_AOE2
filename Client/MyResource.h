#pragma once
#include "obj.h"

class CMyResource :
	public CObj
{
private:
	const TEXINFO* pTreeTex[10];
	const TEXINFO* pTreeShadowTex[10];
	const TEXINFO* pChoppingTreeTex[5];
	const TEXINFO* pRockTex[7];
	const TEXINFO* pGoldTex[7];
	const TEXINFO* pCherryTex[4];
	const TEXINFO* pFishTex[49];
	const TEXINFO* pChamChiTex[48];

	int		m_iFishNum;
	int		m_iTime;
	bool	m_bFogColl;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void LoadResource();
public:
	CMyResource(void);
	CMyResource(D3DXVECTOR3 _vPos, eResourceType _Type, BYTE _byDrawID)
	{
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eResourceType = _Type;
		m_tInfo.byDrawID = _byDrawID;
		m_tInfo.m_eObjType = OT_RESOURCE;
		m_tInfo.iHp = 200;
		m_tInfo.m_eSizeType = BST_MIN;
		m_tInfo.bView = true;
		m_tInfo.iIndex = -1;

		//m_tTile.vPos = rTile.vPos;

	};
	CMyResource(D3DXVECTOR3 _vPos, eResourceType _Type, BYTE _byDrawID, int iIndex)
	{
		m_tInfo.bView = false;
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eResourceType = _Type;
		m_tInfo.byDrawID = _byDrawID;
		m_tInfo.m_eObjType = OT_RESOURCE;
		m_tInfo.iHp = 200;
		m_tInfo.m_eSizeType = BST_MIN;
		m_tInfo.iIndex = iIndex;

		//m_tTile.vPos = rTile.vPos;

	};
	CMyResource(INFO*	pInfo)
	{
		memcpy(&m_tInfo, pInfo, sizeof(INFO));
		//m_tTile.vPos = rTile.vPos;

	};
	virtual ~CMyResource(void);
};

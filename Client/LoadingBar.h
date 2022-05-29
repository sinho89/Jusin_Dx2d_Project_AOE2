#pragma once
#include "obj.h"
#include "TextureMgr.h"
class CLoadingBar :
	public CObj
{

private: // °Ç¼³
	const TEXINFO*	pTexture[99];
	const TEXINFO*	pMakeTex;
	int m_iTime;
	int m_TexSlideX;
	bool	m_bRender;

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void NormalRender();
	void VillagerRender();
	void FishShipRender();
	void TransShipRender();
	void GalleyShipRender();
	void DestroyShipRender();
	void FireShipRender();
	void CannonShipRender();
	void SoldierRender();
public:
	void MakeVillager();
	void MakeFishShip();
	void MakeTransShip();
	void MakeGalleyShip();
	void MakeDestroyShip();
	void MakeFireShip();
	void MakeCannonShip();
	void MakeSoldier();
	void VillagerRenderCheck();
	void FishShipRenderCheck();
	void TransShipRenderCheck();
	void GalleyShipRenderCheck();
	void DestroyShipRenderCheck();
	void FireShipRenderCheck();
	void CannonShipRenderCheck();
	void SoldierRenderCheck();
public:
	CLoadingBar(void);
	CLoadingBar(D3DXVECTOR3 _vPos, eGAUGE_TYPE _eType)
	{
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eGaugeType = _eType;
	}
	virtual ~CLoadingBar(void);
};

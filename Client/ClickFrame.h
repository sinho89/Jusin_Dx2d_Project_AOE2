#pragma once
#include "obj.h"

class CClickFrame :
	public CObj
{
private:
	const TEXINFO*	pClickIcon[2];
	const TEXINFO*	pBuildTex[22];
	const TEXINFO*	pUnitControlIcon[44];
	const TEXINFO*	pInfoIcon[9];
	const TEXINFO*	pUnitIcon[53];
	const TEXINFO*	pUpgradeIcon[109];

	bool			iClickFrame;
	bool			bClickCheck;
	bool			bKeyUpCheck;
	bool			bPortType;
	int				iIndex;

private: // 건설
	const TEXINFO*	pBuildViewTex;


public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void SetVillagerButton();
	void SetBattleUnitButton();
	void VillagerBuildDest();
	void VillagerBuildSource();
	void PushBtnCheck();
	void ClearButton();

	void SetTownButton();
	void SetPortButton();
	void SetPort2Button();
	void SetMineButton();
	void SetBarracksButton();
	void SetMillButton();
public:
	void VillagerBaseRender();
	void BattleUnitRender();
	void VillagerBuildDestRender();
	void VillagerBuildSourceRender();
	
	void TownRender();
	void PortRender();
	void Port2Render();
	void WoodRender();
	void MineRender();
	void MillRender();
	void BarracksRender();

public: // 건설시 프리뷰이미지
	void BuildRender();
	void BuildHome();
	void BuildPort();
	void BuildWood();
	void BuildMine();
	void BuildBarracks();
	void BuildMill();
public:
	CClickFrame(void);
	CClickFrame(D3DXVECTOR3	_vPos, int _iIndex)
	{
		m_tInfo.vPos = _vPos;
		iIndex = _iIndex;
	}
	virtual ~CClickFrame(void);
};

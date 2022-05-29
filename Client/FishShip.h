#pragma once
#include "obj.h"
#include "ObjMgr.h"
class CFishShip :
	public CObj
{
private:
	int m_iTime;
	const TEXINFO* STDTex[5];
	const TEXINFO* FishingTex[5];
	const TEXINFO* DeathTex[5];
	const TEXINFO* pSelectionLine;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void GetResource();
	void FIndSaveBuild();
	void SaveMove();
	void Building();
public:
	CFishShip(void);
	CFishShip(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vWayPos, eUnitType _Type, ePlayerType _TeamType, BYTE _byDrawID)
	{
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eUnitType = _Type;
		m_tInfo.m_ePlayerType = _TeamType;
		m_tInfo.byDrawID = _byDrawID;
		m_tInfo.m_eObjType = OT_UNIT;
		m_tInfo.m_eGroundType = GT_SEA;
		m_tInfo.m_eUnitType = UT_FISHER;
		m_tInfo.iGetResourceCount = 0;
		m_tInfo.iWorkingIndex = 0;

		m_tInfo.fAngle = 270.f;
		m_tInfo.vDir = D3DXVECTOR3(0.f, 1.f, 0.f);
		m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
		m_tInfo.wstrObjKey = L"FishShip";
		m_tInfo.byOriID = m_tInfo.byDrawID;
		m_tInfo.m_eObjType = OT_UNIT;
		m_tInfo.fSpeed = 75.f;
		m_tInfo.vGoalPos = _vWayPos;
		m_tInfo.bMove = true;

		if(m_tInfo.m_ePlayerType == PT_PLAYER)
		{
			list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"MainUI", SORT_UI).begin();
			(*iter)->GetInfo()->iTreeNum -= 100;
			m_tInfo.m_eStateType = STATE_WALK;
		}
		else if(m_tInfo.m_ePlayerType == PT_ENEMY)
		{
		}

	};
	virtual ~CFishShip(void);
};

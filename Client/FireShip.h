#pragma once
#include "obj.h"
#include "ObjMgr.h"
class CFireShip :
	public CObj
{
private:
	int m_iTime;
	int m_iSailTime;
	const TEXINFO* STDTex[9];
	const TEXINFO* DeathTex[6];
	const TEXINFO* SailTex[100];
	const TEXINFO* pSelectionLine;

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CFireShip(void);
	CFireShip(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vWayPos, eUnitType _Type, ePlayerType _TeamType, BYTE _byDrawID)
	{
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eUnitType = _Type;
		m_tInfo.m_ePlayerType = _TeamType;
		m_tInfo.byDrawID = _byDrawID;
		m_tInfo.bySailDrawID = 0;
		m_tInfo.m_eObjType = OT_UNIT;
		m_tInfo.m_eGroundType = GT_SEA;
		m_tInfo.m_eUnitType = UT_FIRESHIP;
		m_tInfo.iGetResourceCount = 0;
		m_tInfo.iWorkingIndex = 0;

		m_tInfo.fAngle = 270.f;
		m_tInfo.vDir = D3DXVECTOR3(0.f, 1.f, 0.f);
		m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
		m_tInfo.wstrObjKey = L"FireShip";
		m_tInfo.byOriID = m_tInfo.byDrawID;
		m_tInfo.byOriSailID = m_tInfo.bySailDrawID;
		m_tInfo.m_eObjType = OT_UNIT;
		m_tInfo.fSpeed = 60.f;
		m_tInfo.vGoalPos = _vWayPos;
		m_tInfo.bMove = true;
		m_tInfo.iIndex = -1;

		if(m_tInfo.m_ePlayerType == PT_PLAYER)
		{
			list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"MainUI", SORT_UI).begin();
			(*iter)->GetInfo()->iTreeNum -= 100;
			(*iter)->GetInfo()->iStoneNum -= 100;
			(*iter)->GetInfo()->iGoldNum -= 50;

			m_tInfo.m_eStateType = STATE_WALK;
		}
		else if(m_tInfo.m_ePlayerType == PT_ENEMY)
		{
			m_tInfo.m_eStateType = STATE_WALK;
		}

	};
	virtual ~CFireShip(void);
};

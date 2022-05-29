#pragma once
#include "obj.h"
#include "ObjMgr.h"

class CVillager :
	public CObj
{
private:
	const TEXINFO* STDTex[75];
	const TEXINFO* WalkTex[75];
	const TEXINFO* ATTTex[75];
	const TEXINFO* Berry_Walk_Tex[75];
	const TEXINFO* Berry_Get_Tex[75];
	const TEXINFO* Building_Tex[75];
	const TEXINFO* Mine_Get_Tex[75];
	const TEXINFO* Gold_Carry_Tex[75];
	const TEXINFO* Stone_Carry_Tex[75];
	const TEXINFO* Wood_Carry_Tex[75];
	const TEXINFO* Wood_Chopping_Tex[75];
	const TEXINFO* Dying_Tex[75];
	const TEXINFO* Dead_Tex[25];
	const TEXINFO* pSelectionLine;

	int m_iTime;
	bool	bGetResource;
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
	CVillager(void);
	CVillager(D3DXVECTOR3 _vPos, eUnitType _Type, ePlayerType _TeamType, BYTE _byDrawID)
	{
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eUnitType = _Type;
		m_tInfo.m_ePlayerType = _TeamType;
		m_tInfo.byDrawID = _byDrawID;
		m_tInfo.m_eObjType = OT_UNIT;
		m_tInfo.m_eGroundType = GT_GROUND;
		m_tInfo.m_eUnitType = UT_VILLAGER;
		m_tInfo.iGetResourceCount = 0;
		m_tInfo.iWorkingIndex = 0;

		m_tInfo.fAngle = 270.f;
		m_tInfo.vDir = D3DXVECTOR3(0.f, 1.f, 0.f);
		m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
		m_tInfo.wstrObjKey = L"Villager";
		m_tInfo.byOriID = m_tInfo.byDrawID;
		m_tInfo.m_eObjType = OT_UNIT;
		m_tInfo.fSpeed = 50.f;
		
		if(m_tInfo.m_ePlayerType == PT_PLAYER)
		{
			m_tInfo.wstrStateKey = L"STD";
		}
		else if(m_tInfo.m_ePlayerType == PT_ENEMY)
		{
			m_tInfo.wstrObjKey = L"Enemy_Villager";
		}

	};

	CVillager(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vWayPos, eUnitType _Type, ePlayerType _TeamType, BYTE _byDrawID)
	{
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eUnitType = _Type;
		m_tInfo.m_ePlayerType = _TeamType;
		m_tInfo.byDrawID = _byDrawID;
		m_tInfo.m_eObjType = OT_UNIT;
		m_tInfo.m_eGroundType = GT_GROUND;
		m_tInfo.m_eUnitType = UT_VILLAGER;
		m_tInfo.iGetResourceCount = 0;
		m_tInfo.iWorkingIndex = 0;

		m_tInfo.fAngle = 270.f;
		m_tInfo.vDir = D3DXVECTOR3(0.f, 1.f, 0.f);
		m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
		m_tInfo.wstrObjKey = L"Villager";
		m_tInfo.byOriID = m_tInfo.byDrawID;
		m_tInfo.m_eObjType = OT_UNIT;
		m_tInfo.fSpeed = 50.f;
		m_tInfo.vGoalPos = _vWayPos;
		m_tInfo.bMove = true;
		m_tInfo.iIndex  = -1;

		if(m_tInfo.m_ePlayerType == PT_PLAYER)
		{
			list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"MainUI", SORT_UI).begin();
			(*iter)->GetInfo()->iFoodNum -= 100;
			m_tInfo.m_eStateType = STATE_WALK;
		}
		else if(m_tInfo.m_ePlayerType == PT_ENEMY)
		{
			m_tInfo.wstrObjKey = L"Enemy_Villager";
			m_tInfo.m_eStateType = STATE_WALK;
		}

	};
	virtual ~CVillager(void);
};

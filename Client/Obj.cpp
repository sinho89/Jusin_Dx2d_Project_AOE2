#include "StdAfx.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "ButtonMgr.h"
#include "MouseMgr.h"
#include "TImeMgr.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Arrow.h"

D3DXVECTOR3 CObj::m_vScroll = D3DXVECTOR3(-2000.f, 0.f, 0.f);

unsigned int	CObj::m_iMakeVillager = 0;
unsigned int	CObj::m_iMakeFishShip = 0;
unsigned int	CObj::m_iMakeTransShip = 0;
unsigned int	CObj::m_iMakeGalleyShip = 0;
unsigned int	CObj::m_iMakeDestroyShip = 0;
unsigned int	CObj::m_iMakeFireShip = 0;
unsigned int	CObj::m_iMakeCannonShip = 0;
unsigned int	CObj::m_iMakeSoldier = 0;
bool			CObj::m_bVillagerGaugeRender = false;
bool			CObj::m_bFishShipGaugeRender = false;
bool			CObj::m_bTransShipGaugeRender = false;
bool			CObj::m_bGalleyShipGaugeRender = false;
bool			CObj::m_bDestroyShipGaugeRender = false;
bool			CObj::m_bFireShipGaugeRender = false;
bool			CObj::m_bCannonShipGaugeRender = false;
bool			CObj::m_bSoldierGaugeRender = false;
eAgeType		CObj::m_eAgeType			 = AT_DARK;
eAgeType		CObj::m_eEnemyAgeType		 = AT_DARK;


bool		CObj::FormationWidth = false;
bool		CObj::FormationRect = false;
bool		CObj::FormationCheck = false;
bool		CObj::FormationDiv = false;
bool		CObj::m_bWarStart = false;

CObj::CObj(void)
{
	m_tInfo.bSelection = false;
	m_bLbuttonCheck = false;
	bGetResource= false;
	m_tInfo.m_eStateType = STATE_STD;
	m_bFrameStart = false;
	m_tInfo.bDirCheck = false;
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_dwTime = GetTickCount();
	m_dwEnemyTime = GetTickCount();
	m_tInfo.bDeath = false;
	m_tInfo.bAttack = false;
}

CObj::~CObj(void)
{
}

INFO* CObj::GetInfo()
{
	return &m_tInfo;
}

void CObj::KeyCheckFunc()
{
	

	
	/*if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if(vMouse.y > 450)
			return;
		
		vMouse.x -= CObj::m_vScroll.x;
		vMouse.y -= CObj::m_vScroll.y;

		if(m_tInfo.m_eObjType == OT_UNIT && m_tInfo.bSelection == true)
		{
			m_tInfo.m_eStateType = STATE_WALK;
			m_tInfo.vGoalPos = vMouse;

			int iIndex = CTileMgr::GetInstance()->GetTileIndex(m_tInfo.vGoalPos);

			if(iIndex == -1)
			{
				m_tInfo.bMove = false;
				m_tInfo.m_eStateType = STATE_STD;
				return;
			}
			else
				m_tInfo.bMove = true;


			if(m_tInfo.wstrObjKey == L"Villager")
				CObj::SetVillagerDir();

			if(m_tInfo.m_eGroundType == GT_GROUND)
			{
				if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_SEA)
				{
					// 지상 유닛 해상 못가게 하기
				}
			}
			if(m_tInfo.m_eGroundType == GT_GROUND)
			{
				if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_GROUND)
				{
					// 해상 유닛 지상 못가게 하기
				}
			}
		}
	}*/

}
void CObj::ArrowDirCheckFunc(D3DXVECTOR3 _vDir, D3DXVECTOR3 _vGoalPos)
{
	float fCos = D3DXVec3Dot(&m_tInfo.vLook, &m_tInfo.vDir);
	m_tInfo.fAngle = acosf(fCos);

	if(m_tInfo.vPos.y < _vGoalPos.y)
	{
		m_tInfo.fAngle = D3DX_PI * 2 - m_tInfo.fAngle;
	}

	m_tInfo.fAngle = m_tInfo.fAngle * 180.f / D3DX_PI;
}

void CObj::SixteenDirCheckFunc(D3DXVECTOR3 _vDir, D3DXVECTOR3 _vGoalPos)
{
	float fCos = D3DXVec3Dot(&m_tInfo.vLook, &m_tInfo.vDir);
	m_tInfo.fAngle = acosf(fCos);

	if(m_tInfo.vPos.y < _vGoalPos.y)
	{
		m_tInfo.fAngle = D3DX_PI * 2 - m_tInfo.fAngle;
	}

	m_tInfo.fAngle = m_tInfo.fAngle * 180.f / D3DX_PI;

	if((m_tInfo.fAngle <= 360.0 && m_tInfo.fAngle > 348.75)
		|| (m_tInfo.fAngle >= 0.0 && m_tInfo.fAngle <= 11.25)) // RIGHT
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_RIGHT; 
	}
	if(m_tInfo.fAngle <= 33.75 && m_tInfo.fAngle > 11.25) // UP_R1
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_UP_R1;
	}
	if(m_tInfo.fAngle <= 56.25 && m_tInfo.fAngle > 33.75) // UP_R2
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_UP_R2;
	}
	if(m_tInfo.fAngle <= 78.75 && m_tInfo.fAngle > 56.25) // UP_R3
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_UP_R3;
	}
	if(m_tInfo.fAngle <= 101.25 && m_tInfo.fAngle > 78.75) // UP
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_UP;
	}
	if(m_tInfo.fAngle <= 123.75 && m_tInfo.fAngle > 101.25) // UP_L3
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_UP_L3;
	}
	if(m_tInfo.fAngle <= 146.25 && m_tInfo.fAngle > 123.75) // UP_L2
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_UP_L2;
	}
	if(m_tInfo.fAngle <= 168.75 && m_tInfo.fAngle > 146.25) // UP_L1
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_UP_L1;
	}
	if(m_tInfo.fAngle <= 191.25 && m_tInfo.fAngle > 168.75) // LEFT
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_LEFT;
	}
	if(m_tInfo.fAngle <= 213.75 && m_tInfo.fAngle > 191.25) // DOWN_L1
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_DOWN_L1;
	}
	if(m_tInfo.fAngle <= 236.25 && m_tInfo.fAngle > 213.75) // DOWN_L2
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_DOWN_L2;
	}
	if(m_tInfo.fAngle <= 258.75 && m_tInfo.fAngle > 236.25) // DOWN_L3
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_DOWN_L3;
	}
	if(m_tInfo.fAngle <= 281.25 && m_tInfo.fAngle > 258.75) // DOWN
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_DOWN;
	}
	if(m_tInfo.fAngle <= 303.75 && m_tInfo.fAngle > 281.25) // DOWN_R3
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_DOWN_R3;
	}
	if(m_tInfo.fAngle <= 326.25 && m_tInfo.fAngle > 303.75) // DOWN_R2
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_DOWN_R2;
	}
	if(m_tInfo.fAngle <= 348.75 && m_tInfo.fAngle > 326.25) // DOWN_R1
	{
		m_tInfo.m_eSixteenDirType = SIXTEEN_DIR_DOWN_R1;
	}
}
void CObj::DirCheckFunc(D3DXVECTOR3 _vDir, D3DXVECTOR3 _vGoalPos)
{
	float fCos = D3DXVec3Dot(&m_tInfo.vLook, &m_tInfo.vDir);
	m_tInfo.fAngle = acosf(fCos);

	if(m_tInfo.vPos.y < _vGoalPos.y)
	{
		m_tInfo.fAngle = D3DX_PI * 2 - m_tInfo.fAngle;
	}

	m_tInfo.fAngle = m_tInfo.fAngle * 180.f / D3DX_PI;

	if((m_tInfo.fAngle <= 360.0 && m_tInfo.fAngle >= 337.5)
		|| (m_tInfo.fAngle >= 0.0 && m_tInfo.fAngle <= 22.4)) // RIGHT
	{
		m_tInfo.m_eDirType = DIR_RIGHT;
	}
	if(m_tInfo.fAngle <= 67.4 && m_tInfo.fAngle >= 22.5) // UP_R
	{
		m_tInfo.m_eDirType = DIR_UP_R;
	}
	if(m_tInfo.fAngle <= 112.4 && m_tInfo.fAngle >= 67.5) // UP
	{
		m_tInfo.m_eDirType = DIR_UP;
	}
	if(m_tInfo.fAngle <= 157.4 && m_tInfo.fAngle >= 112.5) // UP_L
	{
		m_tInfo.m_eDirType = DIR_UP_L;
	}
	if(m_tInfo.fAngle <= 202.4 && m_tInfo.fAngle >= 157.5) // L
	{
		m_tInfo.m_eDirType = DIR_LEFT;
	}
	if(m_tInfo.fAngle <= 247.4 && m_tInfo.fAngle >= 202.5) // DOWN_L
	{
		m_tInfo.m_eDirType = DIR_DOWN_L;
	}
	if(m_tInfo.fAngle <= 292.4 && m_tInfo.fAngle >= 247.5) // DOWN
	{
		m_tInfo.m_eDirType = DIR_DOWN;
	}
	if(m_tInfo.fAngle <= 337.4 && m_tInfo.fAngle >= 292.5) // DOWN_R
	{
		m_tInfo.m_eDirType = DIR_DOWN_R;
	}
}
void CObj::SetSoldierDir()
{
	if(m_tInfo.m_eStateType == STATE_STD)
	{
		if(m_tInfo.m_eDirType == DIR_DOWN) // 보정필요
		{
			m_tFrame.fFrame = 0;
			m_tFrame.fMax = 5;
		}
		if(m_tInfo.m_eDirType == DIR_DOWN_L || m_tInfo.m_eDirType == DIR_DOWN_R)
		{
			m_tFrame.fFrame = 6;
			m_tFrame.fMax = 11;
		}
		if(m_tInfo.m_eDirType == DIR_LEFT || m_tInfo.m_eDirType == DIR_RIGHT)
		{
			m_tFrame.fFrame = 12;
			m_tFrame.fMax = 17;
		}
		if(m_tInfo.m_eDirType == DIR_UP_L || m_tInfo.m_eDirType == DIR_UP_R)
		{
			m_tFrame.fFrame = 18;
			m_tFrame.fMax = 23;
		}
		if(m_tInfo.m_eDirType == DIR_UP)
		{
			m_tFrame.fFrame = 24;
			m_tFrame.fMax = 29;
		}
		m_tFrame.fOriFrame = m_tFrame.fFrame;
	}
	if(m_tInfo.m_eStateType == STATE_WALK)
	{
		if(m_tInfo.m_eDirType == DIR_DOWN) // 보정필요
		{
			m_tFrame.fFrame = 0;
			m_tFrame.fMax = 11;
		}
		if(m_tInfo.m_eDirType == DIR_DOWN_L || m_tInfo.m_eDirType == DIR_DOWN_R)
		{
			m_tFrame.fFrame = 12;
			m_tFrame.fMax = 23;
		}
		if(m_tInfo.m_eDirType == DIR_LEFT || m_tInfo.m_eDirType == DIR_RIGHT)
		{
			m_tFrame.fFrame = 24;
			m_tFrame.fMax = 35;
		}
		if(m_tInfo.m_eDirType == DIR_UP_L || m_tInfo.m_eDirType == DIR_UP_R)
		{
			m_tFrame.fFrame = 36;
			m_tFrame.fMax = 47;
		}
		if(m_tInfo.m_eDirType == DIR_UP)
		{
			m_tFrame.fFrame = 48;
			m_tFrame.fMax = 59;
		}
		m_tFrame.fOriFrame = m_tFrame.fFrame;
	}
	if(m_tInfo.m_eStateType == STATE_ATTACK)
	{
		if(m_tInfo.m_eDirType == DIR_DOWN) // 보정필요
		{
			m_tFrame.fFrame = 0;
			m_tFrame.fMax = 9;
		}
		if(m_tInfo.m_eDirType == DIR_DOWN_L || m_tInfo.m_eDirType == DIR_DOWN_R)
		{
			m_tFrame.fFrame = 10;
			m_tFrame.fMax = 19;
		}
		if(m_tInfo.m_eDirType == DIR_LEFT || m_tInfo.m_eDirType == DIR_RIGHT)
		{
			m_tFrame.fFrame = 20;
			m_tFrame.fMax = 29;
		}
		if(m_tInfo.m_eDirType == DIR_UP_L || m_tInfo.m_eDirType == DIR_UP_R)
		{
			m_tFrame.fFrame = 30;
			m_tFrame.fMax = 39;
		}
		if(m_tInfo.m_eDirType == DIR_UP)
		{
			m_tFrame.fFrame = 40;
			m_tFrame.fMax = 49;
		}
		m_tFrame.fOriFrame = m_tFrame.fFrame;
	}
	if(m_tInfo.m_eStateType == STATE_DYING)
	{
		if(m_tInfo.m_eDirType == DIR_DOWN) // 보정필요
		{
			m_tFrame.fFrame = 0;
			m_tFrame.fMax = 9;
		}
		if(m_tInfo.m_eDirType == DIR_DOWN_L || m_tInfo.m_eDirType == DIR_DOWN_R)
		{
			m_tFrame.fFrame = 10;
			m_tFrame.fMax = 19;
		}
		if(m_tInfo.m_eDirType == DIR_LEFT || m_tInfo.m_eDirType == DIR_RIGHT)
		{
			m_tFrame.fFrame = 20;
			m_tFrame.fMax = 29;
		}
		if(m_tInfo.m_eDirType == DIR_UP_L || m_tInfo.m_eDirType == DIR_UP_R)
		{
			m_tFrame.fFrame = 30;
			m_tFrame.fMax = 39;
		}
		if(m_tInfo.m_eDirType == DIR_UP)
		{
			m_tFrame.fFrame = 40;
			m_tFrame.fMax = 49;
		}
		m_tFrame.fOriFrame = m_tFrame.fFrame;
	}
}
void CObj::SetVillagerDir()
{
	if(m_tInfo.m_eDirType == DIR_DOWN) // 보정필요
	{
		m_tFrame.fFrame = 0;
		m_tFrame.fMax = 14;
	}
	if(m_tInfo.m_eDirType == DIR_DOWN_L || m_tInfo.m_eDirType == DIR_DOWN_R)
	{
		m_tFrame.fFrame = 15;
		m_tFrame.fMax = 29;
	}
	if(m_tInfo.m_eDirType == DIR_LEFT || m_tInfo.m_eDirType == DIR_RIGHT)
	{
		m_tFrame.fFrame = 30;
		m_tFrame.fMax = 44;
	}
	if(m_tInfo.m_eDirType == DIR_UP_L || m_tInfo.m_eDirType == DIR_UP_R)
	{
		m_tFrame.fFrame = 45;
		m_tFrame.fMax = 69;
	}
	if(m_tInfo.m_eDirType == DIR_UP)
	{
		m_tFrame.fFrame = 60;
		m_tFrame.fMax = 74;
	}
	m_tFrame.fOriFrame = m_tFrame.fFrame;
}

void CObj::SetMatrix()
{
	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CObj::m_vScroll.x, m_tInfo.vPos.y  + CObj::m_vScroll.y, 0.f);

	if(m_tInfo.m_eDirType == DIR_DOWN_R
		|| m_tInfo.m_eDirType == DIR_RIGHT
		|| m_tInfo.m_eDirType == DIR_UP_R)
	{
		D3DXMATRIX	matScale;
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);

		m_tInfo.matWorld = matScale * matTrans;
	}
	else
		m_tInfo.matWorld = matTrans;
}
void CObj::SetSixTeenMatrix()
{
	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CObj::m_vScroll.x, m_tInfo.vPos.y  + CObj::m_vScroll.y, 0.f);

	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R1
		|| m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R2
		|| m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R3
		|| m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_RIGHT
		|| m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R1
		|| m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R2
		|| m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R3)
	{
		D3DXMATRIX	matScale;
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);

		m_tInfo.matWorld = matScale * matTrans;
	}
	else
		m_tInfo.matWorld = matTrans;
}
void CObj::WayMove()
{

}
void CObj::AttackFunc(CObj* pObj)
{
	if(m_tInfo.m_eStateType == STATE_ATTACK)
	{
		float fX = pObj->GetInfo()->vPos.x - m_tInfo.vPos.x;
		float fY = pObj->GetInfo()->vPos.y - m_tInfo.vPos.y;
		float fDest = sqrt(fX * fX + fY * fY);

		m_tInfo.vDir = pObj->GetInfo()->vPos - m_tInfo.vPos;
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		SixteenDirCheckFunc(m_tInfo.vDir,  pObj->GetInfo()->vPos);

		if(fDest < m_tInfo.iRange)
		{

			if(m_tInfo.bMove == true)
				m_tInfo.bMove = false;

			if(m_dwTime + 1000 < GetTickCount())
			{
				m_dwTime = GetTickCount();

				CObjMgr::GetInstance()->AddObject(L"Arrow", SORT_OBJECT, CFactory<CArrow>::CreateObject(this, pObj, m_tInfo.m_eSixteenDirType));
			}
		}
	}
}
void CObj::MoveFunc()
{
	if(m_tInfo.m_eStateType == STATE_WALK_BUILD)
	{
		m_tInfo.iGetResourceCount = 0;
		float fX = m_tInfo.vGoalPos.x - m_tInfo.vPos.x;
		float fY = m_tInfo.vGoalPos.y - m_tInfo.vPos.y - 10;
		float fDest = sqrt(fX * fX + fY * fY);

		m_tInfo.vDir = m_tInfo.vGoalPos - m_tInfo.vPos;
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		if(m_tInfo.m_eUnitType == UT_TRANSSHIP || m_tInfo.m_eUnitType == UT_GALLYSHIP)
			SixteenDirCheckFunc(m_tInfo.vDir, m_tInfo.vGoalPos);
		else
			DirCheckFunc(m_tInfo.vDir, m_tInfo.vGoalPos);
		if(m_tInfo.bDirCheck == false)
		{
			if(m_tInfo.m_eUnitType == UT_VILLAGER)
				SetVillagerDir();
			if(m_tInfo.m_eUnitType == UT_FISHER)
				SetFishShipDir();
			if(m_tInfo.m_eUnitType == UT_TRANSSHIP || m_tInfo.m_eUnitType == UT_GALLYSHIP)
				SetTransShipDir();
			m_tInfo.bDirCheck = true;
		}

		m_tInfo.vPos += m_tInfo.vDir * m_tInfo.fSpeed * GETTIME;

		if(fDest < 80)
		{
			int iIndex = CTileMgr::GetInstance()->GetTileIndex(m_tInfo.vGoalPos);
			m_tInfo.bDirCheck = false;
			if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_BUILD
			&& m_tInfo.wstrObjKey == L"Villager")
			{
				m_tInfo.m_eStateType = STATE_BUILD;
				m_tInfo.iWorkingIndex = iIndex;
				return;
			}
		}
		
	}

	else if(m_tInfo.m_eStateType == STATE_WALK)
	{
		m_tInfo.iGetResourceCount = 0;
		float fX = m_tInfo.vGoalPos.x - m_tInfo.vPos.x;
		float fY = m_tInfo.vGoalPos.y - m_tInfo.vPos.y - 10;
		float fDest = sqrt(fX * fX + fY * fY);

		m_tInfo.vDir = m_tInfo.vGoalPos - m_tInfo.vPos;

		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		if(m_tInfo.m_eUnitType == UT_TRANSSHIP || m_tInfo.m_eUnitType == UT_GALLYSHIP 
			||  m_tInfo.m_eUnitType == UT_DESTROYSHIP || m_tInfo.m_eUnitType == UT_FIRESHIP
			|| m_tInfo.m_eUnitType == UT_CANNONSHIP)
			SixteenDirCheckFunc(m_tInfo.vDir, m_tInfo.vGoalPos);
		else
			DirCheckFunc(m_tInfo.vDir, m_tInfo.vGoalPos);
		if(m_tInfo.bDirCheck == false)
		{
			if(m_tInfo.m_eUnitType == UT_VILLAGER)
				SetVillagerDir();
			if(m_tInfo.m_eUnitType == UT_SOLDIER)
				SetSoldierDir();
			if(m_tInfo.m_eUnitType == UT_FISHER)
				SetFishShipDir();
			if(m_tInfo.m_eUnitType == UT_TRANSSHIP || m_tInfo.m_eUnitType == UT_GALLYSHIP 
				||  m_tInfo.m_eUnitType == UT_DESTROYSHIP || m_tInfo.m_eUnitType == UT_FIRESHIP
				|| m_tInfo.m_eUnitType == UT_CANNONSHIP)
				SetTransShipDir();
			m_tInfo.bDirCheck = true;
		}

		m_tInfo.vPos += m_tInfo.vDir * m_tInfo.fSpeed * GETTIME;

		if(fDest < 40)
		{
			int iIndex = CTileMgr::GetInstance()->GetTileIndex(m_tInfo.vGoalPos);

			if(iIndex == -1)
				return;
			m_tInfo.bDirCheck = false;

			if(m_tInfo.m_eUnitType == UT_SOLDIER)
			{
				m_tInfo.m_eStateType = STATE_STD;
				SetSoldierDir();
				return;

			}
			if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType == RT_STONE
				&& m_tInfo.m_eUnitType == UT_VILLAGER)
			{
				m_tInfo.m_eStateType = STATE_MINING_STONE;
				m_tInfo.iWorkingIndex = iIndex;
				bGetResource = true;
			}
			else if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType == RT_GOLD
				&& m_tInfo.m_eUnitType == UT_VILLAGER)
			{
				m_tInfo.m_eStateType = STATE_MINING_GOLD;
				m_tInfo.iWorkingIndex = iIndex;
				bGetResource = true;
			}
			else if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType == RT_CHERRY
				&& m_tInfo.m_eUnitType == UT_VILLAGER)
			{
				m_tInfo.m_eStateType = STATE_GET_CHEERY;
				m_tInfo.iWorkingIndex = iIndex;
				bGetResource = true;
			}
			else if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType == RT_TREE
				&& m_tInfo.m_eUnitType == UT_VILLAGER)
			{
				m_tInfo.m_eStateType = STATE_WOOD_CUTTING;
				m_tInfo.iWorkingIndex = iIndex;
				bGetResource = true;
			}
			else if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_BUILD
				&& m_tInfo.m_eUnitType == UT_VILLAGER)
			{
				m_tInfo.m_eStateType = STATE_BUILD;
				m_tInfo.iWorkingIndex = iIndex;
			}
			else if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType == RT_FISH
				&& m_tInfo.m_eUnitType == UT_FISHER)
			{
				m_tInfo.m_eStateType = STATE_FISHING;
				m_tInfo.iWorkingIndex = iIndex;
			}
			else
				m_tInfo.m_eStateType = STATE_STD;
		}
	}	
}

void CObj::GroundBattleUnitStateCheckFunc()
{
	switch(m_tInfo.m_eStateType)
	{
	case STATE_STD:
		m_tInfo.wstrStateKey = L"STD";
		break;
	case STATE_WALK:
		m_tInfo.wstrStateKey = L"Walk";
		break;
	case STATE_ATTACK:
		m_tInfo.wstrStateKey = L"ATT";
		break;
	case STATE_DYING:
		m_tInfo.wstrStateKey = L"Dying";
		break;
	case STATE_DEATH:
		m_tInfo.wstrStateKey = L"Death";
		break;
	}
}
void CObj::StateCheckFunc()
{
	switch(m_tInfo.m_eStateType)
	{
	case STATE_STD:
		{
			m_tInfo.bFishing = false;
			m_tInfo.wstrStateKey = L"STD";
		}
		break;
	case STATE_WALK:
		if(m_tInfo.m_eUnitType == UT_VILLAGER)
			m_tInfo.wstrStateKey = L"Walk";
		else if(m_tInfo.m_eUnitType == UT_FISHER)
		{
			m_tInfo.bFishing = false;
			m_tInfo.wstrStateKey = L"STD";
		}
		break;
	case STATE_MINING_GOLD:
		m_tInfo.wstrStateKey = L"Miner_Mining";
		break;
	case STATE_MINING_STONE:
		m_tInfo.wstrStateKey = L"Miner_Mining";
		break;
	case STATE_WOOD_CUTTING:
		m_tInfo.wstrStateKey = L"Chopping";
		break;
	case STATE_GET_CHEERY:
		m_tInfo.wstrStateKey = L"Berry_Gatherer_Kneeling";
		break;
	case STATE_CARRY_WOOD:
		m_tInfo.wstrStateKey = L"Carrying_Wood";
		break;
	case STATE_CARRY_CHERRY:
		m_tInfo.wstrStateKey = L"Berry_Gatherer_Walk";
		break;
	case STATE_CARRY_STONE:
		m_tInfo.wstrStateKey = L"Miner_Carrying_Stone";
		break;
	case STATE_CARRY_GOLD:
		m_tInfo.wstrStateKey = L"Miner_Carrying_Gold";
		break;
	case STATE_WALK_BUILD:
		m_tInfo.wstrStateKey = L"Walk";
		break;
	case STATE_BUILD:
		m_tInfo.wstrStateKey = L"Building";
		break;
	case STATE_FISHING:
		//m_tInfo.wstrStateKey = L"Fishing";
		m_tInfo.bFishing = true;
		break;
	case STATE_FISHING_WORK:
		m_tInfo.wstrStateKey = L"STD";
		m_tInfo.bFishing = false;
		break;
	case STATE_DYING:
		m_tInfo.wstrStateKey = L"Dying";
		m_tInfo.bFishing = false;
		break;
	case STATE_DEATH:
		m_tInfo.wstrStateKey = L"Death";
		m_tInfo.bFishing = false;
		break;
	}
}

void CObj::SetWayPoint()
{
	D3DXVECTOR3 vMouse = CMouseMgr::GetMousePos();

	vMouse -= CObj::m_vScroll;

	if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if(m_tInfo.bSelection == true)
		{
			list<CObj*>::iterator Mouse_iter = CObjMgr::GetInstance()->GetObjList(L"Mouse",SORT_MOUSE).begin();

			(*Mouse_iter)->GetInfo()->bRelly = true;
			(*Mouse_iter)->GetInfo()->vWayPos = vMouse;

			m_tInfo.vWayPos = vMouse;
		}
	}
}

void CObj::SetFishShipDir()
{
	if(m_tInfo.m_eDirType == DIR_DOWN) // 보정필요
	{
		m_tInfo.byDrawID = 0;
	}
	if(m_tInfo.m_eDirType == DIR_DOWN_L || m_tInfo.m_eDirType == DIR_DOWN_R)
	{
		m_tInfo.byDrawID = 1;
	}
	if(m_tInfo.m_eDirType == DIR_LEFT || m_tInfo.m_eDirType == DIR_RIGHT)
	{
		m_tInfo.byDrawID = 2;
	}
	if(m_tInfo.m_eDirType == DIR_UP_L || m_tInfo.m_eDirType == DIR_UP_R)
	{
		m_tInfo.byDrawID = 3;
	}
	if(m_tInfo.m_eDirType == DIR_UP)
	{
		m_tInfo.byDrawID = 4;
	}
	m_tInfo.byOriID = m_tInfo.byDrawID;
}	
void CObj::SetBoomShipDir()
{
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN) // 보정필요
	{
		m_tFrame.fFrame = 0;
		m_tFrame.fMax = 6;
		m_tInfo.byDrawID = 0;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_L3 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R3) // 보정필요
	{
		m_tFrame.fFrame = 7;
		m_tFrame.fMax = 13;
		m_tInfo.byDrawID = 1;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_L2 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R2) // 보정필요
	{
		m_tFrame.fFrame = 14;
		m_tFrame.fMax = 20;
		m_tInfo.byDrawID = 2;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_L1 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R1) // 보정필요
	{
		m_tFrame.fFrame = 21;
		m_tFrame.fMax = 27;
		m_tInfo.byDrawID = 3;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_LEFT || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_RIGHT) // 보정필요
	{
		m_tFrame.fFrame = 28;
		m_tFrame.fMax = 34;
		m_tInfo.byDrawID = 4;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_L1 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R1) // 보정필요
	{
		m_tFrame.fFrame = 35;
		m_tFrame.fMax = 41;
		m_tInfo.byDrawID = 5;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_L2 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R2) // 보정필요
	{
		m_tFrame.fFrame = 42;
		m_tFrame.fMax = 48;
		m_tInfo.byDrawID = 6;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_L3 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R3) // 보정필요
	{
		m_tFrame.fFrame = 49;
		m_tFrame.fMax = 55;
		m_tInfo.byDrawID = 7;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP) // 보정필요
	{
		m_tFrame.fFrame = 56;
		m_tFrame.fMax = 62;
		m_tInfo.byDrawID = 8;
	}

	m_tInfo.byOriID = m_tInfo.byDrawID;
	m_tFrame.fOriFrame = m_tFrame.fFrame;
}
void CObj::SetTransShipDir()
{
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN) // 보정필요
	{
		m_tFrame.fFrame = 0;
		m_tFrame.fMax = 19;
		m_tInfo.byDrawID = 0;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_L3 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R3) // 보정필요
	{
		m_tFrame.fFrame = 20;
		m_tFrame.fMax = 39;
		m_tInfo.byDrawID = 1;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_L2 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R2) // 보정필요
	{
		m_tFrame.fFrame = 20;
		m_tFrame.fMax = 39;
		m_tInfo.byDrawID = 2;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_L1 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R1) // 보정필요
	{
		m_tFrame.fFrame = 20;
		m_tFrame.fMax = 39;
		m_tInfo.byDrawID = 3;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_LEFT || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_RIGHT) // 보정필요
	{
		m_tFrame.fFrame = 40;
		m_tFrame.fMax = 59;
		m_tInfo.byDrawID = 4;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_L1 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R1) // 보정필요
	{
		m_tFrame.fFrame = 60;
		m_tFrame.fMax = 79;
		m_tInfo.byDrawID = 5;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_L2 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R2) // 보정필요
	{
		m_tFrame.fFrame = 60;
		m_tFrame.fMax = 79;
		m_tInfo.byDrawID = 6;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_L3 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R3) // 보정필요
	{
		m_tFrame.fFrame = 60;
		m_tFrame.fMax = 79;
		m_tInfo.byDrawID = 7;
	}
	if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP) // 보정필요
	{
		m_tFrame.fFrame = 80;
		m_tFrame.fMax = 99;
		m_tInfo.byDrawID = 8;
	}

	m_tInfo.byOriID = m_tInfo.byDrawID;
	m_tFrame.fOriFrame = m_tFrame.fFrame;
}

FRAME* CObj::GetFrame()
{
	return &m_tFrame;
}

void CObj::EnemyView()
{
}

const TEXINFO* CObj::GetProfil()
{
	return pProfilTex;
}

void CObj::AttackControlDir()
{
	if(m_tInfo.m_eStateType == STATE_ATTACK)
	{
		if(m_tInfo.m_eDirType == DIR_DOWN) // 보정필요
		{
			m_tFrame.fFrame = 0;
			m_tFrame.fMax = 9;
		}
		if(m_tInfo.m_eDirType == DIR_DOWN_L || m_tInfo.m_eDirType == DIR_DOWN_R)
		{
			m_tFrame.fFrame = 10;
			m_tFrame.fMax = 19;
		}
		if(m_tInfo.m_eDirType == DIR_LEFT || m_tInfo.m_eDirType == DIR_RIGHT)
		{
			m_tFrame.fFrame = 20;
			m_tFrame.fMax = 29;
		}
		if(m_tInfo.m_eDirType == DIR_UP_L || m_tInfo.m_eDirType == DIR_UP_R)
		{
			m_tFrame.fFrame = 30;
			m_tFrame.fMax = 39;
		}
		if(m_tInfo.m_eDirType == DIR_UP)
		{
			m_tFrame.fFrame = 40;
			m_tFrame.fMax = 49;
		}
		m_tFrame.fOriFrame = m_tFrame.fFrame;
		m_tInfo.bTest = true;
	}
}

CObj* CObj::GetTarget()
{
	return pTarget;
}



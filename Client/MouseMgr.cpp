#include "StdAfx.h"
#include "MouseMgr.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "ButtonMgr.h"
#include "Factory.h"
#include "Sequence.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "BuildMgr.h"
#include "SoundMgr.h"

bool CMouseMgr::m_bMoveCheck = false;

CMouseMgr::CMouseMgr(void)
{
}

CMouseMgr::~CMouseMgr(void)
{
}

void CMouseMgr::UnitMoveFunc()
{
	D3DXVECTOR3 vMouse = GetMousePos();

	vMouse.x -= CObj::m_vScroll.x;
	vMouse.y -= CObj::m_vScroll.y;

	if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		/*if(m_bMoveCheck == true)
			return;
		m_bMoveCheck = true;*/

		if(vMouse.y + CObj::m_vScroll.y > 450)
			return;

		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

		for(iter; iter != iter_end; ++iter)
		{
			if( (*iter)->GetInfo()->bSelection == true)
			{
				int iIndex = CTileMgr::GetInstance()->GetTileIndex(vMouse);

				if(iIndex == -1)
				{
					(*iter)->GetInfo()->bMove = false;
					(*iter)->GetInfo()->m_eStateType = STATE_STD;
					//(*Obj_iter)->GetInfo()->vGoalPos =false;
					return;
				}

				(*iter)->GetInfo()->m_eStateType = STATE_WALK;
				(*iter)->GetInfo()->vGoalPos = vMouse;
				(*iter)->GetInfo()->bMove = true;

				list<CObj*>::iterator Mouse_iter = CObjMgr::GetInstance()->GetObjList(L"Mouse",SORT_MOUSE).begin();

				(*Mouse_iter)->GetInfo()->vGoalPos = vMouse;
				(*Mouse_iter)->GetInfo()->bMove = true;


				if((*iter)->GetInfo()->m_eUnitType == UT_VILLAGER)
				{
					SetDirFunc((*iter));
					CSoundMgr::GetInstance()->VillagerMoveSound(L"VillagerMove.wav");
				}
				if((*iter)->GetInfo()->m_eUnitType == UT_SOLDIER)
				{
					SetSoldierDirFunc((*iter));
				}
				if((*iter)->GetInfo()->m_eUnitType == UT_FISHER)
				{
					int iRand = rand() % 2;
					if(iRand == 0)
						CSoundMgr::GetInstance()->SeaMoveSound(L"ShipMove2.wav");
					else if(iRand == 1)
						CSoundMgr::GetInstance()->SeaMoveSound(L"ShipMove3.wav");

					SetFisherDirFunc((*iter));
				}
				if((*iter)->GetInfo()->m_eUnitType == UT_TRANSSHIP ||(*iter)->GetInfo()->m_eUnitType == UT_GALLYSHIP 
					||(*iter)->GetInfo()->m_eUnitType == UT_DESTROYSHIP ||(*iter)->GetInfo()->m_eUnitType == UT_FIRESHIP
					 ||(*iter)->GetInfo()->m_eUnitType == UT_CANNONSHIP)
				{
					int iRand = rand() % 2;
					if(iRand == 0)
						CSoundMgr::GetInstance()->SeaMoveSound(L"ShipMove2.wav");
					else if(iRand == 1)
						CSoundMgr::GetInstance()->SeaMoveSound(L"ShipMove3.wav");
					SetSixTeenDirFunc((*iter));
				}
				if((*iter)->GetInfo()->m_eGroundType == GT_GROUND)
				{
					if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_SEA)
					{
						list<CObj*>::iterator Trans_iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
						list<CObj*>::iterator Trans_iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

						for(; Trans_iter != Trans_iter_end; ++Trans_iter)
						{
							if((*Trans_iter)->GetInfo()->m_eUnitType == UT_TRANSSHIP)
							{
								float fX = (*Trans_iter)->GetInfo()->vPos.x - (*iter)->GetInfo()->vGoalPos.x;
								float fY = (*Trans_iter)->GetInfo()->vPos.y - (*iter)->GetInfo()->vGoalPos.y;

								float fDest = sqrtf(fX * fX + fY * fY);

								if(fDest > 50)
								{
									(*iter)->GetInfo()->bMove = false;
									(*iter)->GetInfo()->m_eStateType = STATE_STD;
									return;
								}
							}
						}
					}

					
				}
				if((*iter)->GetInfo()->m_eGroundType == GT_SEA)
				{
					if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_GROUND)
					{
						(*iter)->GetInfo()->bMove = false;
						(*iter)->GetInfo()->m_eStateType = STATE_STD;
						return;
					}
				}
			}
		}
	}
}

void CMouseMgr::UnitSelectionFunc()
{
	D3DXVECTOR3 vMouse = GetMousePos();

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if(vMouse.y > 450)
			return;

		unordered_map<int, CObj*>::iterator Button_iter = CButtonMgr::GetInstance()->GetButtonMap().begin();
		unordered_map<int, CObj*>::iterator Button_iter_end = CButtonMgr::GetInstance()->GetButtonMap().end();

		for(; Button_iter != Button_iter_end; ++Button_iter)
		{
			if(Button_iter->second->GetInfo()->bBuildRender == true)
			{
				vMouse.x -= CObj::m_vScroll.x;
				vMouse.y -= CObj::m_vScroll.y;

				int iIndex = CTileMgr::GetInstance()->GetTileIndex(vMouse);

				if(Button_iter->second->GetInfo()->bBuildLimit == false)
				{
					CObjMgr::GetInstance()->AddObject(L"Sequence", SORT_OBJECT, CFactory<CSequence>::CreateObject(CTileMgr::GetInstance()->GetTile()[iIndex]->vPos, Button_iter->second->GetInfo()->m_eSizeType, Button_iter->second->GetInfo()->m_eBuildType));
				}
				else
				{
					Button_iter->second->GetInfo()->bBuildRender = false;
					return;
				}
				switch(Button_iter->second->GetInfo()->m_eSizeType)
				{
				case BST_MIN:
					break;
				case BST_MID:
					CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX - 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX + 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX - 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX + 1]->m_GroundType = GT_BUILD;
					break;
				case BST_MAX:
					CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX - 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX + 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX - 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX + 1]->m_GroundType = GT_BUILD;
					break;
				case BST_PORT:
					CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX - 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX + 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX - 1]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX]->m_GroundType = GT_BUILD;
					CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX + 1]->m_GroundType = GT_BUILD;
					break;
				}

				Button_iter->second->GetInfo()->bBuildRender = false;
				
				unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->begin();
				unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter_end = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->end();

				for(iter; iter != iter_end; ++iter)
				{
					for(list<CObj*>::iterator Obj_iter = iter->second.begin();
						Obj_iter != iter->second.end(); ++Obj_iter)
					{
						if((*Obj_iter)->GetInfo()->bSelection == true && (*Obj_iter)->GetInfo()->m_eUnitType == UT_VILLAGER)
						{
							(*Obj_iter)->GetInfo()->m_eStateType = STATE_WALK_BUILD;
							(*Obj_iter)->GetInfo()->vGoalPos = vMouse;

							int iIndex = CTileMgr::GetInstance()->GetTileIndex((*Obj_iter)->GetInfo()->vGoalPos);

							if(iIndex == -1)
							{
								(*Obj_iter)->GetInfo()->bMove = false;
								(*Obj_iter)->GetInfo()->m_eStateType = STATE_STD;
								return;
							}
							else
								(*Obj_iter)->GetInfo()->bMove = true;

							if((*Obj_iter)->GetInfo()->m_eUnitType == UT_VILLAGER)
								SetDirFunc((*Obj_iter));

							return;
						}
					}
				}
				return;
			}
		}

		unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->begin();
		unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter_end = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->end();

		for(iter; iter != iter_end; ++iter)
		{
			for(list<CObj*>::iterator Obj_iter = iter->second.begin();
				Obj_iter != iter->second.end(); ++Obj_iter)
			{
				if( (*Obj_iter)->GetInfo()->m_eObjType == OT_UNIT)
				{
					CCollisionMgr::GetInstance()->SelectUnit();
				}
			}
		}
	}
}

void CMouseMgr::SetDirFunc( CObj* pObj )
{
	if(pObj->GetInfo()->m_eDirType == DIR_DOWN) // 보정필요
	{
		pObj->GetFrame()->fFrame = 0;
		pObj->GetFrame()->fMax = 14;
	}
	if(pObj->GetInfo()->m_eDirType == DIR_DOWN_L || pObj->GetInfo()->m_eDirType == DIR_DOWN_R)
	{
		pObj->GetFrame()->fFrame = 15;
		pObj->GetFrame()->fMax = 29;
	}
	if(pObj->GetInfo()->m_eDirType == DIR_LEFT ||pObj->GetInfo()->m_eDirType == DIR_RIGHT)
	{
		pObj->GetFrame()->fFrame = 30;
		pObj->GetFrame()->fMax = 44;
	}
	if(pObj->GetInfo()->m_eDirType == DIR_UP_L || pObj->GetInfo()->m_eDirType == DIR_UP_R)
	{
		pObj->GetFrame()->fFrame = 45;
		pObj->GetFrame()->fMax = 59;
	}
	if(pObj->GetInfo()->m_eDirType == DIR_UP)
	{
		pObj->GetFrame()->fFrame = 60;
		pObj->GetFrame()->fMax = 74;
	}
	pObj->GetFrame()->fOriFrame = pObj->GetFrame()->fFrame;
}

void CMouseMgr::SetSoldierDirFunc( CObj* pObj )
{
	if(pObj->GetInfo()->m_eStateType == STATE_STD)
	{
		if(pObj->GetInfo()->m_eDirType == DIR_DOWN) // 보정필요
		{
			pObj->GetFrame()->fFrame = 0;
			pObj->GetFrame()->fMax = 5;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_DOWN_L || pObj->GetInfo()->m_eDirType == DIR_DOWN_R)
		{
			pObj->GetFrame()->fFrame = 6;
			pObj->GetFrame()->fMax = 11;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_LEFT || pObj->GetInfo()->m_eDirType == DIR_RIGHT)
		{
			pObj->GetFrame()->fFrame = 12;
			pObj->GetFrame()->fMax = 17;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_UP_L || pObj->GetInfo()->m_eDirType == DIR_UP_R)
		{
			pObj->GetFrame()->fFrame = 18;
			pObj->GetFrame()->fMax = 23;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_UP)
		{
			pObj->GetFrame()->fFrame = 24;
			pObj->GetFrame()->fMax = 29;
		}
		pObj->GetFrame()->fOriFrame = pObj->GetFrame()->fFrame;
	}
	if(pObj->GetInfo()->m_eStateType == STATE_WALK)
	{
		if(pObj->GetInfo()->m_eDirType == DIR_DOWN) // 보정필요
		{
			pObj->GetFrame()->fFrame = 0;
			pObj->GetFrame()->fMax = 11;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_DOWN_L || pObj->GetInfo()->m_eDirType == DIR_DOWN_R)
		{
			pObj->GetFrame()->fFrame = 12;
			pObj->GetFrame()->fMax = 23;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_LEFT || pObj->GetInfo()->m_eDirType == DIR_RIGHT)
		{
			pObj->GetFrame()->fFrame = 24;
			pObj->GetFrame()->fMax = 35;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_UP_L || pObj->GetInfo()->m_eDirType == DIR_UP_R)
		{
			pObj->GetFrame()->fFrame = 36;
			pObj->GetFrame()->fMax = 47;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_UP)
		{
			pObj->GetFrame()->fFrame = 48;
			pObj->GetFrame()->fMax = 59;
		}
		pObj->GetFrame()->fOriFrame = pObj->GetFrame()->fFrame;
	}
	if(pObj->GetInfo()->m_eStateType == STATE_ATTACK)
	{
		if(pObj->GetInfo()->m_eDirType == DIR_DOWN) // 보정필요
		{
			pObj->GetFrame()->fFrame = 0;
			pObj->GetFrame()->fMax = 9;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_DOWN_L || pObj->GetInfo()->m_eDirType == DIR_DOWN_R)
		{
			pObj->GetFrame()->fFrame = 10;
			pObj->GetFrame()->fMax = 19;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_LEFT || pObj->GetInfo()->m_eDirType == DIR_RIGHT)
		{
			pObj->GetFrame()->fFrame = 20;
			pObj->GetFrame()->fMax = 29;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_UP_L || pObj->GetInfo()->m_eDirType == DIR_UP_R)
		{
			pObj->GetFrame()->fFrame = 30;
			pObj->GetFrame()->fMax = 39;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_UP)
		{
			pObj->GetFrame()->fFrame = 40;
			pObj->GetFrame()->fMax = 49;
		}
		pObj->GetFrame()->fOriFrame = pObj->GetFrame()->fFrame;
	}
	if(pObj->GetInfo()->m_eStateType == STATE_DYING)
	{
		if(pObj->GetInfo()->m_eDirType == DIR_DOWN) // 보정필요
		{
			pObj->GetFrame()->fFrame = 0;
			pObj->GetFrame()->fMax = 9;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_DOWN_L || pObj->GetInfo()->m_eDirType == DIR_DOWN_R)
		{
			pObj->GetFrame()->fFrame = 10;
			pObj->GetFrame()->fMax = 19;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_LEFT || pObj->GetInfo()->m_eDirType == DIR_RIGHT)
		{
			pObj->GetFrame()->fFrame = 20;
			pObj->GetFrame()->fMax = 29;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_UP_L || pObj->GetInfo()->m_eDirType == DIR_UP_R)
		{
			pObj->GetFrame()->fFrame = 30;
			pObj->GetFrame()->fMax = 39;
		}
		if(pObj->GetInfo()->m_eDirType == DIR_UP)
		{
			pObj->GetFrame()->fFrame = 40;
			pObj->GetFrame()->fMax = 49;
		}
		pObj->GetFrame()->fOriFrame = pObj->GetFrame()->fFrame;
	}
}

void CMouseMgr::SetFisherDirFunc( CObj* pObj )
{
	if(pObj->GetInfo()->m_eDirType == DIR_DOWN) // 보정필요
	{
		pObj->GetInfo()->byDrawID = 0;
	}
	if(pObj->GetInfo()->m_eDirType == DIR_DOWN_L || pObj->GetInfo()->m_eDirType == DIR_DOWN_R)
	{
		pObj->GetInfo()->byDrawID = 1;
	}
	if(pObj->GetInfo()->m_eDirType == DIR_LEFT ||pObj->GetInfo()->m_eDirType == DIR_RIGHT)
	{
		pObj->GetInfo()->byDrawID = 2;
	}
	if(pObj->GetInfo()->m_eDirType == DIR_UP_L || pObj->GetInfo()->m_eDirType == DIR_UP_R)
	{
		pObj->GetInfo()->byDrawID = 3;
	}
	if(pObj->GetInfo()->m_eDirType == DIR_UP)
	{
		pObj->GetInfo()->byDrawID = 4;
	}
	pObj->GetInfo()->byOriID =pObj->GetInfo()->byDrawID;
}


void CMouseMgr::SetSixTeenDirFunc( CObj* pObj )
{
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN) // 보정필요
	{
		pObj->GetFrame()->fFrame = 0;
		pObj->GetFrame()->fMax = 19;
		pObj->GetInfo()->byDrawID = 0;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_L3 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_R3) // 보정필요
	{
		pObj->GetFrame()->fFrame = 20;
		pObj->GetFrame()->fMax = 39;
		pObj->GetInfo()->byDrawID = 1;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_L2 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_R2) // 보정필요
	{
		pObj->GetFrame()->fFrame = 20;
		pObj->GetFrame()->fMax = 39;
		pObj->GetInfo()->byDrawID = 2;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_L1 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_R1) // 보정필요
	{
		pObj->GetFrame()->fFrame = 20;
		pObj->GetFrame()->fMax = 39;
		pObj->GetInfo()->byDrawID = 3;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_LEFT || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_RIGHT) // 보정필요
	{
		pObj->GetFrame()->fFrame = 40;
		pObj->GetFrame()->fMax = 59;
		pObj->GetInfo()->byDrawID = 4;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_L1 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_R1) // 보정필요
	{
		pObj->GetFrame()->fFrame = 60;
		pObj->GetFrame()->fMax = 79;
		pObj->GetInfo()->byDrawID = 5;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_L2 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_R2) // 보정필요
	{
		pObj->GetFrame()->fFrame = 60;
		pObj->GetFrame()->fMax = 79;
		pObj->GetInfo()->byDrawID = 6;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_L3 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_R3) // 보정필요
	{
		pObj->GetFrame()->fFrame = 60;
		pObj->GetFrame()->fMax = 79;
		pObj->GetInfo()->byDrawID = 7;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP) // 보정필요
	{
		pObj->GetFrame()->fFrame = 80;
		pObj->GetFrame()->fMax = 99;
		pObj->GetInfo()->byDrawID = 8;
	}

	pObj->GetInfo()->byOriID = pObj->GetInfo()->byDrawID;
	pObj->GetFrame()->fOriFrame = pObj->GetFrame()->fFrame;
}

#include "StdAfx.h"
#include "CollisionMgr.h"
#include "ButtonMgr.h"
#include "MouseMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "TIleMgr.h"
#include "StageBack.h"
#include "TransShip.h"
#include "SoundMgr.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}
bool CCollisionMgr::MouseAndUnitCol()
{	
	return false;
}
bool CCollisionMgr::SelectUnit()
{
	CButtonMgr::GetInstance()->ClearButton();
	CObjMgr::GetInstance()->SetSelectionFalse();

	POINT ptMouse = { long(CMouseMgr::GetMousePos().x), long(CMouseMgr::GetMousePos().y)};

	ptMouse.x -= long(CObj::m_vScroll.x);
	ptMouse.y -= long(CObj::m_vScroll.y);

	unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->begin();
	unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter_end = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->end();

	for(; iter != iter_end; ++iter)
	{
		for(list<CObj*>::iterator Obj_iter = iter->second.begin();
			Obj_iter != iter->second.end(); ++Obj_iter)
		{
			if((*Obj_iter)->GetInfo()->m_ePlayerType == PT_ENEMY)
				continue;

			float fX = ptMouse.x - (*Obj_iter)->GetInfo()->vPos.x;
			float fY = ptMouse.y - (*Obj_iter)->GetInfo()->vPos.y;

			float fDest = sqrt(fX * fX + fY * fY);

			if( (*Obj_iter)->GetInfo()->m_eBuildType == BT_TOWN && (*Obj_iter)->GetInfo()->m_eObjType == OT_BUILD) // 타운
			{

				if(fDest < 80)
				{
					(*Obj_iter)->GetInfo()->bSelection = true;
					return true;
				}

			}

			if( ((*Obj_iter)->GetInfo()->m_eBuildType == BT_HOME
				|| (*Obj_iter)->GetInfo()->m_eBuildType == BT_PORT
				|| (*Obj_iter)->GetInfo()->m_eBuildType == BT_MINE
				|| (*Obj_iter)->GetInfo()->m_eBuildType == BT_WOOD
				|| (*Obj_iter)->GetInfo()->m_eBuildType == BT_BARRACK
				|| (*Obj_iter)->GetInfo()->m_eBuildType == BT_MILL ) && (*Obj_iter)->GetInfo()->m_eObjType == OT_BUILD) // 집
			{

				if(fDest < 60)
				{
					(*Obj_iter)->GetInfo()->bSelection = true;
					return true;
				}

			}

			if( (*Obj_iter)->GetInfo()->m_eObjType == OT_UNIT) // 소형 유닛
			{

				if(fDest < 20)
				{
					if((*Obj_iter)->GetInfo()->m_eUnitType == UT_VILLAGER)
						CSoundMgr::GetInstance()->VillagerPickSound(L"VillagerPick.wav");
					(*Obj_iter)->GetInfo()->bSelection = true;
					return true;
				}
			}
		}
	}
	
	unordered_map<int, CObj*>::iterator Button_iter = CButtonMgr::GetInstance()->GetButtonMap().begin();
	unordered_map<int, CObj*>::iterator Button_iter_end = CButtonMgr::GetInstance()->GetButtonMap().end();

	for(; Button_iter != Button_iter_end; ++Button_iter)
	{
		if(Button_iter->second->GetInfo()->bBuildRender == true)
		{
			Button_iter->second->GetInfo()->bBuildRender = false;
			return true;
		}
	}

	CObjMgr::GetInstance()->SetSelectionFalse();
	CButtonMgr::GetInstance()->ClearButton();
	return false;
}

int CCollisionMgr::GetPushButtonIndex()
{
	D3DXVECTOR3 vMouse =CMouseMgr::GetMousePos();

	int iIndex = CButtonMgr::GetInstance()->GetButtonIndex(vMouse);

	return iIndex;
}

bool CCollisionMgr::SetGroupUnit(RECT _rcCollBox)
{
	unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->begin();
	unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter_end = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->end();

	for(; iter != iter_end; ++iter)
	{
		for(list<CObj*>::iterator Obj_iter = iter->second.begin();
			Obj_iter != iter->second.end(); ++Obj_iter)
		{
			if((*Obj_iter)->GetInfo()->m_ePlayerType == PT_ENEMY)
				continue;

			POINT ptObjPoint = { long((*Obj_iter)->GetInfo()->vPos.x), long((*Obj_iter)->GetInfo()->vPos.y)};

			if(PtInRect(&_rcCollBox, ptObjPoint))
			{
				if( (*Obj_iter)->GetInfo()->m_eObjType == OT_UNIT /*&& (*Obj_iter)->GetInfo()->m_eGroundType == GT_GROUND*/) // 소형 유닛
				{
					if((*Obj_iter)->GetInfo()->m_eUnitType == UT_VILLAGER)
						CSoundMgr::GetInstance()->VillagerPickSound(L"VillagerPick.wav");
					(*Obj_iter)->GetInfo()->bSelection = true;
				}

				/*if( (*Obj_iter)->GetInfo()->m_eObjType == OT_BUILD)
				{

					(*Obj_iter)->GetInfo()->bSelection = true;
				}*/
			}
		}
	}

	CObjMgr::GetInstance()->SetGroup();

	CButtonMgr::GetInstance()->ClearButton();
		

	return false;
}

bool CCollisionMgr::BuildAndTileCol(eBUILD_SIZE_TYPE	_eType)
{

	D3DXVECTOR3	vMouse = CMouseMgr::GetMousePos();

	vMouse -= CObj::m_vScroll;

 	unordered_map<int, CObj*>::iterator Button_iter = CButtonMgr::GetInstance()->GetButtonMap().begin();
	unordered_map<int, CObj*>::iterator Button_iter_end = CButtonMgr::GetInstance()->GetButtonMap().end();

	for(; Button_iter != Button_iter_end; ++Button_iter)
	{
		if(Button_iter->second->GetInfo()->bBuildRender == true)
		{
			int iIndex = CTileMgr::GetInstance()->GetTileIndex(vMouse);

			if(iIndex > 2500 || iIndex < 0)
				return false;

			switch(_eType)
			{
			case BST_MIN:
				if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType == RT_NONE)
				{
					Button_iter->second->GetInfo()->bBuildLimit = false;
				}
				else
				{
					Button_iter->second->GetInfo()->bBuildLimit = true;
				}
				break;

			case BST_MID:
				if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType == RT_NONE)
				{
					Button_iter->second->GetInfo()->bBuildLimit = false;
				}
				else
				{
					Button_iter->second->GetInfo()->bBuildLimit = true;
				}
				break;
			case BST_MAX:
				if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType == RT_NONE)
				{
					Button_iter->second->GetInfo()->bBuildLimit = false;
				}
				else
				{
					Button_iter->second->GetInfo()->bBuildLimit = true;
				}
				break;
			case BST_PORT:
				if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_SEA
					&& CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType == RT_NONE
					&& ((CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX - 1]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX + 1]->m_GroundType == GT_GROUND)
					|| (CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX - 1]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex - 1]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX - 1]->m_GroundType == GT_GROUND)
					|| (CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX - 1]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX + 1]->m_GroundType == GT_GROUND)
					|| (CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX + 1]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex + 1]->m_GroundType == GT_GROUND
					&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX + 1]->m_GroundType == GT_GROUND)))
				{
					Button_iter->second->GetInfo()->bBuildLimit = false;
				}
				else
				{
					Button_iter->second->GetInfo()->bBuildLimit = true;
				}
				break;
			}
		}
	}

	return false;
}

void CCollisionMgr::UnitCollision(CObj*	pObj)
{
	if(CObj::FormationWidth == true)
		return;
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if(pObj == (*iter))
			continue;

		float fX = pObj->GetInfo()->vPos.x - (*iter)->GetInfo()->vPos.x;
		float fY = pObj->GetInfo()->vPos.y - (*iter)->GetInfo()->vPos.y;

		float fDest = sqrtf(fX * fX + fY * fY);

		D3DXVECTOR3 vDir = pObj->GetInfo()->vPos - (*iter)->GetInfo()->vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		if(fDest < (*iter)->GetInfo()->fCollRange)
		{
			pObj->GetInfo()->vPos += vDir*2.f;
			(*iter)->GetInfo()->vPos -= vDir*2.f;
		}
		
	}
}

void CCollisionMgr::BuildCollision(CObj*	pObj)
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if(pObj == (*iter))
			continue;

		float fX = pObj->GetInfo()->vPos.x - (*iter)->GetInfo()->vPos.x;
		float fY = pObj->GetInfo()->vPos.y - (*iter)->GetInfo()->vPos.y;

		float fDest = sqrtf(fX * fX + fY * fY);

		D3DXVECTOR3 vDir = pObj->GetInfo()->vPos - (*iter)->GetInfo()->vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		if(fDest < (*iter)->GetInfo()->fCollRange)
		{
			pObj->GetInfo()->vPos += vDir*2.f;
		}

	}
}

void CCollisionMgr::ResourceCollision(CObj*	pObj)
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Resource",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Resource",SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if(pObj == (*iter))
			continue;

		if((*iter)->GetInfo()->m_eResourceType == RT_FISH)
			continue;

		float fX = pObj->GetInfo()->vPos.x - (*iter)->GetInfo()->vPos.x;
		float fY = pObj->GetInfo()->vPos.y - (*iter)->GetInfo()->vPos.y;

		float fDest = sqrtf(fX * fX + fY * fY);

		D3DXVECTOR3 vDir = pObj->GetInfo()->vPos - (*iter)->GetInfo()->vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		if(fDest < (*iter)->GetInfo()->fCollRange)
		{
			pObj->GetInfo()->vPos += vDir*2.f;
		}

	}
}
void CCollisionMgr::InitTileSightCollision(CObj*	pObj)
{
	unordered_map<int, TILE*>::iterator iter = CTileMgr::GetInstance()->GetTile().begin();
	unordered_map<int, TILE*>::iterator iter_end = CTileMgr::GetInstance()->GetTile().end();

	int i = 0;

	for(; iter != iter_end; ++iter)
	{
		if(iter->second->m_BuildType == BT_FINDEND)
			continue;

		float fX = pObj->GetInfo()->vPos.x - iter->second->vPos.x;
		float fY = pObj->GetInfo()->vPos.y - iter->second->vPos.y;

		float fDest = sqrtf(fX * fX + fY * fY);

		if(fDest < pObj->GetInfo()->iSight)
		{
			iter->second->byOption = 1;
			iter->second->m_UnitType = UT_FOG;
			iter->second->m_BuildType = BT_FINDEND;
			CTileMgr::GetInstance()->GetFogTile().insert(make_pair(i,iter->second));
			++i;
		}
		else
		{
			iter->second->byOption = 0;
		}
	}
}
void CCollisionMgr::TileSightCollision(CObj*	pObj)
{
	/*list<CObj*>::iterator Obj_iter = CObjMgr::GetInstance()->GetObjList(L"StageBack",SORT_FIRST).begin();

	unordered_map<int, TILE*>::iterator iter = ((CStageBack*)(*Obj_iter))->GetDrawTile().begin();
	unordered_map<int, TILE*>::iterator iter_end = ((CStageBack*)(*Obj_iter))->GetDrawTile().end();*/

	unordered_map<int, TILE*>::iterator iter = CTileMgr::GetInstance()->GetTile().begin();
	unordered_map<int, TILE*>::iterator iter_end = CTileMgr::GetInstance()->GetTile().end();

	int i = 0;

	for(; iter != iter_end; ++iter)
	{
		if(iter->second->m_BuildType == BT_FINDEND)
			continue;

		float fX = pObj->GetInfo()->vPos.x - iter->second->vPos.x;
		float fY = pObj->GetInfo()->vPos.y - iter->second->vPos.y;

		float fDest = sqrtf(fX * fX + fY * fY);

		if(fDest < pObj->GetInfo()->iSight)
		{
			iter->second->byOption = 1;
			iter->second->m_UnitType = UT_FOG;
			iter->second->m_BuildType = BT_FINDEND;
			CTileMgr::GetInstance()->GetFogTile().insert(make_pair(i,iter->second));
			++i;

			
		}
		else
		{
			iter->second->byOption = 0;
		}
	}
}

CObj* CCollisionMgr::UnitBattleFunc( CObj* pObj )
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if(pObj == (*iter))
			continue;

		if(pObj->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			if((*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
				continue;
		}
		
		if(pObj->GetInfo()->m_ePlayerType == PT_ENEMY)
		{
			if((*iter)->GetInfo()->m_ePlayerType == PT_ENEMY)
				continue;
		}

		float fX = pObj->GetInfo()->vPos.x - (*iter)->GetInfo()->vPos.x;
		float fY = pObj->GetInfo()->vPos.y - (*iter)->GetInfo()->vPos.y;

		float fDest = sqrtf(fX * fX + fY * fY);

		D3DXVECTOR3 vDir = pObj->GetInfo()->vPos - (*iter)->GetInfo()->vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		if(fDest < pObj->GetInfo()->iRange)
		{
			return (*iter);
		}
	}

	list<CObj*>::iterator iter2 = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end2 = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).end();

	for(; iter2 != iter_end2; ++iter2)
	{
		if(pObj == (*iter2))
			continue;

		if(pObj->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			if((*iter2)->GetInfo()->m_ePlayerType == PT_PLAYER)
				continue;
		}

		if(pObj->GetInfo()->m_ePlayerType == PT_ENEMY)
		{
			if((*iter2)->GetInfo()->m_ePlayerType == PT_ENEMY)
				continue;
		}

		float fX = pObj->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
		float fY = pObj->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;

		float fDest = sqrtf(fX * fX + fY * fY);

		D3DXVECTOR3 vDir = pObj->GetInfo()->vPos - (*iter2)->GetInfo()->vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		if(fDest < pObj->GetInfo()->iRange)
		{
			return (*iter2);
		}
	}
	return NULL;
}

void CCollisionMgr::EnemySightCollisoin(CObj* pObj)
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_ePlayerType == PT_ENEMY)
			continue;
		
		float fX = pObj->GetInfo()->vPos.x - (*iter)->GetInfo()->vPos.x;
		float fY = pObj->GetInfo()->vPos.y - (*iter)->GetInfo()->vPos.y;

		float fDest = sqrtf(fX * fX + fY * fY);

		if(fDest < (*iter)->GetInfo()->iSight)
		{
			pObj->GetInfo()->bView = true;
			return;
		}
	}

	list<CObj*>::iterator iter2 = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end2 = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).end();

	for(; iter2 != iter_end2; ++iter2)
	{
		if((*iter2)->GetInfo()->m_ePlayerType == PT_ENEMY)
			continue;

		float fX = pObj->GetInfo()->vPos.x - (*iter2)->GetInfo()->vPos.x;
		float fY = pObj->GetInfo()->vPos.y - (*iter2)->GetInfo()->vPos.y;

		float fDest = sqrtf(fX * fX + fY * fY);

		if(fDest < (*iter2)->GetInfo()->iSight)
		{
			pObj->GetInfo()->bView = true;
			return;
		}
	}

	pObj->GetInfo()->bView = false;
}

void CCollisionMgr::TransGroundUnit(CObj* pObj)
{
	if(pObj->GetInfo()->m_eGroundType == GT_SEA)
		return;

	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eUnitType == UT_TRANSSHIP)
		{
			if(pObj == (*iter))
				continue;

			float fX = pObj->GetInfo()->vPos.x - (*iter)->GetInfo()->vPos.x;
			float fY = pObj->GetInfo()->vPos.y - (*iter)->GetInfo()->vPos.y;

			float fDest = sqrtf(fX * fX + fY * fY);

			D3DXVECTOR3 vDir = pObj->GetInfo()->vPos - (*iter)->GetInfo()->vPos;
			D3DXVec3Normalize(&vDir, &vDir);

			if(fDest < 80)
			{
				pObj->GetInfo()->bTrans = true;
				pObj->GetInfo()->m_eStateType = STATE_STD;
				pObj->GetInfo()->bMove = false;
				pObj->GetInfo()->vPos.x = 9999.f;
				pObj->GetInfo()->vPos.y = 9999.f;
				pObj->GetInfo()->bSelection = false;
				(*iter)->GetInfo()->bTrans = true;
				((CTransShip*)(*iter))->GetTransTex()->push_back(pObj->GetProfil());
				break;
			}
		}
	}
}

void CCollisionMgr::SoldierAttCollision( CObj* pObj )
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eGroundType == GT_SEA)
			continue;

		if(pObj->GetInfo()->m_ePlayerType == PT_ENEMY && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			float fX = pObj->GetInfo()->vPos.x - (*iter)->GetInfo()->vPos.x;
			float fY = pObj->GetInfo()->vPos.y - (*iter)->GetInfo()->vPos.y;

			float fDest = sqrtf(fX * fX + fY * fY);

			D3DXVECTOR3 vDir = pObj->GetInfo()->vPos - (*iter)->GetInfo()->vPos;
			D3DXVec3Normalize(&vDir, &vDir);

			pObj->GetInfo()->vDir = vDir;

			if(fDest < 50)
			{
				pObj->GetInfo()->m_eStateType = STATE_ATTACK;
				if(pObj->GetFrame()->fFrame <= pObj->GetFrame()->fMax - 5
					&& pObj->GetFrame()->fFrame > pObj->GetFrame()->fMax - 4)
				{
					(*iter)->GetInfo()->iHp -= pObj->GetInfo()->iAtt;	
				}
				break;
			}
			
		}
	}
}


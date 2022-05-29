#include "StdAfx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "ButtonMgr.h"
IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr(void)
{

}
CObjMgr::~CObjMgr(void)
{
	Release();
}
CObj* CObjMgr::GetTarget( const TCHAR* pObjKey, int iCnt /*= 0*/ )
{
	for (int i = 0; i < SORT_end; ++i)
	{
		unordered_multimap<const TCHAR*, list<CObj*>>::iterator Map_iter = m_ObjMap[i].find(pObjKey);

		if(Map_iter == m_ObjMap[i].end())
			continue;

		list<CObj*>::iterator	Obj_iter = Map_iter->second.begin();

		for (int i = 0; i < iCnt; ++i)
		{
			++Obj_iter;
		}

		return (*Obj_iter)->GetTarget();
	}

	return NULL;
}
const TEXINFO* CObjMgr::GetProfil( const TCHAR* pObjKey, int iCnt /*= 0*/ )
{
	for (int i = 0; i < SORT_end; ++i)
	{
		unordered_multimap<const TCHAR*, list<CObj*>>::iterator Map_iter = m_ObjMap[i].find(pObjKey);

		if(Map_iter == m_ObjMap[i].end())
			continue;

		list<CObj*>::iterator	Obj_iter = Map_iter->second.begin();

		for (int i = 0; i < iCnt; ++i)
		{
			++Obj_iter;
		}

		return (*Obj_iter)->GetProfil();
	}

	return NULL;
}

FRAME* CObjMgr::GetFrame( const TCHAR* pObjKey, int iCnt /*= 0*/ )
{
	for (int i = 0; i < SORT_end; ++i)
	{
		unordered_multimap<const TCHAR*, list<CObj*>>::iterator Map_iter = m_ObjMap[i].find(pObjKey);

		if(Map_iter == m_ObjMap[i].end())
			continue;

		list<CObj*>::iterator	Obj_iter = Map_iter->second.begin();

		for (int i = 0; i < iCnt; ++i)
		{
			++Obj_iter;
		}

		return (*Obj_iter)->GetFrame();
	}

	return NULL;
}


INFO* CObjMgr::GetInfo(const TCHAR* pObjKey, int iCnt)
{
	for (int i = 0; i < SORT_end; ++i)
	{
		unordered_multimap<const TCHAR*, list<CObj*>>::iterator Map_iter = m_ObjMap[i].find(pObjKey);

		if(Map_iter == m_ObjMap[i].end())
			continue;

		list<CObj*>::iterator	Obj_iter = Map_iter->second.begin();

		for (int i = 0; i < iCnt; ++i)
		{
			++Obj_iter;
		}

		return (*Obj_iter)->GetInfo();
	}

	return NULL;
}

list<CObj*>& CObjMgr::GetObjList(const TCHAR* pObjKey, eSortType _ID)
{
	unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter = m_ObjMap[_ID].find(pObjKey);

	return (*iter).second;
}

void CObjMgr::AddObject(const TCHAR* pObjKey, eSortType _ID, CObj* pObj)
{
	unordered_multimap<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[_ID].find(pObjKey);

	if(iter == m_ObjMap[_ID].end())
	{
		list<CObj*>		ObjList;
		ObjList.push_back(pObj);
		m_ObjMap[_ID].insert(make_pair(pObjKey, ObjList));
	}
	else
	{
		iter->second.push_back(pObj);
	}

}
void CObjMgr::EraseObject()
{
	for (int i = 0; i < SORT_end; ++i)
	{
		unordered_multimap<const TCHAR*,list<CObj*>>::iterator Map_iter = m_ObjMap[i].begin();
		unordered_multimap<const TCHAR*,list<CObj*>>::iterator Map_iter_end = m_ObjMap[i].end();

		for(Map_iter; Map_iter != Map_iter_end; )
		{
			for(list<CObj*>::iterator Obj_iter = Map_iter->second.begin();
				Obj_iter != Map_iter->second.end();)
			{
				if((*Obj_iter)->GetInfo()->bAlive == false)
				{
					if((*Obj_iter)->GetInfo()->bSelection == true)
					{
						(*Obj_iter)->GetInfo()->bSelection = false;

						unordered_map<int, CObj*>::iterator iter = m_GroupMap.begin();
						unordered_map<int, CObj*>::iterator iter_end = m_GroupMap.end();

						for(; iter != iter_end; ++iter)
						{
							if(iter->second == (*Obj_iter))
							{
								m_GroupMap.erase(iter);
								break;
							}
						}
					}
					SAFE_DELETE(*Obj_iter);
					Obj_iter = Map_iter->second.erase(Obj_iter);
					
				}
				else
				{
					++Obj_iter;
				}
			}

			if(Map_iter->second.empty())
				Map_iter = m_ObjMap[i].erase(Map_iter);
			else
				++Map_iter;
		}
	}
}

void CObjMgr::Update()
{
	EraseObject();

	for (int i = 0; i < SORT_end; ++i)
	{
		unordered_multimap<const TCHAR*,list<CObj*>>::iterator Map_iter = m_ObjMap[i].begin();
		unordered_multimap<const TCHAR*,list<CObj*>>::iterator Map_iter_end = m_ObjMap[i].end();

		for(Map_iter; Map_iter != Map_iter_end; ++Map_iter)
		{
			for(list<CObj*>::iterator Obj_iter = Map_iter->second.begin();
				Obj_iter != Map_iter->second.end(); ++Obj_iter)
			{
				if(i == SORT_OBJECT)
				{
					m_SortMap.insert(make_pair((*Obj_iter)->GetInfo()->vPos.y, (*Obj_iter)));
					if((*Obj_iter)->GetInfo()->m_eObjType == OT_UNIT)
					{
						if((*Obj_iter)->GetInfo()->bTrans == true && (*Obj_iter)->GetInfo()->m_eGroundType == GT_GROUND)
						{
							unordered_map<int, CObj*>::iterator iter = m_GroupMap.begin();
							unordered_map<int, CObj*>::iterator iter_end = m_GroupMap.end();

							for(; iter != iter_end; ++iter)
							{
								if(iter->second == (*Obj_iter))
								{
									m_GroupMap.erase(iter);
									break;
								}
							}
						}
						CCollisionMgr::GetInstance()->UnitCollision((*Obj_iter));
						CCollisionMgr::GetInstance()->BuildCollision((*Obj_iter));
						CCollisionMgr::GetInstance()->ResourceCollision((*Obj_iter));
						CCollisionMgr::GetInstance()->TransGroundUnit((*Obj_iter));
					}
				}
				(*Obj_iter)->Update();
			}
		}
	}

}
void CObjMgr::Render()
{
	float fRight = -CObj::m_vScroll.x + WINCX + TILESIZEX - 10;
	float fDown  = -CObj::m_vScroll.y + WINCY - TILESIZEY * 2 - 10;
	float fLeft  = -CObj::m_vScroll.x - TILESIZEX + 10;
	float fUp	 = -CObj::m_vScroll.y - TILESIZEY + 10;

	for (int i = 0; i < SORT_end; ++i)
	{
		if(i == SORT_OBJECT)
		{
			for (multimap<float, CObj*>::iterator	iter = m_SortMap.begin();
				iter != m_SortMap.end(); ++iter)
			{
				iter->second->Render();
				/*if(iter->second->GetInfo()->vPos.x < fRight && iter->second->GetInfo()->vPos.y < fDown
					&& iter->second->GetInfo()->vPos.x > fLeft && iter->second->GetInfo()->vPos.y > fUp)
				{
					
				}*/
			}
			m_SortMap.clear();
		}

		else
		{
			for (unordered_multimap<const TCHAR*, list<CObj*>>::iterator	iter = m_ObjMap[i].begin();
				iter != m_ObjMap[i].end(); ++iter)
			{
				for (list<CObj*>::iterator	iter1 = iter->second.begin();
					iter1 != iter->second.end(); ++iter1)
				{
					
					(*iter1)->Render();
					
				}
				if(i == SORT_UI)
					CButtonMgr::GetInstance()->Render();
			}	

		}

	}
	CTileMgr::GetInstance()->SetFindCheck();
}

void CObjMgr::Release()
{
	for (int i = 0; i < SORT_end; ++i)
	{
		unordered_multimap<const TCHAR*,list<CObj*>>::iterator Map_iter = m_ObjMap[i].begin();
		unordered_multimap<const TCHAR*,list<CObj*>>::iterator Map_iter_end = m_ObjMap[i].end();

		for(Map_iter; Map_iter != Map_iter_end; ++Map_iter)
		{
			for(list<CObj*>::iterator Obj_iter = Map_iter->second.begin();
				Obj_iter != Map_iter->second.end(); ++Obj_iter)
			{
				SAFE_DELETE(*Obj_iter);
			}
			Map_iter->second.clear();
		}
		m_ObjMap[i].clear();
	}
}

void CObjMgr::SetSelectionFalse()
{
	for (int i = 0; i < SORT_end; ++i)
	{
		unordered_multimap<const TCHAR*,list<CObj*>>::iterator Map_iter = m_ObjMap[i].begin();
		unordered_multimap<const TCHAR*,list<CObj*>>::iterator Map_iter_end = m_ObjMap[i].end();

		for(Map_iter; Map_iter != Map_iter_end; ++Map_iter)
		{
			for(list<CObj*>::iterator Obj_iter = Map_iter->second.begin();
				Obj_iter != Map_iter->second.end(); ++Obj_iter)
			{
				if((*Obj_iter)->GetInfo()->bSelection == true)
				{
					(*Obj_iter)->GetInfo()->bSelection = false;
				}
			}
		}
	}
}


void CObjMgr::SightCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
		CCollisionMgr::GetInstance()->TileSightCollision((*iter));

}

void CObjMgr::SetGroup()
{
	m_GroupMap.clear();

	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

	int i = 0;
	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->bSelection == true)
		{
			m_GroupMap.insert(make_pair(i, (*iter)));
			++i;
		}
	}
}





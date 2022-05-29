#include "StdAfx.h"
#include "GroupMgr.h"
#include "Obj.h"
#include "ButtonMgr.h"

IMPLEMENT_SINGLETON(CGroupMgr)

CGroupMgr::CGroupMgr(void)
{
}

CGroupMgr::~CGroupMgr(void)
{
}

void CGroupMgr::SingleObject( CObj* pObj, eOBJ_TYPE _eType )
{
	m_GroupMap.clear();

	pObj->GetInfo()->bSelection = true;

	m_GroupMap.insert(make_pair(_eType, pObj));

}

void CGroupMgr::MultiObject( CObj* pObj, eOBJ_TYPE _eType)
{

	pObj->GetInfo()->bSelection = true;

	m_GroupMap.insert(make_pair(_eType, pObj));
}

void CGroupMgr::SetSelectionFalse(void)
{
	unordered_map<eOBJ_TYPE, CObj*>::iterator iter = m_GroupMap.begin();
	unordered_map<eOBJ_TYPE, CObj*>::iterator iter_end = m_GroupMap.end();

	for(; iter != iter_end; ++iter)
		iter->second->GetInfo()->bSelection = false;

	m_GroupMap.clear();
}

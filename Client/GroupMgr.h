#pragma once

class CObj;
class CGroupMgr
{
	DECLARE_SINGLETON(CGroupMgr)
private:
	unordered_map<eOBJ_TYPE, CObj*>		m_GroupMap;
	bool								m_bMultiCheck;
public:
	void SingleObject(CObj* pObj, eOBJ_TYPE _eType);
	void MultiObject(CObj* pObj, eOBJ_TYPE _eType);
	void SetSelectionFalse(void);
public:
	unordered_map<eOBJ_TYPE, CObj*>&		GetGroupMap()
	{
		return m_GroupMap;
	}
private:
	CGroupMgr(void);
public:
	~CGroupMgr(void);
};


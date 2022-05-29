#pragma once

class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)
private:
	unordered_multimap<const TCHAR*, list<CObj*>>			m_ObjMap[SORT_end];
	unordered_map<int, CObj*>								m_GroupMap;				
	multimap<float, CObj*>									m_SortMap;
public:
	void	AddObject(const TCHAR* pObjKey, eSortType _ID, CObj* pObj);
	INFO*	GetInfo(const TCHAR* pObjKey, int iCnt = 0);
	FRAME*	GetFrame(const TCHAR* pObjKey, int iCnt = 0);
	const TEXINFO*	GetProfil(const TCHAR* pObjKey, int iCnt = 0);
	CObj*	GetTarget(const TCHAR* pObjKey, int iCnt = 0);

	unordered_multimap<const TCHAR*, list<CObj*>>*	GetMap(eSortType _ID){ return &m_ObjMap[_ID]; }
	unordered_map<int, CObj*>*						GetGroupMap(){ return &m_GroupMap; }
	list<CObj*>&	GetObjList(const TCHAR* pObjKey, eSortType _ID);
	CObj*			GetObject(const TCHAR* pObjKey, eSortType _ID, int iCnt = 0);
	void SetSelectionFalse();
	void SightCheck();
	D3DXVECTOR3 SetGroupRectForm(D3DXVECTOR3	_vGoalPos);
	void SetGroup();
	void EraseObject();
	void Update();
	void Render();
	void Release();
private:
	CObjMgr(void);
public:
	~CObjMgr(void);
};

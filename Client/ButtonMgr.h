#pragma once

class CObj;
class CButtonMgr
{
	DECLARE_SINGLETON(CButtonMgr)
private:
	unordered_map<int, CObj*>	m_ButtonMap;
public:
	unordered_map<int, CObj*>&	GetButtonMap()
	{
		return m_ButtonMap;
	}
	void AddButton(CObj* pObj, int iIndex);
	void ClearButton();
	void PortSource();
	void Update();
	void Render();
	void Release();
public:
	int				GetButtonIndex(const D3DXVECTOR3&	vPos);
	bool			Picking(const D3DXVECTOR3& vPos, const int& iIndex);	//직선의 방정식..
	void			ButtonChange(eCONTROL_DRAW_TYPE _eType);
private:
	CButtonMgr(void);
public:
	~CButtonMgr(void);
};

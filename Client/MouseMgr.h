#pragma once

class CObj;
class CMouseMgr
{
private:
	static bool	m_bMoveCheck;
public:
	static D3DXVECTOR3 GetMousePos(void)
	{
		D3DXVECTOR3 vPos;

		POINT	ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		vPos.x = (float)ptMouse.x;
		vPos.y = (float)ptMouse.y;
		vPos.z = 0.f;

		return vPos;
	}
	static void UnitMoveFunc();
	static void UnitSelectionFunc();
	static void BuildFunc();
	static void SetDirFunc(CObj*	pObj);
	static void SetSoldierDirFunc(CObj* pObj);
	static void SetSixTeenDirFunc(CObj*	pObj);
	static void SetFisherDirFunc(CObj* pObj);
public:
	CMouseMgr(void);
	~CMouseMgr(void);
};

#pragma once

class CObj;
class CFormation
{
	DECLARE_SINGLETON(CFormation)
private:
	D3DXVECTOR3 vCenterPos;
	bool	bFormationing;
public:
	void	SetFormationWidth();
	void	SetFormationRect();
	void	SetFormationCheck();
	void	SetFormationDiv();
public:
	void	SetTransShipDir(CObj*	pObj);
	void	SixteenDirCheckFunc(D3DXVECTOR3 _vDir, D3DXVECTOR3 _vGoalPos, CObj* pObj);

private:
	CFormation(void);
public:
	~CFormation(void);
};

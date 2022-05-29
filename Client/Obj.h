#pragma once

class CObj
{
protected:
	INFO	m_tInfo;
	FRAME	m_tFrame;
	bool	m_bLbuttonCheck;
	bool	bGetResource;
	bool	m_bFrameStart;
	D3DXVECTOR2		m_vDrawBox[5];
	float	m_fAngle;
	DWORD	m_dwTime;
	DWORD	m_dwEnemyTime;
	const TEXINFO* pProfilTex;
	CObj*			pTarget;

public:
	static bool		FormationWidth;
	static bool		FormationRect;
	static bool		FormationCheck;
	static bool		FormationDiv;
	static D3DXVECTOR3	m_vScroll;
	static eAgeType		m_eAgeType;
	static eAgeType		m_eEnemyAgeType;
	static unsigned int m_iMakeVillager;
	static unsigned int m_iMakeFishShip;
	static unsigned int m_iMakeTransShip;
	static unsigned int m_iMakeGalleyShip;
	static unsigned int m_iMakeDestroyShip;
	static unsigned int m_iMakeFireShip;
	static unsigned int m_iMakeCannonShip;
	static unsigned int m_iMakeSoldier;
	static bool			m_bVillagerGaugeRender;
	static bool			m_bFishShipGaugeRender;
	static bool			m_bTransShipGaugeRender;
	static bool			m_bGalleyShipGaugeRender;
	static bool			m_bDestroyShipGaugeRender;
	static bool			m_bFireShipGaugeRender;
	static bool			m_bCannonShipGaugeRender;
	static bool			m_bSoldierGaugeRender;
	static bool			m_bWarStart;

public:
	virtual HRESULT	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;
public:
	INFO*	GetInfo();
	FRAME*	GetFrame();
	const TEXINFO* GetProfil();
	CObj*	GetTarget();
	void	KeyCheckFunc();
	void	AttackFunc(CObj* pObj);
	void	MoveFunc();
	void	AttackControlDir();
	void	WayMove();
	void	GroundBattleUnitStateCheckFunc();
	void	StateCheckFunc();
	void	DirCheckFunc(D3DXVECTOR3 _vDir, D3DXVECTOR3 _vGoalPos);
	void	SixteenDirCheckFunc(D3DXVECTOR3 _vDir, D3DXVECTOR3 _vGoalPos);
	void	ArrowDirCheckFunc(D3DXVECTOR3 _vDir, D3DXVECTOR3 _vGoalPos);
	void	SetVillagerDir();
	void	SetSoldierDir();
	void	SetMatrix();
	void	SetSixTeenMatrix();
	void	SetWayPoint();
	void	SetFishShipDir();
	void	SetTransShipDir();
	void	SetBoomShipDir();
	void	EnemyView();
public:
	CObj(void);
	virtual ~CObj(void);
};

#pragma once
#include "obj.h"

class CFire :
	public CObj
{
private:
	//const TEXINFO*	m_TexArrow[176];
	//const TEXINFO*	m_TexArrowGround[51];
	//const TEXINFO*	m_TexArrowShadow[17];

	CObj*			m_pUnit;
	CObj*			m_pTarget;

	const TEXINFO*	m_TexArrow;

	float		m_fTime;

	D3DXVECTOR3 m_vLastPos;
	D3DXVECTOR3	m_vNextPos;
	D3DXVECTOR3 m_vCurvePos[3];

	//그림자를 위한 변수.
	D3DXVECTOR3	m_vShadowPos;
	float		m_fShadowAngle;
	D3DXMATRIX	m_matShadowWorld;

private:
	void	MoveArrow(void);
	void	LoadTex(void);
	void	DirAngle(void);
	void	AngleFrame(void);

public:
	virtual HRESULT Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CFire(void);
	CFire(CObj*	pUnit, CObj*	pTargetUnit, eSIXTEEN_DIRECTION_TYPE	_eType);
	virtual ~CFire(void);
};

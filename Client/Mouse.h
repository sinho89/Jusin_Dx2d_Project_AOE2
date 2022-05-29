#pragma once
#include "obj.h"

class CMouse :
	public CObj
{
private:
	const TEXINFO*	MouseTex[19];
	const TEXINFO*	PointTex[6];
	const TEXINFO*	FlagTex[9];
	bool			m_bDrag;
	RECT			m_rcUnitColl;
	FRAME			m_tRelleyFrame;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void MouseDragFunc();
public:
	CMouse(void);
	virtual ~CMouse(void);
};

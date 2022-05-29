#pragma once
#include "obj.h"

class CLogoBack :
	public CObj
{
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CLogoBack(void);
	virtual ~CLogoBack(void);
};

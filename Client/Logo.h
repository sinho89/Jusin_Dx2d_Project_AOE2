#pragma once
#include "scene.h"

class CLogo :
	public CScene
{
private:
	HANDLE				m_hThread;
	CRITICAL_SECTION	m_Crt;
private:
	static inline unsigned int __stdcall ImgLoadThreadFunc(void* pArg);
	CRITICAL_SECTION	GetCrt(void);
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CLogo(void);
	virtual ~CLogo(void);
};

#pragma once
#include "obj.h"

class CEffect :
	public CObj
{
private:
	const TEXINFO* Effect[75];
	int m_iTime;
	int m_iMaxTime;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CEffect(void);
	CEffect(D3DXVECTOR3 _vPos, eDIRECTION_TYPE _DirType)
	{
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eDirType = _DirType;

		m_tFrame = FRAME(0.f, 30.f, 14.f, 0.f);
	
		if(m_tInfo.m_eDirType == DIR_DOWN) // 보정필요
		{
			m_tFrame.fFrame = 0;
			m_tFrame.fMax = 14;
		}
		if(m_tInfo.m_eDirType == DIR_DOWN_L || m_tInfo.m_eDirType == DIR_DOWN_R)
		{
			m_tFrame.fFrame = 15;
			m_tFrame.fMax = 29;
		}
		if(m_tInfo.m_eDirType == DIR_LEFT || m_tInfo.m_eDirType == DIR_RIGHT)
		{
			m_tFrame.fFrame = 30;
			m_tFrame.fMax = 44;
		}
		if(m_tInfo.m_eDirType == DIR_UP_L || m_tInfo.m_eDirType == DIR_UP_R)
		{
			m_tFrame.fFrame = 45;
			m_tFrame.fMax = 69;
		}
		if(m_tInfo.m_eDirType == DIR_UP)
		{
			m_tFrame.fFrame = 60;
			m_tFrame.fMax = 74;
		}
		m_tFrame.fOriFrame = m_tFrame.fFrame;
		
	}

	CEffect(D3DXVECTOR3 _vPos, eSIXTEEN_DIRECTION_TYPE _DirType)
	{
		m_tInfo.vPos = _vPos;
		m_tInfo.m_eSixteenDirType = _DirType;

		m_tFrame = FRAME(0.f, 20.f, 14.f, 0.f);
		
		if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN) // 보정필요
		{
			m_tFrame.fFrame = 0;
			m_tFrame.fMax = 14;
		}
		if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_L1 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_L2
			|| m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_L3 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R1
			|| m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R2 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_DOWN_R3)
		{

			m_tFrame.fFrame = 15;
			m_tFrame.fMax = 29;
		}
		if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_LEFT || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_RIGHT)
		{

			m_tFrame.fFrame = 30;
			m_tFrame.fMax = 44;
		}
		if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_L1 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_L2
			|| m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_L3 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R1
			|| m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R2 || m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP_R3)
		{
			m_tFrame.fFrame = 45;
			m_tFrame.fMax = 69;
		}
		if(m_tInfo.m_eSixteenDirType == SIXTEEN_DIR_UP)
		{
			m_tFrame.fFrame = 60;
			m_tFrame.fMax = 74;
		}

		m_iMaxTime = 40;

		m_tFrame.fOriFrame = m_tFrame.fFrame;

	}
	virtual ~CEffect(void);
};

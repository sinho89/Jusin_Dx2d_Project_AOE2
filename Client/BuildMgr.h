#pragma once

class CBuildMgr
{
	DECLARE_SINGLETON(CBuildMgr)
private:
	bool	m_bPortBuildCheck;
	bool	m_bWoodBuildCheck;
	bool	m_bMineBuildCheck;
	bool	m_bBarracksBuildCheck;
	bool	m_bMillBuildCheck;
public:
	bool*	GetPortBuildCheck()
	{
		return &m_bPortBuildCheck;
	}
	bool*	GetWoodBuildCheck()
	{
		return &m_bWoodBuildCheck;
	}
	bool*	GetMineBuildCheck()
	{
		return &m_bMineBuildCheck;
	}
	bool*	GetBarracksBuildCheck()
	{
		return &m_bBarracksBuildCheck;
	}
	bool*	GetMillBuildCheck()
	{
		return &m_bMillBuildCheck;
	}
private:
	CBuildMgr(void);
public:
	~CBuildMgr(void);
};

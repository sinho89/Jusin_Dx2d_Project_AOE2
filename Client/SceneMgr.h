#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
private:
	CScene*		m_pScene;
public:
	void	SetScene(eSceneType	eType);
	void	Update(void);
	void	Render(void);
	void	Release(void);
private:
	CSceneMgr(void);
public:
	~CSceneMgr(void);
};

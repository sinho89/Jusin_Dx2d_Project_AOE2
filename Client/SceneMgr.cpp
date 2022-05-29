#include "StdAfx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "Stage.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr(void)
{
	m_pScene = NULL;
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

void CSceneMgr::SetScene( eSceneType eType )
{
	SAFE_DELETE(m_pScene);

	switch(eType)
	{
	case ST_LOGO:
		m_pScene = new CLogo;
		break;
	case ST_STAGE:
		m_pScene = new CStage;
		break;
	}

	m_pScene->Initialize();
}

void CSceneMgr::Update( void )
{
	m_pScene->Update();
}

void CSceneMgr::Render( void )
{
	m_pScene->Render();
}

void CSceneMgr::Release( void )
{
	SAFE_DELETE(m_pScene);
}

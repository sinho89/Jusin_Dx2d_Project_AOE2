#include "StdAfx.h"
#include "MainGame.h"
#include "TImeMgr.h"
#include "SceneMgr.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "MouseMgr.h"
#include "CollisionMgr.h"
#include "ButtonMgr.h"
#include "BuildMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame(void)
{
	m_pDevice	= NULL;
	m_fTime		= 0;
	m_iFps		= 0;
	D3DXMatrixIdentity(&matTransFPS);
	memset(m_szBuf, 0, sizeof(m_szBuf));
	CSoundMgr::GetInstance()->LoadSoundFile();

	//AllocConsole(); 
	//freopen( "CONOUT$",  "wt", stdout);
	//SetConsoleTitleA("Debug");
}

CMainGame::~CMainGame(void)
{
	Release();
	//FreeConsole();
}

HRESULT CMainGame::Initialize( void )
{
	m_pDevice = CDevice::GetInstance();
	m_pDevice->InitD3D();

	CSceneMgr::GetInstance()->SetScene(ST_LOGO);

	CTimeMgr::GetInstance()->InitTime();


	return S_OK;
}

int CMainGame::Update( void )
{
	CTimeMgr::GetInstance()->SetTime();

	CSceneMgr::GetInstance()->Update();

	return 0;
}

void CMainGame::Render( void )
{
	CDevice::GetInstance()->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	m_pDevice->Render_Begin();	

	CSceneMgr::GetInstance()->Render();

	D3DXMatrixTranslation(&matTransFPS, 700.f, 5.f, 0.f);

	++m_iFps;
	m_fTime += GETTIME;

	if(m_fTime > 1.f)
	{
		m_fTime = 0.f;
		wsprintf(m_szBuf, L"FPS : %d", m_iFps);
		m_iFps = 0;
	}

	m_pDevice->GetSprite()->SetTransform(&matTransFPS);
	m_pDevice->GetFont()->DrawTextW(m_pDevice->GetSprite(), m_szBuf, lstrlen(m_szBuf), NULL, NULL, D3DCOLOR_ARGB(255, 255, 0, 0));

	m_pDevice->Render_End();	
	CDevice::GetInstance()->GetDevice()->Present(NULL, NULL, NULL, NULL);
}

void CMainGame::Release( void )
{
	CDevice::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CTileMgr::GetInstance()->DestroyInstance();
	CCollisionMgr::GetInstance()->DestroyInstance();
	CButtonMgr::GetInstance()->DestroyInstance();
	CBuildMgr::GetInstance()->DestroyInstance();
	CSoundMgr::GetInstance()->DestroyInstance();
}

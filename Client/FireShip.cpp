#include "StdAfx.h"
#include "FireShip.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Fire.h"
#include "Effect.h"
#include "TimeMgr.h"
#include "SoundMgr.h"

CFireShip::CFireShip(void)
{
}

CFireShip::~CFireShip(void)
{
}
HRESULT	CFireShip::Initialize(void)
{
	for(int i = 0; i < 9; ++i)
		STDTex[i] = CTextureMgr::GetInstance()->GetTexture(L"FireShip", L"STD", i);
	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		for(int i = 0; i < 100; ++i)
		{
			SailTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Ship", L"MoveVibe1", i);
		}
		for(int i = 0; i < 6; ++i)
			DeathTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Ship", L"Death", i);
	}
	else if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		for(int i = 0; i < 100; ++i)
		{
			SailTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Ship", L"MoveVibe2", i);
		}
		for(int i = 0; i < 6; ++i)
			DeathTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Ship", L"Death2", i);
	}

	m_iTime = 0;
	m_iSailTime = 0;
	m_tInfo.bDeath = false;
	m_tInfo.bView = false;
	m_tInfo.fCollRange = 70.f;
	m_tInfo.iSight = 300;
	m_tInfo.iRange = 200;
	

	m_tInfo.iHp = 200;
	m_tInfo.iMaxHp = 200;
	m_tInfo.iAtt = 10;
	m_tInfo.iDef = 0;
	m_tFrame = FRAME(0.f, 10.f, 20.f, 0.f);

	pSelectionLine = CTextureMgr::GetInstance()->GetTexture(L"Select", L"Select", 1);
	pProfilTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 37);

	if(m_tInfo.m_ePlayerType == PT_PLAYER)
		m_tInfo.bView = true;

	return S_OK;
}
int		CFireShip::Update(void)
{
	if(m_tInfo.bDeath == false)
	{
		if(m_tInfo.m_ePlayerType == PT_PLAYER)
		{
			CCollisionMgr::GetInstance()->TileSightCollision(this);
			CObj* pTarget = CCollisionMgr::GetInstance()->UnitBattleFunc(this);

			if(pTarget)
			{
				float fX = pTarget->GetInfo()->vPos.x - m_tInfo.vPos.x;
				float fY = pTarget->GetInfo()->vPos.y - m_tInfo.vPos.y;
				float fDest = sqrt(fX * fX + fY * fY);

				m_tInfo.vDir = pTarget->GetInfo()->vPos - m_tInfo.vPos;
				D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

				SixteenDirCheckFunc(m_tInfo.vDir,  pTarget->GetInfo()->vPos);
				if(m_dwTime + 200 < GetTickCount())
				{
					m_dwTime = GetTickCount();
					CObj::SetTransShipDir();
					CObjMgr::GetInstance()->AddObject(L"Fire", SORT_NORMAL, CFactory<CFire>::CreateObject(this, pTarget, m_tInfo.m_eSixteenDirType));
				}
			}
		}

		else if(m_tInfo.m_ePlayerType == PT_ENEMY)
		{
			CObj* pTarget = CCollisionMgr::GetInstance()->UnitBattleFunc(this);

			if(pTarget)
			{
				m_tInfo.bMove = false;
				float fX = pTarget->GetInfo()->vPos.x - m_tInfo.vPos.x;
				float fY = pTarget->GetInfo()->vPos.y - m_tInfo.vPos.y;
				float fDest = sqrt(fX * fX + fY * fY);

				m_tInfo.vDir = pTarget->GetInfo()->vPos - m_tInfo.vPos;
				D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

				SixteenDirCheckFunc(m_tInfo.vDir,  pTarget->GetInfo()->vPos);
				if(m_dwEnemyTime + 200 < GetTickCount())
				{
					m_dwEnemyTime = GetTickCount();
					CObj::SetTransShipDir();
					CObjMgr::GetInstance()->AddObject(L"Fire", SORT_NORMAL, CFactory<CFire>::CreateObject(this, pTarget, m_tInfo.m_eSixteenDirType));
				}
				//CObj::AttackFunc(pTarget);
			}
			else
			{
				float fX = m_tInfo.vPos.x - m_tInfo.vGoalPos.x;
				float fY = m_tInfo.vPos.y - m_tInfo.vGoalPos.y;
				float fDest = sqrt(fX * fX + fY * fY);
				
				if(fDest > 50)
				{
					m_tInfo.bMove = true;
					m_tInfo.m_eStateType = STATE_WALK;
				}	
				CObj::SetTransShipDir();
				
			}
		}
	}
	
	if(m_tInfo.iHp <= 0 && m_tInfo.bDeath == false)
	{
		CSoundMgr::GetInstance()->ShipDead(L"ShipDead.wav");
		m_tFrame = FRAME(0.f, 5.f, 5.f, 0.f);
		m_tInfo.bDeath = true;
		//m_tInfo.bAlive = false;

	}
	if(m_tInfo.bDeath)
	{
		m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
		if(m_tFrame.fFrame > m_tFrame.fMax - 1)
		{
			m_tInfo.bAlive = false;
			if(m_tInfo.bAlive == false)
				return 0;
			m_tFrame.fFrame = m_tFrame.fOriFrame;
		}

	}
	else if(m_tInfo.bDeath == false)
	{
		if(m_tInfo.bMove == true)
		{
			CObj::MoveFunc();
		}

		if(m_iTime > 10)
		{
			m_iTime = 0;

			if(m_tInfo.m_eStateType == STATE_WALK && m_tInfo.bView == true)
				CObjMgr::GetInstance()->AddObject(L"Effect", SORT_MOVE_EFFECT, CFactory<CEffect>::CreateObject(m_tInfo.vPos, m_tInfo.m_eSixteenDirType));

		}
		++m_iTime;

		m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
		if(m_tFrame.fFrame > m_tFrame.fMax)
		{
			m_tFrame.fFrame = m_tFrame.fOriFrame;
		}
		

		if(m_tInfo.m_ePlayerType == PT_ENEMY)
		{
			CCollisionMgr::GetInstance()->EnemySightCollisoin(this);
		}
			
	}
	CObj::SetSixTeenMatrix();

	return 0;
}
void	CFireShip::Render(void)
{
	if(m_tInfo.bView == false)
		return;

	if(m_tInfo.bDeath)
	{
		if(DeathTex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(DeathTex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(DeathTex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(DeathTex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		return;
	}

	if(m_tInfo.iHp <= 0)
		return;
	if(m_tInfo.bSelection == true)
	{
		if(pSelectionLine == NULL)
			return;

		int fX = pSelectionLine->ImgInfo.Width / 2.f;
		int fY = pSelectionLine->ImgInfo.Height / 2.f - 15;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pSelectionLine->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(STDTex[m_tInfo.byDrawID] == NULL)
		return;

	int fX = int(STDTex[m_tInfo.byDrawID]->ImgInfo.Width / 2.f);
	int fY = int(STDTex[m_tInfo.byDrawID]->ImgInfo.Height / 2.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(STDTex[m_tInfo.byDrawID]->pTexture, 
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));


	if(SailTex[int(m_tFrame.fFrame)] == NULL)
		return;

	fX = int(SailTex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
	fY = int(SailTex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(SailTex[int(m_tFrame.fFrame)]->pTexture, 
		NULL,
		&D3DXVECTOR3(fX, fY + 50, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}
void	CFireShip::Release(void)
{
}
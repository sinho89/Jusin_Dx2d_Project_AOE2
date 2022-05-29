#include "StdAfx.h"
#include "Soldier.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"
#include "TImeMgr.h"
#include "ObjMgr.h"
CSoldier::CSoldier(void)
{
}

CSoldier::~CSoldier(void)
{
}

HRESULT CSoldier::Initialize( void )
{
	pTarget = NULL;
	pProfilTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 12);
	pSelectionLine = CTextureMgr::GetInstance()->GetTexture(L"Select", L"Select", 0);

	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		for(int i = 0; i < 30; ++i)
			STDTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Soldier", L"STD", i);
		for(int i = 0; i < 60; ++i)
			WalkTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Soldier", L"Walk", i);
		for(int i = 0; i < 50; ++i)
		{
			ATTTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Soldier", L"ATT", i);
			DyingTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Soldier", L"Dying", i);
		}
		for(int i = 0; i < 25; ++i)
			DeathTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Soldier", L"Death", i);
	}

	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		for(int i = 0; i < 30; ++i)
			STDTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Enemy_Soldier", L"STD", i);
		for(int i = 0; i < 60; ++i)
			WalkTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Enemy_Soldier", L"Walk", i);
		for(int i = 0; i < 50; ++i)
		{
			ATTTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Enemy_Soldier", L"ATT", i);
			DyingTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Enemy_Soldier", L"Dying", i);
		}
		for(int i = 0; i < 25; ++i)
			DeathTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Enemy_Soldier", L"Death", i);
	}

	m_tInfo.iHp = 80;
	m_tInfo.iMaxHp = 80;
	m_tInfo.iAtt = 10;
	m_tInfo.iDef = 0;

	m_tInfo.fCollRange = 15.f;
	m_tInfo.iSight = 200;
	m_tInfo.bTest = false;
	m_tFrame = FRAME(0.f, 10.f, 9.f, 0.f);
	return S_OK;
}

int CSoldier::Update( void )
{
	if(m_tInfo.bMove == true)
	{
		if(m_tInfo.m_ePlayerType == PT_PLAYER)
		{
			CCollisionMgr::GetInstance()->TileSightCollision(this);
			m_tInfo.bView = true;
		}
		CObj::MoveFunc();
	}

	CObj::GroundBattleUnitStateCheckFunc();
	CObj::SetMatrix();

	m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		if(pTarget && m_tInfo.m_eStateType == STATE_ATTACK)
		{
			if(pTarget->GetInfo()->iHp <= 0)
			{
				pTarget = NULL;
				m_tInfo.m_eStateType = STATE_STD;
			}
			else
				pTarget->GetInfo()->iHp -= m_tInfo.iAtt;
		}
		m_tFrame.fFrame = m_tFrame.fOriFrame;
	}

	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		CCollisionMgr::GetInstance()->EnemySightCollisoin(this);
	}

	if(pTarget == NULL)
		SoldierAttack();

	return 0;
}

void CSoldier::Render( void )
{
	if(m_tInfo.bView == false || m_tInfo.bTrans == true)
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

	if(m_tInfo.wstrStateKey == L"STD")
	{
		if(STDTex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(STDTex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(STDTex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(STDTex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(m_tInfo.wstrStateKey == L"Walk")
	{
		if(WalkTex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(WalkTex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(WalkTex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(WalkTex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(m_tInfo.wstrStateKey == L"ATT")
	{
		if(ATTTex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(ATTTex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(ATTTex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(ATTTex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CSoldier::Release( void )
{

}

void CSoldier::SoldierAttack( void )
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eGroundType == GT_SEA || (*iter)->GetInfo()->iHp <= 0)
			continue;

		if(m_tInfo.m_ePlayerType == PT_ENEMY && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			float fX = m_tInfo.vPos.x - (*iter)->GetInfo()->vPos.x;
			float fY = m_tInfo.vPos.y - (*iter)->GetInfo()->vPos.y;

			float fDest = sqrtf(fX * fX + fY * fY);

			if(fDest < 50)
			{
				m_tInfo.vGoalPos = (*iter)->GetInfo()->vPos;
				pTarget = *iter;
				m_tInfo.m_eStateType = STATE_ATTACK;
				return;
			}
			else if(fDest >= 50 && pTarget != NULL)
			{
				pTarget = NULL;
				m_tInfo.m_eStateType = STATE_STD;
			}

		}
	}

}

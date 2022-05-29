#include "StdAfx.h"
#include "FishShip.h"
#include "ObjMgr.h"
#include "TextureMgr.h"
#include "TIleMgr.h"
#include "TimeMgr.h"
#include "Effect.h"
#include "Factory.h"
#include "CollisionMgr.h"
CFishShip::CFishShip(void)
{
}

CFishShip::~CFishShip(void)
{
}

HRESULT CFishShip::Initialize( void )
{
	m_tInfo.bFishing = false;

	pProfilTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 32);
	pSelectionLine = CTextureMgr::GetInstance()->GetTexture(L"Select", L"Select", 1);

	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		for(int i = 0; i < 5; ++i)
		{
			STDTex[i] = CTextureMgr::GetInstance()->GetTexture(L"FishShip", L"STD", i);
			FishingTex[i] = CTextureMgr::GetInstance()->GetTexture(L"FishShip", L"Fishing", i);
			DeathTex[i] = CTextureMgr::GetInstance()->GetTexture(L"FishShip", L"Death", i);
		}
	}

	m_tInfo.iHp = 60;
	m_tInfo.iMaxHp = 60;
	m_tInfo.iAtt = 0;
	m_tInfo.iDef = 0;
	m_iTime = 0;
	m_tInfo.fCollRange = 20.f;
	m_tInfo.iSight = 250;

	return S_OK;
}

int CFishShip::Update( void )
{
	
	/*system("cls");
	cout << "Goal Pos x: " << m_tInfo.vGoalPos.x << endl;
	cout << "Goal Pos y: " << m_tInfo.vGoalPos.y << endl << endl;
	cout << "Pos x: " << m_tInfo.vPos.x << endl;
	cout << "Pos y: " << m_tInfo.vPos.y << endl;*/
	
	if(m_tInfo.bMove == true)
	{
		CCollisionMgr::GetInstance()->TileSightCollision(this);
		CObj::MoveFunc();
	}
	CObj::StateCheckFunc();
	CObj::SetMatrix();

	SaveMove();


	if(m_iTime > 10)
	{
		
		if(m_tInfo.m_eStateType == STATE_WALK || m_tInfo.m_eStateType == STATE_FISHING_WORK)
			CObjMgr::GetInstance()->AddObject(L"Effect", SORT_MOVE_EFFECT, CFactory<CEffect>::CreateObject(m_tInfo.vPos, m_tInfo.m_eDirType));

		m_iTime = 0;
		if(m_tInfo.m_eStateType == STATE_FISHING)
		{
			GetResource();
		}

		if(m_tInfo.m_eStateType == STATE_BUILD)
		{
			Building();
		}
	}

	++m_iTime;


	return 0;
}

void CFishShip::Render( void )
{
	if(STDTex[m_tInfo.byDrawID] == NULL)
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

	int fX = int(STDTex[m_tInfo.byDrawID]->ImgInfo.Width / 2.f);
	int fY = int(STDTex[m_tInfo.byDrawID]->ImgInfo.Height / 2.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(STDTex[m_tInfo.byDrawID]->pTexture, 
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	if(m_tInfo.bFishing == true)
	{

		if(FishingTex[m_tInfo.byDrawID] == NULL)
			return;

		int fX = int(FishingTex[m_tInfo.byDrawID]->ImgInfo.Width / 2.f);
		int fY = int(FishingTex[m_tInfo.byDrawID]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(FishingTex[m_tInfo.byDrawID]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY - 30, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CFishShip::Release( void )
{

}

void CFishShip::Building()
{
	/*list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Sequence", SORT_OBJECT ).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Sequence", SORT_OBJECT ).end();

	if(iter == iter_end)
		return;

	for(; iter != iter_end; ++iter)
	{
		float fX = CTileMgr::GetInstance()->GetTile()[m_tInfo.iWorkingIndex]->vPos.x - (*iter)->GetInfo()->vPos.x;
		float fY = CTileMgr::GetInstance()->GetTile()[m_tInfo.iWorkingIndex]->vPos.y - (*iter)->GetInfo()->vPos.y;

		float fDest = sqrt(fX * fX + fY * fY);

		if(fDest <= 60)
		{
			if((*iter)->GetInfo()->iHp >= 120)
			{

				m_tInfo.bDirCheck = false;
				m_tInfo.m_eStateType = STATE_STD;
			}
			(*iter)->GetInfo()->iHp += 20;
			break;
		}

	}*/
}

void CFishShip::GetResource()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Resource", SORT_OBJECT ).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Resource", SORT_OBJECT ).end();

	for(; iter != iter_end; ++iter)
	{
		float fX = CTileMgr::GetInstance()->GetTile()[m_tInfo.iWorkingIndex]->vPos.x - (*iter)->GetInfo()->vPos.x;
		float fY = CTileMgr::GetInstance()->GetTile()[m_tInfo.iWorkingIndex]->vPos.y - (*iter)->GetInfo()->vPos.y;

		float fDest = sqrt(fX * fX + fY * fY);

		if(fDest <= 10)
		{
			--(*iter)->GetInfo()->iHp;
			++m_tInfo.iGetResourceCount;
			break;
		}
		
	}

	if(m_tInfo.iGetResourceCount >= 100)
	{
		if((*iter)->GetInfo()->m_eResourceType == RT_FISH)
		{
			m_tInfo.m_eStateType = STATE_FISHING_WORK;
		}

		FIndSaveBuild();
	}
}

void CFishShip::FIndSaveBuild()
{
	unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->begin();
	unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter_end = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->end();

	map<float, CObj*>		m_SaveBuildMap;

	for(; iter != iter_end; ++iter)
	{
		for(list<CObj*>::iterator Obj_iter = iter->second.begin();
			Obj_iter != iter->second.end(); ++Obj_iter)
		{

			if(m_tInfo.m_eStateType == STATE_FISHING_WORK)
			{
				if((*Obj_iter)->GetInfo()->m_eSaveType == SRT_PORT)
				{
					float fX = m_tInfo.vPos.x - (*Obj_iter)->GetInfo()->vPos.x;
					float fY = m_tInfo.vPos.y - (*Obj_iter)->GetInfo()->vPos.y;

					float fDest = sqrt(fX * fX + fY * fY);
					m_SaveBuildMap.insert(make_pair(fDest, (*Obj_iter)));
				}
			}
		}
	}

	map<float, CObj*>::iterator Best_iter = m_SaveBuildMap.begin();

	m_tInfo.vSavePos = Best_iter->second->GetInfo()->vPos;

	m_SaveBuildMap.clear();
}

void CFishShip::SaveMove()
{
	if(m_tInfo.iGetResourceCount >= 100)
	{
		float fX = m_tInfo.vSavePos.x - m_tInfo.vPos.x;
		float fY = m_tInfo.vSavePos.y - m_tInfo.vPos.y - 10;
		float fDest = sqrt(fX * fX + fY * fY);

		m_tInfo.vDir = m_tInfo.vSavePos - m_tInfo.vPos;
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		DirCheckFunc(m_tInfo.vDir, m_tInfo.vSavePos);
		if(m_tInfo.bDirCheck == false)
		{
			SetFishShipDir();
			m_tInfo.bDirCheck = true;
		}
		m_tInfo.vPos += m_tInfo.vDir * m_tInfo.fSpeed * GETTIME;

		if(fDest < 80)
		{
			m_tInfo.bDirCheck = false;
			list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"MainUI", SORT_UI).begin();

			if(m_tInfo.m_eStateType == STATE_FISHING_WORK)
			{
				(*iter)->GetInfo()->iFoodNum += 100;
			}
			// 자원올리기 UI랑 같이
			m_tInfo.m_eStateType = STATE_WALK;
			m_tInfo.vGoalPos = CTileMgr::GetInstance()->GetTile()[m_tInfo.iWorkingIndex]->vPos;
			return;
		}
	}
}

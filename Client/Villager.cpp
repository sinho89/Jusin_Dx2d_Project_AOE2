#include "StdAfx.h"
#include "Villager.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "TImeMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"

CVillager::CVillager(void)
{
}

CVillager::~CVillager(void)
{
}


HRESULT CVillager::Initialize( void )
{
	m_iTime = 0;
	bGetResource = false;
	m_tInfo.bBuildStartVillager = false;

	pSelectionLine = CTextureMgr::GetInstance()->GetTexture(L"Select", L"Select", 0);
	pProfilTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 10);

	if(m_tInfo.m_ePlayerType == PT_PLAYER)
	{
		for(int i = 0; i < 75; ++i)
		{
			STDTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Villager", L"STD", i);
			WalkTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Villager", L"Walk", i);
			ATTTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Villager", L"ATT", i);
			Berry_Walk_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Berry_Gatherer_Walk", i);
			Berry_Get_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Berry_Gatherer_Kneeling", i);
			Building_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Building", i);
			Mine_Get_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Miner_Mining", i);
			Gold_Carry_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Miner_Carrying_Gold", i);
			Stone_Carry_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Miner_Carrying_Stone", i);
			Wood_Carry_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Carrying_Wood", i);
			Wood_Chopping_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Chopping", i);
			Dying_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Dying", i);
		}
		for(int i = 0; i < 25; ++i)
		{
			Dead_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Villager_Death", i);
		}
	}
	else if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		for(int i = 0; i < 75; ++i)
		{
			STDTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Enemy_Villager", L"STD", i);
			WalkTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Enemy_Villager", L"Walk", i);
			ATTTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Enemy_Villager", L"ATT", i);
			Berry_Walk_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Berry_Gatherer_Walk", i);
			Berry_Get_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Berry_Gatherer_Kneeling", i);
			Building_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Building", i);
			Mine_Get_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Miner_Mining", i);
			Gold_Carry_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Miner_Carrying_Gold", i);
			Stone_Carry_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Miner_Carrying_Stone", i);
			Wood_Carry_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Carrying_Wood", i);
			Wood_Chopping_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Chopping", i);
			Dying_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Dying", i);
		}
		for(int i = 0; i < 25; ++i)
		{
			Dead_Tex[i] = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, L"Villager_Death", i);
		}
	}

	m_tInfo.iHp = 80;
	m_tInfo.iMaxHp = 80;
	m_tInfo.iAtt = 0;
	m_tInfo.iDef = 0;

	m_tInfo.fCollRange = 15.f;
	m_tInfo.iSight = 200;

	m_tFrame = FRAME(0.f, 15.f, 15.f, 0.f);
	
	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		m_tInfo.iIndex = CTileMgr::GetInstance()->GetTileIndex(m_tInfo.vPos);
	}

	m_tInfo.bTest = false;
	return S_OK;
}

int CVillager::Update( void )
{
	
	
	/*CObj::KeyCheckFunc();*/
	if(m_tInfo.iHp <= 0)
	{
		m_tInfo.m_eStateType = STATE_DYING;
		if(m_tInfo.bMove == true)
		{
			m_tInfo.bMove = false;
		}
	}
	if(m_tInfo.bMove == true)
	{
		if(m_tInfo.m_ePlayerType == PT_PLAYER)
		{
			CCollisionMgr::GetInstance()->TileSightCollision(this);
			m_tInfo.bView = true;
		}
		CObj::MoveFunc();
	}
	else if(m_tInfo.bMove == false)
		m_tInfo.bTest = false;
	CObj::StateCheckFunc();
	CObj::SetMatrix();
	SaveMove();

	m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		if(m_tInfo.m_eStateType == STATE_DEATH)
			m_tInfo.bAlive = false;
		if(m_tInfo.m_eStateType == STATE_DYING)
		{
			CSoundMgr::GetInstance()->GroundDead(L"DeadVillager");
			m_tInfo.bAlive = false;
		}
		if(m_tInfo.wstrStateKey == L"Miner_Mining"
			|| m_tInfo.wstrStateKey == L"Chopping"
			|| m_tInfo.wstrStateKey == L"Berry_Gatherer_Kneeling")
		{
			GetResource();
		}

		if(m_tInfo.m_eStateType == STATE_BUILD)
		{
			Building();
		}
		m_tFrame.fFrame = m_tFrame.fOriFrame;
	}

	if(m_tInfo.m_ePlayerType == PT_ENEMY)
	{
		CCollisionMgr::GetInstance()->EnemySightCollisoin(this);
	}

	return 0;
}

void CVillager::Render( void )
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

	if(m_tInfo.wstrStateKey == L"Miner_Mining")
	{
		if(Mine_Get_Tex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(Mine_Get_Tex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(Mine_Get_Tex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(Mine_Get_Tex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(m_tInfo.wstrStateKey == L"Berry_Gatherer_Kneeling")
	{
		if(Building_Tex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(Building_Tex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(Building_Tex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(Building_Tex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(m_tInfo.wstrStateKey == L"Chopping")
	{
		if(Wood_Chopping_Tex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(Wood_Chopping_Tex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(Wood_Chopping_Tex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(Wood_Chopping_Tex
			[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(m_tInfo.wstrStateKey == L"Berry_Gatherer_Walk")
	{
		if(Berry_Walk_Tex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(Berry_Walk_Tex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(Berry_Walk_Tex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(Berry_Walk_Tex
			[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(m_tInfo.wstrStateKey == L"Carrying_Wood")
	{
		if(Wood_Carry_Tex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(Wood_Carry_Tex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(Wood_Carry_Tex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(Wood_Carry_Tex
			[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(m_tInfo.wstrStateKey == L"Miner_Carrying_Stone")
	{
		if(Stone_Carry_Tex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(Stone_Carry_Tex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(Stone_Carry_Tex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(Stone_Carry_Tex
			[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(m_tInfo.wstrStateKey == L"Miner_Carrying_Gold")
	{
		if(Gold_Carry_Tex[int(m_tFrame.fFrame)] == NULL)
			return;

		int fX = int(Gold_Carry_Tex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(Gold_Carry_Tex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(Gold_Carry_Tex
			[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if(m_tInfo.wstrStateKey == L"Building")
	{
		if(Building_Tex[int(m_tFrame.fFrame)] == NULL)

			return;

		int fX = int(Building_Tex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(Building_Tex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(Building_Tex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(m_tInfo.wstrStateKey == L"Dying")
	{
		if(Dying_Tex[int(m_tFrame.fFrame)] == NULL)

			return;

		int fX = int(Dying_Tex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(Dying_Tex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(Dying_Tex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(m_tInfo.wstrStateKey == L"Death")
	{
		if(Dead_Tex[int(m_tFrame.fFrame)] == NULL)

			return;

		int fX = int(Dead_Tex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f);
		int fY = int(Dead_Tex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(Dead_Tex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CVillager::Release( void )
{

}

void CVillager::Building()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Sequence", SORT_OBJECT ).begin();
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
			CSoundMgr::GetInstance()->GetResource(L"GetResource.wav");
			(*iter)->GetInfo()->iHp += 20;
			break;
		}

	}
}

void CVillager::GetResource()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Resource", SORT_OBJECT ).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Resource", SORT_OBJECT ).end();

	for(; iter != iter_end; ++iter)
	{
		float fX = CTileMgr::GetInstance()->GetTile()[m_tInfo.iWorkingIndex]->vPos.x - (*iter)->GetInfo()->vPos.x;
		float fY = CTileMgr::GetInstance()->GetTile()[m_tInfo.iWorkingIndex]->vPos.y - (*iter)->GetInfo()->vPos.y;

		float fDest = sqrt(fX * fX + fY * fY);

		if((*iter)->GetInfo()->wstrObjKey == L"Tree" || (*iter)->GetInfo()->wstrObjKey == L"Chopping_Tree")
		{
			fDest -= 70.f;
		}

		if(fDest <= 5)
		{
			--(*iter)->GetInfo()->iHp;
			++m_tInfo.iGetResourceCount;
			/*if((*iter)->GetInfo()->wstrObjKey == L"Chopping_Tree" || (*iter)->GetInfo()->wstrObjKey == L"Cherry")
				CSoundMgr::GetInstance()->GetResource(L"GetResource.wav");
			else
				CSoundMgr::GetInstance()->GetResource2(L"GetResource2.wav");*/
			break;
		}
		
	}

	if(m_tInfo.iGetResourceCount >= 8)
	{
		if((*iter)->GetInfo()->wstrObjKey == L"Cherry")
		{
			m_tInfo.m_eStateType = STATE_CARRY_CHERRY;
		}
		else if((*iter)->GetInfo()->wstrObjKey == L"Tree" || (*iter)->GetInfo()->wstrObjKey == L"Chopping_Tree")
		{
			m_tInfo.m_eStateType = STATE_CARRY_WOOD;
		}
		else if((*iter)->GetInfo()->wstrObjKey == L"Rock")
		{
			m_tInfo.m_eStateType = STATE_CARRY_STONE;
		}
		else if((*iter)->GetInfo()->wstrObjKey == L"Gold")
		{
			m_tInfo.m_eStateType = STATE_CARRY_GOLD;
		}

		FIndSaveBuild();
	}
}

void CVillager::FIndSaveBuild()
{
	unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->begin();
	unordered_multimap<const TCHAR*, list<CObj*>>::iterator iter_end = CObjMgr::GetInstance()->GetMap(SORT_OBJECT)->end();

	map<float, CObj*>		m_SaveBuildMap;

	for(; iter != iter_end; ++iter)
	{
		for(list<CObj*>::iterator Obj_iter = iter->second.begin();
			Obj_iter != iter->second.end(); ++Obj_iter)
		{
		
			if(m_tInfo.m_eStateType == STATE_CARRY_CHERRY)
			{
				if((*Obj_iter)->GetInfo()->m_eSaveType == SRT_EVERYTHING 
					|| (*Obj_iter)->GetInfo()->m_eSaveType == SRT_FOOD)
				{
					float fX = m_tInfo.vPos.x - (*Obj_iter)->GetInfo()->vPos.x;
					float fY = m_tInfo.vPos.y - (*Obj_iter)->GetInfo()->vPos.y;

					float fDest = sqrt(fX * fX + fY * fY);
					m_SaveBuildMap.insert(make_pair(fDest, (*Obj_iter)));
				}
			}
			if(m_tInfo.m_eStateType == STATE_CARRY_GOLD || m_tInfo.m_eStateType == STATE_CARRY_STONE)
			{
				if((*Obj_iter)->GetInfo()->m_eSaveType == SRT_EVERYTHING 
					|| (*Obj_iter)->GetInfo()->m_eSaveType == SRT_MINE)
				{
					float fX = m_tInfo.vPos.x - (*Obj_iter)->GetInfo()->vPos.x;
					float fY = m_tInfo.vPos.y - (*Obj_iter)->GetInfo()->vPos.y;

					float fDest = sqrt(fX * fX + fY * fY);
					m_SaveBuildMap.insert(make_pair(fDest, (*Obj_iter)));
				}
			}
			if(m_tInfo.m_eStateType == STATE_CARRY_WOOD)
			{
				if((*Obj_iter)->GetInfo()->m_eSaveType == SRT_EVERYTHING 
					|| (*Obj_iter)->GetInfo()->m_eSaveType == SRT_TREE)
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

void CVillager::SaveMove()
{
	if(m_tInfo.iGetResourceCount >= 8)
	{
		float fX = m_tInfo.vSavePos.x - m_tInfo.vPos.x;
		float fY = m_tInfo.vSavePos.y - m_tInfo.vPos.y - 10;
		float fDest = sqrt(fX * fX + fY * fY);

		m_tInfo.vDir = m_tInfo.vSavePos - m_tInfo.vPos;
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		DirCheckFunc(m_tInfo.vDir, m_tInfo.vSavePos);
		if(m_tInfo.bDirCheck == false)
		{
			SetVillagerDir();
			m_tInfo.bDirCheck = true;
		}
		m_tInfo.vPos += m_tInfo.vDir * m_tInfo.fSpeed * GETTIME;
	
		if(fDest < 100)
		{
			m_tInfo.bDirCheck = false;

			if(m_tInfo.m_ePlayerType == PT_PLAYER)
			{
				list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"MainUI", SORT_UI).begin();

				if(m_tInfo.m_eStateType == STATE_CARRY_CHERRY)
				{
					(*iter)->GetInfo()->iFoodNum += 100;
				}
				if(m_tInfo.m_eStateType == STATE_CARRY_WOOD)
				{
					(*iter)->GetInfo()->iTreeNum += 100;
				}
				if(m_tInfo.m_eStateType == STATE_CARRY_STONE)
				{
					(*iter)->GetInfo()->iStoneNum += 100;
				}
				if(m_tInfo.m_eStateType == STATE_CARRY_GOLD)
				{
					(*iter)->GetInfo()->iGoldNum += 100;
				}
			}
			// 자원올리기 UI랑 같이
			m_tInfo.m_eStateType = STATE_WALK;
			m_tInfo.vGoalPos = CTileMgr::GetInstance()->GetTile()[m_tInfo.iWorkingIndex]->vPos;
			return;
		}
	}
}

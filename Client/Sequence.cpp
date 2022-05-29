#include "StdAfx.h"
#include "Sequence.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Home.h"
#include "Port.h"
#include "Mine.h"
#include "Wood.h"
#include "Barracks.h"
#include "TileMgr.h"
#include "BuildMgr.h"
#include "Mill.h"

CSequence::CSequence(void)
{
}

CSequence::~CSequence(void)
{
}

HRESULT CSequence::Initialize( void )
{

	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"MainUI", SORT_UI).begin();

	switch(m_tInfo.m_eSizeType)
	{
	case BST_MIN:
		for(int i = 0; i < 3; ++i)
			m_SequenceTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Sequence_Player_Small", L"Sequence_Player_Small", i);

		(*iter)->GetInfo()->iTreeNum -= 200;
		break;
	case BST_MID:
		for(int i = 0; i < 3; ++i)
			m_SequenceTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Sequence_Player_Middle", L"Sequence_Player_Middle", i);

		(*iter)->GetInfo()->iTreeNum -= 400;
		break;
	case BST_MAX:
		for(int i = 0; i < 3; ++i)
			m_SequenceTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Sequence_Player_Big", L"Sequence_Player_Big", i);

		(*iter)->GetInfo()->iTreeNum -= 600;
		break;
	case BST_PORT:
		for(int i = 0; i < 3; ++i)
			m_SequenceTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Port_Build", L"Port_Build", i);

		(*iter)->GetInfo()->iTreeNum -= 400;
		break;
	}
	m_tInfo.iHp = 0;
	m_tInfo.byDrawID = 0;
	return S_OK;
}

int CSequence::Update( void )
{
	if(m_tInfo.iHp >= 40 && m_tInfo.iHp < 80)
	{
		m_tInfo.byDrawID = 1;
	}
	else if(m_tInfo.iHp >= 80 && m_tInfo.iHp < 120)
	{
		m_tInfo.byDrawID = 2;
	}

	if(m_tInfo.iHp > 120)
	{
		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

		for(; iter != iter_end; ++iter)
		{
			if((*iter)->GetInfo()->m_eStateType == STATE_BUILD)
			{
				float fX = (*iter)->GetInfo()->vGoalPos.x - m_tInfo.vPos.x;
				float fY = (*iter)->GetInfo()->vGoalPos.y - m_tInfo.vPos.y;
				float fDest = sqrt(fX * fX + fY * fY);

				if(fDest < 30)
				{
					(*iter)->GetInfo()->m_eStateType = STATE_STD;
				}
			}
		}
		
		if(m_tInfo.m_eSizeType == BST_MID || m_tInfo.m_eSizeType == BST_PORT)
		{
			int iIndex = CTileMgr::GetInstance()->GetTileIndex(m_tInfo.vPos);

			CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType = GT_EMPTY;
			CTileMgr::GetInstance()->GetTile()[iIndex - 1]->m_GroundType = GT_EMPTY;
			CTileMgr::GetInstance()->GetTile()[iIndex + 1]->m_GroundType = GT_EMPTY;
			CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX - 1]->m_GroundType = GT_EMPTY;
			CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX]->m_GroundType = GT_EMPTY;
			CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX + 1]->m_GroundType = GT_EMPTY;
			CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX - 1]->m_GroundType = GT_EMPTY;
			CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX]->m_GroundType = GT_EMPTY;
			CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX + 1]->m_GroundType = GT_EMPTY;

		}
		
		m_tInfo.bAlive = false;

		if(m_tInfo.m_eBuildType == BT_HOME)
			CObjMgr::GetInstance()->AddObject(L"Build", SORT_OBJECT, CFactory<CHome>::CreateObject(m_tInfo.vPos, BT_HOME, PT_PLAYER, 0));

		if(m_tInfo.m_eBuildType == BT_PORT)
		{
			CObjMgr::GetInstance()->AddObject(L"Build", SORT_OBJECT, CFactory<CPort>::CreateObject(m_tInfo.vPos, BT_PORT, PT_PLAYER, 0));
			(*CBuildMgr::GetInstance()->GetPortBuildCheck()) = true;
		}
		if(m_tInfo.m_eBuildType == BT_MINE)
		{
			CObjMgr::GetInstance()->AddObject(L"Build", SORT_OBJECT, CFactory<CMine>::CreateObject(m_tInfo.vPos, BT_MINE, PT_PLAYER, 0));
			(*CBuildMgr::GetInstance()->GetMineBuildCheck()) = true;
		}
		if(m_tInfo.m_eBuildType == BT_WOOD)
		{
			CObjMgr::GetInstance()->AddObject(L"Build", SORT_OBJECT, CFactory<CWood>::CreateObject(m_tInfo.vPos, BT_WOOD, PT_PLAYER, 0));
			(*CBuildMgr::GetInstance()->GetWoodBuildCheck()) = true;
		}
		if(m_tInfo.m_eBuildType == BT_BARRACK)
		{
			CObjMgr::GetInstance()->AddObject(L"Build", SORT_OBJECT, CFactory<CBarracks>::CreateObject(m_tInfo.vPos, BT_BARRACK, PT_PLAYER, 0));
			(*CBuildMgr::GetInstance()->GetBarracksBuildCheck()) = true;
		}
		if(m_tInfo.m_eBuildType == BT_MILL)
		{
			CObjMgr::GetInstance()->AddObject(L"Build", SORT_OBJECT, CFactory<CMill>::CreateObject(m_tInfo.vPos, BT_MILL, PT_PLAYER, 0));
			(*CBuildMgr::GetInstance()->GetMillBuildCheck()) = true;
		}
	}
	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	return 0;
}

void CSequence::Render( void )
{
	if(m_SequenceTex[m_tInfo.byDrawID] == NULL)
		return;

	float fX = m_SequenceTex[m_tInfo.byDrawID]->ImgInfo.Width / 2.f;
	float fY = m_SequenceTex[m_tInfo.byDrawID]->ImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(m_SequenceTex[m_tInfo.byDrawID]->pTexture, 
		NULL,
		&D3DXVECTOR3(fX - CObj::m_vScroll.x, fY - CObj::m_vScroll.y, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CSequence::Release( void )
{

}

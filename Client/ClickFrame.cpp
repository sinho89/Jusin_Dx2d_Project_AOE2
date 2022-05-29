#include "StdAfx.h"
#include "ClickFrame.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"
#include "ButtonMgr.h"
#include "MouseMgr.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "BuildMgr.h"
#include "LoadingBar.h"
#include "Factory.h"
#include "TransShip.h"
#include "TImeMgr.h"
#include "Formation.h"
#include "SoundMgr.h"
CClickFrame::CClickFrame(void)

{
}

CClickFrame::~CClickFrame(void)
{
}

HRESULT CClickFrame::Initialize( void )
{
	m_tInfo.bAlive = true;
	m_tInfo.bPortButtonChange = false;
	m_tInfo.bBuildHome = false;
	m_tInfo.bBuildRender = false;
	m_tInfo.bBuildPort = false;
	m_tInfo.bBuildWood = false;
	m_tInfo.bBuildMine = false;
	m_tInfo.bBuildBarracks = false;
	m_tInfo.bBuildMill = false;

	m_tInfo.bBuildLimit = false;

	for(int i = 0; i < 2; ++i)
		pClickIcon[i] = CTextureMgr::GetInstance()->GetTexture(L"FrameIcon", L"FrameIcon", i);

	for(int i = 0; i < 22; ++i)
	{
		pBuildTex[i] = CTextureMgr::GetInstance()->GetTexture(L"BuildIcon", L"BuildIcon", i);
	}
	for(int i = 0; i < 44; ++i)
	{
		pUnitControlIcon[i] = CTextureMgr::GetInstance()->GetTexture(L"ControlIcon", L"ControlIcon", i);
	}
	for(int i = 0; i < 9; ++i)
	{
		pInfoIcon[i] = CTextureMgr::GetInstance()->GetTexture(L"InterfaceIcon", L"InterfaceIcon", i);
	}
	for(int i = 0; i < 53; ++i)
	{
		pUnitIcon[i] = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", i);
	}
	for(int i = 0; i < 109; ++i)
	{
		pUpgradeIcon[i] = CTextureMgr::GetInstance()->GetTexture(L"UpgradeIcon", L"UpgradeIcon", i);
	}


	m_tInfo.bRenderCheck = 0;
	m_tInfo.bChangeButton = 0;
	iClickFrame = 0;
	bKeyUpCheck = false;
	m_tInfo.m_eControlDrawType = CDT_end;
	m_tInfo.m_eSizeType = BST_end;
	m_tInfo.m_eBuildType = BT_end;
	
	return S_OK;
}

int CClickFrame::Update( void )
{
	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	SetVillagerButton();	/* 시민 */
	SetBattleUnitButton();
	VillagerBuildDest();
	VillagerBuildSource();
	SetTownButton();		/* 마을회관 */
	SetPortButton();

	/*if(*CBuildMgr::GetInstance()->GetPortBuildCheck() == true)
		SetPortButton();*/		/* 항구		*/
	if(*CBuildMgr::GetInstance()->GetMineBuildCheck() == true)
		SetMineButton();
	if(*CBuildMgr::GetInstance()->GetBarracksBuildCheck() == true)
		SetBarracksButton();

	PushBtnCheck(); 

	if(m_tInfo.bBuildRender)
		CCollisionMgr::GetInstance()->BuildAndTileCol(m_tInfo.m_eSizeType);

	return 0;
}

void CClickFrame::Render( void )
{
	if(m_tInfo.bRenderCheck == true)
	{
		if(pClickIcon[iClickFrame] == NULL)
			return;

		float fX = pClickIcon[iClickFrame]->ImgInfo.Width / 2.f;
		float fY = pClickIcon[iClickFrame]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pClickIcon[iClickFrame]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BASE)
			VillagerBaseRender();
		if(m_tInfo.m_eControlDrawType == CDT_BATTILEUNIT_BASE)
			BattleUnitRender();
		if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST)
			VillagerBuildDestRender();
		if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_SOURCE)
			VillagerBuildSourceRender();
		if(m_tInfo.m_eControlDrawType == CDT_TOWN)
			TownRender();
		if(m_tInfo.m_eControlDrawType == CDT_PORT)
			PortRender();
		if(m_tInfo.m_eControlDrawType == CDT_BARRACKS)
			BarracksRender();
			


		if(m_tInfo.bBuildRender)
			BuildRender();
		if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST && m_tInfo.bBuildHome)
			BuildHome();
		if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST && m_tInfo.bBuildPort)
			BuildPort();
		if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST && m_tInfo.bBuildWood)
			BuildWood();
		if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST && m_tInfo.bBuildMine)
			BuildMine();
		if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST && m_tInfo.bBuildMill)
			BuildMill();
		if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_SOURCE && m_tInfo.bBuildBarracks)
			BuildBarracks();
	}
}

void CClickFrame::Release( void )
{

}

void CClickFrame::BuildRender()
{

	D3DXVECTOR3 vRendPos = CMouseMgr::GetMousePos();

	if(m_tInfo.bBuildLimit == false)
	{
		D3DXMATRIX	matTrans;
		D3DXMatrixTranslation(&matTrans, vRendPos.x, vRendPos.y, 0.f);

		if(pBuildViewTex == NULL || vRendPos.y > 450)
			return;

		float fX = pBuildViewTex->ImgInfo.Width / 2.f;
		float fY = pBuildViewTex->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildViewTex->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	else if(m_tInfo.bBuildLimit == true)
	{
		D3DXMATRIX	matTrans;
		D3DXMatrixTranslation(&matTrans, vRendPos.x, vRendPos.y, 0.f);

		if(pBuildViewTex == NULL || vRendPos.y > 450)
			return;

		float fX = pBuildViewTex->ImgInfo.Width / 2.f;
		float fY = pBuildViewTex->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildViewTex->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 0, 0));
	}

}


void CClickFrame::SetBattleUnitButton()
{
	list<CObj*>::iterator iter =  CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end =  CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eUnitType != UT_VILLAGER && (*iter)->GetInfo()->bSelection == true)
		{
			
			if(iIndex == 14)
				return;
			m_tInfo.bRenderCheck = true;
			m_tInfo.m_eControlDrawType = CDT_BATTILEUNIT_BASE;
				
			
		
			/*if((*iter)->GetInfo()->m_eStateType == STATE_WALK
				|| (*iter)->GetInfo()->m_eStateType == STATE_MINING_GOLD
				|| (*iter)->GetInfo()->m_eStateType == STATE_MINING_STONE
				|| (*iter)->GetInfo()->m_eStateType == STATE_GET_CHEERY
				|| (*iter)->GetInfo()->m_eStateType == STATE_WOOD_CUTTING
				|| (*iter)->GetInfo()->m_eStateType == STATE_CARRY_CHERRY
				|| (*iter)->GetInfo()->m_eStateType == STATE_CARRY_GOLD
				|| (*iter)->GetInfo()->m_eStateType == STATE_CARRY_STONE
				|| (*iter)->GetInfo()->m_eStateType == STATE_CARRY_WOOD)
			{
				if(iIndex == 9)
				{
					m_tInfo.bRenderCheck = true;
				}
			}
			else if((*iter)->GetInfo()->m_eUnitType != UT_VILLAGER && (*iter)->GetInfo()->m_eStateType == STATE_STD && iIndex == 9)
			{
				m_tInfo.m_eControlDrawType = CDT_BATTILEUNIT_BASE;
				m_tInfo.bRenderCheck = false;
			}*/
		}
	}
}

void CClickFrame::SetVillagerButton()
{
	if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST || m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_SOURCE)
		return;

	list<CObj*>::iterator iter =  CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end =  CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eUnitType == UT_VILLAGER && (*iter)->GetInfo()->bSelection == true)
		{
			if(iIndex == 0 || iIndex == 1 || iIndex == 2 || iIndex == 3 || iIndex == 4 )
			{
				m_tInfo.bRenderCheck = true;
				m_tInfo.m_eControlDrawType = CDT_VILLAGER_BASE;
			}
			/*if((*iter)->GetInfo()->m_eStateType == STATE_WALK
				|| (*iter)->GetInfo()->m_eStateType == STATE_MINING_GOLD
				|| (*iter)->GetInfo()->m_eStateType == STATE_MINING_STONE
				|| (*iter)->GetInfo()->m_eStateType == STATE_GET_CHEERY
				|| (*iter)->GetInfo()->m_eStateType == STATE_WOOD_CUTTING
				|| (*iter)->GetInfo()->m_eStateType == STATE_CARRY_CHERRY
				|| (*iter)->GetInfo()->m_eStateType == STATE_CARRY_GOLD
				|| (*iter)->GetInfo()->m_eStateType == STATE_CARRY_STONE
				|| (*iter)->GetInfo()->m_eStateType == STATE_CARRY_WOOD)
			{
				if(iIndex == 9)
				{
					m_tInfo.bRenderCheck = true;
				}
			}
			else if((*iter)->GetInfo()->m_eUnitType == UT_VILLAGER && (*iter)->GetInfo()->m_eStateType == STATE_STD && iIndex == 9)
			{
				m_tInfo.m_eControlDrawType = CDT_VILLAGER_BASE;
				m_tInfo.bRenderCheck = false;
			}*/
		}
	}
}	

void CClickFrame::VillagerBuildDest()
{
	if(m_tInfo.bRenderCheck == true 
		&& iIndex == 14 && iClickFrame == 1
		&& (m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST || m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_SOURCE))
	{
		CButtonMgr::GetInstance()->ButtonChange(CDT_VILLAGER_BASE);
		iClickFrame = 0;
	}
	if(m_tInfo.bRenderCheck == true 
		&& m_tInfo.m_eControlDrawType == CDT_VILLAGER_BASE
		&& iIndex == 0 && iClickFrame == 1 )
	{ // 집,방앗간,광석저장소,목재저장소,항구  ( 시대 1 )
		CButtonMgr::GetInstance()->ButtonChange(CDT_VILLAGER_BUILD_DEST);
		iClickFrame = 0;
	}

	if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST)
		if(iIndex == 0 || iIndex == 1 || iIndex == 2 || iIndex == 3 || iIndex == 4 || iIndex == 14)
			m_tInfo.bRenderCheck = true;



	/// 시대1 건설
}

void CClickFrame::VillagerBuildSource()
{
	if(m_tInfo.bRenderCheck == true 
		&& iIndex == 14 && iClickFrame == 1
		&& (m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST || m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_SOURCE))
	{
		CButtonMgr::GetInstance()->ButtonChange(CDT_VILLAGER_BASE);
		iClickFrame = 0;
	}
	if(m_tInfo.bRenderCheck == true 
		&& m_tInfo.m_eControlDrawType == CDT_VILLAGER_BASE
		&& iIndex == 1 && iClickFrame == 1)
	{
		CButtonMgr::GetInstance()->ButtonChange(CDT_VILLAGER_BUILD_SOURCE);
		iClickFrame = 0;
	}
	
	if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_SOURCE)
	{
		if(iIndex == 0 || iIndex == 7 || iIndex == 10 || iIndex == 14)
			m_tInfo.bRenderCheck = true;

		if(CObj::m_eAgeType == AT_FEUDAL)
		{
			if(iIndex == 1 || iIndex == 2 || iIndex == 8)
				m_tInfo.bRenderCheck = true;
		}

		if(CObj::m_eAgeType == AT_IMPERIAL)
		{
			if(iIndex == 1 || iIndex == 2 || iIndex == 3 || iIndex == 8 || iIndex == 12)
				m_tInfo.bRenderCheck = true;
		}

		if(CObj::m_eAgeType == AT_CASTLE)
		{
			if(iIndex == 1 || iIndex == 2 || iIndex == 3 || iIndex == 8 || iIndex == 12)
				m_tInfo.bRenderCheck = true;
		}
	}
}
void CClickFrame::BuildHome()
{
	if(m_tInfo.bRenderCheck == true 
		&& m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST
		&& iIndex == 0 && iClickFrame == 1 )
	{
		if(CObj::m_eAgeType == AT_DARK)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerHome", L"PlayerHome", 0);
		if(CObj::m_eAgeType == AT_FEUDAL)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerHome2", L"PlayerHome2", 0);
		if(CObj::m_eAgeType == AT_IMPERIAL || CObj::m_eAgeType == AT_CASTLE)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerHome3", L"PlayerHome3", 0);
		m_tInfo.m_eSizeType = BST_MID;
		iClickFrame = 0;
		m_tInfo.bBuildRender = true;
		m_tInfo.bBuildHome =false;
	}
}

void CClickFrame::BuildPort()
{
	if(m_tInfo.bRenderCheck == true 
		&& m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST
		&& iIndex == 4 && iClickFrame == 1 )
	{

		if(CObj::m_eAgeType == AT_DARK)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerPort", L"PlayerPort", 0);
		if(CObj::m_eAgeType == AT_FEUDAL)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerPort2", L"PlayerPort2", 0);
		if(CObj::m_eAgeType == AT_IMPERIAL || CObj::m_eAgeType == AT_CASTLE)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerPort4", L"PlayerPort4", 0);

		m_tInfo.m_eSizeType = BST_PORT;
		iClickFrame = 0;
		m_tInfo.bBuildRender = true;
		m_tInfo.bBuildPort =false;
	}
}

void CClickFrame::BuildWood()
{
	if(m_tInfo.bRenderCheck == true 
		&& m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST
		&& iIndex == 3 && iClickFrame == 1 )
	{
		pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerLumberCamp", L"PlayerLumberCamp", 0);
		m_tInfo.m_eSizeType = BST_MID;
		iClickFrame = 0;
		m_tInfo.bBuildRender = true;
		m_tInfo.bBuildWood =false;
	}
}

void CClickFrame::BuildMine()
{
	if(m_tInfo.bRenderCheck == true 
		&& m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST
		&& iIndex == 2 && iClickFrame == 1 )
	{
		pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerMiningCamp", L"PlayerMiningCamp", 0);
		m_tInfo.m_eSizeType = BST_MID;
		iClickFrame = 0;
		m_tInfo.bBuildRender = true;
		m_tInfo.bBuildMine =false;
	}
}
void CClickFrame::BuildBarracks()
{
	if(m_tInfo.bRenderCheck == true 
		&& m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_SOURCE
		&& iIndex == 0 && iClickFrame == 1 )
	{

		if(CObj::m_eAgeType == AT_DARK)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerBarraks", L"PlayerBarraks", 0);
		if(CObj::m_eAgeType == AT_FEUDAL)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerBarracks2", L"PlayerBarraks2", 0);
		if(CObj::m_eAgeType == AT_IMPERIAL || CObj::m_eAgeType == AT_CASTLE)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerBarracks3", L"PlayerBarraks3", 0);

		m_tInfo.m_eSizeType = BST_MAX;
		iClickFrame = 0;
		m_tInfo.bBuildRender = true;
		m_tInfo.bBuildBarracks =false;
	}
}


void CClickFrame::BuildMill()
{
	if(m_tInfo.bRenderCheck == true 
		&& m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST
		&& iIndex == 1 && iClickFrame == 1 )
	{
		if(CObj::m_eAgeType == AT_DARK)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerMill", L"PlayerMill", 0);
		if(CObj::m_eAgeType == AT_FEUDAL)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerMill2", L"PlayerMill2", 0);
		if(CObj::m_eAgeType == AT_IMPERIAL || CObj::m_eAgeType == AT_CASTLE)
			pBuildViewTex = CTextureMgr::GetInstance()->GetTexture(L"PlayerMill3", L"PlayerMill3", 0);
		m_tInfo.m_eSizeType = BST_MID;
		iClickFrame = 0;
		m_tInfo.bBuildRender = true;
		m_tInfo.bBuildMill =false;
	}
}

void CClickFrame::PushBtnCheck()
{

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		if(bClickCheck == true)
			return;
		bClickCheck = true;

		if(iIndex == CCollisionMgr::GetInstance()->GetPushButtonIndex())
		{
			iClickFrame = 1;
			if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST && 
				m_tInfo.bBuildRender == false && iIndex == 0)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				m_tInfo.bBuildHome = true;
				m_tInfo.m_eBuildType = BT_HOME;
			}
			if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST && 
				m_tInfo.bBuildRender == false && iIndex == 4)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				m_tInfo.bBuildPort = true;
				m_tInfo.m_eBuildType = BT_PORT;
			}
			if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST && 
				m_tInfo.bBuildRender == false && iIndex == 2)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				m_tInfo.bBuildMine = true;
				m_tInfo.m_eBuildType = BT_MINE;
			}
			if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST && 
				m_tInfo.bBuildRender == false && iIndex == 3)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				m_tInfo.bBuildWood = true;
				m_tInfo.m_eBuildType = BT_WOOD;
			}
			if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_SOURCE && 
				m_tInfo.bBuildRender == false && iIndex == 0)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				m_tInfo.bBuildBarracks = true;
				m_tInfo.m_eBuildType = BT_BARRACK;
			}
			if(m_tInfo.m_eControlDrawType == CDT_VILLAGER_BUILD_DEST && 
				m_tInfo.bBuildRender == false && iIndex == 1)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				m_tInfo.bBuildMill = true;
				m_tInfo.m_eBuildType = BT_MILL;
			}
			if(m_tInfo.m_eControlDrawType == CDT_BARRACKS && iIndex == 0)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				if(CObj::m_iMakeSoldier == 0)
					CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_SOLDIER));
				++CObj::m_iMakeSoldier;
			}
			if(m_tInfo.m_eControlDrawType == CDT_TOWN && iIndex == 0)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				if(CObj::m_iMakeVillager == 0)
					CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_VILLAGER));
				++CObj::m_iMakeVillager;
			}

			if(m_tInfo.m_eControlDrawType == CDT_PORT && iIndex == 0 && m_tInfo.bPortButtonChange == false)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				if(CObj::m_iMakeFishShip == 0)
					CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_FISHSHIP));
				++CObj::m_iMakeFishShip;
			}
			if(m_tInfo.m_eControlDrawType == CDT_PORT && iIndex == 1 && CObj::m_eAgeType != AT_DARK && m_tInfo.bPortButtonChange == false)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				if(CObj::m_iMakeTransShip == 0)
					CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_TRANSSHIP));
				++CObj::m_iMakeTransShip;
			}

			if(m_tInfo.m_eControlDrawType == CDT_PORT && iIndex == 0 && CObj::m_eAgeType != AT_DARK && m_tInfo.bPortButtonChange == true)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				if(CObj::m_iMakeDestroyShip == 0)
					CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_DESTROYSHIP));
				++CObj::m_iMakeDestroyShip;
			}

			if(m_tInfo.m_eControlDrawType == CDT_PORT && iIndex == 1 && CObj::m_eAgeType != AT_DARK && m_tInfo.bPortButtonChange == true)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				if(CObj::m_iMakeFireShip == 0)
					CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_FIRESHIP));
				++CObj::m_iMakeFireShip;
			}

			if(m_tInfo.m_eControlDrawType == CDT_PORT && iIndex == 2 && (CObj::m_eAgeType == AT_IMPERIAL || CObj::m_eAgeType == AT_CASTLE) && m_tInfo.bPortButtonChange == true)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				if(CObj::m_iMakeCannonShip == 0)
					CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_STONESHIP));
				++CObj::m_iMakeCannonShip;
			}
			
			if(m_tInfo.m_eControlDrawType == CDT_PORT && iIndex == 14 && CObj::m_eAgeType != AT_DARK)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				CButtonMgr::GetInstance()->PortSource();
			}
			if(m_tInfo.m_eControlDrawType == CDT_PORT && iIndex == 3 && CObj::m_eAgeType != AT_DARK && m_tInfo.bPortButtonChange == false)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				if(CObj::m_iMakeGalleyShip == 0)
					CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_GALLYSHIP));
				++CObj::m_iMakeGalleyShip;
			}
			if(m_tInfo.m_eControlDrawType == CDT_TOWN && iIndex == 10)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_UPGRADE_AGE));
			}
			if(m_tInfo.m_eControlDrawType == CDT_BATTILEUNIT_BASE && iIndex == 10)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				CObj::FormationWidth = true;
			}
			if(m_tInfo.m_eControlDrawType == CDT_BATTILEUNIT_BASE && iIndex == 11)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				CObj::FormationRect = true;
			}
			if(m_tInfo.m_eControlDrawType == CDT_BATTILEUNIT_BASE && iIndex == 12)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				CObj::FormationCheck = true;
			}
			if(m_tInfo.m_eControlDrawType == CDT_BATTILEUNIT_BASE && iIndex == 13)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				CObj::FormationDiv = true;
			}
			if(m_tInfo.m_eControlDrawType == CDT_BATTILEUNIT_BASE && iIndex == 2)
			{
				CSoundMgr::GetInstance()->ClickSound(L"Click.wav");
				list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
				list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

				for(; iter != iter_end; ++iter)
				{
					if((*iter)->GetInfo()->m_eUnitType == UT_TRANSSHIP && (*iter)->GetInfo()->bSelection == true &&CObjMgr::GetInstance()->GetGroupMap()->size() == 1)
					{
						int iIndex = CTileMgr::GetInstance()->GetTileIndex((*iter)->GetInfo()->vPos);


						//if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_SEA
						//	&& CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType == RT_NONE
						//	&& ((CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX - 1]->m_GroundType == GT_GROUND
						//	&& CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX]->m_GroundType == GT_GROUND
						//	&& CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX + 1]->m_GroundType == GT_GROUND)
						//	|| (CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX - 1]->m_GroundType == GT_GROUND
						//	&& CTileMgr::GetInstance()->GetTile()[iIndex - 1]->m_GroundType == GT_GROUND
						//	&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX - 1]->m_GroundType == GT_GROUND)
						//	|| (CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX - 1]->m_GroundType == GT_GROUND
						//	&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX]->m_GroundType == GT_GROUND
						//	&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX + 1]->m_GroundType == GT_GROUND)
						//	|| (CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX + 1]->m_GroundType == GT_GROUND
						//	&& CTileMgr::GetInstance()->GetTile()[iIndex + 1]->m_GroundType == GT_GROUND
						//	&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX + 1]->m_GroundType == GT_GROUND)))

						if(CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX - 1]->m_GroundType == GT_GROUND
							&& CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX]->m_GroundType == GT_GROUND
							&& CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX + 1]->m_GroundType == GT_GROUND) // 우-상
						{
							(*iter)->GetInfo()->bTrans = false;
							((CTransShip*)(*iter))->GetTransTex()->clear();

							list<CObj*>::iterator Trans_iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
							list<CObj*>::iterator Trans_iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

							for(; Trans_iter != Trans_iter_end; ++Trans_iter)
							{
								if((*Trans_iter)->GetInfo()->bTrans == true)
								{
									(*Trans_iter)->GetInfo()->vPos.x = CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX]->vPos.x + rand() % 75;
									(*Trans_iter)->GetInfo()->vPos.y = CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX]->vPos.y - rand() % 75;
									(*Trans_iter)->GetInfo()->bTrans = false;

								}
							}
						}

						else if((CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX - 1]->m_GroundType == GT_GROUND
								&& CTileMgr::GetInstance()->GetTile()[iIndex - 1]->m_GroundType == GT_GROUND
								&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX - 1]->m_GroundType == GT_GROUND)) // 좌-상
						{
							(*iter)->GetInfo()->bTrans = false;
							((CTransShip*)(*iter))->GetTransTex()->clear();

							list<CObj*>::iterator Trans_iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
							list<CObj*>::iterator Trans_iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

							for(; Trans_iter != Trans_iter_end; ++Trans_iter)
							{
								if((*Trans_iter)->GetInfo()->bTrans == true)
								{
									(*Trans_iter)->GetInfo()->vPos.x = CTileMgr::GetInstance()->GetTile()[iIndex - 1]->vPos.x - rand() % 75;
									(*Trans_iter)->GetInfo()->vPos.y = CTileMgr::GetInstance()->GetTile()[iIndex - 1]->vPos.y - rand() % 75;
									(*Trans_iter)->GetInfo()->bTrans = false;

								}
							}
						}

						else if((CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX - 1]->m_GroundType == GT_GROUND
								&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX]->m_GroundType == GT_GROUND
								&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX + 1]->m_GroundType == GT_GROUND)) // 좌-하
						{
							(*iter)->GetInfo()->bTrans = false;
							((CTransShip*)(*iter))->GetTransTex()->clear();

							list<CObj*>::iterator Trans_iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
							list<CObj*>::iterator Trans_iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

							for(; Trans_iter != Trans_iter_end; ++Trans_iter)
							{
								if((*Trans_iter)->GetInfo()->bTrans == true)
								{
									(*Trans_iter)->GetInfo()->vPos.x = CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX]->vPos.x - rand() % 75;
									(*Trans_iter)->GetInfo()->vPos.y = CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX]->vPos.y + rand() % 75;
									(*Trans_iter)->GetInfo()->bTrans = false;

								}
							}
						}

						else if(CTileMgr::GetInstance()->GetTile()[iIndex - TILECNTX + 1]->m_GroundType == GT_GROUND
								&& CTileMgr::GetInstance()->GetTile()[iIndex + 1]->m_GroundType == GT_GROUND
								&& CTileMgr::GetInstance()->GetTile()[iIndex + TILECNTX + 1]->m_GroundType == GT_GROUND) // 좌-하
						{
							(*iter)->GetInfo()->bTrans = false;
							((CTransShip*)(*iter))->GetTransTex()->clear();

							list<CObj*>::iterator Trans_iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
							list<CObj*>::iterator Trans_iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

							for(; Trans_iter != Trans_iter_end; ++Trans_iter)
							{
								if((*Trans_iter)->GetInfo()->bTrans == true)
								{
									(*Trans_iter)->GetInfo()->vPos.x = CTileMgr::GetInstance()->GetTile()[iIndex + 1]->vPos.x + rand() % 75;
									(*Trans_iter)->GetInfo()->vPos.y = CTileMgr::GetInstance()->GetTile()[iIndex + 1]->vPos.y + rand() % 75;
									(*Trans_iter)->GetInfo()->bTrans = false;

								}
							}
						}
					}
				}
				
			}
		}
	}
	else
	{
		iClickFrame = 0;
		bClickCheck = false;
	}

	if(m_tInfo.m_eControlDrawType == CDT_end)
	{
		m_tInfo.bBuildRender = false;
	}
}

void CClickFrame::BattleUnitRender()
{
	float fX = 0;
	float fY = 0;  // 

	switch(iIndex)
	{
	case 0:
		if(pUnitControlIcon[0] == NULL)
			return;

		fX = pUnitControlIcon[0]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[0]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[0]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 1:
		if(pUnitControlIcon[1] == NULL)
			return;

		fX = pUnitControlIcon[1]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[1]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[1]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 2:
		if(pUnitControlIcon[2] == NULL)
			return;

		fX = pUnitControlIcon[2]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[2]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[2]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 3:
		if(pUnitControlIcon[3] == NULL)
			return;

		fX = pUnitControlIcon[3]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[3]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[3]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 4:
		if(pUnitControlIcon[4] == NULL)
			return;

		fX = pUnitControlIcon[4]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[4]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[4]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 5:
		if(pUnitControlIcon[5] == NULL)
			return;

		fX = pUnitControlIcon[5]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[5]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[5]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 6:
		if(pUnitControlIcon[7] == NULL)
			return;

		fX = pUnitControlIcon[7]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[7]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[7]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 7:
		if(pUnitControlIcon[9] == NULL)
			return;

		fX = pUnitControlIcon[9]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[9]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[9]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 8:
		if(pUnitControlIcon[11] == NULL)
			return;

		fX = pUnitControlIcon[11]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[11]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[11]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 9:
		if(pUnitControlIcon[21] == NULL)
			return;

		fX = pUnitControlIcon[21]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[21]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[21]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 10:
		if(pUnitControlIcon[13] == NULL)
			return;

		fX = pUnitControlIcon[13]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[13]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[13]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case 11:
		if(pUnitControlIcon[15] == NULL)
			return;

		fX = pUnitControlIcon[15]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[15]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[15]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case 12:
		if(pUnitControlIcon[17] == NULL)
			return;

		fX = pUnitControlIcon[17]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[17]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[17]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case 13:
		if(pUnitControlIcon[19] == NULL)
			return;

		fX = pUnitControlIcon[19]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[19]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[19]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
}
void CClickFrame::VillagerBaseRender()
{
	float fX = 0;
	float fY = 0;

	switch(iIndex)
	{
		case 0:
			if(pUnitControlIcon[22] == NULL)
				return;

			fX = pUnitControlIcon[22]->ImgInfo.Width / 2.f;
			fY = pUnitControlIcon[22]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[22]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 1:
			if(pUnitControlIcon[23] == NULL)
				return;

			fX = pUnitControlIcon[23]->ImgInfo.Width / 2.f;
			fY = pUnitControlIcon[23]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[23]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 2:
			if(pUnitControlIcon[24] == NULL)
				return;

			fX = pUnitControlIcon[24]->ImgInfo.Width / 2.f;
			fY = pUnitControlIcon[24]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[24]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 3:
			if(pUnitControlIcon[3] == NULL)
				return;

			fX = pUnitControlIcon[3]->ImgInfo.Width / 2.f;
			fY = pUnitControlIcon[3]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[3]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 4:
			if(pUnitControlIcon[4] == NULL)
				return;

			fX = pUnitControlIcon[4]->ImgInfo.Width / 2.f;
			fY = pUnitControlIcon[4]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[4]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 9:
			if(pUnitControlIcon[21] == NULL)
				return;

			fX = pUnitControlIcon[21]->ImgInfo.Width / 2.f;
			fY = pUnitControlIcon[21]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[21]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
	}
}

void CClickFrame::ClearButton()
{
}

void CClickFrame::VillagerBuildDestRender()
{
	float fX = 0;
	float fY = 0;

	switch(iIndex)
	{
	case 0:
		if(pBuildTex[15] == NULL)
			return;

		fX = pBuildTex[15]->ImgInfo.Width / 2.f;
		fY = pBuildTex[15]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[15]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 1:
		if(pBuildTex[7] == NULL)
			return;

		fX = pBuildTex[7]->ImgInfo.Width / 2.f;
		fY = pBuildTex[7]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[7]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 2:
		if(pBuildTex[19] == NULL)
			return;

		fX = pBuildTex[19]->ImgInfo.Width / 2.f;
		fY = pBuildTex[19]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[19]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 3:
		if(pBuildTex[20] == NULL)
			return;

		fX = pBuildTex[20]->ImgInfo.Width / 2.f;
		fY = pBuildTex[20]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[20]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 4:
		if(pBuildTex[5] == NULL)
			return;

		fX = pBuildTex[5]->ImgInfo.Width / 2.f;
		fY = pBuildTex[5]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[5]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 14:
		if(pUnitControlIcon[26] == NULL)
			return;

		fX = pUnitControlIcon[26]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[26]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[26]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
}

void CClickFrame::VillagerBuildSourceRender()
{
	float fX = 0;
	float fY = 0;

	switch(iIndex)
	{
	case 0:
		if(pBuildTex[0] == NULL)
			return;

		fX = pBuildTex[0]->ImgInfo.Width / 2.f;
		fY = pBuildTex[0]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[0]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case 1:
		if(CObj::m_eAgeType == AT_DARK)
			return;
		if(pBuildTex[4] == NULL)
			return;

		fX = pBuildTex[4]->ImgInfo.Width / 2.f;
		fY = pBuildTex[4]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[4]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case 2:
		if(CObj::m_eAgeType == AT_DARK)
			return;
		if(pBuildTex[9] == NULL)
			return;

		fX = pBuildTex[9]->ImgInfo.Width / 2.f;
		fY = pBuildTex[9]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[9]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 3:
		if(CObj::m_eAgeType == AT_DARK || CObj::m_eAgeType == AT_FEUDAL)
			return;
		if(pBuildTex[8] == NULL)
			return;

		fX = pBuildTex[8]->ImgInfo.Width / 2.f;
		fY = pBuildTex[8]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[8]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 7:
		if(pBuildTex[12] == NULL)
			return;

		fX = pBuildTex[12]->ImgInfo.Width / 2.f;
		fY = pBuildTex[12]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[12]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 8:
		if(CObj::m_eAgeType == AT_DARK)
			return;
		if(pBuildTex[10] == NULL)
			return;

		fX = pBuildTex[10]->ImgInfo.Width / 2.f;
		fY = pBuildTex[10]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[10]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 10:
		if(pBuildTex[17] == NULL)
			return;

		fX = pBuildTex[17]->ImgInfo.Width / 2.f;
		fY = pBuildTex[17]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[17]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 12:
		if(CObj::m_eAgeType == AT_DARK || CObj::m_eAgeType == AT_FEUDAL)
			return;
		if(pBuildTex[2] == NULL)
			return;

		fX = pBuildTex[2]->ImgInfo.Width / 2.f;
		fY = pBuildTex[2]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pBuildTex[2]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 14:
		if(pUnitControlIcon[26] == NULL)
			return;

		fX = pUnitControlIcon[26]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[26]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[26]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
}

void CClickFrame::SetTownButton()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).end();

	if(iter == iter_end)
	{
		m_tInfo.bRenderCheck = false;
		return;
	}
	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_TOWN && (*iter)->GetInfo()->bSelection == true)
		{
			if(CObj::m_eAgeType == AT_CASTLE)
			{
				if(iIndex == 10)
					m_tInfo.bRenderCheck = false;
				if(iIndex == 0 || iIndex == 4 || iIndex == 14 )
				{
					m_tInfo.bRenderCheck = true;
					m_tInfo.m_eControlDrawType = CDT_TOWN;
				}
			}
			else
			{
				if(iIndex == 0 || iIndex == 4 || iIndex == 14 || iIndex == 10 )
				{
					m_tInfo.bRenderCheck = true;
					m_tInfo.m_eControlDrawType = CDT_TOWN;
				}
			}
		}
	}
}
void CClickFrame::SetPortButton()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).end();

	if(iter == iter_end)
	{
		m_tInfo.bRenderCheck = false;
		return;
	}
	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == true)
		{
			if(m_tInfo.bPortButtonChange == false)
			{
				if(iIndex == 0 || iIndex == 4 )
				{
					m_tInfo.bRenderCheck = true;
					m_tInfo.m_eControlDrawType = CDT_PORT;
				}
				if(CObj::m_eAgeType == AT_FEUDAL)
				{
					if(iIndex == 1 || iIndex == 3 || iIndex == 14)
					{
						m_tInfo.bRenderCheck = true;
						m_tInfo.m_eControlDrawType = CDT_PORT;
					}
				}

				if(CObj::m_eAgeType == AT_IMPERIAL || CObj::m_eAgeType == AT_CASTLE)
				{
					if(iIndex == 1 || iIndex == 3 || iIndex == 14 )
					{
						m_tInfo.bRenderCheck = true;
						m_tInfo.m_eControlDrawType = CDT_PORT;
					}
				}
			}
			else if(m_tInfo.bPortButtonChange == true)
			{
				if(CObj::m_eAgeType == AT_FEUDAL)
				{
					if(iIndex == 0 || iIndex == 1 || iIndex == 4 || iIndex == 14)
					{
						m_tInfo.bRenderCheck = true;
						m_tInfo.m_eControlDrawType = CDT_PORT;
					}
				}

				if(CObj::m_eAgeType == AT_IMPERIAL || CObj::m_eAgeType == AT_CASTLE)
				{
					if(iIndex == 0 || iIndex == 1 || iIndex == 2 || iIndex == 4 || iIndex == 14)
					{
						m_tInfo.bRenderCheck = true;
						m_tInfo.m_eControlDrawType = CDT_PORT;
					}
				}
			}
		}
	}
}


void CClickFrame::SetMineButton()
{

}

void CClickFrame::SetBarracksButton()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).end();

	if(iter == iter_end)
	{
		m_tInfo.bRenderCheck = false;
		return;
	}
	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_BARRACK && (*iter)->GetInfo()->bSelection == true)
		{
			if(iIndex == 0 || iIndex == 4 )
			{
				m_tInfo.bRenderCheck = true;
				m_tInfo.m_eControlDrawType = CDT_BARRACKS;
			}
		}
	}
}
void CClickFrame::SetMillButton()
{

}

void CClickFrame::TownRender()
{
	float fX = 0;
	float fY = 0;

	switch(iIndex)
	{
	case 0:
		if(pUnitIcon[10] == NULL)
			return;

		fX = pUnitIcon[10]->ImgInfo.Width / 2.f;
		fY = pUnitIcon[10]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitIcon[10]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case 4:
		if(pUnitControlIcon[32] == NULL)
			return;

		fX = pUnitControlIcon[32]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[32]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[32]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case 14:
		if(pUnitControlIcon[36] == NULL)
			return;

		fX = pUnitControlIcon[36]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[36]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[36]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case 10:
		int iViewNum = 0;
		if(CObj::m_eAgeType == AT_DARK)
			iViewNum = 29;
		if(CObj::m_eAgeType == AT_FEUDAL)
			iViewNum = 30;
		if(CObj::m_eAgeType == AT_IMPERIAL)
			iViewNum = 31;
		if(CObj::m_eAgeType == AT_CASTLE)
			return;
			
		if(pUpgradeIcon[iViewNum] == NULL)
			return;

		fX = pUpgradeIcon[iViewNum]->ImgInfo.Width / 2.f;
		fY = pUpgradeIcon[iViewNum]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUpgradeIcon[iViewNum]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
}

void CClickFrame::PortRender()
{

	if(m_tInfo.bPortButtonChange == false)
	{

		float fX = 0;
		float fY = 0;

		switch(iIndex)
		{
		case 0:
			if(pUnitIcon[32] == NULL)
				return;

			fX = pUnitIcon[32]->ImgInfo.Width / 2.f;
			fY = pUnitIcon[32]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitIcon[32]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 1:
			if(pUnitIcon[33] == NULL)
				return;

			fX = pUnitIcon[33]->ImgInfo.Width / 2.f;
			fY = pUnitIcon[33]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitIcon[33]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 3:
			if(pUnitIcon[35] == NULL)
				return;

			fX = pUnitIcon[35]->ImgInfo.Width / 2.f;
			fY = pUnitIcon[35]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitIcon[35]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;

		case 8:
			if(pUpgradeIcon[8] == NULL)
				return;

			fX = pUpgradeIcon[8]->ImgInfo.Width / 2.f;
			fY = pUpgradeIcon[8]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUpgradeIcon[8]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 14:
			if(pUnitControlIcon[25] == NULL)
				return;

			fX = pUnitControlIcon[25]->ImgInfo.Width / 2.f;
			fY = pUnitControlIcon[25]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[25]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 4:
			if(pUnitControlIcon[32] == NULL)
				return;

			fX = pUnitControlIcon[32]->ImgInfo.Width / 2.f;
			fY = pUnitControlIcon[32]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[32]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		}
	}

	else if(m_tInfo.bPortButtonChange == true)
	{
		float fX = 0;
		float fY = 0;

		switch(iIndex)
		{
		case 0:
			if(pUnitIcon[39] == NULL)
				return;

			fX = pUnitIcon[39]->ImgInfo.Width / 2.f;
			fY = pUnitIcon[39]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitIcon[39]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 1:
			if(pUnitIcon[37] == NULL)
				return;

			fX = pUnitIcon[37]->ImgInfo.Width / 2.f;
			fY = pUnitIcon[37]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitIcon[37]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 2:
			if(pUnitIcon[40] == NULL)
				return;

			fX = pUnitIcon[40]->ImgInfo.Width / 2.f;
			fY = pUnitIcon[40]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitIcon[40]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		
		case 14:
			if(pUnitControlIcon[25] == NULL)
				return;

			fX = pUnitControlIcon[25]->ImgInfo.Width / 2.f;
			fY = pUnitControlIcon[25]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[25]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case 4:
			if(pUnitControlIcon[32] == NULL)
				return;

			fX = pUnitControlIcon[32]->ImgInfo.Width / 2.f;
			fY = pUnitControlIcon[32]->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[32]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		}

	}
}

void CClickFrame::WoodRender()
{

}

void CClickFrame::MineRender()
{

}

void CClickFrame::BarracksRender()
{
	float fX = 0;
	float fY = 0;

	switch(iIndex)
	{
	case 0:
		if(pUnitIcon[2] == NULL)
			return;

		fX = pUnitIcon[2]->ImgInfo.Width / 2.f;
		fY = pUnitIcon[2]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitIcon[2]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case 4:
		if(pUnitControlIcon[32] == NULL)
			return;

		fX = pUnitControlIcon[32]->ImgInfo.Width / 2.f;
		fY = pUnitControlIcon[32]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pUnitControlIcon[32]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
}

void CClickFrame::MillRender()
{

}

void CClickFrame::Port2Render()
{

}












#include "StdAfx.h"
#include "LoadingBar.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "LoadingBar.h"
#include "Villager.h"
#include "FishShip.h"
#include "TransShip.h"
#include "GallyShip.h"
#include "TImeMgr.h"
#include "DestroyShip.h"
#include "FireShip.h"
#include "CannonShip.h"
#include "Soldier.h"
#include "SoundMgr.h"

CLoadingBar::CLoadingBar(void)
{
}

CLoadingBar::~CLoadingBar(void)
{
}

HRESULT CLoadingBar::Initialize( void )
{
	for(int i = 0; i < 99; ++i)
		pTexture[i] = CTextureMgr::GetInstance()->GetTexture(L"Gauge", L"Gauge", i);

	m_TexSlideX = 40;

	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_VILLAGER)
	{
		pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 10);
		if(CObj::m_iMakeVillager > 4)
			m_TexSlideX -= 10;
	}
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_FISHSHIP)
	{
		pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 32);
		if(CObj::m_iMakeFishShip > 4)
			m_TexSlideX -= 10;
	}
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_TRANSSHIP)
	{
		pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 33);
		if(CObj::m_iMakeTransShip > 4)
			m_TexSlideX -= 10;
	}
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_GALLYSHIP)
	{
		pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 36);
		if(CObj::m_iMakeGalleyShip > 4)
			m_TexSlideX -= 10;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_DESTROYSHIP)
	{
		pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 39);
		if(CObj::m_iMakeDestroyShip > 4)
			m_TexSlideX -= 10;
	}
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_FIRESHIP)
	{
		pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 37);
		if(CObj::m_iMakeFireShip > 4)
			m_TexSlideX -= 10;
	}
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_STONESHIP)
	{
		pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 40);
		if(CObj::m_iMakeCannonShip > 4)
			m_TexSlideX -= 10;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////// Áö»ó ///////////////////////////////////////////
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_SOLDIER)
	{
		pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UnitIcon", L"UnitIcon", 12);
		if(CObj::m_iMakeSoldier > 4)
			m_TexSlideX -= 10;
	}
	if(m_tInfo.m_eGaugeType == GAUGE_UPGRADE_AGE)
	{
		if(CObj::m_eAgeType == AT_DARK)
		{
			pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UpgradeIcon", L"UpgradeIcon", 29);
		}
		if(CObj::m_eAgeType == AT_FEUDAL)
		{
			pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UpgradeIcon", L"UpgradeIcon", 30);
		}
		if(CObj::m_eAgeType == AT_IMPERIAL)
		{
			pMakeTex = CTextureMgr::GetInstance()->GetTexture(L"UpgradeIcon", L"UpgradeIcon", 31);
		}
	}
	
	m_tFrame = FRAME(0.f, 50.f, 98.f, 0.f);

	return S_OK;
}	

int CLoadingBar::Update( void )
{

	m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
	if(m_tFrame.fFrame > m_tFrame.fMax)
	{
		switch(m_tInfo.m_eGaugeType)
		{
		case GAUGE_MAKE_VILLAGER:
			MakeVillager();
			--CObj::m_iMakeVillager;
			if(CObj::m_iMakeVillager > 0 )
			{
				CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_VILLAGER));
			}
			break;

		case GAUGE_MAKE_FISHSHIP:
			MakeFishShip();
			--CObj::m_iMakeFishShip;
			if(CObj::m_iMakeFishShip > 0 )
			{
				CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_FISHSHIP));
			}
			break;
		case GAUGE_MAKE_TRANSSHIP:
			MakeTransShip();
			--CObj::m_iMakeTransShip;
			if(CObj::m_iMakeTransShip > 0 )
			{
				CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_TRANSSHIP));
			}
			break;
		case GAUGE_MAKE_GALLYSHIP:
			MakeGalleyShip();
			--CObj::m_iMakeGalleyShip;
			if(CObj::m_iMakeGalleyShip > 0 )
			{
				CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_GALLYSHIP));
			}
			break;
		case GAUGE_MAKE_DESTROYSHIP:
			MakeDestroyShip();
			--CObj::m_iMakeDestroyShip;
			if(CObj::m_iMakeDestroyShip > 0 )
			{
				CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_DESTROYSHIP));
			}
			break;
		case GAUGE_MAKE_FIRESHIP:
			MakeFireShip();
			--CObj::m_iMakeFireShip;
			if(CObj::m_iMakeFireShip > 0 )
			{
				CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_FIRESHIP));
			}
			break;
		case GAUGE_MAKE_STONESHIP:
			MakeCannonShip();
			--CObj::m_iMakeCannonShip;
			if(CObj::m_iMakeCannonShip > 0 )
			{
				CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_STONESHIP));
			}
			break;
		case GAUGE_MAKE_SOLDIER:
			MakeSoldier();
			--CObj::m_iMakeSoldier;
			if(CObj::m_iMakeSoldier > 0 )
			{
				CObjMgr::GetInstance()->AddObject(L"Gauge", SORT_LOADING, CFactory<CLoadingBar>::CreateObject(D3DXVECTOR3(400.f, 530.f, 0), GAUGE_MAKE_SOLDIER));
			}
			break;
		case GAUGE_UPGRADE_AGE:
			if(CObj::m_eAgeType == AT_DARK)
				CObj::m_eAgeType = AT_FEUDAL;
			else if(CObj::m_eAgeType == AT_FEUDAL)
				CObj::m_eAgeType = AT_IMPERIAL;
			else if(CObj::m_eAgeType == AT_IMPERIAL)
				CObj::m_eAgeType = AT_CASTLE;

			CSoundMgr::GetInstance()->AgeUpgrade(L"AgeUpgrade.wav");

			break;
		}
		
		m_tInfo.bAlive = false;
	}



	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_VILLAGER)
		VillagerRenderCheck();
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_FISHSHIP)
		FishShipRenderCheck();
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_TRANSSHIP)
		TransShipRenderCheck();
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_GALLYSHIP)
		GalleyShipRenderCheck();
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_DESTROYSHIP)
		DestroyShipRenderCheck();
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_FIRESHIP)
		FireShipRenderCheck();
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_STONESHIP)
		CannonShipRenderCheck();
	if(m_tInfo.m_eGaugeType == GAUGE_MAKE_SOLDIER)
		SoldierRenderCheck();

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	return 0;

}

void CLoadingBar::Render( void )
{
	switch(m_tInfo.m_eGaugeType)
	{
	case GAUGE_MAKE_VILLAGER:
		VillagerRender();
		break;
	case GAUGE_MAKE_FISHSHIP:
		FishShipRender();
		break;
	case GAUGE_MAKE_TRANSSHIP:
		TransShipRender();
		break;
	case GAUGE_MAKE_GALLYSHIP:
		GalleyShipRender();
		break;
	case GAUGE_MAKE_DESTROYSHIP:
		DestroyShipRender();
		break;
	case GAUGE_MAKE_FIRESHIP:
		FireShipRender();
		break;
	case GAUGE_MAKE_STONESHIP:
		CannonShipRender();
		break;
	case GAUGE_MAKE_SOLDIER:
		SoldierRender();
		break;
	case GAUGE_UPGRADE_AGE:
		NormalRender();
		break;
	}
}

void CLoadingBar::Release( void )
{

}
void CLoadingBar::NormalRender()
{

	if(m_tInfo.m_eGaugeType == GAUGE_UPGRADE_AGE && CObj::m_eAgeType == AT_CASTLE )
		return;
	if(pTexture[int(m_tFrame.fFrame)] == NULL)
		return;

	float fX = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
	float fY = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(pTexture[int(m_tFrame.fFrame)]->pTexture, 
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, 300.f, 530.f, 0.f);

	if(pMakeTex == NULL)
		return;

	fX = pMakeTex->ImgInfo.Width / 2.f;
	fY = pMakeTex->ImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

	CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

}
void CLoadingBar::MakeVillager()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_TOWN && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CSoundMgr::GetInstance()->CreateGroundUnit(L"VillagerCreate.wav");
			CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CVillager>::CreateObject((*iter)->GetInfo()->vMakePos, (*iter)->GetInfo()->vWayPos, UT_VILLAGER, PT_PLAYER, 0));
			break;
		}
	}
}

void CLoadingBar::MakeFishShip()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CSoundMgr::GetInstance()->CreateGroundUnit(L"CreateShip.wav");
			CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CFishShip>::CreateObject((*iter)->GetInfo()->vMakePos, (*iter)->GetInfo()->vWayPos, UT_FISHER, PT_PLAYER, 0));
			break;
		}
	}
}

void CLoadingBar::MakeTransShip()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CSoundMgr::GetInstance()->CreateGroundUnit(L"CreateShip.wav");
			CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CTransShip>::CreateObject((*iter)->GetInfo()->vMakePos, (*iter)->GetInfo()->vWayPos, UT_TRANSSHIP, PT_PLAYER, 0));
			break;
		}
	}
}

void CLoadingBar::MakeGalleyShip()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CSoundMgr::GetInstance()->CreateGroundUnit(L"CreateShip.wav");
			CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CGallyShip>::CreateObject((*iter)->GetInfo()->vMakePos, (*iter)->GetInfo()->vWayPos, UT_GALLYSHIP, PT_PLAYER, 0));
			break;
		}
	}
}

void CLoadingBar::MakeDestroyShip()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CSoundMgr::GetInstance()->CreateGroundUnit(L"CreateShip.wav");
			CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CDestroyShip>::CreateObject((*iter)->GetInfo()->vMakePos, (*iter)->GetInfo()->vWayPos, UT_DESTROYSHIP, PT_PLAYER, 0));
			break;
		}
	}
}

void CLoadingBar::MakeSoldier()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_BARRACK && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject((*iter)->GetInfo()->vMakePos, (*iter)->GetInfo()->vWayPos, UT_SOLDIER, PT_PLAYER, 0));
			break;
		}
	}
}


void CLoadingBar::MakeFireShip()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CSoundMgr::GetInstance()->CreateGroundUnit(L"CreateShip.wav");
			CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CFireShip>::CreateObject((*iter)->GetInfo()->vMakePos, (*iter)->GetInfo()->vWayPos, UT_FIRESHIP, PT_PLAYER, 0));
			break;
		}
	}
}

void CLoadingBar::MakeCannonShip()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CSoundMgr::GetInstance()->CreateGroundUnit(L"CreateShip.wav");
			CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CCannonShip>::CreateObject((*iter)->GetInfo()->vMakePos, (*iter)->GetInfo()->vWayPos, UT_GALLYSHIP, PT_PLAYER, 0));
			break;
		}
	}
}
void CLoadingBar::VillagerRenderCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetInfo()->m_eBuildType == BT_TOWN && (*iter)->GetInfo()->bSelection == true)
		{
			CObj::m_bVillagerGaugeRender = true;
			return;
		}
		else if( (*iter)->GetInfo()->m_eBuildType == BT_TOWN && (*iter)->GetInfo()->bSelection == false)
		{
			CObj::m_bVillagerGaugeRender = false;
			return;
		}
	}
}	

void CLoadingBar::FishShipRenderCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == true && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bFishShipGaugeRender = true;
			return;
		}
		else if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == false && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bFishShipGaugeRender = false;
			return;
		}
	}
}
void CLoadingBar::TransShipRenderCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == true && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bTransShipGaugeRender = true;
			return;
		}
		else if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == false && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bTransShipGaugeRender = false;
			return;
		}
	}
}

void CLoadingBar::GalleyShipRenderCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == true && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bGalleyShipGaugeRender = true;
			return;
		}
		else if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == false && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bGalleyShipGaugeRender = false;
			return;
		}
	}
}

void CLoadingBar::DestroyShipRenderCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == true && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bDestroyShipGaugeRender = true;
			return;
		}
		else if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == false && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bDestroyShipGaugeRender = false;
			return;
		}
	}
}

void CLoadingBar::FireShipRenderCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == true && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bFireShipGaugeRender = true;
			return;
		}
		else if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == false && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bFireShipGaugeRender = false;
			return;
		}
	}
}

void CLoadingBar::CannonShipRenderCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == true && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bCannonShipGaugeRender = true;
			return;
		}
		else if( (*iter)->GetInfo()->m_eBuildType == BT_PORT && (*iter)->GetInfo()->bSelection == false && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bCannonShipGaugeRender = false;
			return;
		}
	}
}

void CLoadingBar::SoldierRenderCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	for(iter; iter != iter_end; ++iter)
	{
		if( (*iter)->GetInfo()->m_eBuildType == BT_BARRACK && (*iter)->GetInfo()->bSelection == true && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bSoldierGaugeRender = true;
			return;
		}
		else if( (*iter)->GetInfo()->m_eBuildType == BT_BARRACK && (*iter)->GetInfo()->bSelection == false && (*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
		{
			CObj::m_bSoldierGaugeRender = false;
			return;
		}
	}
}
void CLoadingBar::VillagerRender()
{
	if(CObj::m_bVillagerGaugeRender)
	{
		if(pTexture[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));


		if(CObj::m_iMakeVillager >= 1)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 530.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeVillager >= 2)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeVillager >= 3)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeVillager >= 4)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 2, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeVillager >= 5)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 3, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeVillager >= 6)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 4, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeVillager >= 7)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 5, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeVillager >= 8)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 6, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CLoadingBar::FishShipRender()
{
	if(CObj::m_bFishShipGaugeRender)
	{
		if(pTexture[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));


		if(CObj::m_iMakeFishShip >= 1)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 530.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFishShip >= 2)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFishShip >= 3)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFishShip >= 4)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 2, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFishShip >= 5)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 3, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFishShip >= 6)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 4, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFishShip >= 7)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 5, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFishShip >= 8)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 6, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CLoadingBar::TransShipRender()
{
	if(CObj::m_bTransShipGaugeRender)
	{
		if(pTexture[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));


		if(CObj::m_iMakeTransShip >= 1)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 530.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeTransShip >= 2)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeTransShip >= 3)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeTransShip >= 4)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 2, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeTransShip >= 5)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 3, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeTransShip >= 6)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 4, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeTransShip >= 7)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 5, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeTransShip >= 8)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 6, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CLoadingBar::GalleyShipRender()
{
	if(CObj::m_bGalleyShipGaugeRender)
	{
		if(pTexture[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));


		if(CObj::m_iMakeGalleyShip >= 1)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 530.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeGalleyShip >= 2)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeGalleyShip >= 3)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeGalleyShip >= 4)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 2, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeGalleyShip >= 5)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 3, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeGalleyShip >= 6)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 4, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeGalleyShip >= 7)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 5, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeGalleyShip >= 8)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 6, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CLoadingBar::DestroyShipRender()
{
	if(CObj::m_iMakeDestroyShip)
	{
		if(pTexture[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));


		if(CObj::m_iMakeDestroyShip >= 1)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 530.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeDestroyShip >= 2)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeDestroyShip >= 3)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeDestroyShip >= 4)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 2, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeDestroyShip >= 5)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 3, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeDestroyShip >= 6)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 4, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeDestroyShip >= 7)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 5, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeDestroyShip >= 8)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 6, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CLoadingBar::FireShipRender()
{
	if(CObj::m_iMakeFireShip)
	{
		if(pTexture[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));


		if(CObj::m_iMakeFireShip >= 1)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 530.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFireShip >= 2)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFireShip >= 3)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFireShip >= 4)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 2, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFireShip >= 5)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 3, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFireShip >= 6)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 4, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFireShip >= 7)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 5, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeFireShip >= 8)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 6, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CLoadingBar::CannonShipRender()
{
	if(CObj::m_iMakeCannonShip)
	{
		if(pTexture[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));


		if(CObj::m_iMakeCannonShip >= 1)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 530.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeCannonShip >= 2)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeCannonShip >= 3)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeCannonShip >= 4)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 2, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeCannonShip >= 5)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 3, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeCannonShip >= 6)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 4, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeCannonShip >= 7)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 5, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeCannonShip >= 8)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 6, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CLoadingBar::SoldierRender()
{
	if(CObj::m_iMakeSoldier)
	{
		if(pTexture[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = pTexture[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));


		if(CObj::m_iMakeSoldier >= 1)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 530.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeSoldier >= 2)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeSoldier >= 3)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeSoldier >= 4)
		{

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 2, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeSoldier >= 5)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 3, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeSoldier >= 6)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 4, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeSoldier >= 7)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 5, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if(CObj::m_iMakeSoldier >= 8)
		{
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 300.f + m_TexSlideX * 6, 570.f, 0.f);

			if(pMakeTex == NULL)
				return;

			fX = pMakeTex->ImgInfo.Width / 2.f;
			fY = pMakeTex->ImgInfo.Height / 2.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pMakeTex->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

}








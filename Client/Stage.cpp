#include "StdAfx.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "StageBack.h"
#include "MyResource.h"
#include "TIleMgr.h"
#include "MainUI.h"
#include "Town.h"
#include "Villager.h"
#include "CollisionMgr.h"
#include "ButtonMgr.h"
#include "ClickFrame.h"
#include "Mouse.h"
#include "MouseMgr.h"
#include "BuildMgr.h"
#include "MiniMap.h"
#include "Port.h"
#include "Soldier.h"
#include "Formation.h"
#include "SoundMgr.h"
CStage::CStage(void)
{
}

CStage::~CStage(void)
{
	Release();
}

HRESULT CStage::Initialize( void )
{
	(*CBuildMgr::GetInstance()->GetPortBuildCheck()) = false;

	CSoundMgr::GetInstance()->PlayBGMSound(L"Stage2.mp3");
	CObjMgr::GetInstance()->AddObject(L"StageBack", SORT_FIRST, CFactory<CStageBack>::CreateObject());
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[0]->vPos, RT_TREE, 2));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[1]->vPos, RT_TREE, 3));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2]->vPos, RT_TREE, 4));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[3]->vPos, RT_TREE, 5));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[4]->vPos, RT_TREE, 7));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[50]->vPos, RT_TREE, 3));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[51]->vPos, RT_TREE, 4));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[100]->vPos, RT_TREE, 5));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[150]->vPos, RT_TREE, 7));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[200]->vPos, RT_TREE, 8));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2495]->vPos, RT_TREE, 4, 2495));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2496]->vPos, RT_TREE, 5, 2496));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2497]->vPos, RT_TREE, 7, 2497));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2498]->vPos, RT_TREE, 8, 2498));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2499]->vPos, RT_TREE, 3, 2499));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2448]->vPos, RT_TREE, 4, 2448));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2449]->vPos, RT_TREE, 5, 2449));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2399]->vPos, RT_TREE, 7, 2399));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2349]->vPos, RT_TREE, 8, 2349));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2299]->vPos, RT_TREE, 2, 2299));
	/// 돌 ///
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[1998]->vPos, RT_STONE, 1, 1998));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[1999]->vPos, RT_STONE, 3, 1999));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[1948]->vPos, RT_STONE, 4, 1948));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[1949]->vPos, RT_STONE, 5, 1949));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[550]->vPos, RT_STONE, 2, 550));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[551]->vPos, RT_STONE, 1, 551));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[600]->vPos, RT_STONE, 4, 600));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[601]->vPos, RT_STONE, 5, 601));
	/// 금 ///
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[400]->vPos, RT_GOLD, 1));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[401]->vPos, RT_GOLD, 3));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[450]->vPos, RT_GOLD, 4, 450));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[451]->vPos, RT_GOLD, 5));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2148]->vPos, RT_GOLD, 2, 2148));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2149]->vPos, RT_GOLD, 1, 2149));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2099]->vPos, RT_GOLD, 4, 2099));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2098]->vPos, RT_GOLD, 5, 2098));
	/// 체리 ///
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2441]->vPos, RT_CHERRY, 2, 2441));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2442]->vPos, RT_CHERRY, 1, 2442));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2491]->vPos, RT_CHERRY, 0, 2491));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[2492]->vPos, RT_CHERRY, 3, 2492));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[9]->vPos, RT_CHERRY, 2));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[10]->vPos, RT_CHERRY, 3));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[59]->vPos, RT_CHERRY, 0));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[60]->vPos, RT_CHERRY, 1));
	/// 고기 ///
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[969]->vPos, RT_FISH, 0, 969));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[1268]->vPos, RT_FISH, 0, 1268));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[1112]->vPos, RT_FISH, 0, 1112));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[1410]->vPos, RT_FISH, 0, 1410));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[927]->vPos, RT_FISH, 0, 927));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[1179]->vPos, RT_FISH, 0, 1179));
	CObjMgr::GetInstance()->AddObject(L"Resource", SORT_OBJECT, CFactory<CMyResource>::CreateObject(CTileMgr::GetInstance()->GetTile()[1374]->vPos, RT_FISH, 0, 1374));

	/// 플레이어 건물 ///
	CObjMgr::GetInstance()->AddObject(L"Build", SORT_OBJECT, CFactory<CTown>::CreateObject(CTileMgr::GetInstance()->GetTile()[205]->vPos, BT_TOWN, PT_PLAYER, 0));
	/// 적 건물 ///
	CObjMgr::GetInstance()->AddObject(L"Build", SORT_OBJECT, CFactory<CTown>::CreateObject(CTileMgr::GetInstance()->GetTile()[2091]->vPos, BT_TOWN, PT_ENEMY, 0));
	//CObjMgr::GetInstance()->AddObject(L"Build", SORT_OBJECT, CFactory<CPort>::CreateObject(CTileMgr::GetInstance()->GetTile()[1730]->vPos, BT_PORT, PT_ENEMY, 0));

	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CVillager>::CreateObject(CTileMgr::GetInstance()->GetTile()[404]->vPos, UT_VILLAGER, PT_PLAYER, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CVillager>::CreateObject(CTileMgr::GetInstance()->GetTile()[406]->vPos, UT_VILLAGER, PT_PLAYER, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CVillager>::CreateObject(CTileMgr::GetInstance()->GetTile()[358]->vPos, UT_VILLAGER, PT_PLAYER, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CVillager>::CreateObject(CTileMgr::GetInstance()->GetTile()[259]->vPos, UT_VILLAGER, PT_PLAYER, 0));

	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CVillager>::CreateObject(CTileMgr::GetInstance()->GetTile()[2239]->vPos, CTileMgr::GetInstance()->GetTile()[2441]->vPos, UT_VILLAGER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CVillager>::CreateObject(CTileMgr::GetInstance()->GetTile()[2241]->vPos, CTileMgr::GetInstance()->GetTile()[2495]->vPos, UT_VILLAGER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CVillager>::CreateObject(CTileMgr::GetInstance()->GetTile()[2193]->vPos, CTileMgr::GetInstance()->GetTile()[2148]->vPos, UT_VILLAGER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CVillager>::CreateObject(CTileMgr::GetInstance()->GetTile()[2094]->vPos, CTileMgr::GetInstance()->GetTile()[1998]->vPos, UT_VILLAGER, PT_ENEMY, 0));
	
	CTileMgr::GetInstance()->GetTile()[364]->m_GroundType = GT_GROUND;
	CTileMgr::GetInstance()->GetTile()[366]->m_GroundType = GT_GROUND;
	CTileMgr::GetInstance()->GetTile()[328]->m_GroundType = GT_GROUND;
	CTileMgr::GetInstance()->GetTile()[249]->m_GroundType = GT_GROUND;

	CObjMgr::GetInstance()->AddObject(L"MainUI", SORT_UI, CFactory<CMainUI>::CreateObject());

	// 적 보병

	/*CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2228]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2229]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2230]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2231]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2278]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2279]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2280]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2281]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2328]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2329]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2330]->vPos, UT_SOLDIER, PT_ENEMY, 0));
	CObjMgr::GetInstance()->AddObject(L"Unit", SORT_OBJECT, CFactory<CSoldier>::CreateObject(CTileMgr::GetInstance()->GetTile()[2331]->vPos, UT_SOLDIER, PT_ENEMY, 0));
*/
	for(int i = 0, k = 0, j = 0; i < 15; ++i, k += 40)
	{
		if(i % 5 == 0 && i != 0)
		{
			k = 0;
			j += 40;
		}
		CButtonMgr::GetInstance()->AddButton(CFactory<CClickFrame>::CreateObject(D3DXVECTOR3(30.f + (float)k, 490.f + (float)j, 0.f), i), i);
	}
	CObjMgr::GetInstance()->AddObject(L"Mouse", SORT_MOUSE, CFactory<CMouse>::CreateObject());


	CButtonMgr::GetInstance()->ClearButton();
	CObjMgr::GetInstance()->SetSelectionFalse();

	list<CObj*>::iterator Obj_iter = CObjMgr::GetInstance()->GetObjList(L"Resource",SORT_OBJECT).begin();
	list<CObj*>::iterator Obj_iter_end = CObjMgr::GetInstance()->GetObjList(L"Resource",SORT_OBJECT).end();

	int iIndex = 0;
	for(; Obj_iter != Obj_iter_end; ++Obj_iter)
	{
		
		if((*Obj_iter)->GetInfo()->m_eResourceType == RT_TREE)
		{
			D3DXVECTOR3 vTemp = D3DXVECTOR3(0.f, 0.f, 0.f);
			vTemp.x = (*Obj_iter)->GetInfo()->vPos.x;
			vTemp.y = (*Obj_iter)->GetInfo()->vPos.y + 70.f;
			vTemp.z = 0.f;
			iIndex = CTileMgr::GetInstance()->GetTileIndex(vTemp);
		}
		else
			iIndex = CTileMgr::GetInstance()->GetTileIndex((*Obj_iter)->GetInfo()->vPos);
		CTileMgr::GetInstance()->GetTile()[iIndex]->m_eType = (*Obj_iter)->GetInfo()->m_eResourceType;
	}

	list<CObj*>::iterator Unit_iter = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).begin();
	list<CObj*>::iterator Unit_iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit",SORT_OBJECT).end();

	for(;Unit_iter != Unit_iter_end; ++Unit_iter )
	{		
		if((*Unit_iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
			CCollisionMgr::GetInstance()->InitTileSightCollision((*Unit_iter));
	}	

	list<CObj*>::iterator Build_iter = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).begin();
	list<CObj*>::iterator Build_iter_end = CObjMgr::GetInstance()->GetObjList(L"Build",SORT_OBJECT).end();

	for(;Build_iter != Build_iter_end; ++Build_iter )
	{
		if((*Build_iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
			CCollisionMgr::GetInstance()->InitTileSightCollision((*Build_iter));
	}
	CObjMgr::GetInstance()->AddObject(L"MiniMap", SORT_MINIMAP, CFactory<CMiniMap>::CreateObject());
	// 1730 적항구


	return S_OK;
}

int CStage::Update( void )
{
	CMouseMgr::UnitSelectionFunc();
	CMouseMgr::UnitMoveFunc();
	CObjMgr::GetInstance()->Update();
	CButtonMgr::GetInstance()->Update();
	CFormation::GetInstance()->SetFormationWidth();

	return 0;
}

void CStage::Render( void )
{
	CObjMgr::GetInstance()->Render();
}

void CStage::Release( void )
{
	CObjMgr::GetInstance()->DestroyInstance();
}



#include "StdAfx.h"
#include "Logo.h"
#include "ObjMgr.h"
#include "TextureMgr.h"
#include "Factory.h"
#include "LogoBack.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CLogo::CLogo(void)
{
}

CLogo::~CLogo(void)
{
	Release();
}

HRESULT CLogo::Initialize( void )
{
	InitializeCriticalSection(&m_Crt);
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ImgLoadThreadFunc, this, 0, NULL);

	CObjMgr::GetInstance()->AddObject(L"LogoBack", SORT_FIRST, CFactory<CLogoBack>::CreateObject());
	CSoundMgr::GetInstance()->PlayBGMSound(L"Logo.mp3");
	return S_OK;
}

int CLogo::Update( void )
{
	if(GetAsyncKeyState(VK_RETURN))
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		DeleteCriticalSection(&m_Crt);

		CSceneMgr::GetInstance()->SetScene(ST_STAGE);
	}

	CObjMgr::GetInstance()->Update();

	return 0;
}

void CLogo::Render( void )
{
	CObjMgr::GetInstance()->Render();

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, 50.f, 570.f, 0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), CTextureMgr::GetInstance()->GetCurrentPath().c_str(), CTextureMgr::GetInstance()->GetCurrentPath().length(), NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLogo::Release( void )
{
	CObjMgr::GetInstance()->DestroyInstance();
}

unsigned int __stdcall CLogo::ImgLoadThreadFunc( void* pArg )
{
	CLogo*	pLogo = (CLogo*)pArg;

	EnterCriticalSection(&pLogo->GetCrt());

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Loading/Loading%d%d.png", L"LogoBack", TEX_MULTI, L"Loading", 12);
	// 타일 //
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Tile%d%d.png", L"Tile", TEX_MULTI, L"Tile", 80);

	// 플레이어 유닛 //

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Walk/Villager_Walk_0%d%d.png", L"Villager", TEX_MULTI, L"Walk", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/STD/Villager_STD_0%d%d.png", L"Villager", TEX_MULTI, L"STD", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/ATT/Male Villager1473_%d%d.png", L"Villager", TEX_MULTI, L"ATT", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Berry_Gatherer_Kneeling/Male Villager1512_%d%d.png", L"Villager", TEX_MULTI, L"Berry_Gatherer_Kneeling", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Berry_Gatherer_Walk/Male Villager1515_%d%d.png", L"Villager", TEX_MULTI, L"Berry_Gatherer_Walk", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Building/Male Villager1496_%d%d.png", L"Villager", TEX_MULTI, L"Building", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Death/Male Villager1481_%d%d.png", L"Villager", TEX_MULTI, L"Death", 25);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Dying/Male Villager1476_%d%d.png", L"Villager", TEX_MULTI, L"Dying", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Miner_Carrying_Gold/Male Villager2117_%d%d.png", L"Villager", TEX_MULTI, L"Miner_Carrying_Gold", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Miner_Carrying_Stone/Male Villager1552_%d%d.png", L"Villager", TEX_MULTI, L"Miner_Carrying_Stone", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Miner_Mining/Male Villager1560_%d%d.png", L"Villager", TEX_MULTI, L"Miner_Mining", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Woodcutter_Carrying_Wood/Male Villager1536_%d%d.png", L"Villager", TEX_MULTI, L"Carrying_Wood", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/Woodcutter_Chopping/Male Villager1545_%d%d.png", L"Villager", TEX_MULTI, L"Chopping", 75);

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Fishing_Boat/STD/Player_Fishing_Boat_STD_00%d.png", L"FishShip", TEX_MULTI, L"STD", 5);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Fishing_Boat/Fishing/Player_Fishing_Boat_Fishing_00%d.png", L"FishShip", TEX_MULTI, L"Fishing", 5);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Fishing_Boat/Death/Player_Fishing_Boat_Death_00%d.png", L"FishShip", TEX_MULTI, L"Death", 5);

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Ship/Transport/Ship_Transport_00%d.png", L"TransShip", TEX_MULTI, L"STD", 9);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Ship/Galley/3/Ship_Galley3_00%d.png", L"GalleyShip", TEX_MULTI, L"STD", 9);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Ship/Fire/Ship_Fire_00%d.png", L"FireShip", TEX_MULTI, L"STD", 9);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Ship/Cannon/Ship_Cannon_00%d.png", L"CannonShip", TEX_MULTI, L"STD", 9);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Ship/Demolition/2/Ship_Demolition2_00%d.png", L"DestroyShip", TEX_MULTI, L"STD", 9);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Ship/Demolition/ATT/2/Ship_Demolition2_ATT_0%d%d.png", L"DestroyShip", TEX_MULTI, L"ATT", 63);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Ship/Death/Player_Ship_Death_00%d.png", L"Ship", TEX_MULTI, L"Death", 6);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Ship/Flag/5/Player_Ship_Flag_%d%d%d.png", L"Ship", TEX_MULTI, L"MoveVibe1", 100);

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Soldier/1/ATT/Img/Player_Soldier1_ATT_Img_0%d%d.png", L"Soldier", TEX_MULTI, L"ATT", 50);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Soldier/1/STD/Img/Player_Soldier1_STD_Img_0%d%d.png", L"Soldier", TEX_MULTI, L"STD", 30);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Soldier/1/Walk/Img/Player_Soldier1_Walk_Img_0%d%d.png", L"Soldier", TEX_MULTI, L"Walk", 60);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Soldier/1/Dying/Img/Player_Soldier1_Dying_Img_0%d%d.png", L"Soldier", TEX_MULTI, L"Dying", 50);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Soldier/1/Death/Player_Soldier1_Death_0%d%d.png", L"Soldier", TEX_MULTI, L"Death", 25);

	// 적 유닛

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Soldier/1/ATT/Img/Enemy_Soldier1_ATT_Img_0%d%d.png", L"Enemy_Soldier", TEX_MULTI, L"ATT", 50);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Soldier/1/STD/Img/Enemy_Soldier1_STD_Img_0%d%d.png", L"Enemy_Soldier", TEX_MULTI, L"STD", 30);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Soldier/1/Walk/Img/Enemy_Soldier1_Walk_Img_0%d%d.png", L"Enemy_Soldier", TEX_MULTI, L"Walk", 60);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Soldier/1/Dying/Img/Enemy_Soldier1_Dying_Img_0%d%d.png", L"Enemy_Soldier", TEX_MULTI, L"Dying", 50);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Soldier/1/Death/Enemy_Soldier1_Death_0%d%d.png", L"Enemy_Soldier", TEX_MULTI, L"Death", 25);

	//
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/Walk/Enemy_Male_Walk_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"Walk", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/STD/Enemy_Male_STD_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"STD", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/ATT/Enemy_Male_Villager_ATT_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"ATT", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/Farming_Walk/Enemy_Male_Villager_Farming_Walk_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"Berry_Gatherer_Walk", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/Building/Enemy_Male_Villager_Building_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"Building", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/Death/Enemy_Male_Villager_Death_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"Death", 25);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/Dying/Enemy_Male_Villager_Dying_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"Dying", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/Miner_Carrying_Gold/Enemy_Male_Villager_Miner_Carrying_Gold_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"Miner_Carrying_Gold", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/Miner_Carrying_Stone/Enemy_Male_Villager_Miner_Carrying_Stone_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"Miner_Carrying_Stone", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/Miner_Mining/Enemy_Male_Villager_Miner_Mining_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"Miner_Mining", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/Woodcutter_Carrying/Enemy_Male_WoodCutter_Carrying_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"Carrying_Wood", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Male_Villager/Woodcutter_Chopping/Enemy_Male_WoodCutter_Chopping_0%d%d.png", L"Enemy_Villager", TEX_MULTI, L"Chopping", 75);

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Ship/Flag/5/Enemy_Ship_Flag_%d%d%d.png", L"Ship", TEX_MULTI, L"MoveVibe2", 100);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Enemy/Ship/Death/Enemy_Ship_Death_00%d.png", L"Ship", TEX_MULTI, L"Death2", 6);

	// 적 건물 //
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Dark_Age/Town.png", L"EnemyTown", TEX_SINGLE, L"EnemyTown");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Dark_Age/Port.png", L"EnemyPort", TEX_SINGLE, L"EnemyPort");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Dark_Age/Barracks.png", L"EnemyBarracks", TEX_SINGLE, L"EnemyBarracks");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Dark_Age/Lumber_Camp.png", L"EnemyLumberCamp", TEX_SINGLE, L"EnemyLumberCamp");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Dark_Age/Mining_Camp.png", L"EnemyMiningCamp", TEX_SINGLE, L"EnemyMiningCamp");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Dark_Age/Home%d.png", L"EnemyHome", TEX_MULTI, L"EnemyHome", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Dark_Age/Mill/Mill_0%d%d.png", L"EnemyMill", TEX_MULTI, L"EnemyMill", 43);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Feudal_Age/Town.png", L"EnemyTown2", TEX_SINGLE, L"EnemyTown2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Castle_Age/Town.png", L"EnemyTown3", TEX_SINGLE, L"EnemyTown3");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Imperial_Age/Town.png", L"EnemyTown4", TEX_SINGLE, L"EnemyTown4");

	// UI //
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Cursor/Mouse_0%d%d.png", L"Mouse", TEX_MULTI, L"Mouse", 19);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Flag/Flag_00%d.png", L"Flag", TEX_MULTI, L"Flag", 9);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Gauge/Gauge_0%d%d.png", L"Gauge", TEX_MULTI, L"Gauge", 99);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Icon/Building/Icon0%d%d.png", L"BuildIcon", TEX_MULTI, L"BuildIcon", 22);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Icon/Control/Icon0%d%d.png", L"ControlIcon", TEX_MULTI, L"ControlIcon", 44);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Icon/Frame/IconFrame_%d.png", L"FrameIcon", TEX_MULTI, L"FrameIcon", 2);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Icon/Interface/Icon00%d.png", L"InterfaceIcon", TEX_MULTI, L"InterfaceIcon", 9);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Icon/Unit/Icon0%d%d.png", L"UnitIcon", TEX_MULTI, L"UnitIcon", 53);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Icon/Upgrade/Icon_%d%d%d.png", L"UpgradeIcon", TEX_MULTI, L"UpgradeIcon", 109);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Point/Point_00%d.png", L"PointIcon", TEX_MULTI, L"PointIcon", 6);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/Main_UI.png", L"MainUI", TEX_SINGLE, L"MainUI");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/MiniMap/Minimap_00%d.png", L"MiniMap", TEX_MULTI, L"MiniMap", 4);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Interface/MiniMap/MinimapLine.png", L"MiniView", TEX_SINGLE, L"MiniView");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Number/Num_00%d.png", L"Num", TEX_MULTI, L"Num", 9);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Select%d.png", L"Select", TEX_MULTI, L"Select", 5);

	// 화살 //
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Arrow/Ground/Arrow_Ground_0%d%d.png", L"Arrow_Ground", TEX_MULTI, L"Arrow_Ground", 51);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Arrow/Img/Arrow_Img_%d%d%d.png", L"Arrow_Img", TEX_MULTI, L"Arrow_Img", 176);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Arrow/Shadow/Arrow_Shadow_0%d%d.png", L"Arrow_Shadow", TEX_MULTI, L"Arrow_Shadow", 17);

	// 자원 및 기타 오브젝트 & 이펙트 //
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Bird/Bird_0%d%d.png", L"Bird", TEX_MULTI, L"Bird", 60);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Bone/Bone_0%d%d.png", L"Bone", TEX_MULTI, L"Bone", 15);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Catchnet/Make/Enemy/Catchnet_Enemy_00%d.png", L"Make_Catchnet_Enemy", TEX_MULTI, L"Make_Catchnet_Enemy", 4);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Catchnet/Make/Player/Catchnet_Player_00%d.png", L"Make_Catchnet_Player", TEX_MULTI, L"Make_Catchnet_Player", 4);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Catchnet/STD/Enemy/Catchnet_Enemy_STD_00%d.png", L"STD_Catchnet_Enemy", TEX_MULTI, L"STD_Catchnet_Enemy", 6);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Catchnet/STD/Player/Catchnet_Player_STD_00%d.png", L"STD_Catchnet_Player", TEX_MULTI, L"STD_Catchnet_Player", 6);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Effect/Boom1/Boom1_00%d.png", L"Boom1", TEX_MULTI, L"Boom1", 10);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Effect/Boom2/Boom2_00%d.png", L"Boom2", TEX_MULTI, L"Boom2", 10);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Effect/Boom3/Boom3_00%d.png", L"Boom3", TEX_MULTI, L"Boom3", 10);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Effect/Boom4/Boom4_0%d%d.png", L"Boom4", TEX_MULTI, L"Boom4", 20);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Effect/Boom5/Boom5_0%d%d.png", L"Boom5", TEX_MULTI, L"Boom5", 20);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Effect/Boom6/Boom6_00%d.png", L"Boom6", TEX_MULTI, L"Boom6", 6);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Effect/Boom7/Boom7_0%d%d.png", L"Boom7", TEX_MULTI, L"Boom7", 40);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Effect/Effect/Middle/Marlin_Effect_Middle_0%d%d.png", L"BoomMiss", TEX_MULTI, L"BoomMiss", 15);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Missile/1/Missile1_00%d.png", L"Missile1", TEX_MULTI, L"Missile1", 9);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Missile/2/Missile2_00%d.png", L"Missile2", TEX_MULTI, L"Missile2", 10);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Missile/Shadow/Missile_Shadow_0%d%d.png", L"Missile_Shadow", TEX_MULTI, L"Missile_Shadow", 18);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/ChamChi_0%d%d.png", L"ChamChi", TEX_MULTI, L"ChamChi", 50);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/Cherry_00%d.png", L"Cherry", TEX_MULTI, L"Cherry", 4);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/Gold_00%d.png", L"Gold", TEX_MULTI, L"Gold", 7);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/Marlin_0%d%d.png", L"Marlin", TEX_MULTI, L"Marlin", 49);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/Rock_00%d.png", L"Rock", TEX_MULTI, L"Rock", 7);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/Tree_00%d.png", L"Tree", TEX_MULTI, L"Tree", 10);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Ship_Move_Effect/Ship_Effect_0%d%d.png", L"Ship_Move_Effect", TEX_MULTI, L"Ship_Move_Effect", 75);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Smoke/Smoke_0%d%d.png", L"Smoke", TEX_MULTI, L"Smoke", 23);

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Stone/Fire/Stone_Fire_00%d.png", L"Stone_Fire", TEX_MULTI, L"Stone_Fire", 10);

	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Stone/Normal/Stone_00%d.png", L"Stone", TEX_MULTI, L"Stone", 6);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Tree/Chopping/Tree_D_00%d.png", L"Chopping_Tree", TEX_MULTI, L"Chopping_Tree", 5);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Tree/Shadow/TreeShadow_00%d.png", L"Tree_Shadow", TEX_MULTI, L"Tree_Shadow", 10);

	// 플레이어 건물 //
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Town.png", L"PlayerTown", TEX_SINGLE, L"PlayerTown");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Port.png", L"PlayerPort", TEX_SINGLE, L"PlayerPort");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Port_Shadow.png", L"Port_Shadow", TEX_SINGLE, L"Port_Shadow");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Town_Shadow.png", L"Town_Shadow", TEX_SINGLE, L"Town_Shadow");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Barracks.png", L"PlayerBarraks", TEX_SINGLE, L"PlayerBarraks");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Lumber_Camp.png", L"PlayerLumberCamp", TEX_SINGLE, L"PlayerLumberCamp");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Mining_Camp.png", L"PlayerMiningCamp", TEX_SINGLE, L"PlayerMiningCamp");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Home%d.png", L"PlayerHome", TEX_MULTI, L"PlayerHome", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Mill/Mill%d%d.png", L"PlayerMill", TEX_MULTI, L"PlayerMill", 43);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Home%d.png", L"PlayerHome2", TEX_MULTI, L"PlayerHome2", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Town.png", L"PlayerTown2", TEX_SINGLE, L"PlayerTown2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Port.png", L"PlayerPort2", TEX_SINGLE, L"PlayerPort2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Port_Shadow.png", L"Port_Shadow2", TEX_SINGLE, L"Port_Shadow2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Barracks.png", L"PlayerBarracks2", TEX_SINGLE, L"PlayerBarracks2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Lumber_Camp.png", L"PlayerLumberCamp2", TEX_SINGLE, L"PlayerLumberCamp2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Mining_Camp.png", L"PlayerMiningCamp2", TEX_SINGLE, L"PlayerMiningCamp2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Tower.png", L"PlayerTower", TEX_SINGLE, L"PlayerTower");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Archer_Barracks.png", L"PlayerArcherBarracks", TEX_SINGLE, L"PlayerArcherBarracks");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Knight_Barracks.png", L"PlayerKnightBarracks", TEX_SINGLE, L"PlayerKnightBarracks");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Feudal_Age/Mill/Mill%d.png", L"PlayerMill2", TEX_MULTI, L"PlayerMill2", 8);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Mill/Mill%d.png", L"PlayerMill3", TEX_MULTI, L"PlayerMill3", 10);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Town.png", L"PlayerTown3", TEX_SINGLE, L"PlayerTown3");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Town_Shadow.png", L"Town_Shadow2", TEX_SINGLE, L"Town_Shadow2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Archer_Barracks.png", L"PlayerArcherBarracks2", TEX_SINGLE, L"PlayerArcherBarracks2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Knight_Barracks.png", L"PlayerKnightBarracks2", TEX_SINGLE, L"PlayerKnightBarracks2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Home%d.png", L"PlayerHome3", TEX_MULTI, L"PlayerHome3", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Barracks.png", L"PlayerBarracks3", TEX_SINGLE, L"PlayerBarracks3");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Port.png", L"PlayerPort3", TEX_SINGLE, L"PlayerPort3");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Port_Shadow.png", L"Port_Shadow3", TEX_SINGLE, L"Port_Shadow3");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Lumber_Camp.png", L"PlayerLumberCamp3", TEX_SINGLE, L"PlayerLumberCamp2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Mining_Camp.png", L"PlayerMiningCamp3", TEX_SINGLE, L"PlayerMiningCamp2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Castle_Age/Tower.png", L"PlayerTower2", TEX_SINGLE, L"PlayerTower2");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Imperial_Age/Tower.png", L"PlayerTower3", TEX_SINGLE, L"PlayerTower3");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Imperial_Age/Town.png", L"PlayerTown4", TEX_SINGLE, L"PlayerTown4");
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Imperial_Age/Port.png", L"PlayerPort4", TEX_SINGLE, L"PlayerPort4");

	// 건물 짓기 및 파괴 //
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Broken/Broken_00%d.png", L"Broken", TEX_MULTI, L"Broken", 4);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Enemy/Big/Img/Sequence_Enemy_Big_Img_00%d.png", L"Sequence_Enemy_Big", TEX_MULTI, L"Sequence_Enemy_Big", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Enemy/Middle/Img/Sequence_Enemy_Middle_Img_00%d.png", L"Sequence_Enemy_Middle", TEX_MULTI, L"Sequence_Enemy_Middle", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Enemy/Small/Img/Sequence_Enemy_Small_Img_00%d.png", L"Sequence_Enemy_Small", TEX_MULTI, L"Sequence_Enemy_Small", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Player/Big/Img/Sequence_Player_Big_Img_00%d.png", L"Sequence_Player_Big", TEX_MULTI, L"Sequence_Player_Big", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Player/Middle/Img/Sequence_Player_Middle_Img_00%d.png", L"Sequence_Player_Middle", TEX_MULTI, L"Sequence_Player_Middle", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Player/Small/Img/Sequence_Player_Small_Img_00%d.png", L"Sequence_Player_Small", TEX_MULTI, L"Sequence_Player_Small", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Player/Port_Build_%d.png", L"Port_Build", TEX_MULTI, L"Port_Build", 3);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Fire/Big/Fire3_0%d%d.png", L"Fire", TEX_MULTI, L"Fire3", 20);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Fire/Middle/Fire2_0%d%d.png", L"Fire", TEX_MULTI, L"Fire2", 20);
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sequence/Fire/Small/Fire1_0%d%d.png", L"Fire", TEX_MULTI, L"Fire1", 20);
	
	TCHAR szTemp[256] = L"Load Complete";

	//이렇게 쓰지마...leak 남더라....
	//wstring wstrPath = L"Load Complete";

	CTextureMgr::GetInstance()->GetCurrentPath() = szTemp;

	LeaveCriticalSection(&pLogo->GetCrt());
	_endthreadex(0);

	return 0;	

}

CRITICAL_SECTION CLogo::GetCrt( void )
{
	return m_Crt;
}
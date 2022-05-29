#include "StdAfx.h"
#include "MainUI.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "ButtonMgr.h"
#include "TIleMgr.h"
#include "TransShip.h"
CMainUI::CMainUI(void)
{

}


CMainUI::~CMainUI(void)
{
}

HRESULT CMainUI::Initialize( void )
{
	m_tInfo.vPos = D3DXVECTOR3(float(WINCX / 2), float(WINCY / 2), 0.f);
	m_tInfo.wstrObjKey = L"MainUI";
	pMainUITex = CTextureMgr::GetInstance()->GetTexture(m_tInfo.wstrObjKey, m_tInfo.wstrObjKey, 0);

	for(int i = 0; i < 80; ++i)
		pTexInfo[i] = CTextureMgr::GetInstance()->GetTexture(L"Tile", L"Tile", i);
	
	m_tInfo.iTreeNum = 8000;
	m_tInfo.iFoodNum = 10000;
	m_tInfo.iStoneNum = 5000;
	m_tInfo.iGoldNum = 5000;

	int iCnt = 0;

	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
			++iCnt;
	}

	m_tInfo.iUnitCount = iCnt;
	m_tInfo.iUnitMaxCount = 20;

	pMiniViewTex = CTextureMgr::GetInstance()->GetTexture(L"MiniView", L"MiniView", 0);

	for(int i = 0; i < 4; ++i)
	{
		pMiniMapTex[i] = CTextureMgr::GetInstance()->GetTexture(L"MiniMap", L"MiniMap", i);
	}

	for(int i = 0; i < 9 ; ++i)
		pIconTex[i] = CTextureMgr::GetInstance()->GetTexture(L"InterfaceIcon", L"InterfaceIcon", i);

	return S_OK;
}

int CMainUI::Update( void )
{
	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	int iCnt = 0;

	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->m_ePlayerType == PT_PLAYER)
			++iCnt;
	}

	m_tInfo.iUnitCount = iCnt;

	return 0;
}

void CMainUI::Render( void )
{
	if(pMainUITex == NULL)
		return;

	float fX = pMainUITex->ImgInfo.Width / 2.f;
	float fY = pMainUITex->ImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(pMainUITex->pTexture, 
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	TCHAR	szTreeBuf[128] = L"";
	wsprintf(szTreeBuf, L"%d", m_tInfo.iTreeNum); //////////////// 나무

	D3DXMATRIX	matTreeTrans;
	D3DXMatrixTranslation(&matTreeTrans, 40.f, 5.f, 0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTreeTrans);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szTreeBuf, lstrlen(szTreeBuf), NULL, NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	TCHAR	szFoodBuf[128] = L"";
	wsprintf(szFoodBuf, L"%d", m_tInfo.iFoodNum); //////////////// 고기

	D3DXMATRIX	matFoodTrans;
	D3DXMatrixTranslation(&matFoodTrans, 110.f, 5.f, 0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matFoodTrans);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szFoodBuf, lstrlen(szFoodBuf), NULL, NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	TCHAR	szGoldBuf[128] = L"";
	wsprintf(szGoldBuf, L"%d", m_tInfo.iGoldNum); //////////////// 골드

	D3DXMATRIX	matGoldTrans;
	D3DXMatrixTranslation(&matGoldTrans, 190.f, 5.f, 0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matGoldTrans);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szGoldBuf, lstrlen(szGoldBuf), NULL, NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	TCHAR	szStoneBuf[128] = L"";
	wsprintf(szStoneBuf, L"%d", m_tInfo.iStoneNum); //////////////// 돌

	D3DXMATRIX	matStoneTrans;
	D3DXMatrixTranslation(&matStoneTrans, 270.f, 5.f, 0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matStoneTrans);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szStoneBuf, lstrlen(szStoneBuf), NULL, NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	TCHAR	szUnitBuf[128] = L"";
	wsprintf(szUnitBuf, L"%d / %d", m_tInfo.iUnitCount, m_tInfo.iUnitMaxCount); //////////////// 돌

	D3DXMATRIX	matUnitTrans;
	D3DXMatrixTranslation(&matUnitTrans, 340.f, 5.f, 0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matUnitTrans);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		szUnitBuf, lstrlen(szUnitBuf), NULL, NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));


	/////////////////////// 유닛 프로필 ///////////////////////
	ProfilRender();
	BuildProfilRender();
}

void CMainUI::Release( void )
{

}
bool CMainUI::MiniMapRenderCheck()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->bMove == true)
			return true;
	}

	return false;
}
void CMainUI::MiniMapRender()
{
	for(int i = 0; i < TILECNTY; ++i)
	{
		for(int j = 0; j < TILECNTX; ++j)
		{
			int iIndex = i * TILECNTX + j;

			if(pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID] == NULL)
				return;

			float fX = pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID]->ImgInfo.Width / 2.f;
			float fY = pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID]->ImgInfo.Height / 2.f;

			D3DXMATRIX	matTrans;
			D3DXMATRIX	matScale;
			D3DXMatrixTranslation(&matTrans, (CTileMgr::GetInstance()->GetTile()[iIndex]->vPos.x + 9300) * 0.055 , (CTileMgr::GetInstance()->GetTile()[iIndex]->vPos.y + 8475) * 0.055, 0.f);
			D3DXMatrixScaling(&matScale, 0.055f, 0.055f, 0.f);

			D3DXMATRIX	matWorld;

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);


			if(CTileMgr::GetInstance()->GetTile()[iIndex]->byOption == 0 && CTileMgr::GetInstance()->GetTile()[iIndex]->m_UnitType != UT_FOG)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(0, 255, 255, 255));
			}
			if( CTileMgr::GetInstance()->GetTile()[iIndex]->byOption == 1)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			if(CTileMgr::GetInstance()->GetTile()[iIndex]->byOption == 0 && CTileMgr::GetInstance()->GetTile()[iIndex]->m_UnitType == UT_FOG)
			{
				CDevice::GetInstance()->GetSprite()->Draw(pTexInfo[CTileMgr::GetInstance()->GetTile()[iIndex]->byDrawID]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(128, 255, 255, 255));
			}
		}
	}
}

void CMainUI::ProfilRender()
{
	unordered_map<int, CObj*>::iterator iter = CObjMgr::GetInstance()->GetGroupMap()->begin();
	unordered_map<int, CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetGroupMap()->end();

	if(iter == iter_end)
		return;

	int iX = 0;
	int iY = 0;

	if(CObjMgr::GetInstance()->GetGroupMap()->size() == 1)
	{

		D3DXMATRIX	matTrans;
		TCHAR	szBuf[128] = L"";

		switch(iter->second->GetInfo()->m_eUnitType)
		{
		case UT_VILLAGER:
			wsprintf(szBuf, L"Villager");

			D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 0, 0, 0));
			break;
		case UT_FISHER:
			wsprintf(szBuf, L"Fishing Ship");

			D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 0, 0, 0));
			break;
		case UT_TRANSSHIP:
			wsprintf(szBuf, L"TransPort Ship");

			D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 0, 0, 0));
			break;
		case UT_GALLYSHIP:
			wsprintf(szBuf, L"Gally Ship");

			D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 0, 0, 0));
			break;
		case UT_DESTROYSHIP:
			wsprintf(szBuf, L"Demolition Ship");

			D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 0, 0, 0));
			break;
		case UT_FIRESHIP:
			wsprintf(szBuf, L"Fire Ship");

			D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 0, 0, 0));
			break;
		case UT_CANNONSHIP:
			wsprintf(szBuf, L"Cannon Gallion");

			D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 0, 0, 0));
			break;
		}
		if(iter->second->GetInfo()->m_eUnitType == UT_FISHER && iter->second->GetInfo()->iGetResourceCount > 0)
		{
			float fX = 0;
			float fY = 0;
			D3DXMATRIX	matTrans;

			switch(iter->second->GetInfo()->m_eStateType)
			{
			case STATE_FISHING:
				fX = pIconTex[2]->ImgInfo.Width / 2.f;
				fY = pIconTex[2]->ImgInfo.Height / 2.f;

				D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pIconTex[2]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));

				break;

			case STATE_FISHING_WORK:
				fX = pIconTex[2]->ImgInfo.Width / 2.f;
				fY = pIconTex[2]->ImgInfo.Height / 2.f;

				D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pIconTex[2]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));

				break;

			}

			TCHAR	szBuf[128] = L"";
			wsprintf(szBuf, L"%d", iter->second->GetInfo()->iGetResourceCount);

			D3DXMatrixTranslation(&matTrans, 380, 580, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 0, 0, 0));

		}

		if(iter->second->GetInfo()->m_eUnitType == UT_VILLAGER && iter->second->GetInfo()->iGetResourceCount > 0)
		{
			float fX = 0;
			float fY = 0;
			D3DXMATRIX	matTrans;

			switch(iter->second->GetInfo()->m_eStateType)
			{
			case STATE_GET_CHEERY:
				fX = pIconTex[2]->ImgInfo.Width / 2.f;
				fY = pIconTex[2]->ImgInfo.Height / 2.f;

				D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pIconTex[2]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));

				break;

			case STATE_CARRY_CHERRY:
				fX = pIconTex[2]->ImgInfo.Width / 2.f;
				fY = pIconTex[2]->ImgInfo.Height / 2.f;

				D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pIconTex[2]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));

				break;

			case STATE_WOOD_CUTTING:
				fX = pIconTex[0]->ImgInfo.Width / 2.f;
				fY = pIconTex[0]->ImgInfo.Height / 2.f;

				D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pIconTex[0]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case STATE_CARRY_WOOD:
				fX = pIconTex[0]->ImgInfo.Width / 2.f;
				fY = pIconTex[0]->ImgInfo.Height / 2.f;

				D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pIconTex[0]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case STATE_MINING_GOLD:
				fX = pIconTex[3]->ImgInfo.Width / 2.f;
				fY = pIconTex[3]->ImgInfo.Height / 2.f;

				D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pIconTex[3]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case STATE_CARRY_GOLD:
				fX = pIconTex[3]->ImgInfo.Width / 2.f;
				fY = pIconTex[3]->ImgInfo.Height / 2.f;

				D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pIconTex[3]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case STATE_MINING_STONE:
				fX = pIconTex[1]->ImgInfo.Width / 2.f;
				fY = pIconTex[1]->ImgInfo.Height / 2.f;

				D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pIconTex[1]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case STATE_CARRY_STONE:
				fX = pIconTex[1]->ImgInfo.Width / 2.f;
				fY = pIconTex[1]->ImgInfo.Height / 2.f;

				D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pIconTex[1]->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			}

			TCHAR	szBuf[128] = L"";
			wsprintf(szBuf, L"%d", iter->second->GetInfo()->iGetResourceCount);

			D3DXMatrixTranslation(&matTrans, 380, 580, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 0, 0, 0));

		}
		if(iter->second->GetInfo()->m_eUnitType == UT_TRANSSHIP && iter->second->GetInfo()->bTrans == true && iter->second->GetInfo()->bSelection == true)
		{
			CObj*	pObj = iter->second;

			list<const TEXINFO*>::iterator Trans_iter = ((CTransShip*)pObj)->GetTransTex()->begin();
			list<const TEXINFO*>::iterator Trans_iter_end = ((CTransShip*)pObj)->GetTransTex()->end();

			if(Trans_iter == Trans_iter_end)
				return;

			for(; Trans_iter != Trans_iter_end; ++Trans_iter)
			{

				if((*Trans_iter) == NULL)
					return;

				float fX = (*Trans_iter)->ImgInfo.Width / 2.f;
				float fY = (*Trans_iter)->ImgInfo.Height / 2.f;

				D3DXMATRIX	matTrans;
				D3DXMatrixTranslation(&matTrans, 250 + iX, 530 + iY, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw((*Trans_iter)->pTexture, 
					NULL,
					&D3DXVECTOR3(fX, fY, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));

				iX += 35;

				if(iX >= 245)
				{
					iX = 0;
					iY += 35;
				}
			}

		
			return;
		}
		if(iter->second->GetProfil() == NULL)
			return;

		float fX = iter->second->GetProfil()->ImgInfo.Width / 2.f;
		float fY = iter->second->GetProfil()->ImgInfo.Height / 2.f;

		D3DXMatrixTranslation(&matTrans, 250 + iX, 500 + iY, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(iter->second->GetProfil()->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		fX = pIconTex[7]->ImgInfo.Width / 2.f;
		fY = pIconTex[7]->ImgInfo.Height / 2.f;

		D3DXMatrixTranslation(&matTrans, 350, 530, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(pIconTex[7]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		fX = pIconTex[8]->ImgInfo.Width / 2.f;
		fY = pIconTex[8]->ImgInfo.Height / 2.f;

		D3DXMatrixTranslation(&matTrans, 350, 555, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(pIconTex[8]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));


		if(iter->second->GetInfo()->m_eUnitType != UT_VILLAGER && iter->second->GetInfo()->m_eUnitType != UT_FISHER)
		{
			float fX = pIconTex[6]->ImgInfo.Width / 2.f;
			float fY = pIconTex[6]->ImgInfo.Height / 2.f;
			
			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 355, 585, 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pIconTex[6]->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));

			TCHAR	szBuf[128] = L"";
			wsprintf(szBuf, L"%d", iter->second->GetInfo()->iRange);

			D3DXMatrixTranslation(&matTrans, 380, 580, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 0, 0, 0));
		}
		
		wsprintf(szBuf, L"%d/%d", iter->second->GetInfo()->iHp, iter->second->GetInfo()->iMaxHp);

		D3DXMatrixTranslation(&matTrans, 235, 520, 0.f);
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 255, 0, 0));

		wsprintf(szBuf, L"%d", iter->second->GetInfo()->iAtt);

		D3DXMatrixTranslation(&matTrans, 380, 525, 0.f);
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetFont()->DrawTextW(
			CDevice::GetInstance()->GetSprite(),
			szBuf, lstrlen(szBuf), NULL, NULL,
			D3DCOLOR_ARGB(255, 0, 0, 0));

		wsprintf(szBuf, L"%d", iter->second->GetInfo()->iDef);

		D3DXMatrixTranslation(&matTrans, 380, 550, 0.f);
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetFont()->DrawTextW(
			CDevice::GetInstance()->GetSprite(),
			szBuf, lstrlen(szBuf), NULL, NULL,
			D3DCOLOR_ARGB(255, 0, 0, 0));

		return;
	}

	else if(CObjMgr::GetInstance()->GetGroupMap()->size() > 1)
	{
		for(; iter != iter_end; ++iter)
		{
			if(iter->second->GetProfil() == NULL)
				return;

			float fX = iter->second->GetProfil()->ImgInfo.Width / 2.f;
			float fY = iter->second->GetProfil()->ImgInfo.Height / 2.f;

			D3DXMATRIX	matTrans;
			D3DXMatrixTranslation(&matTrans, 250 + iX, 500 + iY, 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(iter->second->GetProfil()->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));

			iX += 35;

			if(iX >= 245)
			{
				iX = 0;
				iY += 35;
			}
		}
	}
}

void CMainUI::BuildProfilRender()
{
	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Build", SORT_OBJECT).end();

	if(iter == iter_end)
		return;

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->bSelection == true)
		{
			D3DXMATRIX	matTrans;
			TCHAR	szBuf[128] = L"";

			switch((*iter)->GetInfo()->m_eBuildType)
			{
			case BT_TOWN:
				wsprintf(szBuf, L"Town");

				D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 0, 0, 0));
				break;
			case BT_HOME:
				wsprintf(szBuf, L"Home");

				D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 0, 0, 0));
				break;
			case BT_BARRACK:
				wsprintf(szBuf, L"Barrack");

				D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 0, 0, 0));
				break;
			case BT_MILL:
				wsprintf(szBuf, L"Mill");

				D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 0, 0, 0));
				break;
			case BT_PORT:
				wsprintf(szBuf, L"Port");

				D3DXMatrixTranslation(&matTrans, 350, 480, 0.f);
				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 0, 0, 0));
				break;
			}

			if((*iter)->GetProfil() == NULL)
				return;

			float fX = (*iter)->GetProfil()->ImgInfo.Width / 2.f;
			float fY = (*iter)->GetProfil()->ImgInfo.Height / 2.f;

			D3DXMatrixTranslation(&matTrans, 250, 500, 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw((*iter)->GetProfil()->pTexture, 
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));

			wsprintf(szBuf, L"%d/%d", (*iter)->GetInfo()->iHp, (*iter)->GetInfo()->iMaxHp);

			D3DXMatrixTranslation(&matTrans, 230, 520, 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetFont()->DrawTextW(
				CDevice::GetInstance()->GetSprite(),
				szBuf, lstrlen(szBuf), NULL, NULL,
				D3DCOLOR_ARGB(255, 255, 0, 0));
		}
	}
}

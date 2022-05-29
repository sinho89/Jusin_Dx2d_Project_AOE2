#include "StdAfx.h"
#include "BackGround.h"
#include "TextureMgr.h"
#include "ToolView.h"

CBackGround::CBackGround(void)
{
	ZeroMemory(&m_vPos, sizeof(D3DXVECTOR3));
}

CBackGround::~CBackGround(void)
{
	Release();
}
HRESULT CBackGround::Initialize(void)
{
	for(int i = 0; i < TILECNTY; ++i)
	{
		for(int j = 0; j < TILECNTX; ++j)
		{
			TILE*	pTile = new TILE;

			m_vPos.x = float(TILESIZEX / 2 * ( j - i ) + ((TILESIZEX * TILECNTX) / 2.f));
			m_vPos.y = float(TILESIZEY / 2 * ( j + i ));

			pTile->vPos = D3DXVECTOR3(m_vPos.x, m_vPos.y, 0.f);
			pTile->vSize = D3DXVECTOR3(float(TILESIZEX), float(TILESIZEY), 0.f);
			pTile->byOption = 0;
			pTile->byDrawID = 50;
			pTile->m_eType = RT_NONE;
			pTile->m_GroundType = GT_SEA;
			pTile->m_BuildType = BT_end;
			pTile->m_UnitType = UT_end;
			pTile->byOriID = pTile->byDrawID;

			pTile->wstrObjKey = L"Tile";
			pTile->wstrStateKey = L"Tile";

			m_vecTile.push_back(pTile);
		}
	}

	//m_pMainView = (CTool63View*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	return S_OK;
}

void CBackGround::Update(void)
{
	//얘는 아직 할게없어...
}

void CBackGround::Render(void)
{
	D3DXMATRIX	matTrans;
	D3DXMatrixIdentity(&matTrans);

	for(int i = 0; i < TILECNTY; ++i)
	{
		for(int j = 0; j < TILECNTX; ++j)
		{
			int iIndex = i * TILECNTX + j;

			const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Tile",  L"Tile", m_vecTile[iIndex]->byDrawID);

			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0), m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1), 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, 
				NULL,
				&D3DXVECTOR3(TILESIZEX / 2.f, TILESIZEY / 2.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	for(size_t i = 0; i < m_vecResource.size(); ++i)
	{
		const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_vecResource[i]->wstrObjKey, m_vecResource[i]->wstrStateKey, m_vecResource[i]->byDrawID);
		const TEXINFO*	pTexShadowInfo = CTextureMgr::GetInstance()->GetTexture(L"TreeShadow", L"TreeShadow", m_vecResource[i]->byDrawID);

		if(m_vecResource[i]->wstrStateKey == L"Tree")
		{

			D3DXMatrixTranslation(&matTrans, m_vecResource[i]->vPos.x - m_pMainView->GetScrollPos(0) - 30, m_vecResource[i]->vPos.y - m_pMainView->GetScrollPos(1), 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pTexShadowInfo->pTexture, 
				NULL,
				&D3DXVECTOR3(pTexShadowInfo->ImgInfo.Width / 2.f, pTexShadowInfo->ImgInfo.Height / 2.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(100, 0, 0, 0));
		}

		D3DXMatrixTranslation(&matTrans, m_vecResource[i]->vPos.x - m_pMainView->GetScrollPos(0), m_vecResource[i]->vPos.y - m_pMainView->GetScrollPos(1), 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, 
			NULL,
			&D3DXVECTOR3(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	for(size_t i = 0; i < m_vecBuild.size(); ++i)
	{
		const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_vecBuild[i]->wstrObjKey, m_vecBuild[i]->wstrStateKey, m_vecBuild[i]->byDrawID);
		const TEXINFO*	pTexShadowInfo = CTextureMgr::GetInstance()->GetTexture(L"TownShadow", L"TownShadow", m_vecBuild[i]->byDrawID);

		if(m_vecBuild[i]->wstrObjKey == L"Town")
		{
			D3DXMatrixTranslation(&matTrans, m_vecBuild[i]->vPos.x - m_pMainView->GetScrollPos(0) - 10, m_vecBuild[i]->vPos.y - m_pMainView->GetScrollPos(1) + 70, 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pTexShadowInfo->pTexture, 
				NULL,
				&D3DXVECTOR3(pTexShadowInfo->ImgInfo.Width / 2.f, pTexShadowInfo->ImgInfo.Height / 2.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(150, 0, 0, 0));
		}
		D3DXMatrixTranslation(&matTrans, m_vecBuild[i]->vPos.x - m_pMainView->GetScrollPos(0), m_vecBuild[i]->vPos.y - m_pMainView->GetScrollPos(1), 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, 
			NULL,
			&D3DXVECTOR3(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	for(size_t i = 0; i < m_vecUnit.size(); ++i)
	{
		const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_vecUnit[i]->wstrObjKey, m_vecUnit[i]->wstrStateKey, m_vecUnit[i]->byDrawID);

		D3DXMatrixTranslation(&matTrans, m_vecUnit[i]->vPos.x - m_pMainView->GetScrollPos(0), m_vecUnit[i]->vPos.y - m_pMainView->GetScrollPos(1), 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, 
			NULL,
			&D3DXVECTOR3(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	for(int i = 0; i < TILECNTY; ++i)
	{
		for(int j = 0; j < TILECNTX; ++j)
		{
			int iIndex = i * TILECNTX + j;

			//폰트를 여기서 출력한다...
			TCHAR	szBuf[128] = L"";
			wsprintf(szBuf, L"%d", iIndex);
			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0), m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1), 0.f);
			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			switch(m_vecTile[iIndex]->m_GroundType)
			{
			case GT_GROUND:
				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 0, 0, 0));
				break;
			case GT_SEA:
				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case GT_UNIT:
				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 0, 255, 255));
				break;
			case GT_EMPTY:
				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 255, 0, 0));
				break;
			}
			switch(m_vecTile[iIndex]->m_eType)
			{
			case RT_TREE:
				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 0, 255, 0));
				break;
			case RT_FISH:
				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 0, 0, 255));
				break;
			case RT_STONE:
				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 128, 128, 128));
				break;
			case RT_GOLD:
				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 255, 255, 0));
				break;
			case RT_CHERRY:
				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szBuf, lstrlen(szBuf), NULL, NULL,
					D3DCOLOR_ARGB(255, 255, 0, 255));
				break;
			}
		}
	}

}


void CBackGround::Release(void)
{
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		delete m_vecTile[i];
	}
	m_vecTile.clear();

	for(size_t i = 0; i < m_vecResource.size(); ++i)
	{
		delete m_vecResource[i];
	}
	m_vecResource.clear();

	for(size_t i = 0; i < m_vecBuild.size(); ++i)
	{
		delete m_vecBuild[i];
	}
	m_vecBuild.clear();

	for(size_t i = 0; i < m_vecUnit.size(); ++i)
	{
		delete m_vecUnit[i];
	}
	m_vecUnit.clear();

}

void CBackGround::AddUnit( const D3DXVECTOR3& vPos, int _iSel, wstring _wstrObjKey, wstring _wstrStateKey )
{
	int iIndex = GetTileIndex(vPos);

	if(iIndex == -1 ||  m_vecTile[iIndex]->m_eType != RT_NONE)
		return;

	INFO*	pUnit = new INFO;

	pUnit->vPos = m_vecTile[iIndex]->vPos;

	pUnit->byDrawID = _iSel;

	pUnit->wstrObjKey = L"Villager";
	pUnit->wstrStateKey = _wstrStateKey;

	if(pUnit->wstrObjKey ==  L"Villager")
	{
		m_vecTile[iIndex]->m_GroundType = GT_UNIT;
		pUnit->m_eUnitType = UT_VILLAGER;
	}

	m_vecUnit.push_back(pUnit);
}

void CBackGround::AddBuild( const D3DXVECTOR3& vPos, int _iSel, wstring _wstrObjKey )
{
	int iIndex = GetTileIndex(vPos);

	if(iIndex == -1 ||  m_vecTile[iIndex]->m_eType != RT_NONE)
		return;

	INFO*	pBuild = new INFO;

	pBuild->m_eAgeType = AT_end;
	pBuild->m_eBuildType = BT_TOWN;
	pBuild->m_ePlayerType = PT_NONE;
	pBuild->m_eUnitType = UT_end;
	pBuild->bAlive = true;
	pBuild->wstrObjKey = _wstrObjKey;
	pBuild->wstrStateKey = _wstrObjKey;
	pBuild->byDrawID = 0;
	pBuild->vPos = m_vecTile[iIndex]->vPos;

	m_vecTile[iIndex]->m_GroundType = GT_EMPTY;
	m_vecTile[iIndex + 1]->m_GroundType = GT_EMPTY;
	m_vecTile[iIndex - 1]->m_GroundType = GT_EMPTY;
	m_vecTile[iIndex + TILECNTX + 1]->m_GroundType = GT_EMPTY;
	m_vecTile[iIndex + TILECNTX]->m_GroundType = GT_EMPTY;
	m_vecTile[iIndex + TILECNTX - 1]->m_GroundType = GT_EMPTY;
	m_vecTile[iIndex - TILECNTX + 1]->m_GroundType = GT_EMPTY;
	m_vecTile[iIndex - TILECNTX]->m_GroundType = GT_EMPTY;
	m_vecTile[iIndex - TILECNTX - 1]->m_GroundType = GT_EMPTY;

	m_vecBuild.push_back(pBuild);

	
}

void CBackGround::AddResource( const D3DXVECTOR3& vPos , int _iSel, wstring _wstrObjKey)
{
	int iIndex = GetTileIndex(vPos);

	if(iIndex == -1 ||  m_vecTile[iIndex]->m_eType != RT_NONE)
		return;

	INFO*	pResource = new INFO;
	
	pResource->m_eAgeType = AT_end;
	pResource->m_eBuildType = BT_end;
	pResource->m_ePlayerType = PT_NONE;
	pResource->m_eUnitType = UT_end;
	pResource->bAlive = true;
	pResource->wstrObjKey = _wstrObjKey;
	pResource->wstrStateKey = _wstrObjKey;
	pResource->byDrawID = _iSel;
	pResource->vPos = m_vecTile[iIndex]->vPos;

	if(_wstrObjKey == L"Tree" || _wstrObjKey == L"ChamChi" || _wstrObjKey == L"Fish")
		pResource->vPos.y -= 60.f;


	if(pResource->wstrObjKey ==  L"Tree")
	{
		m_vecTile[iIndex]->m_eType = RT_TREE;
		pResource->m_eResourceType = RT_TREE;
	}
	if(pResource->wstrObjKey ==  L"Marlin")
	{
		m_vecTile[iIndex]->m_eType = RT_FISH;
		pResource->m_eResourceType = RT_FISH;
	}
	if(pResource->wstrObjKey ==  L"ChamChi")
	{
		m_vecTile[iIndex]->m_eType = RT_FISH;
		pResource->m_eResourceType = RT_FISH;
	}
	if(pResource->wstrObjKey ==  L"Cherry")
	{
		m_vecTile[iIndex]->m_eType = RT_CHERRY;
		pResource->m_eResourceType = RT_CHERRY;
	}
	if(pResource->wstrObjKey ==  L"Gold")
	{
		m_vecTile[iIndex]->m_eType = RT_GOLD;
		pResource->m_eResourceType = RT_GOLD;
	}
	if(pResource->wstrObjKey ==  L"Rock")
	{
		m_vecTile[iIndex]->m_eType = RT_STONE;
		pResource->m_eResourceType = RT_STONE;
	}


	m_vecResource.push_back(pResource);
}
int CBackGround::GetTileIndex(const D3DXVECTOR3& vPos)
{
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if(Picking(vPos, i))
		{
			return i;
		}
	}
	return -1;
}
void CBackGround::TileChange(const D3DXVECTOR3& vPos, const int& iDrawID)
{
	int iIndex = GetTileIndex(vPos);

	if(iIndex == -1)
		return;

	if(iDrawID >= 50 && iDrawID < 80)
		m_vecTile[iIndex]->m_GroundType = GT_SEA;
	else if (iDrawID < 50 && iDrawID >= 0)
		m_vecTile[iIndex]->m_GroundType = GT_GROUND;

	m_vecTile[iIndex]->byDrawID = iDrawID;
}

bool CBackGround::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
{
	//직선의 방정식... y = ax + b
	//기울기는 (y증가량 / x증가량으로 구할 수 있음...
	//y절편 b 는 x가 0일 때의 y값...

	//기울기를 먼저 구해라...
	float fGradient = (TILESIZEY / 2.f) / (TILESIZEX / 2.f);

	//마름모 각 꼭지점 4개를 만들어라...
	D3DXVECTOR3	vPoint[4] = 
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILESIZEY / 2.f, 0),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILESIZEX / 2.f, m_vecTile[iIndex]->vPos.y, 0),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILESIZEY / 2.f, 0),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILESIZEX / 2.f, m_vecTile[iIndex]->vPos.y, 0),
	};


	float fB[4] = 
	{
		//y절편 구해라.....
		vPoint[0].y - fGradient * vPoint[0].x,
		vPoint[1].y + fGradient * vPoint[1].x,
		vPoint[2].y - fGradient * vPoint[2].x,
		vPoint[3].y + fGradient * vPoint[3].x,
	};

	//직선의 방정식은 y = ax + b

	//y - ax - b = 0	: 직선과 동일선상...
	//y - ax - b < 0	: 직선보다 아래에 있는점...
	//y - ax - b > 0	: 직선보다 위에 있는 애다....


	//(0,0) 기준으로 지나가는 선이라고 가정하고...
	if(vPos.y - fGradient * vPos.x - fB[0] > 0 &&
		vPos.y + fGradient * vPos.x - fB[1] < 0 &&
		vPos.y - fGradient * vPos.x - fB[2] < 0 &&
		vPos.y + fGradient * vPos.x - fB[3] > 0)
	{
		return true;
	}

	return false;

}
void CBackGround::SetMainView(CToolView* pMainView)
{
	m_pMainView = pMainView;
}
void CBackGround::MiniViewRender(void)
{
	D3DXMATRIX	matTrans;
	D3DXMATRIX	matScale;
	D3DXMATRIX	matWorld;
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	for(int i = 0; i < TILECNTY; ++i)
	{
		for(int j = 0; j < TILECNTX; ++j)
		{
			int iIndex = i * TILECNTX + j;

			const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Tile", L"Tile", m_vecTile[iIndex]->byDrawID);

			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x * 0.2f, m_vecTile[iIndex]->vPos.y * 0.2f, 0.f);
			D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.f);

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, 
				NULL,
				&D3DXVECTOR3(TILESIZEX / 2.f, TILESIZEY / 2.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}
	for(size_t i = 0; i < m_vecResource.size(); ++i)
	{
		const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_vecResource[i]->wstrObjKey, m_vecResource[i]->wstrStateKey, m_vecResource[i]->byDrawID);
		const TEXINFO*	pTexShadowInfo = CTextureMgr::GetInstance()->GetTexture(L"TreeShadow", L"TreeShadow", m_vecResource[i]->byDrawID);

		if(m_vecResource[i]->wstrStateKey == L"Tree")
		{

			D3DXMatrixTranslation(&matTrans, m_vecResource[i]->vPos.x * 0.2, m_vecResource[i]->vPos.y * 0.2, 0.f);
			D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.f);

			matWorld = matScale * matTrans;


			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pTexShadowInfo->pTexture, 
				NULL,
				&D3DXVECTOR3(pTexShadowInfo->ImgInfo.Width / 2.f, pTexShadowInfo->ImgInfo.Height / 2.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(100, 0, 0, 0));
		}

		D3DXMatrixTranslation(&matTrans, m_vecResource[i]->vPos.x * 0.2, m_vecResource[i]->vPos.y * 0.2, 0.f);
		D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.f);

		matWorld = matScale * matTrans;


		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, 
			NULL,
			&D3DXVECTOR3(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	for(size_t i = 0; i < m_vecBuild.size(); ++i)
	{
		const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_vecBuild[i]->wstrObjKey, m_vecBuild[i]->wstrStateKey, m_vecBuild[i]->byDrawID);
		const TEXINFO*	pTexShadowInfo = CTextureMgr::GetInstance()->GetTexture(L"TownShadow", L"TownShadow", m_vecBuild[i]->byDrawID);

		if(m_vecBuild[i]->wstrObjKey == L"Town")
		{
			D3DXMatrixTranslation(&matTrans, m_vecBuild[i]->vPos.x * 0.2, m_vecBuild[i]->vPos.y * 0.2, 0.f);
			D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.f);

			matWorld = matScale * matTrans;


			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pTexShadowInfo->pTexture, 
				NULL,
				&D3DXVECTOR3(pTexShadowInfo->ImgInfo.Width / 2.f, pTexShadowInfo->ImgInfo.Height / 2.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(200, 0, 0, 0));
		}
		D3DXMatrixTranslation(&matTrans, m_vecBuild[i]->vPos.x * 0.2, m_vecBuild[i]->vPos.y * 0.2, 0.f);
		D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.f);

		matWorld = matScale * matTrans;


		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, 
			NULL,
			&D3DXVECTOR3(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	for(size_t i = 0; i < m_vecUnit.size(); ++i)
	{
		const TEXINFO*	pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_vecUnit[i]->wstrObjKey, m_vecUnit[i]->wstrStateKey, m_vecUnit[i]->byDrawID);

		D3DXMatrixTranslation(&matTrans, m_vecUnit[i]->vPos.x * 0.2, m_vecUnit[i]->vPos.y * 0.2, 0.f);
		D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.f);

		matWorld = matScale * matTrans;


		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, 
			NULL,
			&D3DXVECTOR3(pTexInfo->ImgInfo.Width / 2.f, pTexInfo->ImgInfo.Height / 2.f, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}


#include "StdAfx.h"
#include "Formation.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "TImeMgr.h"
IMPLEMENT_SINGLETON(CFormation)

CFormation::CFormation(void)
{
	bFormationing = false;
}

CFormation::~CFormation(void)
{
}

void CFormation::SetFormationWidth()
{
	if(CObj::FormationWidth == false)
		return;

	list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();
	list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).end();

	if(bFormationing == false)
	{
		vCenterPos = D3DXVECTOR3(0.f, 0.f, 0.f);
		int			iSelectUnitCnt = 0;

		for(; iter != iter_end; ++iter)
		{
			if((*iter)->GetInfo()->bSelection == true && (*iter)->GetInfo()->m_eGroundType == GT_SEA)
			{
				vCenterPos += (*iter)->GetInfo()->vPos;
				++iSelectUnitCnt;
			}
		}
		vCenterPos /= float(iSelectUnitCnt);
	}

	bFormationing = true;

	iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();

	D3DXVECTOR3 vTerm = D3DXVECTOR3(0.f, 0.f, 0.f);

	int iCnt = 0;

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->bSelection == true && (*iter)->GetInfo()->m_eGroundType == GT_SEA)
		{
			D3DXVECTOR3 vWidthPos = vCenterPos;

			switch(iCnt)
			{
			case 0:
				vWidthPos.x -= 200.f;
				vWidthPos.y -= 100.f;
				break;

			case 1:
				vWidthPos.x -= 100.f;
				vWidthPos.y -= 100.f;
				break;

			case 2:
				vWidthPos.y -= 100.f;
				break;

			case 3:
				vWidthPos.x += 100.f;
				vWidthPos.y -= 100.f;
				break;

			case 4:
				vWidthPos.x += 200.f;
				vWidthPos.y -= 100.f;
				break;
			case 5:
				vWidthPos.x -= 200.f;
				break;

			case 6:
				vWidthPos.x -= 100.f;
				break;

			case 7:
				break;

			case 8:
				vWidthPos.x += 100.f;
				break;

			case 9:
				vWidthPos.x += 200.f;
				break;
			case 10:
				vWidthPos.x -= 200.f;
				vWidthPos.y += 100.f;
				break;

			case 11:
				vWidthPos.x -= 100.f;
				vWidthPos.y += 100.f;
				break;

			case 12:
				vWidthPos.y += 100.f;
				break;

			case 13:
				vWidthPos.x += 100.f;
				vWidthPos.y += 100.f;
				break;

			case 14:
				vWidthPos.x += 200.f;
				vWidthPos.y += 100.f;
				break;
			}

			float fX = vWidthPos.x - (*iter)->GetInfo()->vPos.x;
			float fY = vWidthPos.y - (*iter)->GetInfo()->vPos.y;
			float fDest = sqrt(fX * fX + fY * fY);

			(*iter)->GetInfo()->vDir = vWidthPos - (*iter)->GetInfo()->vPos;

			D3DXVec3Normalize(&(*iter)->GetInfo()->vDir, &(*iter)->GetInfo()->vDir);

			SixteenDirCheckFunc((*iter)->GetInfo()->vDir, vWidthPos, (*iter));
			SetTransShipDir((*iter));
			if((*iter)->GetInfo()->bDirCheck == false)
			{
				SetTransShipDir((*iter));
				(*iter)->GetInfo()->bDirCheck = true;
			}

			(*iter)->GetInfo()->vPos += (*iter)->GetInfo()->vDir * (*iter)->GetInfo()->fSpeed * GETTIME;

			if(fDest <= 5)
			{
				(*iter)->GetInfo()->bFormation = true;
				(*iter)->GetInfo()->bMove = false;
				(*iter)->GetInfo()->m_eStateType = STATE_STD;
				(*iter)->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_DOWN;
				(*iter)->GetInfo()->fAngle = 270.f;
				SetTransShipDir((*iter));
				
			}
			++iCnt;
		}
	}

	iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();

	int iFormCnt = 0;

	for(; iter != iter_end; ++iter)
	{
		if((*iter)->GetInfo()->bFormation == true)
		{
			++iFormCnt;
		}
	}

	if(iFormCnt == iCnt)
	{
		CObj::FormationWidth = false;

		iter = CObjMgr::GetInstance()->GetObjList(L"Unit", SORT_OBJECT).begin();

		for(; iter != iter_end; ++iter)
		{
			if((*iter)->GetInfo()->bFormation == true)
			{
				(*iter)->GetInfo()->bFormation = false;
			}
		}
		bFormationing = false;

	}	
}

void CFormation::SetFormationRect()
{

}

void CFormation::SetFormationCheck()
{

}

void CFormation::SetFormationDiv()
{

}
void CFormation::SetTransShipDir(CObj*	pObj)
{
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN) // 보정필요
	{
		pObj->GetFrame()->fFrame = 0;
		pObj->GetFrame()->fMax = 19;
		pObj->GetInfo()->byDrawID = 0;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_L3 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_R3) // 보정필요
	{
		pObj->GetFrame()->fFrame = 20;
		pObj->GetFrame()->fMax = 39;
		pObj->GetInfo()->byDrawID = 1;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_L2 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_R2) // 보정필요
	{
		pObj->GetFrame()->fFrame = 20;
		pObj->GetFrame()->fMax = 39;
		pObj->GetInfo()->byDrawID = 2;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_L1 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_DOWN_R1) // 보정필요
	{
		pObj->GetFrame()->fFrame = 20;
		pObj->GetFrame()->fMax = 39;
		pObj->GetInfo()->byDrawID = 3;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_LEFT || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_RIGHT) // 보정필요
	{
		pObj->GetFrame()->fFrame = 40;
		pObj->GetFrame()->fMax = 59;
		pObj->GetInfo()->byDrawID = 4;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_L1 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_R1) // 보정필요
	{
		pObj->GetFrame()->fFrame = 60;
		pObj->GetFrame()->fMax = 79;
		pObj->GetInfo()->byDrawID = 5;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_L2 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_R2) // 보정필요
	{
		pObj->GetFrame()->fFrame = 60;
		pObj->GetFrame()->fMax = 79;
		pObj->GetInfo()->byDrawID = 6;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_L3 || pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP_R3) // 보정필요
	{
		pObj->GetFrame()->fFrame = 60;
		pObj->GetFrame()->fMax = 79;
		pObj->GetInfo()->byDrawID = 7;
	}
	if(pObj->GetInfo()->m_eSixteenDirType == SIXTEEN_DIR_UP) // 보정필요
	{
		pObj->GetFrame()->fFrame = 80;
		pObj->GetFrame()->fMax = 99;
		pObj->GetInfo()->byDrawID = 8;
	}

	pObj->GetInfo()->byOriID = pObj->GetInfo()->byDrawID;
	pObj->GetFrame()->fOriFrame = pObj->GetFrame()->fFrame;
}
void CFormation::SixteenDirCheckFunc(D3DXVECTOR3 _vDir, D3DXVECTOR3 _vGoalPos, CObj* pObj)
{
	float fCos = D3DXVec3Dot(&pObj->GetInfo()->vLook, &pObj->GetInfo()->vDir);
	pObj->GetInfo()->fAngle = acosf(fCos);

	if(pObj->GetInfo()->vPos.y < _vGoalPos.y)
	{
		pObj->GetInfo()->fAngle = D3DX_PI * 2 - pObj->GetInfo()->fAngle;
	}

	pObj->GetInfo()->fAngle = pObj->GetInfo()->fAngle * 180.f / D3DX_PI;

	if((pObj->GetInfo()->fAngle <= 360.0 && pObj->GetInfo()->fAngle > 348.75)
		|| (pObj->GetInfo()->fAngle >= 0.0 && pObj->GetInfo()->fAngle <= 11.25)) // RIGHT
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_RIGHT; 
	}
	if(pObj->GetInfo()->fAngle <= 33.75 && pObj->GetInfo()->fAngle > 11.25) // UP_R1
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_UP_R1;
	}
	if(pObj->GetInfo()->fAngle <= 56.25 && pObj->GetInfo()->fAngle > 33.75) // UP_R2
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_UP_R2;
	}
	if(pObj->GetInfo()->fAngle <= 78.75 && pObj->GetInfo()->fAngle > 56.25) // UP_R3
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_UP_R3;
	}
	if(pObj->GetInfo()->fAngle <= 101.25 && pObj->GetInfo()->fAngle > 78.75) // UP
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_UP;
	}
	if(pObj->GetInfo()->fAngle <= 123.75 && pObj->GetInfo()->fAngle > 101.25) // UP_L3
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_UP_L3;
	}
	if(pObj->GetInfo()->fAngle <= 146.25 && pObj->GetInfo()->fAngle > 123.75) // UP_L2
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_UP_L2;
	}
	if(pObj->GetInfo()->fAngle <= 168.75 && pObj->GetInfo()->fAngle > 146.25) // UP_L1
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_UP_L1;
	}
	if(pObj->GetInfo()->fAngle <= 191.25 && pObj->GetInfo()->fAngle > 168.75) // LEFT
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_LEFT;
	}
	if(pObj->GetInfo()->fAngle <= 213.75 && pObj->GetInfo()->fAngle > 191.25) // DOWN_L1
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_DOWN_L1;
	}
	if(pObj->GetInfo()->fAngle <= 236.25 && pObj->GetInfo()->fAngle > 213.75) // DOWN_L2
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_DOWN_L2;
	}
	if(pObj->GetInfo()->fAngle <= 258.75 && pObj->GetInfo()->fAngle > 236.25) // DOWN_L3
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_DOWN_L3;
	}
	if(pObj->GetInfo()->fAngle <= 281.25 && pObj->GetInfo()->fAngle > 258.75) // DOWN
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_DOWN;
	}
	if(pObj->GetInfo()->fAngle <= 303.75 && pObj->GetInfo()->fAngle > 281.25) // DOWN_R3
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_DOWN_R3;
	}
	if(pObj->GetInfo()->fAngle <= 326.25 && pObj->GetInfo()->fAngle > 303.75) // DOWN_R2
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_DOWN_R2;
	}
	if(pObj->GetInfo()->fAngle <= 348.75 && pObj->GetInfo()->fAngle > 326.25) // DOWN_R1
	{
		pObj->GetInfo()->m_eSixteenDirType = SIXTEEN_DIR_DOWN_R1;
	}
}
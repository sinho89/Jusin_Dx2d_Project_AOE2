#include "StdAfx.h"
#include "Cannon.h"
#include "TextureMgr.h"
#include "TImeMgr.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "CannonBoom.h"
#include "TileMgr.h"
#include "SoundMgr.h"
CCannon::CCannon(void)
{
}

CCannon::CCannon(CObj*	pUnit, CObj*	pTargetUnit, eSIXTEEN_DIRECTION_TYPE	_eType)
{
	m_pUnit = pUnit;
	m_pTarget = pTargetUnit;
	//m_vMovePoint = pTargetUnit->GetInfo()->vPos;
	m_tInfo.vPos = pUnit->GetInfo()->vPos;

	switch(_eType)
	{
	case SIXTEEN_DIR_DOWN:
		m_tInfo.vPos.y += 45;
		break;
	case SIXTEEN_DIR_UP:
		m_tInfo.vPos.y -= 45;
		break;
	case SIXTEEN_DIR_LEFT:
		m_tInfo.vPos.x -= 80;
		break;
	case SIXTEEN_DIR_RIGHT:
		m_tInfo.vPos.x += 80;
		break;
	case SIXTEEN_DIR_UP_R1:
		m_tInfo.vPos.x += 60;
		m_tInfo.vPos.y -= 10;
		break;
	case SIXTEEN_DIR_UP_R2:
		m_tInfo.vPos.x += 40;
		m_tInfo.vPos.y -= 20;
		break;
	case SIXTEEN_DIR_UP_R3:
		m_tInfo.vPos.x += 20;
		m_tInfo.vPos.y -= 30;
		break;
	case SIXTEEN_DIR_UP_L1:
		m_tInfo.vPos.x -= 60;
		m_tInfo.vPos.y -= 10;
		break;
	case SIXTEEN_DIR_UP_L2:
		m_tInfo.vPos.x -= 40;
		m_tInfo.vPos.y -= 20;
		break;
	case SIXTEEN_DIR_UP_L3:
		m_tInfo.vPos.x -= 20;
		m_tInfo.vPos.y -= 30;
		break;
	case SIXTEEN_DIR_DOWN_R1:
		m_tInfo.vPos.x += 60;
		m_tInfo.vPos.y += 10;
		break;
	case SIXTEEN_DIR_DOWN_R2:
		m_tInfo.vPos.x += 40;
		m_tInfo.vPos.y += 20;
		break;
	case SIXTEEN_DIR_DOWN_R3:
		m_tInfo.vPos.x += 20;
		m_tInfo.vPos.y += 30;
		break;
	case SIXTEEN_DIR_DOWN_L1:
		m_tInfo.vPos.x -= 60;
		m_tInfo.vPos.y += 10;
		break;
	case SIXTEEN_DIR_DOWN_L2:
		m_tInfo.vPos.x -= 40;
		m_tInfo.vPos.y += 20;
		break;
	case SIXTEEN_DIR_DOWN_L3:
		m_tInfo.vPos.x -= 20;
		m_tInfo.vPos.y += 30;
		break;
	}
	m_vShadowPos = m_tInfo.vPos;
	m_vNextPos = m_tInfo.vPos;

	m_vCurvePos[0] = m_tInfo.vPos;
	m_vCurvePos[1] = D3DXVECTOR3((m_tInfo.vPos.x + pTargetUnit->GetInfo()->vPos.x)*0.5f, (m_tInfo.vPos.y + pTargetUnit->GetInfo()->vPos.y) * 0.5f - 125.f, 0.f);
	m_vCurvePos[2] = pTargetUnit->GetInfo()->vPos;

	m_vLastPos = pTargetUnit->GetInfo()->vPos;


	CSoundMgr::GetInstance()->CannonStartSound(L"CannonStart.wav");
}

CCannon::~CCannon(void)
{
}

HRESULT CCannon::Initialize( void )
{
	m_TexArrow = CTextureMgr::GetInstance()->GetTexture(L"Stone", L"Stone", 0);

	m_fAngle = 0.f;
	m_fTime	 = 0.f;

	return S_OK;
}

int CCannon::Update( void )
{
	if(m_pTarget->GetInfo()->bDeath == true || m_pUnit->GetInfo()->bDeath == true || m_pTarget->GetInfo()->bBoom == true)
	{
		m_tInfo.bAlive = false;
		return 0;
	}

	if(m_pTarget->GetInfo()->bAlive == false || (m_pTarget->GetInfo()->iHp <= 0))
	{
		m_tInfo.bAlive = false;
		return 0;
	}

	if(m_fTime >= 1)
	{
		float fX = m_pTarget->GetInfo()->vPos.x - m_tInfo.vPos.x;
		float fY = m_pTarget->GetInfo()->vPos.y - m_tInfo.vPos.y;
		float fDest = sqrt(fX * fX + fY * fY);

		if(fDest < 50)
		{
			if(m_pUnit->GetInfo()->m_ePlayerType == PT_ENEMY)
			{
				if(CObj::m_bWarStart == false)
					CSoundMgr::GetInstance()->WarStart(L"WarStart2.wav");

				CObj::m_bWarStart = true;

			}
			m_pTarget->GetInfo()->iHp -= m_pUnit->GetInfo()->iAtt;
			CObjMgr::GetInstance()->AddObject(L"CannonBoom", SORT_NORMAL, CFactory<CCannonBoom>::CreateObject(m_vLastPos, true));
		}
		else
		{
			int iIndex = CTileMgr::GetInstance()->GetTileIndex(m_vLastPos);
			if(CTileMgr::GetInstance()->GetTile()[iIndex]->m_GroundType == GT_SEA)
				CObjMgr::GetInstance()->AddObject(L"CannonBoom", SORT_NORMAL, CFactory<CCannonBoom>::CreateObject(m_vLastPos, false));
			else 
				CObjMgr::GetInstance()->AddObject(L"CannonBoom", SORT_NORMAL, CFactory<CCannonBoom>::CreateObject(m_vLastPos, true));
		}
		m_tInfo.bAlive = false;

	}
	MoveArrow();

	D3DXMATRIX	matTrans;
	D3DXMATRIX	matScale;
	D3DXMATRIX	matRot;
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRot);


	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CObj::m_vScroll.x, m_tInfo.vPos.y + CObj::m_vScroll.y, m_tInfo.vPos.z);
	D3DXMatrixRotationZ(&matRot, m_fAngle);
	m_tInfo.matWorld = matScale * matRot * matTrans;

	return 0;
}

void CCannon::Render( void )
{
	int fX = (int)m_TexArrow->ImgInfo.Width / 2;
	int fY = (int)m_TexArrow->ImgInfo.Height / 2;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(m_TexArrow->pTexture, NULL, 
		&D3DXVECTOR3((float)fX, (float)fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CCannon::Release( void )
{

}

void CCannon::MoveArrow(void)
{
	m_tInfo.vPos = m_vNextPos;

	m_fTime += 0.25f * GETTIME;

	m_vCurvePos[1] = D3DXVECTOR3((m_vCurvePos[0].x + m_vLastPos.x) * 0.5f, (m_vCurvePos[0].y + m_vLastPos.y) * 0.5f - 100.f, 0.f);
	m_vCurvePos[2] = m_vLastPos;

	m_vNextPos.x = pow((1 - m_fTime), 2) * m_vCurvePos[0].x + 
		2 * m_fTime * (1 - m_fTime) * m_vCurvePos[1].x + 
		pow(m_fTime, 2) * m_vCurvePos[2].x;

	m_vNextPos.y = pow((1 - m_fTime), 2) * m_vCurvePos[0].y + 
		1.5 * m_fTime * (1 - m_fTime) * m_vCurvePos[1].y + 
		pow(m_fTime, 2) * m_vCurvePos[2].y;

	D3DXVec3Subtract(&m_tInfo.vDir, &m_vNextPos, &m_tInfo.vPos);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	float fTheta = atan2f(m_tInfo.vDir.y, m_tInfo.vDir.x);
	m_fAngle = fTheta + D3DX_PI;
}
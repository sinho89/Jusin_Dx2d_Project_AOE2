#include "StdAfx.h"
#include "Mouse.h"
#include "MouseMgr.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"
#include "ButtonMgr.h"
#include "GroupMgr.h"
#include "TImeMgr.h"

CMouse::CMouse(void)
:m_bDrag(false)
{
	memset(&m_rcUnitColl, 0, sizeof(RECT));
}

CMouse::~CMouse(void)
{
}

HRESULT CMouse::Initialize( void )
{
	for(int i = 0; i < 19; ++i)
		MouseTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Mouse", L"Mouse", i);
	for(int i = 0; i < 6; ++i)
		PointTex[i] = CTextureMgr::GetInstance()->GetTexture(L"PointIcon", L"PointIcon", i);
	for(int i = 0; i < 9; ++i)
		FlagTex[i] = CTextureMgr::GetInstance()->GetTexture(L"Flag", L"Flag", i);

	
	for(int i = 0; i < 5; ++i)
		m_vDrawBox[i] = D3DXVECTOR2(0.f, 0.f);

	m_tInfo.bAlive = true;
	m_bDrag = false;
	m_tInfo.bMove = false;
	m_tInfo.bRelly = false;
	m_tInfo.m_eObjType = OT_MOUSE;

	m_tFrame = FRAME(0.f, 10.f, 5.f, 0.f);
	m_tRelleyFrame = FRAME(0.f, 10.f, 8.f, 0.f);
	m_tInfo.byDrawID = 0;
	m_tInfo.vGoalPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tInfo.vWayPos = D3DXVECTOR3(0.f, 0.f, 0.f);

	return S_OK;
}

int CMouse::Update( void )
{
	/*if(!CCollisionMgr::GetInstance()->SelectUnit())
		int iA = 10;*/

	if(m_tInfo.bMove == true)
	{
		m_tFrame.fFrame += m_tFrame.fCount * GETTIME;
		if(m_tFrame.fFrame > m_tFrame.fMax)
		{
			m_tInfo.bMove = false;
			m_tFrame.fFrame = m_tFrame.fOriFrame;
		}
	}

	if(m_tInfo.bRelly == true)
	{
		m_tRelleyFrame.fFrame += m_tRelleyFrame.fCount * GETTIME;
		if(m_tRelleyFrame.fFrame > m_tRelleyFrame.fMax)
		{
			m_tInfo.bRelly = false;
			m_tRelleyFrame.fFrame = m_tRelleyFrame.fOriFrame;
		}
	}

	MouseDragFunc();

	ShowCursor(false);
	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;


	return 0;
}

void CMouse::Render( void )
{
	if(m_bDrag)
	{
		CDevice::GetInstance()->Render_End();
		CDevice::GetInstance()->Render_Begin();

		CDevice::GetInstance()->GetLine()->Draw(m_vDrawBox, 5, D3DCOLOR_XRGB(255,255,255));
			
		CDevice::GetInstance()->Render_End();
		CDevice::GetInstance()->Render_Begin();
	}

	if(m_tInfo.bMove == true)
	{
		if(PointTex[int(m_tFrame.fFrame)] == NULL)
			return;

		float fX = PointTex[int(m_tFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = PointTex[int(m_tFrame.fFrame)]->ImgInfo.Height / 2.f;

		D3DXMATRIX	matTrans;
		D3DXMatrixTranslation(&matTrans, m_tInfo.vGoalPos.x + CObj::m_vScroll.x, m_tInfo.vGoalPos.y + CObj::m_vScroll.y, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(PointTex[int(m_tFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(m_tInfo.bRelly == true)
	{
		if(FlagTex[int(m_tRelleyFrame.fFrame)] == NULL)
			return;

		float fX = FlagTex[int(m_tRelleyFrame.fFrame)]->ImgInfo.Width / 2.f;
		float fY = FlagTex[int(m_tRelleyFrame.fFrame)]->ImgInfo.Height / 2.f;

		D3DXMATRIX	matTrans;
		D3DXMatrixTranslation(&matTrans, m_tInfo.vWayPos.x + CObj::m_vScroll.x, m_tInfo.vWayPos.y + CObj::m_vScroll.y, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(FlagTex[int(m_tRelleyFrame.fFrame)]->pTexture, 
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if(MouseTex[m_tInfo.byDrawID] == NULL)
		return;

	float fX = MouseTex[m_tInfo.byDrawID]->ImgInfo.Width / 2.f - 13;
	float fY = MouseTex[m_tInfo.byDrawID]->ImgInfo.Height / 2.f - 16;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(MouseTex[m_tInfo.byDrawID]->pTexture, 
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	
}

void CMouse::Release( void )
{
	
}

void CMouse::MouseDragFunc()
{

	m_tInfo.vPos = CMouseMgr::GetMousePos();

	if(KEY_DOWN(VK_LBUTTON) && m_tInfo.vPos.y < 450)
	{
		if(m_bDrag == false)
			m_vDrawBox[0] = D3DXVECTOR2(m_tInfo.vPos.x, m_tInfo.vPos.y);

		m_bDrag = true;

		m_vDrawBox[1] = D3DXVECTOR2(m_tInfo.vPos.x , m_vDrawBox[0].y);
		m_vDrawBox[2] = D3DXVECTOR2(m_tInfo.vPos.x , m_tInfo.vPos.y);
		m_vDrawBox[3] = D3DXVECTOR2(m_vDrawBox[0].x, m_tInfo.vPos.y);
		m_vDrawBox[4] = D3DXVECTOR2(m_vDrawBox[0].x, m_vDrawBox[0].y);
	}

	if(m_bDrag == true && KEY_UP(VK_LBUTTON))
	{
		m_bDrag = false;

		RECT rcCollBox;

		rcCollBox.left = m_vDrawBox[0].x - CObj::m_vScroll.x;
		rcCollBox.top =	m_vDrawBox[1].y - CObj::m_vScroll.y;
		rcCollBox.right =	m_vDrawBox[2].x - CObj::m_vScroll.x;
		rcCollBox.bottom =	m_vDrawBox[3].y - CObj::m_vScroll.y;
	

		if(!CCollisionMgr::GetInstance()->SetGroupUnit(rcCollBox))
		{
			//CButtonMgr::GetInstance()->ClearButton();
		}


		for(int i = 0; i < 5; ++i)
			m_vDrawBox[i] = D3DXVECTOR2(0.f, 0.f);
	}


}
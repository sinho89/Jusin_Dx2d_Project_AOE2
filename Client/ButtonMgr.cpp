#include "StdAfx.h"
#include "ButtonMgr.h"
#include "Obj.h"
IMPLEMENT_SINGLETON(CButtonMgr)

CButtonMgr::CButtonMgr(void)
{
}

CButtonMgr::~CButtonMgr(void)
{
	Release();
}

int CButtonMgr::GetButtonIndex( const D3DXVECTOR3& vPos )
{
	POINT ptMouse;

	ptMouse.x = vPos.x;
	ptMouse.y = vPos.y;

	for(size_t i = 0; i < m_ButtonMap.size(); ++i)
	{
		RECT rcButton = {
			m_ButtonMap[i]->GetInfo()->vPos.x - 18.f,
			m_ButtonMap[i]->GetInfo()->vPos.y - 18.f,
			m_ButtonMap[i]->GetInfo()->vPos.x + 18.f,
			m_ButtonMap[i]->GetInfo()->vPos.y + 18.f
		};

		if(PtInRect(&rcButton, ptMouse))
		{
			return i;
		}
	}

	return -1;
}

bool CButtonMgr::Picking( const D3DXVECTOR3& vPos, const int& iIndex )
{
	return 0;
}

void CButtonMgr::AddButton( CObj* pObj, int iIndex )
{
	m_ButtonMap.insert(make_pair(iIndex, pObj));
}

void CButtonMgr::Release()
{
	unordered_map<int, CObj*>::iterator iter = m_ButtonMap.begin();
	unordered_map<int, CObj*>::iterator iter_end = m_ButtonMap.end();

	for(iter; iter != iter_end; ++iter)
		SAFE_DELETE(iter->second);
	m_ButtonMap.clear();
}

void CButtonMgr::Update()
{
	unordered_map<int, CObj*>::iterator iter = CButtonMgr::GetInstance()->GetButtonMap().begin();
	unordered_map<int, CObj*>::iterator iter_end = CButtonMgr::GetInstance()->GetButtonMap().end();

	for(; iter != iter_end; ++iter)
		iter->second->Update();
}

void CButtonMgr::Render()
{
	unordered_map<int, CObj*>::iterator iter = CButtonMgr::GetInstance()->GetButtonMap().begin();
	unordered_map<int, CObj*>::iterator iter_end = CButtonMgr::GetInstance()->GetButtonMap().end();

	for(; iter != iter_end; ++iter)
		iter->second->Render();
}

void CButtonMgr::ClearButton()
{
	unordered_map<int, CObj*>::iterator iter = CButtonMgr::GetInstance()->GetButtonMap().begin();
	unordered_map<int, CObj*>::iterator iter_end = CButtonMgr::GetInstance()->GetButtonMap().end();

	for(; iter != iter_end; ++iter)
	{
		iter->second->GetInfo()->bRenderCheck = 0;
		iter->second->GetInfo()->m_eControlDrawType = CDT_end;
	}
}

void CButtonMgr::PortSource()
{
	unordered_map<int, CObj*>::iterator iter = CButtonMgr::GetInstance()->GetButtonMap().begin();
	unordered_map<int, CObj*>::iterator iter_end = CButtonMgr::GetInstance()->GetButtonMap().end();

	for(; iter != iter_end; ++iter)
	{
		iter->second->GetInfo()->bRenderCheck = false;
		if(iter->second->GetInfo()->bPortButtonChange == false)
			iter->second->GetInfo()->bPortButtonChange = true;
		else if(iter->second->GetInfo()->bPortButtonChange == true)
			iter->second->GetInfo()->bPortButtonChange = false;
	}
}

void CButtonMgr::ButtonChange(eCONTROL_DRAW_TYPE _eType)
{
	unordered_map<int, CObj*>::iterator iter = CButtonMgr::GetInstance()->GetButtonMap().begin();
	unordered_map<int, CObj*>::iterator iter_end = CButtonMgr::GetInstance()->GetButtonMap().end();

	for(; iter != iter_end; ++iter)
	{
		iter->second->GetInfo()->m_eControlDrawType = _eType;
		iter->second->GetInfo()->bRenderCheck = 0;
	}
}



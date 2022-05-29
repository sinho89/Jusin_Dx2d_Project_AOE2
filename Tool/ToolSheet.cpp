// ToolSheet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ToolSheet.h"


// CToolSheet

IMPLEMENT_DYNAMIC(CToolSheet, CPropertySheet)

CToolSheet::CToolSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CToolSheet::CToolSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}
CToolSheet::CToolSheet(void)
{

	AddPage(&m_TilePage);
	AddPage(&m_ResourcePage);
	AddPage(&m_UnitPage);
	AddPage(&m_BuildPage);

}

CToolSheet::~CToolSheet()
{
}


BEGIN_MESSAGE_MAP(CToolSheet, CPropertySheet)
END_MESSAGE_MAP()


// CToolSheet 메시지 처리기입니다.

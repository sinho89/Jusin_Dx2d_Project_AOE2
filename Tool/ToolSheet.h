#pragma once



// CToolSheet
#include "TilePage.h"
#include "ResourcePage.h"
#include "UnitPage.h"
#include "BuildPage.h"

class CToolSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CToolSheet)
public:
	CTilePage		m_TilePage;
	CResourcePage	m_ResourcePage;
	CUnitPage		m_UnitPage;
	CBuildPage		m_BuildPage;
public:
	CToolSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CToolSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CToolSheet();
	virtual ~CToolSheet();

protected:
	DECLARE_MESSAGE_MAP()
};



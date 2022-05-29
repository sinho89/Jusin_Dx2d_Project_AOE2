// ToolPopUp.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ToolPopUp.h"
#include "ToolSheet.h"


// CToolPopUp ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CToolPopUp, CDialog)

CToolPopUp::CToolPopUp(CWnd* pParent /*=NULL*/)
	: CDialog(CToolPopUp::IDD, pParent)
{
	m_pSheet = NULL;
}

CToolPopUp::~CToolPopUp()
{
	if(m_pSheet != NULL)
	{
		delete m_pSheet;
		m_pSheet = NULL;
	}
}

void CToolPopUp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolPopUp, CDialog)
END_MESSAGE_MAP()


// CToolPopUp �޽��� ó�����Դϴ�.

BOOL CToolPopUp::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_pSheet == NULL)
	{
		m_pSheet = new CToolSheet;
	}

	if(m_pSheet->GetSafeHwnd() == NULL)
		m_pSheet->Create(this, WS_CHILD | WS_VISIBLE);

	m_pSheet->MoveWindow(0, 0, 500, 400);
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

// ToolPopUp.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ToolPopUp.h"
#include "ToolSheet.h"


// CToolPopUp 대화 상자입니다.

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


// CToolPopUp 메시지 처리기입니다.

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
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

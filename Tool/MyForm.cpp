// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(CMyForm::IDD)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_MAPTOOL_BTN, &CMyForm::OnBnClickedMaptoolBtn)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


// CMyForm 메시지 처리기입니다.


void CMyForm::OnBnClickedMaptoolBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_ToolPopUp.GetSafeHwnd() == NULL)
	{
		m_ToolPopUp.Create(IDD_TOOLPOPUP);
	}

	m_ToolPopUp.ShowWindow(SW_SHOW);
}

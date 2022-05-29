#pragma once


// CToolPopUp 대화 상자입니다.

class CToolSheet;
class CToolPopUp : public CDialog
{
	DECLARE_DYNAMIC(CToolPopUp)
public:
	CToolSheet*		m_pSheet;
public:
	CToolPopUp(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CToolPopUp();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TOOLPOPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

#pragma once


// CToolPopUp ��ȭ �����Դϴ�.

class CToolSheet;
class CToolPopUp : public CDialog
{
	DECLARE_DYNAMIC(CToolPopUp)
public:
	CToolSheet*		m_pSheet;
public:
	CToolPopUp(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CToolPopUp();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TOOLPOPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

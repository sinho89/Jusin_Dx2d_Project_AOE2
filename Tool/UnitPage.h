#pragma once
#include "afxwin.h"


// CUnitPage ��ȭ �����Դϴ�.

class CUnitPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CUnitPage)

private:
	map<CString, CImage*>		m_MapPngImage;
public:
	int					m_iDrawID;
	wstring				m_wstrObjKey;
	wstring				m_wstrStateKey;
public:
	CUnitPage();
	virtual ~CUnitPage();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_UNITPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_UnitList;
	CStatic m_UnitPicture;
	afx_msg void OnLbnSelchangeUnitList();
	afx_msg void OnBnClickedUnitSave();
	afx_msg void OnBnClickedUnitLoad();
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
};

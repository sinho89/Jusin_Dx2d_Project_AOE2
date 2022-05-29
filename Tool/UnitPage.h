#pragma once
#include "afxwin.h"


// CUnitPage 대화 상자입니다.

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

// 대화 상자 데이터입니다.
	enum { IDD = IDD_UNITPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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

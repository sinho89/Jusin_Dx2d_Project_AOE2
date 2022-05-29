#pragma once
#include "afxwin.h"


// CBuildPage 대화 상자입니다.

class CBuildPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CBuildPage)

private:
	map<CString, CImage*>		m_MapPngImage;
public:
	int					m_iDrawID;
	wstring				m_wstrObjKey;
public:
	CBuildPage();
	virtual ~CBuildPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BUILDPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_BuildList;
	CStatic m_BuildPicture;
	afx_msg void OnLbnSelchangeBuildList();
	afx_msg void OnBnClickedBuildSave();
	afx_msg void OnBnClickedBuildLoad();
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
};

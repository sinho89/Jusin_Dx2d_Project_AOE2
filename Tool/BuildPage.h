#pragma once
#include "afxwin.h"


// CBuildPage ��ȭ �����Դϴ�.

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

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BUILDPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

#pragma once
#include "afxwin.h"


// CResourcePage ��ȭ �����Դϴ�.

class CResourcePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CResourcePage)

private:
	map<CString, CImage*>		m_MapPngImage;
public:
	int					m_iDrawID;
	wstring				m_wstrObjKey;
public:
	CResourcePage();
	virtual ~CResourcePage();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RESOURCEPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ResourceList;
	CStatic m_ResourcePicture;
	afx_msg void OnLbnSelchangeResourceList();
	afx_msg void OnBnClickedResourceSave();
	afx_msg void OnBnClickedResourceLoad();
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
};

#pragma once
#include "afxwin.h"


// CTilePage ��ȭ �����Դϴ�.

class CTilePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTilePage)

private:
	map<CString, CImage*>		m_MapPngImage;
public:
	int		m_iDrawID;
public:
	CTilePage();
	virtual ~CTilePage();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TILEPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
	afx_msg void OnLbnSelchangeTileList();
	afx_msg void OnBnClickedTilesaveBtn();
	afx_msg void OnBnClickedTileloadBtn();
	CListBox m_TileList;
	CStatic m_TilePicture;
};

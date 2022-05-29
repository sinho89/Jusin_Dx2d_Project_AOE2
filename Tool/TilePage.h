#pragma once
#include "afxwin.h"


// CTilePage 대화 상자입니다.

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

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TILEPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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

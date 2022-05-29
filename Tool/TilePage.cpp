// TilePage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "TilePage.h"
#include "MainFrm.h"
#include "MiniView.h"
#include "ToolView.h"
#include "BackGround.h"


// CTilePage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTilePage, CPropertyPage)

CTilePage::CTilePage()
	: CPropertyPage(CTilePage::IDD)
{
	m_iDrawID = 0;

}

CTilePage::~CTilePage()
{
	map<CString, CImage*>::iterator iter = m_MapPngImage.begin();
	for(iter; iter != m_MapPngImage.end(); ++iter)
	{
		delete iter->second;
	}

	m_MapPngImage.clear();
}

void CTilePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TILE_LIST, m_TileList);
	DDX_Control(pDX, IDC_TILE_PICTURE, m_TilePicture);
}


BEGIN_MESSAGE_MAP(CTilePage, CPropertyPage)
	ON_LBN_SELCHANGE(IDC_TILE_LIST, &CTilePage::OnLbnSelchangeTileList)
	ON_BN_CLICKED(IDC_TILESAVE_BTN, &CTilePage::OnBnClickedTilesaveBtn)
	ON_BN_CLICKED(IDC_TILELOAD_BTN, &CTilePage::OnBnClickedTileloadBtn)
END_MESSAGE_MAP()


// CTilePage 메시지 처리기입니다.

BOOL CTilePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	TCHAR	szForderPath[MAX_PATH] = L"../Texture/Tile";
	char szPath[MAX_PATH] = "";

	WideCharToMultiByte(CP_ACP, NULL,
		szForderPath, -1, szPath, MAX_PATH, NULL, FALSE);

	_finddata_t		fd;
	long			handle;
	int				iResult = 1;

	//모든 파일을 의미하는 *.* 로 하자...
	strcat_s(szPath, "\\*.*");
	handle = _findfirst(szPath, &fd);

	//파일을 찾아서 핸들이 없으면...
	//그냥 함수 종료 시켜라...
	if(handle == -1)
		return FALSE;

	//일단 결과가 -1이 아닐 때까지..
	//파일이 없으면 -1 이 나옴...
	while(iResult != -1)
	{
		//폴더 경로를 받은 다음에..
		//"\\" 을 붙이고
		//파일 이름을 합성한다..
		CString	strPath = szForderPath;
		strPath += L"\\";
		strPath += fd.name;

		//이미지의 이름만 담을 변수
		CString strImageName;
		//경로로부터 파일 이름을 얻어오는 함수...
		strImageName = PathFindFileName(strPath);
		//확장자 자르기...
		PathRemoveExtension((LPWSTR)strImageName.operator LPCWSTR());


		///////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		//맵에다가 이미지랑 이름을 넣어놔야지...
		map<CString, CImage*>::iterator iter = m_MapPngImage.find(strImageName);
		if(iter == m_MapPngImage.end())
		{
			CImage*	pPngImage = new CImage;

			if(pPngImage->Load(strPath) == 0)
			{
				m_MapPngImage.insert(make_pair(strImageName, pPngImage));
				m_TileList.AddString(strImageName);
			}
			else
				delete pPngImage;

		}

		iResult = _findnext(handle, &fd);

	}
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
BOOL CTilePage::OnSetActive()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceTileOpenCheck = true;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceObjOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceUnitOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceBuildOpenCheck = false;

	return CPropertyPage::OnSetActive();
}

void CTilePage::OnLbnSelchangeTileList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString	strSelectName;

	int iSelNum = m_TileList.GetCurSel();
	m_TileList.GetText(iSelNum, strSelectName);

	map<CString, CImage*>::iterator iter = m_MapPngImage.find(strSelectName);

	if(iter == m_MapPngImage.end())
		return;

	m_TilePicture.SetBitmap(*iter->second);

	///////////////////////////m_iDrawID 에 값을 제대로 채워 줘야 겠다...
	int iSel = m_TileList.GetCurSel();

	strSelectName;
	m_TileList.GetText(iSel, strSelectName);

	int i = 0;
	for(i; i < strSelectName.GetLength(); ++i)
	{
		if(isdigit(strSelectName[i]) != 0)
			break;
	}

	//1인자의 인덱스부터 2인자의 인덱스까지 글자를 지우는 함수..
	strSelectName.Delete(0, i);

	//문자를 숫자로 바꿀 수 있다..
	m_iDrawID = _tstoi(strSelectName);

	UpdateData(FALSE);
}

void CTilePage::OnBnClickedTilesaveBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strPath = L"../Data/Tile.dat";

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame*		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CToolView*	pMainView = pMainFrame->m_pMainView;
	CBackGround*	pBackGround = pMainView->m_pBackGround;

	vector<TILE*>*	pVecTile = &pBackGround->m_vecTile;

	//세이브...

	DWORD	dwByte = 0;
	HANDLE	hFile = CreateFile(strPath, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL)
	{
		MSG_BOX(L"파일 개방 실패");
		return;
	}

	for(size_t i = 0; i < pVecTile->size(); ++i)
	{
		WriteFile(hFile, (*pVecTile)[i], sizeof(TILE), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MSG_BOX(L"타일 저장 성공!!");
}

void CTilePage::OnBnClickedTileloadBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame*		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CToolView*	pMainView = pMainFrame->m_pMainView;
	CMiniView*		pMiniView = pMainFrame->m_pMiniView;
	CBackGround*	pBackGround = pMainView->m_pBackGround;

	vector<TILE*>*	pVecTile = &pBackGround->m_vecTile;


	DWORD	dwByte = 0;

	CString strPathName = L"../Data/Tile.dat";

	HANDLE hFile = CreateFile(strPathName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	for(size_t i = 0; i < pVecTile->size(); ++i)
	{
		delete (*pVecTile)[i];
	}
	pVecTile->clear();

	while(true)
	{
		TILE*	pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);

		if(dwByte == 0)
		{
			delete pTile;
			break;
		}

		pVecTile->push_back(pTile);
	}
	CloseHandle(hFile);

	pMainView->Invalidate(FALSE);
	pMiniView->Invalidate(FALSE);
}

// TilePage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "TilePage.h"
#include "MainFrm.h"
#include "MiniView.h"
#include "ToolView.h"
#include "BackGround.h"


// CTilePage ��ȭ �����Դϴ�.

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


// CTilePage �޽��� ó�����Դϴ�.

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

	//��� ������ �ǹ��ϴ� *.* �� ����...
	strcat_s(szPath, "\\*.*");
	handle = _findfirst(szPath, &fd);

	//������ ã�Ƽ� �ڵ��� ������...
	//�׳� �Լ� ���� ���Ѷ�...
	if(handle == -1)
		return FALSE;

	//�ϴ� ����� -1�� �ƴ� ������..
	//������ ������ -1 �� ����...
	while(iResult != -1)
	{
		//���� ��θ� ���� ������..
		//"\\" �� ���̰�
		//���� �̸��� �ռ��Ѵ�..
		CString	strPath = szForderPath;
		strPath += L"\\";
		strPath += fd.name;

		//�̹����� �̸��� ���� ����
		CString strImageName;
		//��ηκ��� ���� �̸��� ������ �Լ�...
		strImageName = PathFindFileName(strPath);
		//Ȯ���� �ڸ���...
		PathRemoveExtension((LPWSTR)strImageName.operator LPCWSTR());


		///////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		//�ʿ��ٰ� �̹����� �̸��� �־������...
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
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
BOOL CTilePage::OnSetActive()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceTileOpenCheck = true;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceObjOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceUnitOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceBuildOpenCheck = false;

	return CPropertyPage::OnSetActive();
}

void CTilePage::OnLbnSelchangeTileList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString	strSelectName;

	int iSelNum = m_TileList.GetCurSel();
	m_TileList.GetText(iSelNum, strSelectName);

	map<CString, CImage*>::iterator iter = m_MapPngImage.find(strSelectName);

	if(iter == m_MapPngImage.end())
		return;

	m_TilePicture.SetBitmap(*iter->second);

	///////////////////////////m_iDrawID �� ���� ����� ä�� ��� �ڴ�...
	int iSel = m_TileList.GetCurSel();

	strSelectName;
	m_TileList.GetText(iSel, strSelectName);

	int i = 0;
	for(i; i < strSelectName.GetLength(); ++i)
	{
		if(isdigit(strSelectName[i]) != 0)
			break;
	}

	//1������ �ε������� 2������ �ε������� ���ڸ� ����� �Լ�..
	strSelectName.Delete(0, i);

	//���ڸ� ���ڷ� �ٲ� �� �ִ�..
	m_iDrawID = _tstoi(strSelectName);

	UpdateData(FALSE);
}

void CTilePage::OnBnClickedTilesaveBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strPath = L"../Data/Tile.dat";

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CToolView*	pMainView = pMainFrame->m_pMainView;
	CBackGround*	pBackGround = pMainView->m_pBackGround;

	vector<TILE*>*	pVecTile = &pBackGround->m_vecTile;

	//���̺�...

	DWORD	dwByte = 0;
	HANDLE	hFile = CreateFile(strPath, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL)
	{
		MSG_BOX(L"���� ���� ����");
		return;
	}

	for(size_t i = 0; i < pVecTile->size(); ++i)
	{
		WriteFile(hFile, (*pVecTile)[i], sizeof(TILE), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MSG_BOX(L"Ÿ�� ���� ����!!");
}

void CTilePage::OnBnClickedTileloadBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

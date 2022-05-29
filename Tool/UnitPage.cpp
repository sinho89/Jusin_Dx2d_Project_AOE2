// UnitPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitPage.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "MiniView.h"
#include "BackGround.h"

// CUnitPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitPage, CPropertyPage)

CUnitPage::CUnitPage()
	: CPropertyPage(CUnitPage::IDD)
{

}

CUnitPage::~CUnitPage()
{
	map<CString, CImage*>::iterator iter = m_MapPngImage.begin();
	for(iter; iter != m_MapPngImage.end(); ++iter)
	{
		delete iter->second;
	}

	m_MapPngImage.clear();
}

void CUnitPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UNIT_LIST, m_UnitList);
	DDX_Control(pDX, IDC_UNIT_PICTURE, m_UnitPicture);
}


BEGIN_MESSAGE_MAP(CUnitPage, CPropertyPage)
	ON_LBN_SELCHANGE(IDC_UNIT_LIST, &CUnitPage::OnLbnSelchangeUnitList)
	ON_BN_CLICKED(IDC_UNIT_SAVE, &CUnitPage::OnBnClickedUnitSave)
	ON_BN_CLICKED(IDC_UNIT_LOAD, &CUnitPage::OnBnClickedUnitLoad)
END_MESSAGE_MAP()


// CUnitPage 메시지 처리기입니다.

void CUnitPage::OnLbnSelchangeUnitList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString	strSelectName;

	int iSelNum = m_UnitList.GetCurSel();
	m_UnitList.GetText(iSelNum, strSelectName); // 이부분에 _ 짤라서 오브젝트키랑 드로우아이디 넣기

	PathRemoveExtension((LPWSTR)strSelectName.operator LPCWSTR());

	map<CString, CImage*>::iterator iter = m_MapPngImage.find(strSelectName);

	if(iter == m_MapPngImage.end())
		return;

	m_UnitPicture.SetBitmap(*iter->second);

	///////////////////////////m_iDrawID 에 값을 제대로 채워 줘야 겠다...
	int iSel = m_UnitList.GetCurSel();

	strSelectName;
	m_UnitList.GetText(iSel, strSelectName);

	int i = 0;
	for(i; i < strSelectName.GetLength(); ++i)
	{
		if(isdigit(strSelectName[i]) != 0)
			break;
	}
	int j = 0;
	for(j; j < strSelectName.GetLength(); ++j)
	{
		if(strSelectName[j] == '_')
			break;
	}
	int k = 0;
	int l = 0;
	for(k; k < strSelectName.GetLength(); ++k)
	{
		if(strSelectName[k] == '_')
			++l;
		if(l >= 2)
			break;
	}

	//1인자의 인덱스부터 2인자의 인덱스까지 글자를 지우는 함수..

	CString strObjTemp;
	CString strStateTemp;
	strObjTemp = strSelectName;
	strStateTemp = strSelectName;
	strSelectName.Delete(0, i);
	strObjTemp.Delete(j, strObjTemp.GetLength());
	strStateTemp.Delete(0,j + 1);
	strStateTemp.Delete(3,strObjTemp.GetLength());

	m_iDrawID = _tstoi(strSelectName);

	m_wstrObjKey = strObjTemp;
	m_wstrStateKey = strStateTemp;


	UpdateData(FALSE);
}

void CUnitPage::OnBnClickedUnitSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strPath = L"../Data/Unit.dat";

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame*		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CToolView*	pMainView = pMainFrame->m_pMainView;
	CBackGround*	pBackGround = pMainView->m_pBackGround;

	vector<INFO*>*	pVecUnit = &pBackGround->m_vecUnit;

	//세이브...

	DWORD	dwByte = 0;
	HANDLE	hFile = CreateFile(strPath, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL)
	{
		MSG_BOX(L"파일 개방 실패");
		return;
	}

	for(size_t i = 0; i < pVecUnit->size(); ++i)
	{
		WriteFile(hFile, (*pVecUnit)[i], sizeof(INFO), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MSG_BOX(L"유닛 저장 성공!!");
}

void CUnitPage::OnBnClickedUnitLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame*		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CToolView*	pMainView = pMainFrame->m_pMainView;
	CMiniView*		pMiniView = pMainFrame->m_pMiniView;
	CBackGround*	pBackGround = pMainView->m_pBackGround;

	vector<INFO*>*	pvecUnit = &pBackGround->m_vecUnit;


	DWORD	dwByte = 0;

	CString strPathName = L"../Data/Unit.dat";

	HANDLE hFile = CreateFile(strPathName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	for(size_t i = 0; i < pvecUnit->size(); ++i)
	{
		delete (*pvecUnit)[i];
	}
	pvecUnit->clear();

	while(true)
	{
		INFO*	pUnit = new INFO;

		ReadFile(hFile, pUnit, sizeof(INFO), &dwByte, NULL);

		if(dwByte == 0)
		{
			delete pUnit;
			break;
		}

		pvecUnit->push_back(pUnit);
	}
	CloseHandle(hFile);

	pMainView->Invalidate(FALSE);
	pMiniView->Invalidate(FALSE);
}

BOOL CUnitPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	TCHAR	szForderPath[2][MAX_PATH] = 
	{
		L"../Texture/Unit/Player/Male_Villager/STD"
		,L"../Texture/Unit/Player/Scout_Cavalry/1/STD/Img"
	};



	char szPath[MAX_PATH] = "";

	for(int i = 0; i < 2; ++i)
	{


		WideCharToMultiByte(CP_ACP, NULL,
			szForderPath[i], -1, szPath, MAX_PATH, NULL, FALSE);

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
			CString	strPath = szForderPath[i];
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
					m_UnitList.AddString(strImageName);
				}
				else
					delete pPngImage;

			}

			iResult = _findnext(handle, &fd);

		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CUnitPage::OnSetActive()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceTileOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceObjOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceUnitOpenCheck = true;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceBuildOpenCheck = false;

	return CPropertyPage::OnSetActive();
}

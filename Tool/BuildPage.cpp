// BuildPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "BuildPage.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "MiniView.h"
#include "BackGround.h"

// CBuildPage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBuildPage, CPropertyPage)

CBuildPage::CBuildPage()
	: CPropertyPage(CBuildPage::IDD)
{

}

CBuildPage::~CBuildPage()
{
	map<CString, CImage*>::iterator iter = m_MapPngImage.begin();
	for(iter; iter != m_MapPngImage.end(); ++iter)
	{
		delete iter->second;
	}

	m_MapPngImage.clear();
}

void CBuildPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUILD_LIST, m_BuildList);
	DDX_Control(pDX, IDC_BUILD_PICTURE, m_BuildPicture);
}


BEGIN_MESSAGE_MAP(CBuildPage, CPropertyPage)
	ON_LBN_SELCHANGE(IDC_BUILD_LIST, &CBuildPage::OnLbnSelchangeBuildList)
	ON_BN_CLICKED(IDC_BUILD_SAVE, &CBuildPage::OnBnClickedBuildSave)
	ON_BN_CLICKED(IDC_BUILD_LOAD, &CBuildPage::OnBnClickedBuildLoad)
END_MESSAGE_MAP()


// CBuildPage �޽��� ó�����Դϴ�.

void CBuildPage::OnLbnSelchangeBuildList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString	strSelectName;

	int iSelNum = m_BuildList.GetCurSel();
	m_BuildList.GetText(iSelNum, strSelectName); // �̺κп� _ ©�� ������ƮŰ�� ��ο���̵� �ֱ�

	PathRemoveExtension((LPWSTR)strSelectName.operator LPCWSTR());

	map<CString, CImage*>::iterator iter = m_MapPngImage.find(strSelectName);

	if(iter == m_MapPngImage.end())
		return;

	m_BuildPicture.SetBitmap(*iter->second);

	///////////////////////////m_iDrawID �� ���� ����� ä�� ��� �ڴ�...
	int iSel = m_BuildList.GetCurSel();

	strSelectName;
	m_BuildList.GetText(iSel, strSelectName);

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

	//1������ �ε������� 2������ �ε������� ���ڸ� ����� �Լ�..

	CString strTemp;
	strTemp = strSelectName;
	strSelectName.Delete(0, i);
	strTemp.Delete(j, strTemp.GetLength());

	m_iDrawID = _tstoi(strSelectName);

	m_wstrObjKey = strTemp;


	UpdateData(FALSE);
}

void CBuildPage::OnBnClickedBuildSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strPath = L"../Data/Build.dat";

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CToolView*	pMainView = pMainFrame->m_pMainView;
	CBackGround*	pBackGround = pMainView->m_pBackGround;

	vector<INFO*>*	pVecBuild = &pBackGround->m_vecBuild;

	//���̺�...

	DWORD	dwByte = 0;
	HANDLE	hFile = CreateFile(strPath, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL)
	{
		MSG_BOX(L"���� ���� ����");
		return;
	}

	for(size_t i = 0; i < pVecBuild->size(); ++i)
	{
		WriteFile(hFile, (*pVecBuild)[i], sizeof(INFO), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MSG_BOX(L"�ǹ� ���� ����!!");
}

void CBuildPage::OnBnClickedBuildLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CToolView*	pMainView = pMainFrame->m_pMainView;
	CMiniView*		pMiniView = pMainFrame->m_pMiniView;
	CBackGround*	pBackGround = pMainView->m_pBackGround;

	vector<INFO*>*	pVecBuild = &pBackGround->m_vecBuild;


	DWORD	dwByte = 0;

	CString strPathName = L"../Data/Build.dat";

	HANDLE hFile = CreateFile(strPathName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	for(size_t i = 0; i < pVecBuild->size(); ++i)
	{
		delete (*pVecBuild)[i];
	}
	pVecBuild->clear();

	while(true)
	{
		INFO*	pBuild = new INFO;

		ReadFile(hFile, pBuild, sizeof(INFO), &dwByte, NULL);

		if(dwByte == 0)
		{
			delete pBuild;
			break;
		}

		pVecBuild->push_back(pBuild);
	}
	CloseHandle(hFile);

	pMainView->Invalidate(FALSE);
	pMiniView->Invalidate(FALSE);
}

BOOL CBuildPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	TCHAR	szForderPath[2][MAX_PATH] = 
	{
		L"../Texture/Player_Age/Dark_Age"
		,L"../Texture/Enemy_Age/Dark_Age"
	};



	char szPath[MAX_PATH] = "";

	for(int i = 0; i < 2; ++i)
	{


		WideCharToMultiByte(CP_ACP, NULL,
			szForderPath[i], -1, szPath, MAX_PATH, NULL, FALSE);

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
			CString	strPath = szForderPath[i];
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
					m_BuildList.AddString(strImageName);
				}
				else
					delete pPngImage;

			}

			iResult = _findnext(handle, &fd);

		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.

}

BOOL CBuildPage::OnSetActive()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceTileOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceObjOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceUnitOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceBuildOpenCheck = true;


	return CPropertyPage::OnSetActive();
}

// ResourcePage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ResourcePage.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "BackGround.h"
#include "MiniView.h"

// CResourcePage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CResourcePage, CPropertyPage)

CResourcePage::CResourcePage()
	: CPropertyPage(CResourcePage::IDD)
{
	m_iDrawID = 0;
}

CResourcePage::~CResourcePage()
{
	map<CString, CImage*>::iterator iter = m_MapPngImage.begin();
	for(iter; iter != m_MapPngImage.end(); ++iter)
	{
		delete iter->second;
	}

	m_MapPngImage.clear();
}

void CResourcePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESOURCE_LIST, m_ResourceList);
	DDX_Control(pDX, IDC_RESOURCE_PICTURE, m_ResourcePicture);
}


BEGIN_MESSAGE_MAP(CResourcePage, CPropertyPage)
	ON_LBN_SELCHANGE(IDC_RESOURCE_LIST, &CResourcePage::OnLbnSelchangeResourceList)
	ON_BN_CLICKED(IDC_RESOURCE_SAVE, &CResourcePage::OnBnClickedResourceSave)
	ON_BN_CLICKED(IDC_RESOURCE_LOAD, &CResourcePage::OnBnClickedResourceLoad)
END_MESSAGE_MAP()


// CResourcePage �޽��� ó�����Դϴ�.

void CResourcePage::OnLbnSelchangeResourceList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString	strSelectName;

	int iSelNum = m_ResourceList.GetCurSel();
	m_ResourceList.GetText(iSelNum, strSelectName); // �̺κп� _ ©�� ������ƮŰ�� ��ο���̵� �ֱ�

	PathRemoveExtension((LPWSTR)strSelectName.operator LPCWSTR());

	map<CString, CImage*>::iterator iter = m_MapPngImage.find(strSelectName);

	if(iter == m_MapPngImage.end())
		return;

	m_ResourcePicture.SetBitmap(*iter->second);

	///////////////////////////m_iDrawID �� ���� ����� ä�� ��� �ڴ�...
	int iSel = m_ResourceList.GetCurSel();

	strSelectName;
	m_ResourceList.GetText(iSel, strSelectName);

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


	//���ڸ� ���ڷ� �ٲ� �� �ִ�..

	UpdateData(FALSE);
}

void CResourcePage::OnBnClickedResourceSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strPath = L"../Data/Resource.dat";

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CToolView*	pMainView = pMainFrame->m_pMainView;
	CBackGround*	pBackGround = pMainView->m_pBackGround;

	vector<INFO*>*	pVecResource = &pBackGround->m_vecResource;

	//���̺�...

	DWORD	dwByte = 0;
	HANDLE	hFile = CreateFile(strPath, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL)
	{
		MSG_BOX(L"���� ���� ����");
		return;
	}

	for(size_t i = 0; i < pVecResource->size(); ++i)
	{
		WriteFile(hFile, (*pVecResource)[i], sizeof(INFO), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MSG_BOX(L"������Ʈ ���� ����!!");
}

void CResourcePage::OnBnClickedResourceLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CToolView*	pMainView = pMainFrame->m_pMainView;
	CMiniView*		pMiniView = pMainFrame->m_pMiniView;
	CBackGround*	pBackGround = pMainView->m_pBackGround;

	vector<INFO*>*	pVecResource = &pBackGround->m_vecResource;


	DWORD	dwByte = 0;

	CString strPathName = L"../Data/Resource.dat";

	HANDLE hFile = CreateFile(strPathName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	for(size_t i = 0; i < pVecResource->size(); ++i)
	{
		delete (*pVecResource)[i];
	}
	pVecResource->clear();

	while(true)
	{
		INFO*	pResource = new INFO;

		ReadFile(hFile, pResource, sizeof(INFO), &dwByte, NULL);

		if(dwByte == 0)
		{
			delete pResource;
			break;
		}

		pVecResource->push_back(pResource);
	}
	CloseHandle(hFile);

	pMainView->Invalidate(FALSE);
	pMiniView->Invalidate(FALSE);
}

BOOL CResourcePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	TCHAR	szForderPath[MAX_PATH] = L"../Texture/Object/Resource";
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
				m_ResourceList.AddString(strImageName);
			}
			else
				delete pPngImage;

		}

		iResult = _findnext(handle, &fd);

	}

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CResourcePage::OnSetActive()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceTileOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceObjOpenCheck = true;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceUnitOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceBuildOpenCheck = false;

	return CPropertyPage::OnSetActive();
}

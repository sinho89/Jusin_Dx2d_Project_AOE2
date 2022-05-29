// UnitPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitPage.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "MiniView.h"
#include "BackGround.h"

// CUnitPage ��ȭ �����Դϴ�.

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


// CUnitPage �޽��� ó�����Դϴ�.

void CUnitPage::OnLbnSelchangeUnitList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString	strSelectName;

	int iSelNum = m_UnitList.GetCurSel();
	m_UnitList.GetText(iSelNum, strSelectName); // �̺κп� _ ©�� ������ƮŰ�� ��ο���̵� �ֱ�

	PathRemoveExtension((LPWSTR)strSelectName.operator LPCWSTR());

	map<CString, CImage*>::iterator iter = m_MapPngImage.find(strSelectName);

	if(iter == m_MapPngImage.end())
		return;

	m_UnitPicture.SetBitmap(*iter->second);

	///////////////////////////m_iDrawID �� ���� ����� ä�� ��� �ڴ�...
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

	//1������ �ε������� 2������ �ε������� ���ڸ� ����� �Լ�..

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strPath = L"../Data/Unit.dat";

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*		pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CToolView*	pMainView = pMainFrame->m_pMainView;
	CBackGround*	pBackGround = pMainView->m_pBackGround;

	vector<INFO*>*	pVecUnit = &pBackGround->m_vecUnit;

	//���̺�...

	DWORD	dwByte = 0;
	HANDLE	hFile = CreateFile(strPath, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == NULL)
	{
		MSG_BOX(L"���� ���� ����");
		return;
	}

	for(size_t i = 0; i < pVecUnit->size(); ++i)
	{
		WriteFile(hFile, (*pVecUnit)[i], sizeof(INFO), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MSG_BOX(L"���� ���� ����!!");
}

void CUnitPage::OnBnClickedUnitLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
					m_UnitList.AddString(strImageName);
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

BOOL CUnitPage::OnSetActive()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceTileOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceObjOpenCheck = false;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceUnitOpenCheck = true;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_bPlaceBuildOpenCheck = false;

	return CPropertyPage::OnSetActive();
}


// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
#include "Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"

#include "TextureMgr.h"
#include "MainFrm.h"
#include "BackGround.h"
#include "MyForm.h"
#include "ToolSheet.h"
#include "MiniView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CToolView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_pBackGround = NULL;
	m_bPlaceTileOpenCheck = false;
	m_bPlaceObjOpenCheck = false;
	m_bPlaceUnitOpenCheck = false;
	m_bPlaceBuildOpenCheck = false;
}

CToolView::~CToolView()
{
	CDevice::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();

	SAFE_DELETE(m_pBackGround);
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CDevice::GetInstance()->Render_Begin();

	m_pBackGround->Render();

	CDevice::GetInstance()->Render_End(m_hWnd);
}


// CToolView �μ�


void CToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CToolView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CToolView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	SetScrollSizes(MM_TEXT, CSize(TILECNTX * TILESIZEX, TILESIZEY * TILECNTY));

	//â ����� �����غ���...
	CMainFrame*	pFrame = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWindow;
	pFrame->GetWindowRect(&rcWindow);

	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left,
		rcWindow.bottom - rcWindow.top);

	RECT	rcMainView;
	GetClientRect(&rcMainView);

	float fRowFrm = float(rcWindow.right - rcMainView.right);
	float fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	pFrame->SetWindowPos(NULL, 0, 0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);
}

int CToolView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	g_hWnd = m_hWnd;

	if(FAILED(CDevice::GetInstance()->InitD3D()))
	{
		AfxMessageBox(L"Device �ʱ�ȭ ���� !!");
	}

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Tile%d%d.png", L"Tile", TEX_MULTI, L"Tile", 80)))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/Cherry_00%d.png", L"Cherry", TEX_MULTI, L"Cherry", 4)))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/Gold_00%d.png", L"Gold", TEX_MULTI, L"Gold", 7)))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/ChamChi_0%d%d.png", L"ChamChi", TEX_MULTI, L"ChamChi", 49)))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/Marlin_0%d%d.png", L"Marlin", TEX_MULTI, L"Marlin", 49)))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/Rock_00%d.png", L"Rock", TEX_MULTI, L"Rock", 7)))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Resource/Tree_00%d.png", L"Tree", TEX_MULTI, L"Tree", 10)))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/Tree/Shadow/TreeShadow_00%d.png", L"TreeShadow", TEX_MULTI, L"TreeShadow", 10)))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Town.png", L"Town", TEX_SINGLE, L"Town")))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Enemy_Age/Dark_Age/Town.png", L"EnemyTown", TEX_SINGLE, L"EnemyTown")))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player_Age/Dark_Age/Town_Shadow.png", L"TownShadow", TEX_SINGLE, L"TownShadow")))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Unit/Player/Male_Villager/STD/Villager_STD_0%d%d.png", L"Villager", TEX_MULTI, L"STD", 75)))
	{
		AfxMessageBox(L"Tile Texture �ε� ����!!");
	}



	m_pBackGround = new CBackGround;
	m_pBackGround->Initialize();

	m_pBackGround->SetMainView(this);

	return 0;
}

CBackGround* CToolView::GetBackGround()
{
	return m_pBackGround;
}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(m_bPlaceTileOpenCheck == true
		&& m_bPlaceObjOpenCheck == false
		&& m_bPlaceUnitOpenCheck == false
		&& m_bPlaceBuildOpenCheck == false)
	{
		int iSel = ((CMainFrame*)AfxGetMainWnd())->m_pMyForm->m_ToolPopUp.m_pSheet->m_TilePage.m_iDrawID;

		m_pBackGround->TileChange(D3DXVECTOR3(float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f), iSel);

	}
	else if(m_bPlaceTileOpenCheck == false
		&& m_bPlaceObjOpenCheck == true
		&& m_bPlaceUnitOpenCheck == false
		&& m_bPlaceBuildOpenCheck == false)
	{
		int iSel = ((CMainFrame*)AfxGetMainWnd())->m_pMyForm->m_ToolPopUp.m_pSheet->m_ResourcePage.m_iDrawID;
		m_pBackGround->AddResource(D3DXVECTOR3(float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f), iSel,((CMainFrame*)AfxGetMainWnd())->m_pMyForm->m_ToolPopUp.m_pSheet->m_ResourcePage.m_wstrObjKey);

	}

	else if(m_bPlaceTileOpenCheck == false
		&& m_bPlaceObjOpenCheck == false
		&& m_bPlaceUnitOpenCheck == false
		&& m_bPlaceBuildOpenCheck == true)
	{
		int iSel = ((CMainFrame*)AfxGetMainWnd())->m_pMyForm->m_ToolPopUp.m_pSheet->m_ResourcePage.m_iDrawID;
		m_pBackGround->AddBuild(D3DXVECTOR3(float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f), iSel, ((CMainFrame*)AfxGetMainWnd())->m_pMyForm->m_ToolPopUp.m_pSheet->m_BuildPage.m_wstrObjKey);

	}

	else if(m_bPlaceTileOpenCheck == false
		&& m_bPlaceObjOpenCheck == false
		&& m_bPlaceUnitOpenCheck == true
		&& m_bPlaceBuildOpenCheck == false)
	{
		int iSel = ((CMainFrame*)AfxGetMainWnd())->m_pMyForm->m_ToolPopUp.m_pSheet->m_ResourcePage.m_iDrawID;
		m_pBackGround->AddUnit(D3DXVECTOR3(float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f), iSel, ((CMainFrame*)AfxGetMainWnd())->m_pMyForm->m_ToolPopUp.m_pSheet->m_UnitPage.m_wstrObjKey, ((CMainFrame*)AfxGetMainWnd())->m_pMyForm->m_ToolPopUp.m_pSheet->m_UnitPage.m_wstrStateKey);

	}

	Invalidate(FALSE);

	((CMainFrame*)AfxGetMainWnd())->m_pMiniView->Invalidate(FALSE);

	CScrollView::OnLButtonDown(nFlags, point);
}

void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnLButtonDown(nFlags, point);
}

#include "StdAfx.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)


CDevice::~CDevice(void)
{
	Release();
}

//장치 초기화
//1.장치를 조사한다.(특정 성능에 대한 조사를 한다.)
//2.장치를 대표하는 객체를 생성한다.
//3.장치를 대표하는 객체가 존재 및 생성할 수 있는 클래스를 설계한다.
//4.장치에 명령을 내리기 위해서 3번의 클래스를 사용한다.
//5.싱글톤을 사용해서 여러 객체들에서 접근할 수 있게 한다..

HRESULT CDevice::InitD3D(void)
{
	//D3d 오브젝트 생성, D3ddevice 생성을 위해서 필요함...
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//장치의 성능을 조사하고, 저장할 변수
	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(DeviceCaps));

	if(FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, &DeviceCaps)))
	{

		MSG_BOX(L"Device Creation Failed");
		return E_FAIL;
	}
	
	//특정 성능에 대한 정보 조사...
	//버텍스 프로세싱...
	//+ 조명 연산...
	

	DWORD	vp;
	if(DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	
	D3DPRESENT_PARAMETERS	d3dpp;	//장치를 생성할 때 우리가 세팅해 주어야 하는 구조체..

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	//이건 우리가 만든 함수... 여기서 값을 채울 꺼임...
	SetParameters(d3dpp);

	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp,
		&m_pd3dDevice)))
	{
		MSG_BOX(L"디바이스 생성 실패");
		return E_FAIL;
	}

	///////스프라이트 객체 초기화...//////////////
	if(FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pSprite)))
	{
		MSG_BOX(L"Sprite Init Failed");
		return E_FAIL;
	}

	//폰트 객체 초기화...
	D3DXFONT_DESCW	FontInfo;
	ZeroMemory(&FontInfo, sizeof(D3DXFONT_DESCW));

	FontInfo.Height = 12;
	FontInfo.Width = 6;
	FontInfo.Weight	= FW_HEAVY;
	
	FontInfo.CharSet = HANGUL_CHARSET;	//한글을 쓸거다..
	lstrcpy(FontInfo.FaceName, L"돋움");	//서체 지정

	if(FAILED(D3DXCreateFontIndirect(m_pd3dDevice, &FontInfo, &m_pFont)))
	{
		MSG_BOX(L"폰트 객체 생성 실패");
		return E_FAIL;
	}

	return S_OK;
}

void CDevice::SetParameters(D3DPRESENT_PARAMETERS& d3dpp)
{
	d3dpp.BackBufferWidth = WINCX;	//백버퍼 사이즈...
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	//백버퍼 포맷...
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;	//확대 축소시 이미지 보정(보간)
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//백버퍼의 버퍼링 방식을 결정한다...
	//전면 버퍼, 후면 버퍼가 있음...
	//포인터의 대상을 바꾸는 기법을 페이지 플리핑 이라고 부르며
	//실제로 스왑체인이라고 부르는 방법으로 깜빡임을 감소시킴...


	d3dpp.hDeviceWindow = g_hWnd;			//윈도우 핸들...
	d3dpp.Windowed = TRUE;					//창모드 여부 결정
	d3dpp.EnableAutoDepthStencil = TRUE;	//
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	//깊이 24비트, 스텐실 8비트

	//전체화면 모드로 바꿨을 때 모니터의 주사율을 따라가도록 설정함...
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//주사율과 프레임 사이에 간격이 생겼을 때 어떻게 할 것인가...
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	
}

void CDevice::Render_Begin(void)
{
	//0, NULL, 버퍼를 삭제할 때 특정 위치를 삭제할 것인지에 대한 인자값...
	//스텐실, 깊이버퍼 후면 버퍼를 지운다...
	//현재는 파랑색으로 지운다...
	
	CDevice::GetInstance()->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	m_pd3dDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::Render_End(void)
{

	m_pSprite->End();
	m_pd3dDevice->EndScene();
	//1, 2 인자 : 렉트 2 개를 만들고, 두 개의 비율차만큼 확대/축소하는 용도
	//3인자 : 어느 윈도우에 넣을 것인가...(핸들)
	//4인자 : 보여주지 않을 곳을 설정할 수 있다...
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

}

void CDevice::Render_End(HWND _hWnd)
{
	m_pSprite->End();
	m_pd3dDevice->EndScene();
	m_pd3dDevice->Present(NULL, NULL, _hWnd, NULL);
}


void CDevice::Release(void)
{
	//릴리즈 순서를 반드시 지켜야 된다....
	m_pSprite->Release();
	m_pFont->Release();
	m_pd3dDevice->Release();
	m_pD3D->Release();
	
}

LPDIRECT3DDEVICE9 CDevice::GetDevice(void)
{
	return m_pd3dDevice;
}

LPD3DXSPRITE CDevice::GetSprite(void)
{
	return m_pSprite;
}

LPD3DXFONT CDevice::GetFont(void)
{
	return m_pFont;
}

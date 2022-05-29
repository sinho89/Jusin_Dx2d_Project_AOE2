#include "StdAfx.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)


CDevice::~CDevice(void)
{
	Release();
}

//��ġ �ʱ�ȭ
//1.��ġ�� �����Ѵ�.(Ư�� ���ɿ� ���� ���縦 �Ѵ�.)
//2.��ġ�� ��ǥ�ϴ� ��ü�� �����Ѵ�.
//3.��ġ�� ��ǥ�ϴ� ��ü�� ���� �� ������ �� �ִ� Ŭ������ �����Ѵ�.
//4.��ġ�� ����� ������ ���ؼ� 3���� Ŭ������ ����Ѵ�.
//5.�̱����� ����ؼ� ���� ��ü�鿡�� ������ �� �ְ� �Ѵ�..

HRESULT CDevice::InitD3D(void)
{
	//D3d ������Ʈ ����, D3ddevice ������ ���ؼ� �ʿ���...
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//��ġ�� ������ �����ϰ�, ������ ����
	D3DCAPS9	DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(DeviceCaps));

	if(FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, &DeviceCaps)))
	{

		MSG_BOX(L"Device Creation Failed");
		return E_FAIL;
	}
	
	//Ư�� ���ɿ� ���� ���� ����...
	//���ؽ� ���μ���...
	//+ ���� ����...
	

	DWORD	vp;
	if(DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	
	D3DPRESENT_PARAMETERS	d3dpp;	//��ġ�� ������ �� �츮�� ������ �־�� �ϴ� ����ü..

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	//�̰� �츮�� ���� �Լ�... ���⼭ ���� ä�� ����...
	SetParameters(d3dpp);

	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp,
		&m_pd3dDevice)))
	{
		MSG_BOX(L"����̽� ���� ����");
		return E_FAIL;
	}

	///////��������Ʈ ��ü �ʱ�ȭ...//////////////
	if(FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pSprite)))
	{
		MSG_BOX(L"Sprite Init Failed");
		return E_FAIL;
	}

	//��Ʈ ��ü �ʱ�ȭ...
	D3DXFONT_DESCW	FontInfo;
	ZeroMemory(&FontInfo, sizeof(D3DXFONT_DESCW));

	FontInfo.Height = 12;
	FontInfo.Width = 6;
	FontInfo.Weight	= FW_HEAVY;
	
	FontInfo.CharSet = HANGUL_CHARSET;	//�ѱ��� ���Ŵ�..
	lstrcpy(FontInfo.FaceName, L"����");	//��ü ����

	if(FAILED(D3DXCreateFontIndirect(m_pd3dDevice, &FontInfo, &m_pFont)))
	{
		MSG_BOX(L"��Ʈ ��ü ���� ����");
		return E_FAIL;
	}

	return S_OK;
}

void CDevice::SetParameters(D3DPRESENT_PARAMETERS& d3dpp)
{
	d3dpp.BackBufferWidth = WINCX;	//����� ������...
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	//����� ����...
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;	//Ȯ�� ��ҽ� �̹��� ����(����)
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//������� ���۸� ����� �����Ѵ�...
	//���� ����, �ĸ� ���۰� ����...
	//�������� ����� �ٲٴ� ����� ������ �ø��� �̶�� �θ���
	//������ ����ü���̶�� �θ��� ������� �������� ���ҽ�Ŵ...


	d3dpp.hDeviceWindow = g_hWnd;			//������ �ڵ�...
	d3dpp.Windowed = TRUE;					//â��� ���� ����
	d3dpp.EnableAutoDepthStencil = TRUE;	//
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	//���� 24��Ʈ, ���ٽ� 8��Ʈ

	//��üȭ�� ���� �ٲ��� �� ������� �ֻ����� ���󰡵��� ������...
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//�ֻ����� ������ ���̿� ������ ������ �� ��� �� ���ΰ�...
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	
}

void CDevice::Render_Begin(void)
{
	//0, NULL, ���۸� ������ �� Ư�� ��ġ�� ������ �������� ���� ���ڰ�...
	//���ٽ�, ���̹��� �ĸ� ���۸� �����...
	//����� �Ķ������� �����...
	
	CDevice::GetInstance()->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	m_pd3dDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::Render_End(void)
{

	m_pSprite->End();
	m_pd3dDevice->EndScene();
	//1, 2 ���� : ��Ʈ 2 ���� �����, �� ���� ��������ŭ Ȯ��/����ϴ� �뵵
	//3���� : ��� �����쿡 ���� ���ΰ�...(�ڵ�)
	//4���� : �������� ���� ���� ������ �� �ִ�...
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
	//������ ������ �ݵ�� ���Ѿ� �ȴ�....
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

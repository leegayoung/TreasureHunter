#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "CScreen.h"


CScreen::CScreen(HWND hwnd)
{
	m_pD3D = NULL;
	m_pD3Device = NULL;

	InitScreen(hwnd);
}


CScreen::~CScreen()
{
	ShutdownScreen();
}


void CScreen::InitScreen(HWND hwnd)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
		return ;

	RECT rc;
	GetClientRect(hwnd, &rc); //윈도우 핸들을 주면 윈도우 크기를 얻어옴

	int width = rc.right - rc.left + 1;
	int height = rc.bottom - rc.top + 1;


	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = hwnd;

	auto hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3Device);

	if (FAILED(hr))
		return ;

}
void CScreen::ShutdownScreen()
{
	if (m_pD3Device != NULL)
	{
		m_pD3Device->Release();
		m_pD3Device = NULL;
	}
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

void CScreen::BeginRender()
{
	if (m_pD3Device == NULL)
		return;
	m_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(200, 34, 67), 1.0f, 0);
}
void CScreen::EndRender()
{
	m_pD3Device->Present(0, 0, 0, 0);
}

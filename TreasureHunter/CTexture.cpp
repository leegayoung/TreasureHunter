#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "CTexture.h"


CTexture::CTexture(LPDIRECT3DDEVICE9 pD3Device)
{
	m_pD3Device = pD3Device;
}


CTexture::~CTexture()
{
	for (int i = 0; i < TEXTURE_POOL_MAX; i++)
	{
		ReleaseTexture(i);
	}
}

int CTexture::LoadTexture(const TCHAR* filename)
{
	int slotid = GetEmptySlot();

	if (slotid == -1)
		return -1;

	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;

	auto hr = D3DXCreateTextureFromFileEx(m_pD3Device, filename, 0, 0, 0, 0,
		D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &info, NULL, &texture);


	if (FAILED(hr))
		return -1;

	m_pTexture[slotid] = texture;

	return slotid;
}
void CTexture::ReleaseTexture(int slotid)
{
	if (m_pTexture[slotid] != NULL)
	{
		m_pTexture[slotid]->Release();
		m_pTexture[slotid] = NULL;
	}
}

int CTexture::GetEmptySlot() const
{
	for (int i = 0;i < TEXTURE_POOL_MAX; i++)
	{
		if (m_pTexture[i] == NULL)
			return i;
	}
	return -1;
}
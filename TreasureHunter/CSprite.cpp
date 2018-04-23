#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "CSprite.h"


CSprite::CSprite(LPDIRECT3DDEVICE9 pD3Device, LPDIRECT3DTEXTURE9 pTexture, float cx ,float cy)
	:m_pD3Device(pD3Device),
	m_pTexture(pTexture),
	m_Pos(0.f,0.f,0.f),
	m_Center(cx,cy,0),
	m_pSpr(NULL)
{
	InitSprite(pD3Device);
}


CSprite::~CSprite()
{
	ReleaseSprite();
}

bool CSprite::InitSprite(LPDIRECT3DDEVICE9 pD3Device)
{
	auto hr = D3DXCreateSprite(pD3Device, &m_pSpr);
	if (FAILED(hr))
		return false;
	return true;
}
void CSprite::ReleaseSprite()
{
	if (m_pSpr != NULL)
	{
		m_pSpr->Release();
		m_pSpr = NULL;
	}
}
void CSprite::Draw()
{
	m_pSpr->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSpr->Draw(m_pTexture, 0, &m_Center, &m_Pos, D3DCOLOR_XRGB(255, 255, 255));
	m_pSpr->End();
}

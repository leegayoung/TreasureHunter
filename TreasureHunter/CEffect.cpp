#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "CSprite.h"
#include "CEffect.h"


CEffect::CEffect(LPDIRECT3DDEVICE9 pD3Device, LPDIRECT3DTEXTURE9 texture, float cx, float cy)
	:m_Frame(0),
	m_bAlive(false)
{
	for (int i = 0; i < SPR_MAX; i++)
	{
		m_Spr[i] = new CSprite(pD3Device, texture, cx, cy);
	}
}


CEffect::~CEffect()
{
	for (int i = 0; i < SPR_MAX; i++)
	{
		delete m_Spr[i];
	}
}

void CEffect::SetTexture(int id, LPDIRECT3DTEXTURE9 texture)
{
	m_Spr[id]->SetTexture(texture);
}
void CEffect::SetPosition(D3DXVECTOR3& pos)
{
	for (int i = 0; i < SPR_MAX; i++)
		m_Spr[i]->SetPosition(pos);
}
void CEffect::SetAwake(D3DXVECTOR3& pos)
{
	m_bAlive = true;
	m_Frame = 0;
	m_PrevTime = GetTickCount();
	SetPosition(pos);
}
void CEffect::Update()
{
	if (m_bAlive == true)
	{
		DWORD time = GetTickCount() - m_PrevTime;
		if (time > 100)
		{
			m_Frame++;
			m_PrevTime = GetTickCount();
			
			if (m_Frame >= SPR_MAX)
				m_bAlive = false;

		}
	}
}
void CEffect::Draw()
{
	if (m_bAlive == true)
		m_Spr[m_Frame]->Draw();
}
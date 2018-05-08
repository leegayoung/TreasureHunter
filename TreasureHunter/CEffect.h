#pragma once

#define SPR_MAX 7

class CSprite;
class CEffect
{
public:
	explicit CEffect(LPDIRECT3DDEVICE9 pD3Device, LPDIRECT3DTEXTURE9 texture,float cx,float cy);
	virtual ~CEffect();

	void SetTexture(int id, LPDIRECT3DTEXTURE9 texture);
	void SetPosition(D3DXVECTOR3& pos);
	void SetAwake(D3DXVECTOR3& pos);
	void Update();
	void Draw();


private:
	CSprite * m_Spr[SPR_MAX];
	int m_Frame;
	bool m_bAlive;
	DWORD m_PrevTime;
};


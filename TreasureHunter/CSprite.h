#pragma once



class CSprite
{
public:
	explicit CSprite(LPDIRECT3DDEVICE9 pD3Device,LPDIRECT3DTEXTURE9 pTexture,float cx =0.0f, float cy =0.0f);
	virtual ~CSprite();

	bool InitSprite(LPDIRECT3DDEVICE9 pD3Device);
	void ReleaseSprite();

	virtual void Update(DWORD dwCurTime){}
	virtual void Draw();

	void SetPosition(float x, float y)
	{
		m_Pos = D3DXVECTOR3(x, y, 0);
	}

	void SetPosition(D3DXVECTOR3& pos)
	{
		m_Pos = pos;
	}

	const D3DXVECTOR3& GetPosition() const
	{
		return m_Pos;
	}

	void SetTexture(LPDIRECT3DTEXTURE9 texture)
	{
		m_pTexture = texture;
	}


protected:
	LPDIRECT3DDEVICE9 m_pD3Device;
	LPD3DXSPRITE m_pSpr;
	LPDIRECT3DTEXTURE9 m_pTexture;

	D3DXVECTOR3 m_Center;
	D3DXVECTOR3 m_Pos;
};


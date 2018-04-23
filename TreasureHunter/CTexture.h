#pragma once
#define TEXTURE_POOL_MAX 32
class CTexture
{
public:
	explicit CTexture(LPDIRECT3DDEVICE9 pD3Device);
	virtual ~CTexture();

	int LoadTexture(const TCHAR* filename);
	void ReleaseTexture(int slotid);

private:
	int GetEmptySlot() const;
	LPDIRECT3DDEVICE9 m_pD3Device;
	LPDIRECT3DTEXTURE9 m_pTexture[TEXTURE_POOL_MAX];
};


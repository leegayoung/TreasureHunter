#pragma once
class CScreen
{
public:
	explicit CScreen(HWND hwnd);
	virtual ~CScreen();

	LPDIRECT3DDEVICE9 GetDevice() const { return m_pD3Device; }
	operator LPDIRECT3DDEVICE9() const { return m_pD3Device; }
	operator const LPDIRECT3DDEVICE9() { return m_pD3Device; }

	HRESULT BeginScene() { return m_pD3Device->BeginScene(); }
	HRESULT EndScene() { return m_pD3Device->EndScene(); }

	void BeginRender();
	void EndRender();

	void InitScreen(HWND hwnd);
	void ShutdownScreen();

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3Device;

};


#pragma once

#define BOARD_MAX 10

#define BK_FAIL 0
#define BK_READY 1
#define BK_HIT 2
#define BK_SHIP 3
#define BK_MAX 4

class CSprite;

class CBoard
{
public:
	explicit CBoard(LPDIRECT3DDEVICE9 pD3Device,float cx,float cy, int playerID);
	virtual ~CBoard();

	void SetTexture(int slotID, LPDIRECT3DTEXTURE9 texture);
	void ClearBoard();
	void SetPosition(float x, float y);

	bool IsEmptyBlock(int x, int y, int shipID);
	void PutShip(int x, int y, int shipID);

	void PutSmallShip(int x, int y, int shipID);
	void PutMiddleShip(int x, int y, int shipID);
	void PutBigShip(int x, int y, int shipID);

	void ChangePos(float mx, float my, int &x, int &y);

	bool FindShipHead(int x, int y, int &shipID, int &startX);
	void ClearShip(int x, int y, int &shipID);

	void Draw();


private:
	float m_fBlockWidth;
	float m_fBlockHeight;
	float m_fBlockCX;
	float m_fBlockCY;
	int m_PlayerId;
	int m_ShipBlockCount;
	int m_HitScore;
	int m_ComboCount;

	float m_fStartX;
	float m_fStartY;

	CSprite* m_Board[BOARD_MAX][BOARD_MAX];
	int m_BoardState[BOARD_MAX][BOARD_MAX];

	LPDIRECT3DTEXTURE9 m_Textures[BK_MAX];

};


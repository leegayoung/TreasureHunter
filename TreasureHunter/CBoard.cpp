#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "CSprite.h"
#include "CBoard.h"


CBoard::CBoard(LPDIRECT3DDEVICE9 pD3Device, float cx, float cy, int playerID)
	:m_fBlockWidth(cx*2-1),
	m_fBlockHeight(cy*2-1),
	m_fBlockCX(cx),
	m_fBlockCY(cy),
	m_PlayerId(playerID),
	m_ShipBlockCount(0),
	m_HitScore(0),
	m_ComboCount(0)
{
	for (int y = 0; y < BOARD_MAX; y++)
	{
		for (int x = 0; x < BOARD_MAX; x++)
		{
			m_Board[y][x] = new CSprite(pD3Device, NULL, cx, cy);
			m_Board[y][x]->SetPosition(m_fBlockWidth *x, m_fBlockHeight *y);
			m_BoardState[y][x] = 0;
		}
	}
}


CBoard::~CBoard()
{
	for (int y = 0; y < BOARD_MAX; y++)
	{
		for (int x = 0; x < BOARD_MAX; x++)
		{
			delete m_Board[y][x];
		}
	}
}

void CBoard::SetTexture(int slotID, LPDIRECT3DTEXTURE9 texture)
{
	m_Textures[slotID] = texture;
}

void CBoard::ClearBoard()
{
	for (int y = 0; y < BOARD_MAX; y++)
	{
		for (int x = 0; x < BOARD_MAX; x++)
		{
			m_Board[y][x]->SetTexture(m_Textures[BK_READY]);
			m_BoardState[y][x] = 0;
		}
	}
}
void CBoard::SetPosition(float sx, float sy)
{
	for (int y = 0; y < BOARD_MAX; y++)
	{
		for (int x = 0; x < BOARD_MAX; x++)
		{
			m_Board[y][x]->SetPosition(m_fBlockWidth *x + sx, m_fBlockHeight *y + sy);
		}
	}
	m_fStartX = sx;
	m_fStartY = sy;
}

int GetTailSize(int shipID)
{
	switch (shipID)
	{
	case 1:
	case 2:
		return 1;
	case 3:
	case 4:
		return 2;
	case 5:
		return 3;
	}
	return -1;
}


bool CBoard::IsEmptyBlock(int x, int y, int shipID)
{
	int tail = GetTailSize(shipID);

	if (tail == -1)
		return false;

	if (x >= 0 && x + tail < BOARD_MAX && y >= 0 && y < BOARD_MAX)
	{
		for (int i = x; i <= x + tail; i++)
		{
			if (m_BoardState[y][i] != 0)
				return false;
		}
		return true;
	}
	return false;
}

void CBoard::PutSmallShip(int x, int y, int shipID)
{
	//if (m_PlayerId == 0)
	{
		m_Board[y][x]->SetTexture(m_Textures[BK_SHIP]);
		m_Board[y][x + 1]->SetTexture(m_Textures[BK_SHIP]);
	}
	

	m_BoardState[y][x] = shipID;
	m_BoardState[y][x+1] = shipID;

	m_ShipBlockCount += 2;
}
void CBoard::PutMiddleShip(int x, int y, int shipID)
{
	//if (m_PlayerId == 0)
	{
		m_Board[y][x]->SetTexture(m_Textures[BK_SHIP]);
		m_Board[y][x + 1]->SetTexture(m_Textures[BK_SHIP]);
		m_Board[y][x + 2]->SetTexture(m_Textures[BK_SHIP]);
	}
	m_BoardState[y][x] = shipID;
	m_BoardState[y][x + 1] = shipID;
	m_BoardState[y][x + 2] = shipID;

	m_ShipBlockCount += 3;
}
void CBoard::PutBigShip(int x, int y, int shipID)
{
	//if (m_PlayerId == 0)
	{
		m_Board[y][x]->SetTexture(m_Textures[BK_SHIP]);
		m_Board[y][x + 1]->SetTexture(m_Textures[BK_SHIP]);
		m_Board[y][x + 2]->SetTexture(m_Textures[BK_SHIP]);
		m_Board[y][x + 3]->SetTexture(m_Textures[BK_SHIP]);
	}
	m_BoardState[y][x] = shipID;
	m_BoardState[y][x + 1] = shipID;
	m_BoardState[y][x + 2] = shipID;
	m_BoardState[y][x + 3] = shipID;

	m_ShipBlockCount += 4;
}


void CBoard::PutShip(int x, int y, int shipID)
{
	switch (shipID)
	{
	case 1:
	case 2:
		PutSmallShip(x, y, shipID);
		break;
	case 3:
	case 4:
		PutMiddleShip(x, y, shipID);
		break;
	case 5:
		PutBigShip(x, y, shipID);
		break;
	}
}

void CBoard::ChangePos(float mx, float my, int &x, int &y)
{
	float localX = mx - (m_fStartX - m_fBlockCX);
	float localY = my - (m_fStartY - m_fBlockCY);

	int sizeX = (int)(m_fBlockCX * 2);
	int sizeY = (int)(m_fBlockCY * 2);

	x = ((int)localX) / sizeX;
	y = ((int)localY) / sizeY;

	if (x < 0 || x >= BOARD_MAX)
		x = -1;
	if (y < 0 || y >= BOARD_MAX)
		y = -1;

}

bool CBoard::FindShipHead(int x, int y, int &shipID, int &startX)
{
	shipID = -1;
	startX = -1;

	if (x >= 0 && x < BOARD_MAX && y >= 0 && y < BOARD_MAX)
	{
		if (m_BoardState[y][x] >= 1 && m_BoardState[y][x] <= 5)
		{
			shipID = m_BoardState[y][x];

			int n = x;

			while (n > 0 && m_BoardState[y][n - 1] == shipID)
				n--;
			startX = n;
			return true;
		}
	}
	return false;

}
void CBoard::ClearShip(int x, int y, int &shipID)
{
	int tail = GetTailSize(shipID);

	if (x >= 0 && x+tail < BOARD_MAX && y >= 0 && y < BOARD_MAX)
	{
		for (int i = x; i <= x + tail; i++)
		{
			m_BoardState[y][i] = 0;
			m_Board[y][i]->SetTexture(m_Textures[BK_READY]);
		}
		m_ShipBlockCount -= (tail - 1);
	}

}

bool CBoard::IsClicked(int x, int y)
{
	int state = m_BoardState[y][x];

	if (state <= -1 && state >= 100)
		return true;

	return false;
}

void CBoard::ChangeBlock(int x, int y)
{
	int state = m_BoardState[y][x];

	if (state >= 1 && state <= 5)
		m_Board[y][x]->SetTexture(m_Textures[BK_HIT]);
	else
		m_Board[y][x]->SetTexture(m_Textures[BK_FAIL]);

}

bool CBoard::GetBlockPos(int x, int y, D3DXVECTOR3& pos)
{
	if (x >= 0 && x < BOARD_MAX && y >= 0 && y < BOARD_MAX)
	{
		pos = m_Board[y][x]->GetPosition();
		return true;
	}
	return false;

}

void CBoard::Draw()
{
	for (int y = 0; y < BOARD_MAX; y++)
	{
		for (int x = 0; x < BOARD_MAX; x++)
		{
			m_Board[y][x]->Draw();
		}
	}
}
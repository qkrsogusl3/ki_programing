#pragma once

#include "Player.h"
#include "defines.h"

class CMapManager
{
private:
	int mMap[MAP_LENGTH] = { 0 };//������ �ʱ��̷� ��ҵ� �ʱ�ȭ
public:
	CMapManager();
	~CMapManager();

	void DrawMap();
	int* GetMap();
	char CheckSlimeEncount(CPlayer *tPlayer);
};


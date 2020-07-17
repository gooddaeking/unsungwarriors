#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class cave2 : public gameNode
{
private:
	player* _player; //플레이어 클래스
	enemyManager* _enemyManager;	//적매니져 클래스

	image* _cave2;
	image* _collision;

	RECT _backGround;
	float _x, _y;
	float _colX, _colY;
	int _width, _height;
	int _count;
	int frameX[4];
	float _probeY;

	POINT _point;
	RECT _enterance;
	RECT _exit;
	RECT _shop;
	bool _openShop;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	cave2() {}
	~cave2() {}
};
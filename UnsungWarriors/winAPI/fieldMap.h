#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class fieldMap : public gameNode
{
private:
	player* _player; //플레이어 클래스
	enemyManager* _enemyManager;	//적매니져 클래스

	image* _terrain;
	image* _collision;

	RECT _backGround;
	float _x, _y;
	float _colX, _colY;
	float _bX, _bY;
	int _width, _height;
	int _count;
	int frameX, frameY;
	float _probeY;

	POINT _point;
	RECT _enterance;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	fieldMap() {}
	~fieldMap() {}
};


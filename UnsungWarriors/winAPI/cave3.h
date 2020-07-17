#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class cave3 : public gameNode
{
private:
	player* _player; //플레이어 클래스
	enemyManager* _enemyManager;	//적매니져 클래스

	image* _cave3;
	image* _collision;

	RECT _backGround;
	RECT _pike[2];
	RECT _spring[2];
	bool _jumping[2];
	int _jumpFrame[2];
	float _x, _y;
	float _colX, _colY;
	int _width, _height;
	int _count;
	int frameX[10];
	float _probeY;

	POINT _point;
	RECT _enterance;
	RECT _exit;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	cave3() {}
	~cave3() {}
};
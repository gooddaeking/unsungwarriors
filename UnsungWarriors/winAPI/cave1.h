#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class cave1 : public gameNode
{
private:
	player* _player; //플레이어 클래스
	enemyManager* _enemyManager;	//적매니져 클래스

	image* _cave1;
	image* _collision;

	RECT _backGround;
	RECT _pike[4];
	RECT _spring[3];
	bool _jumping[3];
	int _jumpFrame[3];
	float _x, _y;
	float _colX, _colY;
	int _width, _height;
	int _count;
	int frameX[25];
	float _probeY;

	POINT _point;
	RECT _enterance;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	cave1() {}
	~cave1() {}
};
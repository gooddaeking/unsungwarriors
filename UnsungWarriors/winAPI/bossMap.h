#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class bossMap : public gameNode
{
private:
	player* _player; //�÷��̾� Ŭ����
	enemyManager* _enemyManager;	//���Ŵ��� Ŭ����

	image* _bossMap;
	image* _collision;

	RECT _backGround;
	float _x, _y;
	float _colX, _colY;
	int _width, _height;
	int _count;
	int frameX[9];
	float _probeY;
	bool bgmOn;

	POINT _point;
	RECT _enterance;
	RECT _exit;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	bossMap() {}
	~bossMap() {}
};

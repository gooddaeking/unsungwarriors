#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum ENEMYSTATE
{
	E_IDLE, E_MOVE, E_FOUND, E_ATT, E_HIT, E_HIT2, E_DEAD, E_SUMMON
};

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터를 만든다
class enemy : public gameNode
{
private:
	image* _image;		//에너미 이미지
	RECT _rc;			//충돌용 렉트

	//프레임 이미지를 돌리기 위한 변수
	ENEMYSTATE _state;
	bool _isLeft;
	bool _found;
	int _count;
	int _currentFrameX;
	int _currentFrameY;
	float _x, _y;
	float _probeU, _probeD, _probeL, _probeR;
	int frameX, frameY;
	float _gravity;
	int _hp;
	int _dmg;
	RECT _rcAtt;
	bool _hit;
	bool _life;

	//랜덤으로 총알발사 쿨타임 주기
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	virtual void move();		//업데이트
	virtual void draw();		//렌더
	virtual void animation();	//업데이트

	float getEnemyX() { return _x; }
	void setEnemyX(float x) { _x = x; }
	float getEnemyY() { return _y; }
	void setEnemyY(float y) { _y = y; }
	float getGravity() { return _gravity; }
	void setGravity(float gravity) { _gravity = gravity; }
	int getCount() { return _count; }
	void setCount(int count) { _count = count; }
	int getFrameX() { return frameX; }
	void setFrameX(int frame) { frameX = frame; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	bool bulletCountFire();

	//충돌용 렉트 가져오기
	int getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state ; }
	RECT getRect() { return _rc; }
	RECT getAttRect() { return _rcAtt; }
	int getDmg() { return _dmg; }
	void setHit(bool hit) { _hit = hit; }

	enemy() {}
	~enemy() {}
};

class boss : public gameNode
{
private:
	image* _image;		//에너미 이미지
	RECT _rc;			//충돌용 렉트
	vector<enemy*> _enemy;

	//프레임 이미지를 돌리기 위한 변수
	ENEMYSTATE _state;
	bool _isLeft;
	bool _found;
	int _count;
	int _currentFrameX;
	int _currentFrameY;
	int _exploFrameX[12];
	int _randomX[12], _randomY[12];
	float _x, _y;
	float _probeU, _probeD, _probeL, _probeR;
	int frameX, frameY;
	float _gravity;
	int _maxHp, _hp;
	int _dmg;
	RECT _rcAtt;
	bool _hit;
	bool _life;

	RECT _okay;

	//랜덤으로 총알발사 쿨타임 주기
	int _fireCount;
	int _rndFireConut;

	progressBar* _hpBar;	 //체력바

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	virtual void move();		//업데이트
	virtual void draw();		//렌더
	virtual void animation();	//업데이트

	float getEnemyX() { return _x; }
	void setEnemyX(float x) { _x = x; }
	float getEnemyY() { return _y; }
	void setEnemyY(float y) { _y = y; }
	float getGravity() { return _gravity; }
	void setGravity(float gravity) { _gravity = gravity; }
	int getCount() { return _count; }
	void setCount(int count) { _count = count; }
	int getFrameX() { return frameX; }
	void setFrameX(int frame) { frameX = frame; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	bool bulletCountFire();

	//충돌용 렉트 가져오기
	int getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }
	vector<enemy*> getMinion() { return _enemy; }
	void setMinioin(vector<enemy*> enemy) { _enemy = enemy; }
	RECT getRect() { return _rc; }
	RECT getAttRect() { return _rcAtt; }
	int getDmg() { return _dmg; }
	void setHit(bool hit) { _hit = hit; }

	boss() {}
	~boss() {}
};

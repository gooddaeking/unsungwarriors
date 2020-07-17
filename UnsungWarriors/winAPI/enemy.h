#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum ENEMYSTATE
{
	E_IDLE, E_MOVE, E_FOUND, E_ATT, E_HIT, E_HIT2, E_DEAD, E_SUMMON
};

//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͸� �����
class enemy : public gameNode
{
private:
	image* _image;		//���ʹ� �̹���
	RECT _rc;			//�浹�� ��Ʈ

	//������ �̹����� ������ ���� ����
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

	//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	virtual void move();		//������Ʈ
	virtual void draw();		//����
	virtual void animation();	//������Ʈ

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

	//�浹�� ��Ʈ ��������
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
	image* _image;		//���ʹ� �̹���
	RECT _rc;			//�浹�� ��Ʈ
	vector<enemy*> _enemy;

	//������ �̹����� ������ ���� ����
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

	//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	int _fireCount;
	int _rndFireConut;

	progressBar* _hpBar;	 //ü�¹�

public:
	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	virtual void move();		//������Ʈ
	virtual void draw();		//����
	virtual void animation();	//������Ʈ

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

	//�浹�� ��Ʈ ��������
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

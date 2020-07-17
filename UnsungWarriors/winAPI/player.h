#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"
#include "inven.h"
#include "shop.h"

//��ȣ������ Ŭ���� ���漱��
class enemyManager;

enum STATE
{
	IDLE, MOVE, JUMP, DASH, FALL, ATT1, ATT2, ATT3, HIT, DEAD
};

class player : public gameNode
{
private:
	enemyManager* _em;  //����� �����Ҵ� ��!!
	inven* _inven;
	shop* _shop;
	//���ΰ��ӿ��� ������ EM�� �÷��̾�� ������ EM��
	//���� �ٸ� �޸� �ּҶ� ���� ������ �� ����!!!
private:
	image* _player;		//�÷��̾� �̹���
	//RECT _rcPlayer;		//�÷��̾� ������ ��Ʈ
	missile* _missile;	//�̻��� Ŭ����
	bomb* _bomb;		//��ź Ŭ����

	vector<tagItem> _vWeapon;
	vector<tagItem> _vAcce;
	vector<tagItem> _vShield;
	
	RECT _hit;
	RECT _rcAtt;
	RECT _rcAtt2;
	RECT _rcAtt3;

	STATE _state;
	int frameX, frameY, _count, _dashCount;
	int _dmg, _gold;
	bool _life;
	bool _dashOnL, _dashOnR;
	bool _dashLight;
	float _x, _y;
	float _probeU, _probeD, _probeL, _probeR;
	float _speed;
	float _gravity;
	bool _att2, _att3, _coolDown;
	bool _isLeft;
	bool _comeback;
	bool _magicOn;
	int magicFrameX, magicFrameY, alpha;
	RECT electric;
	RECT _camera;
	POINT _point;

	progressBar* _hpBar;	 //ü�¹�
	progressBar2* _mpBar;
	float _maxHp, _currentHp; //�ִ�ü��, ����ü��
	float _maxMp, _currentMp; //�ִ�ü��, ����ü��

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//��źŬ���� ��������
	bomb* getBomb() { return _bomb; }

	//��ź����
	void removeBomb(int index);

	//�浹�Լ�(�÷��̾��Ѿ�, �̴Ͼ��浹)
	void collision();

	//�÷��̾� �ִϸ��̼�
	void animation();
	void camera();

	//������
	void hitDamage(float damage);

	//���̺�ε�
	void save();
	void load();

	//�÷��̾� �̹��� ��������
	image* getPlayerImg() { return _player; }
	RECT getHit() { return _hit; }
	bool getLife() { return _life; }
	int getHp() { return _currentHp; }
	void setHp(int currentHp) { _currentHp = currentHp; }
	int getMp() { return _currentMp; }
	float get_X() { return _x; }
	void set_X(float x) { _x = x; }
	float get_Y() { return _y; }
	void set_Y(float y) { _y = y; }
	float getGravity() { return _gravity; }
	void setGravity(float gravity) { _gravity = gravity; }

	inven* getInven() { return _inven; }
	shop* getShop() { return _shop; }

	//��ȣ������ ���Ŵ��� �����͸� �Ѱܹ��� �����Լ�
	void setEMLink(enemyManager* em) { _em = em; }

	player() {}
	~player() {}
};


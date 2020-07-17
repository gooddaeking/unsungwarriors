#pragma once
#include "gameNode.h"
#include "minion.h"  //�̴Ͼ� Ŭ���� ����ϱ� ����
#include "bullet.h"	 //�����Ѿ� Ŭ���� ����ϱ� ����

//��ȣ������ Ŭ���� ���漱��
class player;

class enemyManager : public gameNode
{
private:
	player* _player;

private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;
	vector<boss*> _vBoss;
	vector<boss*>::iterator _viBoss;
	bullet* _bullet; //�����Ѿ� Ŭ����
	int _count;

public:
	HRESULT init();
	HRESULT init1();
	HRESULT init2();
	HRESULT initBoss();
	void release();
	void update();
	void render();

	//�̴Ͼ� ���� => �ʱ�ȭ�� �ִ´�
	void setMinion();
	void setMinion1();
	void setMinion2();
	void setBoss();
	//�̴Ͼ� �Ѿ˹߻�
	void minionBulletFire();
	//�̴Ͼ� ����
	void removeMinion(int index);

	//�̴Ͼ� ���� ��������
	vector<enemy*> getMinion() { return _vMinion; }
	void setMinioin(vector<enemy*> vMinion) { _vMinion = vMinion; }
	vector<boss*> getBoss() { return _vBoss; }
	void setBoss(vector<boss*> vBoss) { _vBoss = vBoss; }

	//�浹�Լ� (�̴Ͼ���� �Ѿ˵�, �÷��̾�)
	void collision();

	//��ȣ������ �÷��̾� �����͸� ���� �����Լ�
	void setPlayerLink(player* player) { _player = player; }

	enemyManager() {}
	~enemyManager() {}
};


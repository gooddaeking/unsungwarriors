#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	//�̴Ͼ� ����, ����, �Ϲݸ���
	//���� �Լ��� ���� ó���ϸ� ������ ���⿡ ���ϴ�

	//�̴Ͼ� ����
	this->setMinion();
	//��������
	//this->setBoss();

	//�Ѿ� Ŭ���� �ʱ�ȭ
	//_bullet = new bullet;
	//_bullet->init("torch", 15, 600);

	return S_OK;
}

HRESULT enemyManager::init1()
{
	//�̴Ͼ� ����, ����, �Ϲݸ���
	//���� �Լ��� ���� ó���ϸ� ������ ���⿡ ���ϴ�

	//�̴Ͼ� ����
	this->setMinion1();
	//��������
	//this->setBoss();

	//�Ѿ� Ŭ���� �ʱ�ȭ
	//_bullet = new bullet;
	//_bullet->init("torch", 15, 600);

	return S_OK;
}

HRESULT enemyManager::init2()
{
	//�̴Ͼ� ����, ����, �Ϲݸ���
	//���� �Լ��� ���� ó���ϸ� ������ ���⿡ ���ϴ�

	//�̴Ͼ� ����
	this->setMinion2();
	//��������
	//this->setBoss();

	//�Ѿ� Ŭ���� �ʱ�ȭ
	//_bullet = new bullet;
	//_bullet->init("torch", 15, 600);

	return S_OK;
}

HRESULT enemyManager::initBoss()
{
	//�̴Ͼ� ����, ����, �Ϲݸ���
	//���� �Լ��� ���� ó���ϸ� ������ ���⿡ ���ϴ�

	//�̴Ͼ� ����
	this->setBoss();
	//��������
	//this->setBoss();

	//�Ѿ� Ŭ���� �ʱ�ȭ
	//_bullet = new bullet;
	//_bullet->init("torch", 15, 600);

	return S_OK;
}

void enemyManager::release()
{
	//�Ѿ� Ŭ���� ����
	//_bullet->release();
	//SAFE_DELETE(_bullet);
}

void enemyManager::update()
{
	//�Ѿ� ������Ʈ
	//_bullet->update();

	//���Ϳ� ��� �̴Ͼ�� ������Ʈ
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->update();
	}
	for (int i = 0; i < _vBoss.size(); i++)
	{
		_vBoss[i]->update();
	}

	//�̴Ͼ� �Ѿ˹߻�
	//this->minionBulletFire();

	//�浹�Լ�
	//this->collision();
}

void enemyManager::render()
{
	//�Ѿ�Ŭ���� ����
	//_bullet->render();

	//���Ϳ� ��� �̴Ͼ�� ����
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->render();
	}
	for (int i = 0; i < _vBoss.size(); i++)
	{
		_vBoss[i]->render();
	}
}

void enemyManager::setMinion()
{
	//for (int i = 0; i < 4; i++)
	//{
	//	enemy* ufo = new minion;
	//	ufo->init("skeleton(idle)", PointMake(1500 + i * 1500, 300));
	//	_vMinion.push_back(ufo);
	//}
	enemy* ufo = new minion;
	ufo->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 1700 , CAMERADATA->get_Y() + 800));
	_vMinion.push_back(ufo);
	enemy* ufo1 = new minion;
	ufo1->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 2500, CAMERADATA->get_Y() + 800));
	_vMinion.push_back(ufo1);
	enemy* ufo2 = new minion;
	ufo2->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 4500, CAMERADATA->get_Y() + 1000));
	_vMinion.push_back(ufo2);
	enemy* ufo3 = new minion;
	ufo3->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 5000, CAMERADATA->get_Y() + 1000));
	_vMinion.push_back(ufo3);
}

void enemyManager::setMinion1()
{
	enemy* ufo = new minion;
	ufo->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 1900, CAMERADATA->get_Y() + 1500));
	_vMinion.push_back(ufo);
	enemy* ufo1 = new minion;
	ufo1->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 2650, CAMERADATA->get_Y() + 1700));
	_vMinion.push_back(ufo1);
	enemy* ufo2 = new minion;
	ufo2->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 2700, CAMERADATA->get_Y() + 2500));
	_vMinion.push_back(ufo2);
	enemy* ufo3 = new minion;
	ufo3->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 5500, CAMERADATA->get_Y() + 1250));
	_vMinion.push_back(ufo3);
	enemy* ufo10 = new minion;
	ufo10->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 5600, CAMERADATA->get_Y() + 1250));
	_vMinion.push_back(ufo10);
	enemy* ufo4 = new minion;
	ufo4->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 9200, CAMERADATA->get_Y() + 1550));
	_vMinion.push_back(ufo4);
	enemy* ufo5 = new minion;
	ufo5->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 10500, CAMERADATA->get_Y() + 2300));
	_vMinion.push_back(ufo5);
	enemy* ufo6 = new minion;
	ufo6->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 11000, CAMERADATA->get_Y() + 2300));
	_vMinion.push_back(ufo6);
	enemy* ufo8 = new minion;
	ufo8->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 12800, CAMERADATA->get_Y() + 2200));
	_vMinion.push_back(ufo8);
	enemy* ufo7 = new minion;
	ufo7->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 13400, CAMERADATA->get_Y() + 2300));
	_vMinion.push_back(ufo7);
	enemy* ufo9 = new minion;
	ufo9->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 16000, CAMERADATA->get_Y() + 1700));
	_vMinion.push_back(ufo9);
}

void enemyManager::setMinion2()
{
	enemy* ufo = new minion;
	ufo->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 4140, CAMERADATA->get_Y() + 1100));
	_vMinion.push_back(ufo);
	enemy* ufo1 = new minion;
	ufo1->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 4500, CAMERADATA->get_Y() + 1900));
	_vMinion.push_back(ufo1);
	enemy* ufo2 = new minion;
	ufo2->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 4700, CAMERADATA->get_Y() + 1900));
	_vMinion.push_back(ufo2);
	enemy* ufo3 = new minion;
	ufo3->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 6000, CAMERADATA->get_Y() + 1600));
	_vMinion.push_back(ufo3);
	enemy* ufo4 = new minion;
	ufo4->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 6300, CAMERADATA->get_Y() + 1600));
	_vMinion.push_back(ufo4);
	enemy* ufo5 = new minion;
	ufo5->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 6700, CAMERADATA->get_Y() + 1600));
	_vMinion.push_back(ufo5);
	enemy* ufo6 = new minion;
	ufo6->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 1760, CAMERADATA->get_Y() + 2200));
	_vMinion.push_back(ufo6);
	enemy* ufo7 = new minion;
	ufo7->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 1200, CAMERADATA->get_Y() + 3100));
	_vMinion.push_back(ufo7);
}

void enemyManager::setBoss()
{
	enemy* ufo = new minion;
	ufo->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 1900, CAMERADATA->get_Y() + 500));
	_vMinion.push_back(ufo);
	enemy* ufo1 = new minion;
	ufo1->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 2650, CAMERADATA->get_Y() + 500));
	_vMinion.push_back(ufo1);
	enemy* ufo2 = new minion;
	ufo2->init("skeleton(idle)", PointMake(CAMERADATA->get_X() + 2700, CAMERADATA->get_Y() + 500));
	_vMinion.push_back(ufo2);
	boss* bossking = new boss;
	bossking->init("boss(move)", PointMake(CAMERADATA->get_X() + 3500, CAMERADATA->get_Y() + 600));
	_vBoss.push_back(bossking);
}

void enemyManager::minionBulletFire()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		//int a = 10;
		//int* p = &a;
		//cout << p << endl; //a�� �ּ�
		//cout << *p << endl; //a�� ��
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 30, -(PI_2), 3.0f);
		}
	}
}

void enemyManager::removeMinion(int index)
{
	_vMinion.erase(_vMinion.begin() + index);
}

void enemyManager::collision()
{
	//�浹�Լ� (�̴Ͼ���� �Ѿ˵�, �÷��̾�)
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
			&_player->getPlayerImg()->boudingBox()))
		{
			//�����Ѿ� ����
			_bullet->removeBullet(i);
			//�÷��̾� ������
			_player->hitDamage(10);
			break;
		}
	}
}

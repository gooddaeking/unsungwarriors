#include "stdafx.h"
#include "fieldMap.h"

HRESULT fieldMap::init()
{
	_terrain = IMAGEMANAGER->findImage("�ʵ�����");
	_collision = IMAGEMANAGER->findImage("�ʵ��浹");
	SOUNDMANAGER->play("fieldbgm", 0.2f);

	if (!PLAYERDATA->getComeback())
	{
		_x = 0;
		_y = -500;
		//�÷��̾� Ŭ���� �ʱ�ȭ
		_player = new player;
		_player->init();
		_player->set_X(_x + 300);
		_player->set_Y(_y + 1120);
	}
	else
	{
		_x = -4800;
		_y = -400;
		//�÷��̾� Ŭ���� �ʱ�ȭ
		_player = new player;
		_player->init();
		_player->set_X(_x + 6000);
		_player->set_Y(_y + 1020);
	}
	_colX = _x;
	_colY = _y;
	_width = _terrain->getWidth();
	_height = _terrain->getHeight();
	_bX = 0;
	_bY = -1024;
	_count = frameX = frameY = 0;
	CAMERADATA->setImage(_collision);
	CAMERADATA->set_X(_x);
	CAMERADATA->set_Y(_y);
	CAMERADATA->setWidth(_width);
	CAMERADATA->setHeight(_height);

	//���Ŵ��� Ŭ���� �ʱ�ȭ
	_enemyManager = new enemyManager;
	_enemyManager->init();
	

	//��ȣ����
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void fieldMap::release()
{
	//�÷��̾� Ŭ���� ����
	_player->release();
	SAFE_DELETE(_player);

	//���Ŵ��� Ŭ���� ����
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void fieldMap::update()
{
	//�÷��̾� Ŭ���� ������Ʈ
	_player->update();

	_x = CAMERADATA->get_X();
	_y = CAMERADATA->get_Y();
	_bX = CAMERADATA->get_X() / 2;
	CAMERADATA->getImage()->setX(CAMERADATA->get_X());
	CAMERADATA->getImage()->setY(CAMERADATA->get_Y());
	_colX = _x;
	_colY = _y;
	_point.x = _player->get_X();
	_point.y = _player->get_Y();

	_enterance = RectMake(_x + 5871, _y + 860, 140, 270);

	//���Ŵ��� ������Ʈ
	_enemyManager->update();

	_count++;
	if (_count % 5 == 0)
	{
		frameX++;
		if (frameX > 11)
		{
			frameX = 0;
		}
	}


	if (INPUT->GetKeyDown('A') && PtInRect(&_enterance, _point))
	{
		SOUNDMANAGER->stop("fieldbgm");
		//�κ��丮 ������ ����
		if (!_player->getInven()->getWeapon().empty()) PLAYERDATA->setWeapon(_player->getInven()->getWeapon()[0]._serial);
		else PLAYERDATA->setWeapon(-1);
		if (!_player->getInven()->getAcce().empty()) PLAYERDATA->setAcce(_player->getInven()->getAcce()[0]._serial);
		else PLAYERDATA->setAcce(-1);
		if (!_player->getInven()->getShield().empty()) PLAYERDATA->setShield(_player->getInven()->getShield()[0]._serial);
		else PLAYERDATA->setShield(-1);
		PLAYERDATA->clearSeiral();
		for (int i = 0; i < _player->getInven()->getInven().size(); i++)
		{
			PLAYERDATA->setSerial(_player->getInven()->getInven()[i]._serial);
		}
		//�÷��̾� HP ��� ����
		PLAYERDATA->setHp(_player->getHp());
		PLAYERDATA->setMp(_player->getMp());
		PLAYERDATA->setGold(_player->getInven()->getMoney());
		//�����ΰ���
		PLAYERDATA->setComeback(false);
		SCENEMANAGER->loadScene("����1ȭ��");
	}
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->stop("fieldbgm");
		SCENEMANAGER->loadScene("����ȭ��");
	}
	if (INPUT->GetKeyDown('Y'))
	{
		SOUNDMANAGER->stop("fieldbgm");
		//�κ��丮 ������ ����
		if (!_player->getInven()->getWeapon().empty()) PLAYERDATA->setWeapon(_player->getInven()->getWeapon()[0]._serial);
		else PLAYERDATA->setWeapon(-1);
		if (!_player->getInven()->getAcce().empty()) PLAYERDATA->setAcce(_player->getInven()->getAcce()[0]._serial);
		else PLAYERDATA->setAcce(-1);
		if (!_player->getInven()->getShield().empty()) PLAYERDATA->setShield(_player->getInven()->getShield()[0]._serial);
		else PLAYERDATA->setShield(-1);
		PLAYERDATA->clearSeiral();
		for (int i = 0; i < _player->getInven()->getInven().size(); i++)
		{
			PLAYERDATA->setSerial(_player->getInven()->getInven()[i]._serial);
		}
		//�÷��̾� HP ��� ����
		PLAYERDATA->setHp(_player->getHp());
		PLAYERDATA->setMp(_player->getMp());
		PLAYERDATA->setGold(_player->getInven()->getMoney());
		//�����ΰ���
		PLAYERDATA->setComeback(false);
		SCENEMANAGER->loadScene("����1ȭ��");
	}
}

void fieldMap::render()
{
	//��׶��� ����
	IMAGEMANAGER->render("��׶���", getMemDC(), _bX, _bY);
	_terrain->render(getMemDC(), _x, _y);

	if (PtInRect(&_enterance, _point))
	{
		IMAGEMANAGER->alphaRender("notice", getMemDC(), _enterance.left - 80, _enterance.top - 100, 150);
		IMAGEMANAGER->render("enter", getMemDC(), _enterance.left - 80, _enterance.top - 100);
	}

	//�÷��̾� Ŭ���� ����
	_player->render();

	//���Ŵ��� Ŭ���� ����
	_enemyManager->render();

}

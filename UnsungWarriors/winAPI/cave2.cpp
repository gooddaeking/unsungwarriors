#include "stdafx.h"
#include "cave2.h"

HRESULT cave2::init()
{

	_cave2 = IMAGEMANAGER->findImage("����2");
	_collision = IMAGEMANAGER->findImage("����2�浹");
	SOUNDMANAGER->play("cave2bgm", 0.2f);

	if (!PLAYERDATA->getComeback())
	{
		_x = 0;
		_y = -500;
		//�÷��̾� Ŭ���� �ʱ�ȭ
		_player = new player;
		_player->init();
		_player->set_X(_x + 600);
		_player->set_Y(_y + 1070);
	}
	else
	{
		_x = -2200;
		_y = -600;
		//�÷��̾� Ŭ���� �ʱ�ȭ
		_player = new player;
		_player->init();
		_player->set_X(_x + 3500);
		_player->set_Y(_y + 1220);
	}
	
	_colX = _x;
	_colY = _y;
	_width = _cave2->getWidth();
	_height = _cave2->getHeight();
	_count = 0;

	_openShop = false;

	CAMERADATA->setImage(_collision);
	CAMERADATA->set_X(_x);
	CAMERADATA->set_Y(_y);
	CAMERADATA->setWidth(_width);
	CAMERADATA->setHeight(_height);
	
	for (int i = 0; i < 4; i++)
	{
		frameX[i] = 0;
	}

	//���Ŵ��� Ŭ���� �ʱ�ȭ
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//��ȣ����
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void cave2::release()
{
	//�÷��̾� Ŭ���� ����
	_player->release();
	SAFE_DELETE(_player);

	//���Ŵ��� Ŭ���� ����
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void cave2::update()
{
	//�÷��̾� Ŭ���� ������Ʈ
	_player->update();

	CAMERADATA->getImage()->setX(CAMERADATA->get_X());
	CAMERADATA->getImage()->setY(CAMERADATA->get_Y());
	_point.x = _player->get_X();
	_point.y = _player->get_Y();

	_shop = RectMake(_x + 1592, _y + 1080, 240, 280);
	_enterance = RectMake(_x + 3507, _y + 1134, 120, 200);
	_exit = RectMake(_x + 625, _y + 980, 120, 200);

	//���Ŵ��� ������Ʈ
	//_enemyManager->update();

	_x = CAMERADATA->get_X();
	_y = CAMERADATA->get_Y();

	_count++;
	if (_count % 5 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			frameX[i]++;
			if (frameX[i] > 11)
			{
				frameX[i] = RANDOM->Range(0, 3);
			}
		}
	}
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->stop("cave2bgm");
		SCENEMANAGER->loadScene("����ȭ��");
	}
	if (INPUT->GetKeyDown('A'))
	{
		if(PtInRect(&_shop, _point)) _player->getShop()->setShop(true);
		else if (PtInRect(&_exit, _point))
		{
			SOUNDMANAGER->stop("cave2bgm");
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
			PLAYERDATA->setComeback(true);
			SCENEMANAGER->loadScene("����1ȭ��");
		}
		else if (PtInRect(&_enterance, _point))
		{
			SOUNDMANAGER->stop("cave2bgm");
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
			SCENEMANAGER->loadScene("����3ȭ��");
		}
	}
	if (INPUT->GetKeyDown('Y'))
	{
		SOUNDMANAGER->stop("cave2bgm");
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
		SCENEMANAGER->loadScene("����3ȭ��");
	}
}

void cave2::render()
{
	//��׶��� ����
	_cave2->render(getMemDC(), _x, _y);

	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 405, _y + 1049 - 144, frameX[0], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 903, _y + 1049 - 144, frameX[1], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 3261, _y + 1234 - 144, frameX[2], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 3811, _y + 1234 - 144, frameX[3], 0);

	if (PtInRect(&_shop, _point))
	{
		IMAGEMANAGER->alphaRender("notice", getMemDC(), _x + 1562, _y + 1030, 150);
		IMAGEMANAGER->render("openshop", getMemDC(), _x + 1562, _y + 1030);
	}
	if (PtInRect(&_enterance, _point))
	{
		IMAGEMANAGER->alphaRender("notice", getMemDC(), _enterance.left - 80, _enterance.top - 100, 150);
		IMAGEMANAGER->render("enter", getMemDC(), _enterance.left - 80, _enterance.top - 100);
	}
	if (PtInRect(&_exit, _point))
	{
		IMAGEMANAGER->alphaRender("notice", getMemDC(), _exit.left - 100, _exit.top - 100, 150);
		IMAGEMANAGER->render("exit", getMemDC(), _exit.left - 100, _exit.top - 100);
	}

	//�÷��̾� Ŭ���� ����
	_player->render();

	//���Ŵ��� Ŭ���� ����
	//_enemyManager->render();

}

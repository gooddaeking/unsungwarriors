#include "stdafx.h"
#include "bossMap.h"

HRESULT bossMap::init()
{

	_bossMap = IMAGEMANAGER->findImage("보스맵");
	_collision = IMAGEMANAGER->findImage("보스맵(충돌)");

	if (!PLAYERDATA->getComeback())
	{
		_x = 0;
		_y = -500;
		//플레이어 클래스 초기화
		_player = new player;
		_player->init();
		_player->set_X(_x + 300);
		_player->set_Y(_y + 600);
	}
	else
	{
		_x = 100;
		_y = 940;
		//플레이어 클래스 초기화
		_player = new player;
		_player->init();
		_player->set_X(_x + 300);
		_player->set_Y(_y + 2440);
	}

	_colX = _x;
	_colY = _y;
	_width = _bossMap->getWidth();
	_height = _bossMap->getHeight();
	_count = 0;
	bgmOn = false;

	CAMERADATA->setImage(_collision);
	CAMERADATA->set_X(_x);
	CAMERADATA->set_Y(_y);
	CAMERADATA->setWidth(_width);
	CAMERADATA->setHeight(_height);

	for (int i = 0; i < 9; i++)
	{
		frameX[i] = 0;
	}
	//적매니져 클래스 초기화
	_enemyManager = new enemyManager;
	_enemyManager->initBoss();


	//상호참조
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void bossMap::release()
{
	//플레이어 클래스 해제
	_player->release();
	SAFE_DELETE(_player);

	//적매니져 클래스 해제
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void bossMap::update()
{
	//플레이어 클래스 업데이트
	_player->update();

	CAMERADATA->getImage()->setX(CAMERADATA->get_X());
	CAMERADATA->getImage()->setY(CAMERADATA->get_Y());
	_point.x = _player->get_X();
	_point.y = _player->get_Y();

	_enterance = RectMake(_x + 440, _y + 2400, 120, 200);
	_exit = RectMake(_x + 2800, _y + 940, 120, 200);

	//적매니져 업데이트
	_enemyManager->update();

	_x = CAMERADATA->get_X();
	_y = CAMERADATA->get_Y();

	if (_enemyManager->getBoss()[0]->getEnemyX() - _player->get_X() < 1000)
	{
		bgmOn = true;
	}
	if (bgmOn && _count > 0)
	{
		SOUNDMANAGER->play("bossbgm", 0.2f);
		_count = -100000;
	}

	_count++;
	if (_count % 5 == 0)
	{
		for (int i = 0; i < 9; i++)
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
		SOUNDMANAGER->stop("bossbgm");
		SCENEMANAGER->loadScene("시작화면");
	}
	if (INPUT->GetKeyDown('A'))
	{
		if (_point.x > 1500)
		{
			SOUNDMANAGER->stop("bossbgm");
			//인벤토리 아이템 저장
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
			//플레이어 HP 골드 저장
			PLAYERDATA->setHp(_player->getHp());
			PLAYERDATA->setMp(_player->getMp());
			PLAYERDATA->setGold(_player->getInven()->getMoney());
			//돌아가기
			PLAYERDATA->setComeback(true);
			SCENEMANAGER->loadScene("필드화면");
		}
		else if (PtInRect(&_enterance, _point))
		{
			SOUNDMANAGER->stop("bossbgm");
			//인벤토리 아이템 저장
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
			//플레이어 HP 골드 저장
			PLAYERDATA->setHp(_player->getHp());
			PLAYERDATA->setMp(_player->getMp());
			PLAYERDATA->setGold(_player->getInven()->getMoney());
			//앞으로가기
			PLAYERDATA->setComeback(false);
			SCENEMANAGER->loadScene("던전4화면");
		}
	}
	
}

void bossMap::render()
{
	//백그라운드 렌더
	_bossMap->render(getMemDC(), _x, _y);

	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 20, _y + 620, frameX[0], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 1380, _y + 840, frameX[1], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 1890, _y + 840, frameX[2], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 2390, _y + 840, frameX[3], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 2900, _y + 840, frameX[4], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 4680, _y + 680, frameX[5], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 5100, _y + 680, frameX[6], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 5580, _y + 680, frameX[7], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 6080, _y + 660, frameX[8], 0);

	
	if (PtInRect(&_exit, _point))
	{
		IMAGEMANAGER->alphaRender("notice", getMemDC(), _exit.left - 100, _exit.top - 100, 150);
		IMAGEMANAGER->render("enter", getMemDC(), _exit.left - 100, _exit.top - 100);
	}

	//플레이어 클래스 렌더
	_player->render();

	//적매니져 클래스 렌더
	_enemyManager->render();

}

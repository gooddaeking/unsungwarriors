#include "stdafx.h"
#include "cave3.h"

HRESULT cave3::init()
{

	_cave3 = IMAGEMANAGER->findImage("던전3");
	_collision = IMAGEMANAGER->findImage("던전3충돌");
	SOUNDMANAGER->play("cavebgm", 0.2f);

	if (!PLAYERDATA->getComeback())
	{
		_x = -2200;
		_y = -500;
		//플레이어 클래스 초기화
		_player = new player;
		_player->init();
		_player->set_X(_x + 2600);
		_player->set_Y(_y + 1000);
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
	_width = _cave3->getWidth();
	_height = _cave3->getHeight();
	_count = 0;

	for (int i = 0; i < 2; i++)
	{
		_jumping[i] = false;
		_jumpFrame[i] = 0;
	}

	CAMERADATA->setImage(_collision);
	CAMERADATA->set_X(_x);
	CAMERADATA->set_Y(_y);
	CAMERADATA->setWidth(_width);
	CAMERADATA->setHeight(_height);

	for (int i = 0; i < 10; i++)
	{
		frameX[i] = 0;
	}
	//적매니져 클래스 초기화
	_enemyManager = new enemyManager;
	_enemyManager->init2();


	//상호참조
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void cave3::release()
{
	//플레이어 클래스 해제
	_player->release();
	SAFE_DELETE(_player);

	//적매니져 클래스 해제
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void cave3::update()
{
	//플레이어 클래스 업데이트
	_player->update();

	CAMERADATA->getImage()->setX(CAMERADATA->get_X());
	CAMERADATA->getImage()->setY(CAMERADATA->get_Y());
	_point.x = _player->get_X();
	_point.y = _player->get_Y();

	_enterance = RectMake(_x + 440, _y + 2400, 120, 200);
	_exit = RectMake(_x + 2800, _y + 940, 120, 200);

	_pike[0] = RectMake(_x + 2135, _y + 2585, 277, 130);
	_pike[1] = RectMake(_x + 2680, _y + 2550, 270, 130);
	_spring[0] = RectMake(_x + 3860, _y + 1970, 64, 64);
	_spring[1] = RectMake(_x + 950, _y + 3290, 64, 64);

	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_pike[i], &_player->getHit()))
		{
			_player->setHp(_player->getHp() - 2);
			_player->setGravity(-20.0f);
			break;
		}
		if (IntersectRect(&rc, &_spring[i], &_player->getHit()))
		{
			_jumping[i] = true;
		}
	}

	//적매니져 업데이트
	_enemyManager->update();

	_x = CAMERADATA->get_X();
	_y = CAMERADATA->get_Y();

	_count++;
	if (_count % 5 == 0)
	{
		for (int i = 0; i < 10; i++)
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
		SOUNDMANAGER->stop("cavebgm");
		SCENEMANAGER->loadScene("시작화면");
	}
	if (INPUT->GetKeyDown('A'))
	{
		if (PtInRect(&_exit, _point))
		{
			SOUNDMANAGER->stop("cavebgm");
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
			PLAYERDATA->setComeback(true);
			SCENEMANAGER->loadScene("던전2화면");
		}
		else if (PtInRect(&_enterance, _point))
		{
			SOUNDMANAGER->stop("cavebgm");
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
			SCENEMANAGER->loadScene("보스맵");
		}
	}
	if (INPUT->GetKeyDown('Y'))
	{
		SOUNDMANAGER->stop("cavebgm");
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
		SCENEMANAGER->loadScene("보스맵");
	}
}

void cave3::render()
{
	//백그라운드 렌더
	_cave3->render(getMemDC(), _x, _y);

	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 2530, _y + 940 - 144, frameX[0], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 3279, _y + 928 - 144, frameX[1], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 263, _y + 2423 - 144, frameX[2], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 707, _y + 2418 - 144, frameX[3], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 965, _y + 2866 - 144, frameX[4], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 2244, _y + 2346 - 144, frameX[5], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 2787, _y + 2336 - 144, frameX[6], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 3374, _y + 1943 - 144, frameX[7], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 6714, _y + 888 - 144, frameX[8], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 5800, _y + 720 - 144, frameX[9], 0);

	IMAGEMANAGER->frameRender("spring", getMemDC(), _spring[0].left, _spring[0].top, _jumpFrame[0], 0);
	IMAGEMANAGER->frameRender("spring", getMemDC(), _spring[1].left, _spring[1].top, _jumpFrame[1], 0);

	for (int i = 0; i < 2; i++)
	{
		if (_jumping[i])
		{
			if (_count % 3 == 0)
			{
				_jumpFrame[i]++;
				if (_jumpFrame[i] > 2 && _jumpFrame[i] < 4)
				{
					if (_count % 3 == 0)
					{
						_player->setGravity(-40.0f);
						SOUNDMANAGER->play("jumping");
					}
				}
				if (_jumpFrame[i] > 4)
				{
					_jumpFrame[i] = 0;
					_jumping[i] = false;
				}
			}
		}
	}

	if (PtInRect(&_enterance, _point))
	{
		IMAGEMANAGER->alphaRender("notice", getMemDC(), _enterance.left - 80, _enterance.top - 100, 150);
		IMAGEMANAGER->render("enter", getMemDC(), _enterance.left - 80, _enterance.top - 100);
	}
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

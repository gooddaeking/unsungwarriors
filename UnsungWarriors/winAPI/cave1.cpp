#include "stdafx.h"
#include "cave1.h"

HRESULT cave1::init()
{

	_cave1 = IMAGEMANAGER->findImage("던전1");
	_collision = IMAGEMANAGER->findImage("던전1충돌");
	SOUNDMANAGER->play("cavebgm", 0.2f);

	if (!PLAYERDATA->getComeback())
	{
		_x = 0;
		_y = -1024;
		//플레이어 클래스 초기화
		_player = new player;
		_player->init();
		_player->set_X(_x + 300);
		_player->set_Y(_y + 1470);
	}
	else
	{
		_x = -14500;
		_y = -1300;
		//플레이어 클래스 초기화
		_player = new player;
		_player->init();
		_player->set_X(_x + 15700);
		_player->set_Y(_y + 1870);
	}

	
	_colX = _x;
	_colY = _y;
	_width = _cave1->getWidth();
	_height = _cave1->getHeight();
	_count = 0;
	for (int i = 0; i < 3; i++)
	{
		_jumping[i] = false;
		_jumpFrame[i] = 0;
	}

	for (int i = 0; i < 25; i++)
	{
		frameX[i] = 0;
	}

	CAMERADATA->setImage(_collision);
	CAMERADATA->set_X(_x);
	CAMERADATA->set_Y(_y);
	CAMERADATA->setWidth(_width);
	CAMERADATA->setHeight(_height);

	//적매니져 클래스 초기화
	_enemyManager = new enemyManager;
	_enemyManager->init1();

	//상호참조
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void cave1::release()
{
	//플레이어 클래스 해제
	_player->release();
	SAFE_DELETE(_player);

	//적매니져 클래스 해제
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void cave1::update()
{
	//플레이어 클래스 업데이트
	_player->update();

	CAMERADATA->getImage()->setX(CAMERADATA->get_X());
	CAMERADATA->getImage()->setY(CAMERADATA->get_Y());
	_point.x = _player->get_X();
	_point.y = _player->get_Y();

	_enterance = RectMake(_x + 15840, _y + 1770, 120, 200);

	_pike[0] = RectMake(_x + 3800, _y + 2160, 206, 142);
	_pike[1] = RectMake(_x + 4360, _y + 2160, 206, 142);
	_pike[2] = RectMake(_x + 11480, _y + 2560, 563, 148);
	_pike[3] = RectMake(_x + 14400, _y + 2560, 704, 156);
	_spring[0] = RectMake(_x + 3260, _y + 2440, 64, 64);
	_spring[1] = RectMake(_x + 4680, _y + 2020, 64, 64);
	_spring[2] = RectMake(_x + 4300, _y + 1600, 64, 64);

	for (int i = 0; i < 4; i++)
	{
		RECT rc;
		if(IntersectRect(&rc, &_pike[i], &_player->getHit()))
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
		for (int i = 0; i < 25; i++)
		{
			frameX[i]++;
			if (frameX[i] > 11)
			{
				frameX[i] = RANDOM->Range(0,3);
			}
		}
	}

	if (INPUT->GetKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->stop("cavebgm");
		SCENEMANAGER->loadScene("시작화면");
	}
	if (_point.x < 20)
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
		//돌아가기
		PLAYERDATA->setComeback(true);
		SCENEMANAGER->loadScene("필드화면");
	}
	if (INPUT->GetKeyDown('A') && PtInRect(&_enterance, _point))
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
		SCENEMANAGER->loadScene("던전2화면");
	}
	if (INPUT->GetKeyDown('Y'))
	{
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
		SCENEMANAGER->loadScene("던전2화면");
	}
}

void cave1::render()
{
	//백그라운드 렌더
	_cave1->render(getMemDC(), _x, _y);

	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 833, _y + 1307, frameX[0], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 1247, _y + 1503 - 144, frameX[1], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 1996, _y + 1446 - 144, frameX[2], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 2372, _y + 1604 - 144, frameX[3], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 2698, _y + 2509 - 144, frameX[4], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 3267, _y + 1727 - 144, frameX[5], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 3841, _y + 1857 - 144, frameX[6], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 4229, _y + 1392 - 144, frameX[7], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 4938, _y + 1009 - 144, frameX[8], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 6868, _y + 1351 - 144, frameX[9], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 7827, _y + 1460 - 144, frameX[10], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 8545, _y + 1760 - 144, frameX[11], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 9038, _y + 1375 - 144, frameX[12], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 9470, _y + 1375 - 144, frameX[13], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 9587, _y + 2244 - 144, frameX[14], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 10337, _y + 2395 - 144, frameX[15], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 11734, _y + 2338 - 144, frameX[16], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 12282, _y + 2191 - 144, frameX[17], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 12809, _y + 2192 - 144, frameX[18], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 13178, _y + 2129 - 144, frameX[19], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 14190, _y + 2306 - 144, frameX[20], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 14737, _y + 2221 - 144, frameX[21], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 15222, _y + 1988 - 144, frameX[22], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 15654, _y + 1788 - 144, frameX[23], 0);
	IMAGEMANAGER->frameRender("torch", getMemDC(), _x + 16085, _y + 1789 - 144, frameX[24], 0);

	IMAGEMANAGER->frameRender("spring", getMemDC(), _spring[0].left, _spring[0].top, _jumpFrame[0], 0);
	IMAGEMANAGER->frameRender("spring", getMemDC(), _spring[1].left, _spring[1].top, _jumpFrame[1], 0);
	IMAGEMANAGER->frameRender("spring", getMemDC(), _spring[2].left, _spring[2].top, _jumpFrame[2], 0);
	
	for (int i = 0; i < 3; i++)
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

	//플레이어 클래스 렌더
	_player->render();

	//적매니져 클래스 렌더
	_enemyManager->render();

}

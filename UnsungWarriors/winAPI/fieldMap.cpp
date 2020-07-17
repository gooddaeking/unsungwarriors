#include "stdafx.h"
#include "fieldMap.h"

HRESULT fieldMap::init()
{
	_terrain = IMAGEMANAGER->findImage("필드지형");
	_collision = IMAGEMANAGER->findImage("필드충돌");
	SOUNDMANAGER->play("fieldbgm", 0.2f);

	if (!PLAYERDATA->getComeback())
	{
		_x = 0;
		_y = -500;
		//플레이어 클래스 초기화
		_player = new player;
		_player->init();
		_player->set_X(_x + 300);
		_player->set_Y(_y + 1120);
	}
	else
	{
		_x = -4800;
		_y = -400;
		//플레이어 클래스 초기화
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

	//적매니져 클래스 초기화
	_enemyManager = new enemyManager;
	_enemyManager->init();
	

	//상호참조
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void fieldMap::release()
{
	//플레이어 클래스 해제
	_player->release();
	SAFE_DELETE(_player);

	//적매니져 클래스 해제
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void fieldMap::update()
{
	//플레이어 클래스 업데이트
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

	//적매니져 업데이트
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
		SCENEMANAGER->loadScene("던전1화면");
	}
	if (INPUT->GetKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->stop("fieldbgm");
		SCENEMANAGER->loadScene("시작화면");
	}
	if (INPUT->GetKeyDown('Y'))
	{
		SOUNDMANAGER->stop("fieldbgm");
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
		SCENEMANAGER->loadScene("던전1화면");
	}
}

void fieldMap::render()
{
	//백그라운드 렌더
	IMAGEMANAGER->render("백그라운드", getMemDC(), _bX, _bY);
	_terrain->render(getMemDC(), _x, _y);

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

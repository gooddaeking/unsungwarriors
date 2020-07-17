#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init()
{
	//플레이어 이미지 초기화
	_player = IMAGEMANAGER->findImage("idle");
	//플레이어 렉트
	//_rcPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 52, 64);

	frameX = frameY = _count = 0;
	//_x = CAMERADATA->get_X() + 300;
	//_y = CAMERADATA->get_Y() + 900;

	_speed = 5.0f;
	_gravity = 0.0f;
	_isLeft = false;
	_dashCount = magicFrameX = magicFrameY = alpha = 0;
	_dashOnL = _dashOnR = _dashLight = false;
	if (PLAYERDATA->getComeback()) _isLeft = true;
	_state = IDLE;
	_att2 = _att3 = _coolDown = _magicOn = false;
	_camera = RectMake(0, 0, WINSIZEX, WINSIZEY);

	//미사일 클래스 초기화
	_missile = new missile;
	_missile->init(10, 500);

	//폭탄 클래스 초기화
	_bomb = new bomb;
	_bomb->init(5, 600);

	//체력바 클래스 초기화
	_hpBar = new progressBar;
	_hpBar->init("frontHp", "bgHp");
	_mpBar = new progressBar2;
	_mpBar->init("frontMp", "bgMp");
	//피통 초기화
	_maxHp = 30;
	_maxMp = 100;
	_currentHp = PLAYERDATA->getHp();
	_currentMp = PLAYERDATA->getMp();
	_dmg = 1;
	_gold = 0;
	_life = true;
	
	_inven = new inven;
	_inven->init();
	_shop = new shop;
	_shop->init();

	//상호참조
	_inven->setSHOPLink(_shop);
	_shop->setInvenLink(_inven);

	return S_OK;
}

void player::release()
{
	//미사일 클래스 해제
	_missile->release();
	SAFE_DELETE(_missile);

	//폭탄 클래스 해제
	_bomb->release();
	SAFE_DELETE(_bomb);

	//체력바 클래스 해제
	_hpBar->release();
	SAFE_DELETE(_hpBar);

	//체력바 클래스 해제
	_mpBar->release();
	SAFE_DELETE(_mpBar);

	_inven->release();
	SAFE_DELETE(_inven);
	_shop->release();
	SAFE_DELETE(_shop);
}

void player::update()
{
	_vWeapon = _inven->getWeapon();
	if (!_vWeapon.empty()) _dmg = _vWeapon[0]._dmg;
	_vAcce = _inven->getAcce();
	_vShield = _inven->getShield();
	PLAYERDATA->setX(_x);
	PLAYERDATA->setY(_y);
	if (_life)
	{
		_hit = RectMakeCenter(_x + 35, _y + 70, 70, 70);
		_dashCount++;
		if (_dashCount % 20 == 0)
		{
			_dashOnL = _dashOnR = false;
		}

		if (_count % 10 == 0) _currentMp++;
		if (_currentMp > _maxMp)
		{
			_currentMp = _maxMp;
		}

		//플레이어 움직이기 & 화면밖으로 나가지 못하게 만들기
		if (INPUT->GetKey(VK_LEFT) && _x > 0 &&
			_state != ATT1 && _state != ATT2 && _state != ATT3)
		{
			_x -= _speed;
			_isLeft = true;
			_state = MOVE;
			if (_dashOnL)
			{
				_dashLight = true;
				frameX = 7;
				_x -= 200;
				_dashOnL = _dashOnR = false;
				_dashCount = 0;
			}
		}
		else if (INPUT->GetKey(VK_RIGHT) && _x + 70 < WINSIZEX &&
			_state != ATT1 && _state != ATT2 && _state != ATT3)
		{
			_x += _speed;
			_isLeft = false;
			_state = MOVE;
			if (_dashOnR)
			{
				_dashLight = true;
				frameX = 0;
				_x += 200;
				_dashOnL = _dashOnR = false;
				_dashCount = 0;
			}
		}
		if (INPUT->GetKeyDown(VK_UP) &&
			_state != ATT1 && _state != ATT2 && _state != ATT3)
		{
			_gravity = -20.0f;
			_state = JUMP;
			if (!_isLeft)
			{
				frameX = 0;
			}
			else
			{
				frameX = 6;
			}
		}
		else if (INPUT->GetKey(VK_DOWN))
		{
			_y += _speed;
			_state = MOVE;
		}
		if (INPUT->GetKeyUp(VK_LEFT))
		{
			_state = IDLE;
			_count = 0;
			if (_dashCount > 120)
			{
				_dashOnL = true;
				_dashCount = 0;
			}
		}
		if (INPUT->GetKeyUp(VK_RIGHT))
		{
			_state = IDLE;
			_count = 0;
			if (_dashCount > 120)
			{
				_dashOnR = true;
				_dashCount = 0;
			}
		}



		//총알발사
		if (INPUT->GetKeyDown('Z') && _coolDown)
		{
			_gravity = 0;
			_count = 0;
			if (_state != ATT1 && _state != ATT2 && _state != ATT3)
			{
				_state = ATT1;
				if (!_isLeft)
				{
					frameX = 0;
				}
				else
				{
					frameX = 6;
				}
			}
			else if (_state == ATT1)
			{
				_att2 = true;
			}
			else if (_state == ATT2)
			{
				_att3 = true;
			}
		}
		//폭탄발사
		if (INPUT->GetKeyDown('B'))
		{
			_bomb->fire(_player->getX() + _player->getWidth() / 2, _player->getY() - 50);
		}
		if (INPUT->GetKeyDown('S') && !_vAcce.empty())
		{
			if (!_isLeft)
			{
				if (_vAcce[0]._itemName == "taranis" && _currentMp >= 20)
				{
					_currentMp -= 20;
					_magicOn = true;
					magicFrameX = 0;
				}
			}
			else
			{
				if (_vAcce[0]._itemName == "taranis"&& _currentMp >= 20)
				{
					_currentMp -= 20;
					_magicOn = true;
					magicFrameX = 7;
				}
			}
			if (_vAcce[0]._itemName == "bark" && _currentMp >= 40)
			{
				_currentMp -= 40;
				_magicOn = true;
			}
		}

		if (_currentHp <= 0)
		{
			_currentHp = 0;
			_life = false;
		}
	}
	else
	{
		_state = DEAD;
		for (int i = 0; i < _em->getMinion().size(); i++)
		{
			_em->getMinion()[i]->setState(E_IDLE);
		}
		for (int i = 0; i < _em->getBoss().size(); i++)
		{
			_em->getBoss()[i]->setState(E_MOVE);
			for (int j = 0; j < _em->getBoss()[i]->getMinion().size(); j++)
			{
				_em->getBoss()[i]->getMinion()[j]->setState(E_IDLE);
			}
		}
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			PLAYERDATA->setHp(_maxHp);
			SOUNDMANAGER->stop("fieldbgm");
			SOUNDMANAGER->stop("cavebgm");
			SOUNDMANAGER->stop("cave2bgm");
			SOUNDMANAGER->stop("bossbgm");
			SCENEMANAGER->loadScene("시작화면");
		}
	}

	//미사일 클래스 업데이트
	_missile->update();
	//폭탄 클래스 업데이트
	_bomb->update();
	//충돌함수
	this->collision();

	//체력바 업데이트
	_hpBar->update();
	//체력바 위치, 피통도 업데이트 해줘야 한다
	_hpBar->setPos(165, 20);
	_hpBar->setGauge(_maxHp, _currentHp);
	_mpBar->update();
	_mpBar->setPos(165, 50);
	_mpBar->setGauge(_maxMp, _currentMp);


	//플레이어 데이터로 세이브 로드
	if (INPUT->GetKeyDown('F5'))
	{
		this->save();
	}
	if (INPUT->GetKeyDown('F8'))
	{
		this->load();
	}

	_gravity += 1.0f;
	if (_gravity > 7.0f)
	{
		_state = FALL;
	}
	if (_gravity > 13.0f)
	{
		_gravity = 13.0f;
	}
	_y += _gravity;

	
	_probeD = _y + _player->getHeight() / 2;
	_probeR = _x + 70;
	
	for (int i = _probeD - 10; i < _probeD; i++)
	{
		COLORREF color = GetPixel(CAMERADATA->getImage()->getMemDC(), _x + 35 - CAMERADATA->get_X(), i - CAMERADATA->get_Y());
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _player->getHeight() / 2;
			_gravity = 0;
			_coolDown = true;
			if (!INPUT->GetKey(VK_LEFT) && !INPUT->GetKey(VK_RIGHT)
				&& _state != ATT1 && _state != ATT2 && _state != ATT3)
			{
				_state = IDLE;
			}
			break;
		}
	}
	for (int i = _y + 5; i < _y + 15; i++)
	{
		COLORREF color = GetPixel(CAMERADATA->getImage()->getMemDC(), _x + 35 - CAMERADATA->get_X(), i - CAMERADATA->get_Y());
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i;
			_gravity = 0;
			break;
		}
	}
	for (int i = _x + 5; i < _x + 15; i++)
	{
		COLORREF color = GetPixel(CAMERADATA->getImage()->getMemDC(), i - CAMERADATA->get_X(), _y + 52 - CAMERADATA->get_Y());
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_x = i;
			break;
		}
	}
	for (int i = _probeR - 15; i < _probeR + 5; i++)
	{
		COLORREF color = GetPixel(CAMERADATA->getImage()->getMemDC(), i - CAMERADATA->get_X(), _y + 52 - CAMERADATA->get_Y());
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_x = i - 70;
			break;
		}
	}
	
	this->animation();
	this->camera();

	_inven->update();
	_shop->update();
}

void player::render()
{

	//플레이어 렌더
	//_player->frameRender(getMemDC(), _player->getX(), _player->getY(),frameX,frameY);
	if(_state == IDLE) IMAGEMANAGER->frameRender("idle", getMemDC(), _x, _y, frameX, frameY);
	else if(_state == MOVE) IMAGEMANAGER->frameRender("move", getMemDC(), _x, _y, frameX, frameY);
	else if (_state == JUMP) IMAGEMANAGER->frameRender("jump", getMemDC(), _x, _y, frameX, frameY);
	else if (_state == FALL) IMAGEMANAGER->frameRender("fall", getMemDC(), _x, _y, frameX, frameY);
	else if (_state == ATT1)
	{
		IMAGEMANAGER->frameRender("att1", getMemDC(), _x, _y, frameX, frameY);
		IMAGEMANAGER->frameRender("잔상1", getMemDC(), _x - 80, _y - 40, frameX, frameY);
	}
	else if (_state == ATT2) 
	{
		IMAGEMANAGER->frameRender("att2", getMemDC(), _x, _y, frameX, frameY);
		IMAGEMANAGER->frameRender("잔상2", getMemDC(), _x - 100, _y - 80, frameX, frameY);
	}
	else if (_state == ATT3)
	{
		IMAGEMANAGER->frameRender("att3", getMemDC(), _x, _y, frameX, frameY);
		IMAGEMANAGER->frameRender("잔상3", getMemDC(), _x - 100, _y - 40, frameX, frameY);
	}
	else if (_state == DEAD)
	{
		IMAGEMANAGER->alphaRender("death", getMemDC(), _x, _y, alpha);
	}


	if (_magicOn)
	{
		if (_count % 2 == 0 && !_isLeft)
		{
			magicFrameX++;
			alpha += 10;
		}
		else if (_count % 2 == 0 && _isLeft)
		{
			magicFrameX--;
			alpha += 10;
		}
		if (_vAcce[0]._itemName == "taranis" && !_isLeft)
		{
			IMAGEMANAGER->frameRender("electric", getMemDC(), _x + 52, _y + 35, frameX, 0);
			if (magicFrameX > 3 && magicFrameX < 5)
			{
				electric = RectMake(_x + 52, _y + 35, 256, 64);
			}
			if (magicFrameX > 7)
			{
				magicFrameX = 0;
				_magicOn = false;
				electric = RectMake(0, 0, 0, 0);
			}
		}
		else if (_vAcce[0]._itemName == "taranis" && _isLeft)
		{
			IMAGEMANAGER->frameRender("electric", getMemDC(), _x - 256, _y + 35, frameX, 1);
			if (magicFrameX > 3 && magicFrameX < 5)
			{
				electric = RectMake(_x - 256, _y + 35, 256, 64);
			}
			if (magicFrameX < 0)
			{
				magicFrameX = 0;
				_magicOn = false;
				electric = RectMake(0, 0, 0, 0);
			}
		}
		if (_vAcce[0]._itemName == "bark")
		{
			IMAGEMANAGER->alphaRender("heal", getMemDC(), _x - 20 , _y, alpha);
			if (alpha > 205)
			{
				_magicOn = false;
				_currentHp += 2;
				alpha = 0;
			}
		}
	}

	IMAGEMANAGER->render("inven(icon)", getMemDC(), 160, 80);
	if (!_vAcce.empty()) _vAcce[0]._itemIcon->render(getMemDC(), 250, 72);

	if (!_isLeft && _dashLight)
	{
		IMAGEMANAGER->frameRender("dash", getMemDC(), _x - 205, _y, frameX, 0);
		if (_count % 2 == 0)
		{
			frameX++;
			if (frameX > 7)
			{
				_dashLight = false;
			}
		}
	}
	if (_isLeft && _dashLight)
	{
		IMAGEMANAGER->frameRender("dash", getMemDC(), _x + 35, _y, frameX, 1);
		if (_count % 2 == 0)
		{
			frameX--;
			if (frameX < 0)
			{
				_dashLight = false;
			}
		}
	}

	//무기 랜더
	if (_state == IDLE)
	{
		if (!_isLeft) IMAGEMANAGER->frameRender("crude(idle)", getMemDC(), _x, _y + 67, frameX, 0);
		else if (_isLeft) IMAGEMANAGER->frameRender("crude(idle)", getMemDC(), _x - 10, _y + 67, frameX, 1);
	}
	else if (_state == MOVE)
	{
		if (!_isLeft) IMAGEMANAGER->frameRender("crude(move)", getMemDC(), _x - 8, _y - 12, frameX, 0);
		else if (_isLeft) IMAGEMANAGER->frameRender("crude(move)", getMemDC(), _x - 81, _y - 12, frameX, 1);
	}
	else if (_state == JUMP)
	{
		if (!_isLeft) IMAGEMANAGER->frameRender("crude(jump)", getMemDC(), _x, _y + 61, frameX, 0);
		else if (_isLeft) IMAGEMANAGER->frameRender("crude(jump)", getMemDC(), _x - 10, _y + 61, frameX, 1);
	}
	else if (_state == FALL)
	{
		if (!_isLeft) IMAGEMANAGER->frameRender("crude(fall)", getMemDC(), _x - 8, _y + 59, frameX, 0);
		else if (_isLeft) IMAGEMANAGER->frameRender("crude(fall)", getMemDC(), _x - 18, _y + 59, frameX, 1);
	}
	else if (_state == ATT1)
	{
		if (!_isLeft) IMAGEMANAGER->frameRender("crude(att1)", getMemDC(), _x - 56, _y - 25, frameX, 0);
		else if (_isLeft) IMAGEMANAGER->frameRender("crude(att1)", getMemDC(), _x - 40, _y - 25, frameX, 1);
	}
	else if (_state == ATT2)
	{
		if (!_isLeft) IMAGEMANAGER->frameRender("crude(att2)", getMemDC(), _x - 55, _y + 10, frameX, 0);
		else if (_isLeft) IMAGEMANAGER->frameRender("crude(att2)", getMemDC(), _x + 55, _y + 10, frameX, 1);
	}
	else if (_state == ATT3)
	{
		if (!_isLeft) IMAGEMANAGER->frameRender("crude(att3)", getMemDC(), _x - 15, _y - 22, frameX, 0);
		else if (_isLeft) IMAGEMANAGER->frameRender("crude(att3)", getMemDC(), _x - 32, _y - 22, frameX, 1);
	}

	//for (int i = 0; i < _att.size(); i++)
	//{
	//	Rectangle(getMemDC(),_att[i]);
	//}

	//미사일 클래스 렌더
	_missile->render();

	//폭탄 클래스 렌더
	_bomb->render();

	//체력바 클래스 렌더
	_hpBar->render();
	_mpBar->render();
	IMAGEMANAGER->render("CharPortrait",getMemDC());

	
	_inven->render();
	_shop->render();
}
//폭탄삭제
void player::removeBomb(int index)
{
	_bomb->removeBomb(index);
}

//충돌함수(플레이어총알, 미니언충돌)
void player::collision()
{
	for (int i = 0; i < _bomb->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_bomb->getBullet()[i].rc,
				&_em->getMinion()[j]->getRect()))
			{
				_bomb->removeBomb(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

	for (int j = 0; j < _em->getMinion().size(); j++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_rcAtt,
			&_em->getMinion()[j]->getRect()) && _x + 35 < _em->getMinion()[j]->getEnemyX() + 72)
		{
			_em->getMinion()[j]->setCount(0);
			_em->getMinion()[j]->setFrameX(9);
			_em->getMinion()[j]->setState(E_HIT);
			_em->getMinion()[j]->setIsLeft(true);
			_em->getMinion()[j]->setHp(_em->getMinion()[j]->getHp() - _dmg);
		}
		else if (IntersectRect(&rc, &_rcAtt,
			&_em->getMinion()[j]->getRect()) && _x + 35 > _em->getMinion()[j]->getEnemyX() + 72)
		{
			_em->getMinion()[j]->setCount(0);
			_em->getMinion()[j]->setFrameX(0);
			_em->getMinion()[j]->setState(E_HIT);
			_em->getMinion()[j]->setIsLeft(false);
			_em->getMinion()[j]->setHp(_em->getMinion()[j]->getHp() - _dmg);
		}
		if (IntersectRect(&rc, &_rcAtt2,
			&_em->getMinion()[j]->getRect()) && _x + 35 < _em->getMinion()[j]->getEnemyX() + 72)
		{
			_em->getMinion()[j]->setCount(0);
			_em->getMinion()[j]->setFrameX(9);
			_em->getMinion()[j]->setState(E_HIT);
			_em->getMinion()[j]->setIsLeft(true);
			_em->getMinion()[j]->setHp(_em->getMinion()[j]->getHp() - _dmg);

		}
		else if (IntersectRect(&rc, &_rcAtt2,
			&_em->getMinion()[j]->getRect()) && _x + 35 > _em->getMinion()[j]->getEnemyX() + 72)
		{
			_em->getMinion()[j]->setCount(0);
			_em->getMinion()[j]->setFrameX(0);
			_em->getMinion()[j]->setState(E_HIT);
			_em->getMinion()[j]->setIsLeft(false);
			_em->getMinion()[j]->setHp(_em->getMinion()[j]->getHp() - _dmg);
		}
		if (IntersectRect(&rc, &_rcAtt3,
			&_em->getMinion()[j]->getRect()) && _x + 35 < _em->getMinion()[j]->getEnemyX() + 72)
		{
			_em->getMinion()[j]->setCount(0);
			_em->getMinion()[j]->setFrameX(11);
			_em->getMinion()[j]->setGravity(-15.0f);
			_em->getMinion()[j]->setState(E_HIT2);
			_em->getMinion()[j]->setIsLeft(true);
			_em->getMinion()[j]->setHp(_em->getMinion()[j]->getHp() - (_dmg + 2));
		}
		else if (IntersectRect(&rc, &_rcAtt3,
			&_em->getMinion()[j]->getRect()) && _x + 35 > _em->getMinion()[j]->getEnemyX() + 72)
		{
			_em->getMinion()[j]->setCount(0);
			_em->getMinion()[j]->setFrameX(0);
			_em->getMinion()[j]->setGravity(-15.0f);
			_em->getMinion()[j]->setState(E_HIT2);
			_em->getMinion()[j]->setIsLeft(false);
			_em->getMinion()[j]->setHp(_em->getMinion()[j]->getHp() - (_dmg + 2));
		}

		if (IntersectRect(&rc, &_hit, &_em->getMinion()[j]->getAttRect()))
		{
			_currentHp -= _em->getMinion()[j]->getDmg();
			_em->getMinion()[j]->setHit(true);
			break;
		}
	}

	for (int j = 0; j < _em->getMinion().size(); j++)
	{
		RECT rc;
		if (IntersectRect(&rc, &electric,
			&_em->getMinion()[j]->getRect()) && _x + 35 < _em->getMinion()[j]->getEnemyX() + 72)
		{
			_em->getMinion()[j]->setCount(0);
			_em->getMinion()[j]->setFrameX(9);
			_em->getMinion()[j]->setState(E_HIT);
			_em->getMinion()[j]->setIsLeft(true);
			_em->getMinion()[j]->setHp(_em->getMinion()[j]->getHp() - _inven->getItem()->getItem()[9]._dmg);
		}
		else if (IntersectRect(&rc, &electric,
			&_em->getMinion()[j]->getRect()) && _x + 35 > _em->getMinion()[j]->getEnemyX() + 72)
		{
			_em->getMinion()[j]->setCount(0);
			_em->getMinion()[j]->setFrameX(0);
			_em->getMinion()[j]->setState(E_HIT);
			_em->getMinion()[j]->setIsLeft(false);
			_em->getMinion()[j]->setHp(_em->getMinion()[j]->getHp() - _inven->getItem()->getItem()[9]._dmg);
		}
	}

	for (int i = 0; i < _em->getBoss().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_rcAtt,
			&_em->getBoss()[i]->getRect()) && _x + 35 < _em->getBoss()[i]->getEnemyX() + 250)
		{
			_em->getBoss()[i]->setIsLeft(true);
			_em->getBoss()[i]->setHp(_em->getBoss()[i]->getHp() - _dmg);
		}
		else if (IntersectRect(&rc, &_rcAtt,
			&_em->getBoss()[i]->getRect()) && _x + 35 > _em->getBoss()[i]->getEnemyX() + 250)
		{
			_em->getBoss()[i]->setIsLeft(false);
			_em->getBoss()[i]->setHp(_em->getBoss()[i]->getHp() - _dmg);
		}
		if (IntersectRect(&rc, &_rcAtt2,
			&_em->getBoss()[i]->getRect()) && _x + 35 < _em->getBoss()[i]->getEnemyX() + 250)
		{
			_em->getBoss()[i]->setIsLeft(true);
			_em->getBoss()[i]->setHp(_em->getBoss()[i]->getHp() - _dmg);

		}
		else if (IntersectRect(&rc, &_rcAtt2,
			&_em->getBoss()[i]->getRect()) && _x + 35 > _em->getBoss()[i]->getEnemyX() + 250)
		{
			_em->getBoss()[i]->setIsLeft(false);
			_em->getBoss()[i]->setHp(_em->getBoss()[i]->getHp() - _dmg);
		}
		if (IntersectRect(&rc, &_rcAtt3,
			&_em->getBoss()[i]->getRect()) && _x + 35 < _em->getBoss()[i]->getEnemyX() + 250)
		{
			_em->getBoss()[i]->setIsLeft(true);
			_em->getBoss()[i]->setHp(_em->getBoss()[i]->getHp() - (_dmg + 2));
		}
		else if (IntersectRect(&rc, &_rcAtt3,
			&_em->getBoss()[i]->getRect()) && _x + 35 > _em->getBoss()[i]->getEnemyX() + 250)
		{
			_em->getBoss()[i]->setIsLeft(false);
			_em->getBoss()[i]->setHp(_em->getBoss()[i]->getHp() - (_dmg + 2));
		}
		if (IntersectRect(&rc, &_hit, &_em->getBoss()[i]->getAttRect()))
		{
			_currentHp -= _em->getBoss()[i]->getDmg();
			_em->getBoss()[i]->setHit(true);
			break;
		}
		for (int j = 0; j < _em->getBoss()[i]->getMinion().size(); j++)
		{
			if (IntersectRect(&rc, &_rcAtt,
				&_em->getBoss()[i]->getMinion()[j]->getRect()) && _x + 35 < _em->getBoss()[i]->getMinion()[j]->getEnemyX() + 72)
			{
				_em->getBoss()[i]->getMinion()[j]->setCount(0);
				_em->getBoss()[i]->getMinion()[j]->setFrameX(9);
				_em->getBoss()[i]->getMinion()[j]->setState(E_HIT);
				_em->getBoss()[i]->getMinion()[j]->setIsLeft(true);
				_em->getBoss()[i]->getMinion()[j]->setHp(_em->getBoss()[i]->getMinion()[j]->getHp() - _dmg);
			}
			else if (IntersectRect(&rc, &_rcAtt,
				&_em->getBoss()[i]->getMinion()[j]->getRect()) && _x + 35 > _em->getBoss()[i]->getMinion()[j]->getEnemyX() + 72)
			{
				_em->getBoss()[i]->getMinion()[j]->setCount(0);
				_em->getBoss()[i]->getMinion()[j]->setFrameX(0);
				_em->getBoss()[i]->getMinion()[j]->setState(E_HIT);
				_em->getBoss()[i]->getMinion()[j]->setIsLeft(false);
				_em->getBoss()[i]->getMinion()[j]->setHp(_em->getBoss()[i]->getMinion()[j]->getHp() - _dmg);
			}
			if (IntersectRect(&rc, &_rcAtt2,
				&_em->getBoss()[i]->getMinion()[j]->getRect()) && _x + 35 < _em->getBoss()[i]->getMinion()[j]->getEnemyX() + 72)
			{
				_em->getBoss()[i]->getMinion()[j]->setCount(0);
				_em->getBoss()[i]->getMinion()[j]->setFrameX(9);
				_em->getBoss()[i]->getMinion()[j]->setState(E_HIT);
				_em->getBoss()[i]->getMinion()[j]->setIsLeft(true);
				_em->getBoss()[i]->getMinion()[j]->setHp(_em->getBoss()[i]->getMinion()[j]->getHp() - _dmg);

			}
			else if (IntersectRect(&rc, &_rcAtt2,
				&_em->getBoss()[i]->getMinion()[j]->getRect()) && _x + 35 > _em->getBoss()[i]->getMinion()[j]->getEnemyX() + 72)
			{
				_em->getBoss()[i]->getMinion()[j]->setCount(0);
				_em->getBoss()[i]->getMinion()[j]->setFrameX(0);
				_em->getBoss()[i]->getMinion()[j]->setState(E_HIT);
				_em->getBoss()[i]->getMinion()[j]->setIsLeft(false);
				_em->getBoss()[i]->getMinion()[j]->setHp(_em->getBoss()[i]->getMinion()[j]->getHp() - _dmg);
			}
			if (IntersectRect(&rc, &_rcAtt3,
				&_em->getBoss()[i]->getMinion()[j]->getRect()) && _x + 35 < _em->getBoss()[i]->getMinion()[j]->getEnemyX() + 72)
			{
				_em->getBoss()[i]->getMinion()[j]->setCount(0);
				_em->getBoss()[i]->getMinion()[j]->setFrameX(11);
				_em->getBoss()[i]->getMinion()[j]->setGravity(-15.0f);
				_em->getBoss()[i]->getMinion()[j]->setState(E_HIT2);
				_em->getBoss()[i]->getMinion()[j]->setIsLeft(true);
				_em->getBoss()[i]->getMinion()[j]->setHp(_em->getBoss()[i]->getMinion()[j]->getHp() - (_dmg + 2));
			}
			else if (IntersectRect(&rc, &_rcAtt3,
				&_em->getBoss()[i]->getMinion()[j]->getRect()) && _x + 35 > _em->getBoss()[i]->getMinion()[j]->getEnemyX() + 72)
			{
				_em->getBoss()[i]->getMinion()[j]->setCount(0);
				_em->getBoss()[i]->getMinion()[j]->setFrameX(0);
				_em->getBoss()[i]->getMinion()[j]->setGravity(-15.0f);
				_em->getBoss()[i]->getMinion()[j]->setState(E_HIT2);
				_em->getBoss()[i]->getMinion()[j]->setIsLeft(false);
				_em->getBoss()[i]->getMinion()[j]->setHp(_em->getBoss()[i]->getMinion()[j]->getHp() - (_dmg + 2));
			}
			if (IntersectRect(&rc, &_hit, &_em->getBoss()[i]->getMinion()[j]->getAttRect()))
			{
				_currentHp -= _em->getBoss()[i]->getMinion()[j]->getDmg();
				_em->getBoss()[i]->getMinion()[j]->setHit(true);
				break;
			}
		}
	}
}

//피통깍기
void player::hitDamage(float damage)
{
	_currentHp -= damage;
}

void player::save()
{
	PLAYERDATA->setHp(_currentHp);
}

void player::load()
{
	_currentHp = PLAYERDATA->getHp();
}

void player::animation()
{
	switch (_state)
	{
	case IDLE:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			if (_count % 6 == 0)
			{
				frameX++;
				if (frameX > 9)
				{
					frameX = 0;
				}
			}
		}
		else
		{
			frameY = 1;
			if (_count % 6 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 9;
				}
			}
		}
		break;
	case MOVE:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			if (_count % 5 == 0)
			{
				frameX++;
				if (frameX > 13)
				{
					frameX = 0;
				}
			}
		}
		else
		{
			frameY = 1;
			if (_count % 5 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 13;
				}
			}
		}
		break;
	case JUMP:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			if (_count % 4 == 0)
			{
				frameX++;
				if (frameX > 6)
				{
					frameX = 6;
				}
			}
		}
		else
		{
			frameY = 1;
			if (_count % 4 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 0;
				}
			}
		}
		break;
		//case RUN:
		//	//왼쪽프레임 일때 인덱스 변경하기(애니메이션)
		//	break;
	case FALL:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			if (_count % 3 == 0)
			{
				frameX++;
				if (frameX > 3)
				{
					frameX = 3;
				}
			}
		}
		else
		{
			frameY = 1;
			if (_count % 3 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 0;
				}
			}
		}
		break;
	case ATT1:
		_gravity = -1;
		_count++;
		if (_count > 25)
		{
			_state = IDLE;
		}
		if (!_isLeft)
		{
			if (frameX < 3)
			{
				_x += 5;
			}
			frameY = 0;
			if (frameX > 0 && frameX < 2)
			{
				_rcAtt = RectMake(_x + 45, _y + 35, 70, 70);
				if (_count % 3 == 0)
				{
					SOUNDMANAGER->play("타격1", 0.4f);
				}
			}
			if (_count % 3 == 0)
			{
				frameX++;
				if (frameX > 6)
				{
					_rcAtt = RectMake(0, 0, 0, 0);
					frameX = 6;
					if (_att2)
					{
						_state = ATT2;
						if (!_isLeft)
						{
							frameX = 0;
							_x += 1.0f;
						}
						else
						{
							frameX = 6;
							_x -= 1.0f;
						}
					}
				}
			}
		}
		else
		{
			if (frameX > 3)
			{
				_x -= 5;
			}
			frameY = 1;
			if (frameX < 6 && frameX > 4)
			{
				_rcAtt = RectMake(_x - 35, _y + 35, 70, 70);
				if (_count % 3 == 0)
				{
					SOUNDMANAGER->play("타격1", 0.4f);
				}
			}
			if (_count % 3 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					_rcAtt = RectMake(0, 0, 0, 0);
					frameX = 0;
					if (_att2)
					{
						_state = ATT2;
						if (!_isLeft)
						{
							frameX = 0;
							_x += 1.0f;
						}
						else
						{
							frameX = 6;
							_x -= 1.0f;
						}
					}
				}
			}
		}
		break;
	case ATT2:
		_gravity = -1;
		_count++;
		if (_count > 25)
		{
			_state = IDLE;
			_att2 = false;
		}
		if (!_isLeft)
		{
			if (frameX < 3)
			{
				_x += 5;
			}
			frameY = 0;
			if (frameX > 3 && frameX < 5)
			{
				_rcAtt2 = RectMake(_x + 45, _y + 35, 70, 70);
				if (_count % 3 == 0)
				{
					SOUNDMANAGER->play("타격2", 0.4f);
				}
			}
			if (_count % 2 == 0)
			{
				frameX++;
				if (frameX > 6)
				{
					_rcAtt2 = RectMake(0, 0, 0, 0);
					frameX = 6;
					_gravity = 0;
					if (_att3)
					{
						_state = ATT3;
						_att2 = false;
						if (!_isLeft)
						{
							frameX = 0;
							_x += 1.0f;
						}
						else
						{
							frameX = 6;
							_x -= 1.0f;
						}
					}
				}
			}
		}
		else
		{
			if (frameX > 3)
			{
				_x -= 5;
			}
			frameY = 1;
			if (frameX < 3 && frameX > 1)
			{
				_rcAtt2 = RectMake(_x - 35, _y + 35, 70, 70);
				if (_count % 3 == 0)
				{
					SOUNDMANAGER->play("타격2", 0.4f);
				}
			}
			if (_count % 2 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					_rcAtt2 = RectMake(0, 0, 0, 0);
					frameX = 0;
					_gravity = 0;
					if (_att3)
					{
						_state = ATT3;
						_att2 = false;
						if (!_isLeft)
						{
							frameX = 0;
							_x += 1.0f;
						}
						else
						{
							frameX = 6;
							_x -= 1.0f;
						}
					}
				}
			}
		}
		break;
	case ATT3:
		_gravity = -4.0f;
		_count++;
		if (!_isLeft)
		{
			if (frameX < 3)
			{
				_x += 5;
			}
			frameY = 0;
			if (frameX > 3 && frameX < 5)
			{
				_rcAtt3 = RectMake(_x + 45, _y + 35, 70, 70);
				if (_count % 4 == 0)
				{
					SOUNDMANAGER->play("타격3", 0.4f);
				}
			}
			if (_count % 4 == 0)
			{
				_rcAtt3 = RectMake(0, 0, 0, 0);
				frameX++;
				if (frameX > 6)
				{
					frameX = 6;
					_state = IDLE;
					_att3 = false;
					_coolDown = false;
				}
			}
		}
		else
		{
			if (frameX > 3)
			{
				_x -= 5;
			}
			frameY = 1;
			if (frameX < 3 && frameX > 1)
			{
				_rcAtt3 = RectMake(_x - 35, _y + 35, 70, 70);
				if (_count % 4 == 0)
				{
					SOUNDMANAGER->play("타격3", 0.4f);
				}
			}
			if (_count % 4 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					_rcAtt3 = RectMake(0, 0, 0, 0);
					frameX = 0;
					_state = IDLE;
					_att3 = false;
					_coolDown = false;
				}
			}
		}
		break;
	case HIT:
		break;
	case DEAD:
		_count++;
		_gravity = -2.0f;
		if (alpha >= 50 && alpha < 60)
		{
			SOUNDMANAGER->play("죽음", 0.4f);
		}
		if (_count % 4 == 0)
		{
			alpha += 10;
			if (alpha > 255)
			{
				alpha = 200;
			}
		}
		break;
	}
}

void player::camera()
{
	
	if (!_isLeft )
	{
		_camera.right = _x + 1230;
		_camera.left = _x - 370;
		_camera.top = _y - 550;
		_camera.bottom = _y + 350;

		if (_camera.right > WINSIZEX && CAMERADATA->get_X() - 10 > WINSIZEX - CAMERADATA->getWidth())
		{
			_x -= _speed;
			_camera.right -= _speed;
			CAMERADATA->set_X(CAMERADATA->get_X() - _speed);
			for (int i = 0; i < _em->getMinion().size(); i++)
			{
				_em->getMinion()[i]->setEnemyX(_em->getMinion()[i]->getEnemyX() - _speed);
			}
			for (int i = 0; i < _em->getBoss().size(); i++)
			{
				_em->getBoss()[i]->setEnemyX(_em->getBoss()[i]->getEnemyX() - _speed);
				for (int j = 0; j < _em->getBoss()[i]->getMinion().size(); j++)
				{
					_em->getBoss()[i]->getMinion()[j]->setEnemyX(_em->getBoss()[i]->getMinion()[j]->getEnemyX() - _speed);
				}
			}
			
		}
		if (_camera.right > WINSIZEX + 100 && CAMERADATA->get_X() - 10 > WINSIZEX - CAMERADATA->getWidth())
		{
			_x -= (_camera.right - WINSIZEX) / 50;
			_camera.right -= (_camera.right - WINSIZEX) / 50;
			CAMERADATA->set_X(CAMERADATA->get_X() - (_camera.right - WINSIZEX) / 50);
			for (int i = 0; i < _em->getMinion().size(); i++)
			{
				_em->getMinion()[i]->setEnemyX(_em->getMinion()[i]->getEnemyX() - (_camera.right - WINSIZEX) / 50);
			}
			for (int i = 0; i < _em->getBoss().size(); i++)
			{
				_em->getBoss()[i]->setEnemyX(_em->getBoss()[i]->getEnemyX() - (_camera.right - WINSIZEX) / 50);
				for (int j = 0; j < _em->getBoss()[i]->getMinion().size(); j++)
				{
					_em->getBoss()[i]->getMinion()[j]->setEnemyX(_em->getBoss()[i]->getMinion()[j]->getEnemyX() - (_camera.right - WINSIZEX) / 50);
				}
			}
		}
	}
	else if (_isLeft)
	{
		_camera.left = _x - 1230;
		_camera.right = _x + 370;
		_camera.top = _y - 550;
		_camera.bottom = _y + 350;

		if (_camera.left < 0 && CAMERADATA->get_X() + 10 < 0)
		{
			_x += _speed;
			_camera.left += _speed;
			CAMERADATA->set_X(CAMERADATA->get_X() + _speed);
			for (int i = 0; i < _em->getMinion().size(); i++)
			{
				_em->getMinion()[i]->setEnemyX(_em->getMinion()[i]->getEnemyX() + _speed);
			}
			for (int i = 0; i < _em->getBoss().size(); i++)
			{
				_em->getBoss()[i]->setEnemyX(_em->getBoss()[i]->getEnemyX() + _speed);
				for (int j = 0; j < _em->getBoss()[i]->getMinion().size(); j++)
				{
					_em->getBoss()[i]->getMinion()[j]->setEnemyX(_em->getBoss()[i]->getMinion()[j]->getEnemyX() + _speed);
				}
			}
		}
		if (_camera.left < -100 && CAMERADATA->get_X() + 10 < 0)
		{
			_x -= _camera.left / 50;
			_camera.left -= _camera.left / 50;
			CAMERADATA->set_X(CAMERADATA->get_X() - _camera.left / 50);
			for (int i = 0; i < _em->getMinion().size(); i++)
			{
				_em->getMinion()[i]->setEnemyX(_em->getMinion()[i]->getEnemyX() - _camera.left / 50);
			}
			for (int i = 0; i < _em->getBoss().size(); i++)
			{
				_em->getBoss()[i]->setEnemyX(_em->getBoss()[i]->getEnemyX() - _camera.left / 50);
				for (int j = 0; j < _em->getBoss()[i]->getMinion().size(); j++)
				{
					_em->getBoss()[i]->getMinion()[j]->setEnemyX(_em->getBoss()[i]->getMinion()[j]->getEnemyX() - _camera.left / 50);
				}
			}
		}
	}

	//if (_camera.top < 0 && CAMERADATA->get_Y() + 10 < 0)
	//{
	//	_y -= 1;
	//	_camera.top -= 1;
	//	CAMERADATA->set_Y(CAMERADATA->get_Y() - 1);
	//}
	if (_camera.top < -10 && CAMERADATA->get_Y() + 10 < 0)
	{
		_y += 1;
		_camera.top += 1;
		CAMERADATA->set_Y(CAMERADATA->get_Y() + 1);
		for (int i = 0; i < _em->getMinion().size(); i++)
		{
			_em->getMinion()[i]->setEnemyY(_em->getMinion()[i]->getEnemyY() + 1);
		}
		for (int i = 0; i < _em->getBoss().size(); i++)
		{
			_em->getBoss()[i]->setEnemyY(_em->getBoss()[i]->getEnemyY() + 1);
			for (int j = 0; j < _em->getBoss()[i]->getMinion().size(); j++)
			{
				_em->getBoss()[i]->getMinion()[j]->setEnemyY(_em->getBoss()[i]->getMinion()[j]->getEnemyY() + 1);
			}
		}
	}
	if (_camera.top < -200 && CAMERADATA->get_Y() + 10 < 0)
	{
		_y -= _camera.top / 50;
		_camera.top -= _camera.top / 50;
		CAMERADATA->set_Y(CAMERADATA->get_Y() - _camera.top / 50);
		for (int i = 0; i < _em->getMinion().size(); i++)
		{
			_em->getMinion()[i]->setEnemyY(_em->getMinion()[i]->getEnemyY() - _camera.top / 50);
		}
		for (int i = 0; i < _em->getBoss().size(); i++)
		{
			_em->getBoss()[i]->setEnemyY(_em->getBoss()[i]->getEnemyY() - _camera.top / 50);
			for (int j = 0; j < _em->getBoss()[i]->getMinion().size(); j++)
			{
				_em->getBoss()[i]->getMinion()[j]->setEnemyY(_em->getBoss()[i]->getMinion()[j]->getEnemyY() - _camera.top / 50);
			}
		}
	}
	//if (_camera.bottom > WINSIZEY && CAMERADATA->get_Y() - 10 > WINSIZEY - CAMERADATA->getHeight())
	//{
	//	_y -= 1;
	//	_camera.bottom -= 1;
	//	CAMERADATA->set_Y(CAMERADATA->get_Y() - 1);
	//}
	if (_camera.bottom - 10 > WINSIZEY && CAMERADATA->get_Y() - 10 > WINSIZEY - CAMERADATA->getHeight())
	{
		_y -= 1;
		_camera.bottom -= 1;
		CAMERADATA->set_Y(CAMERADATA->get_Y() - 1);
		for (int i = 0; i < _em->getMinion().size(); i++)
		{
			_em->getMinion()[i]->setEnemyY(_em->getMinion()[i]->getEnemyY() - 1);
		}
		for (int i = 0; i < _em->getBoss().size(); i++)
		{
			_em->getBoss()[i]->setEnemyY(_em->getBoss()[i]->getEnemyY() - 1);
			for (int j = 0; j < _em->getBoss()[i]->getMinion().size(); j++)
			{
				_em->getBoss()[i]->getMinion()[j]->setEnemyY(_em->getBoss()[i]->getMinion()[j]->getEnemyY() - 1);
			}
		}
	}
	if (_camera.bottom > WINSIZEY + 100 && CAMERADATA->get_Y() - 10 > WINSIZEY - CAMERADATA->getHeight())
	{
		_y -= (_camera.bottom - WINSIZEY) / 50;
		_camera.bottom -= (_camera.bottom - WINSIZEY) / 50;
		CAMERADATA->set_Y(CAMERADATA->get_Y() - (_camera.bottom - WINSIZEY) / 50);
		for (int i = 0; i < _em->getMinion().size(); i++)
		{
			_em->getMinion()[i]->setEnemyY(_em->getMinion()[i]->getEnemyY() - (_camera.bottom - WINSIZEY) / 50);
		}
		for (int i = 0; i < _em->getBoss().size(); i++)
		{
			_em->getBoss()[i]->setEnemyY(_em->getBoss()[i]->getEnemyY() - (_camera.bottom - WINSIZEY) / 50);
			for (int j = 0; j < _em->getBoss()[i]->getMinion().size(); j++)
			{
				_em->getBoss()[i]->getMinion()[j]->setEnemyY(_em->getBoss()[i]->getMinion()[j]->getEnemyY() - (_camera.bottom - WINSIZEY) / 50);
			}
		}
	}
	//CAMERADATA->get_X() - 10 > WINSIZEX - CAMERADATA->getWidth()
	//_camera.left = _player->getX() - 500;
	//_camera.right = _camera.left + 1000;
	//
	//if (_camera.left < 0 && _isLeft)
	//{
	//	_camera.left = 0;
	//	if (_player->getX() < 35 && _player->getX() - CAMERADATA->get_X() > 35)
	//	{
	//		_player->setX(35);
	//	}
	//	CAMERADATA->set_X(CAMERADATA->get_X() - _speed);
	//	_rcBg.right = _rcBg.left + 2000;
	//	_rcLand.left -= _speed;
	//	_rcLand.right = _rcLand.left + 2000;
	//	if (_rcBg.left >= 0)
	//	{
	//		_rcBg.left = 0;
	//		_rcLand.left = 0;
	//	}
	//}
	//else if (_camera.right > WINSIZEX && !_isLeft)
	//{
	//	_camera.right = WINSIZEX;
	//	if (_player->getX() > 670 && _rcBg.right - _player->getX() > 135)
	//	{
	//		_player->getX() = 670;
	//	}
	//	_rcBg.right -= _speed;
	//	_rcBg.left = _rcBg.right - 2000;
	//	_rcLand.right -= _speed;
	//	_rcLand.left = _rcLand.right - 2000;
	//	if (_rcBg.right <= WINSIZEX + 5)
	//	{
	//		_rcBg.right = WINSIZEX + 5;
	//		_rcLand.right = WINSIZEX + 5;
	//	}
	//}
}

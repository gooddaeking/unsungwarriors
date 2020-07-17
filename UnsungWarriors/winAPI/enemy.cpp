#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT position)
{
	//프레임 변수 초기화
	_count = 0;
	_currentFrameX = _currentFrameY = 0;
	frameX = frameY = 0;
	_gravity = 0;
	_rcAtt = RectMake(0, 0, 0, 0);
	_dmg = 1;
	_hp = 90;
	_life = true;
	_hit = false;

	//이미지, 이미지렉트 초기화
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());
	
	_x = position.x;
	_y = position.y;
	_state = E_IDLE;
	_isLeft = true;
	_found = false;
	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 0;
	_rndFireConut = RANDOM->Range(1, 1000);

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	this->move();
	this->animation();
}

void enemy::render()
{
	this->draw();
}

//알아서 만들면 된다
void enemy::move()
{
	_gravity += 1.0f;
	if (_gravity > 13.0f)
	{
		_gravity = 13.0f;
	}
	_y += _gravity;

	if (_hp < 0)
	{
		_hp = 0;
		frameX = 0;
		_life = false;
	}
	if (_hit)
	{
		_rcAtt = RectMake(0, 0, 0, 0);
	}
	if (_hit && _count % 30 == 0)
	{
		_hit = false;
	}

	//if (_isLeft) frameY = 1;
	//else frameY = 0;
	if (_life)
	{
		_rc = RectMakeCenter(_x + 72, _y + 72, 72, 72);
		if (!_found)
		{
			if (_isLeft)
			{
				if (_count % 100 == 0 && _state == E_IDLE)
				{
					_state = E_MOVE;
					_count = RANDOM->Range(0, 50);
				}
				if (_count % 300 == 0 && _state == E_MOVE)
				{
					_state = E_IDLE;
					_isLeft = false;
				}
				if (_x - PLAYERDATA->getX() > 0 && _x - PLAYERDATA->getX() < 600 && _y + 150 > PLAYERDATA->getY() && _y - 150 < PLAYERDATA->getY() && !_found)
				{
					_state = E_FOUND;
					frameX = 9;
					_found = true;
				}
			}
			else
			{
				if (_count % 100 == 0 && _state == E_IDLE)
				{
					_state = E_MOVE;
					_count = RANDOM->Range(0, 50);
				}
				if (_count % 300 == 0 && _state == E_MOVE)
				{
					_state = E_IDLE;
					_isLeft = true;
				}
				if (PLAYERDATA->getX() - _x > 0 && PLAYERDATA->getX() - _x < 600 && _y + 150 > PLAYERDATA->getY() && _y - 150 < PLAYERDATA->getY() && !_found)
				{
					_state = E_FOUND;
					frameX = 0;
					_found = true;
				}
			}
		}
		else if (_found && _state != E_FOUND && _state != E_ATT && _state != E_HIT && _state != E_HIT2)
		{
			if (PLAYERDATA->getX() < _x + 75)
			{
				_isLeft = true;
			}
			else if (PLAYERDATA->getX() > _x + 75)
			{
				_isLeft = false;
			}
			if (!_isLeft && PLAYERDATA->getX() - _x < 144 && _y + 144 > PLAYERDATA->getY() && _y - 50 < PLAYERDATA->getY())
			{
				frameX = 0;
				_state = E_ATT;
			}
			else if (_isLeft && _x - PLAYERDATA->getX() < 50 && _y + 144 > PLAYERDATA->getY() && _y - 50 < PLAYERDATA->getY())
			{
				frameX = 6;
				_state = E_ATT;
			}
		}
	}
	else
	{
		_rc = RectMakeCenter(0, 0, 0, 0);
		_state = E_DEAD;
	}
	//if (_state == E_HIT || _state == E_HIT2)
	//{
	//	if (PLAYERDATA->getX() < _x)
	//	{
	//		_isLeft = true;
	//	}
	//	else
	//	{
	//		_isLeft = false;
	//	}
	//}


	_probeD = _y + _image->getHeight() / 2;
	_probeR = _x + 144;

	for (int i = _probeD - 10; i < _probeD; i++)
	{
		COLORREF color = GetPixel(CAMERADATA->getImage()->getMemDC(), _x + 35 - CAMERADATA->get_X(), i - CAMERADATA->get_Y());
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _image->getHeight() / 2;
			_gravity = 0;
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
			_x = i - 150;
			break;
		}
	}
}

void enemy::draw()
{
	//_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);

	if (_state == E_IDLE) IMAGEMANAGER->frameRender("skeleton(idle)", getMemDC(), _x, _y, frameX, frameY);
	else if (_state == E_MOVE) IMAGEMANAGER->frameRender("skeleton(move)", getMemDC(), _x, _y, frameX, frameY);
	else if (_state == E_FOUND)
	{
		IMAGEMANAGER->frameRender("skeleton(found)", getMemDC(), _x, _y, frameX, frameY);
		if (!_isLeft) IMAGEMANAGER->render("found", getMemDC(), _x + 92, _y);
		else IMAGEMANAGER->render("found", getMemDC(), _x -10, _y);
	}
	else if (_state == E_ATT) IMAGEMANAGER->frameRender("skeleton(att)", getMemDC(), _x - 32, _y - 32, frameX, frameY);
	else if (_state == E_HIT) IMAGEMANAGER->frameRender("skeleton(hit)", getMemDC(), _x, _y, frameX, frameY);
	else if (_state == E_HIT2) IMAGEMANAGER->frameRender("skeleton(hit2)", getMemDC(), _x - 36, _y - 72, frameX, frameY);
	else if (_state == E_DEAD) IMAGEMANAGER->frameRender("skeleton(dead)", getMemDC(), _x + 36, _y + 36 , frameX, frameY);

}

void enemy::animation()
{
	//_count++;
	//if (_count % 5 == 0)
	//{
	//	_image->setFrameX(_image->getFrameX());
	//	_currentFrameX++;
	//	if (_currentFrameX >= _image->getMaxFrameX() + 1)
	//	{
	//		_currentFrameX = 0;
	//		_count = 0;
	//	}
	//}
	switch (_state)
	{
	case E_IDLE:
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
	case E_MOVE:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			_x += 2;
			if (_count % 5 == 0)
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
			_x -= 2;
			if (_count % 5 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 9;
				}
			}
		}
		break;
	case E_FOUND:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			if (_count % 2 == 0)
			{
				frameX++;
				if (frameX > 8)
				{
					_state = E_MOVE;
				}
			}
		}
		else
		{
			frameY = 1;
			if (_count % 2 == 0)
			{
				frameX--;
				if (frameX < 1)
				{
					_state = E_MOVE;
				}
			}
		}
		break;
	case E_ATT:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			_x -= 0.5f;
			if (frameX > 5)
			{
				_x += 2.0f;
			}
			if (_count % 5 == 0)
			{
				frameX++;
				if (frameX > 6)
				{
					frameX = 6;
					
					if (_count % 30 == 0)
					{
						_state = E_MOVE;
					}
				}
				if (frameX >= 6 && !_hit)
				{
					_rcAtt = RectMake(_x + 104, _y + 72, 70, 70);
				}
			}
		}
		else
		{
			frameY = 1;
			_x += 0.5f;
			if (frameX < 1)
			{
				_x -= 2.0f;
			}
			if (_count % 5 == 0)
			{
				frameX--;
				
				if (frameX < 0)
				{
					frameX = 0;
					if (_count % 30 == 0)
					{
						_state = E_MOVE;
					}
				}
				if (frameX <= 0 && !_hit)
				{
					_rcAtt = RectMake(_x - 36, _y + 72, 70, 70);
				}
			}
		}
		break;
	case E_HIT:
		_count++;
		if (!_isLeft)
		{
			if (frameX != 9)
			{
				_x -= 2.0f;
			}
			frameY = 0;
			if (_count % 3 == 0)
			{
				frameX++;
				if (frameX > 9)
				{
					frameX = 9;
					if (_count % 50 == 0)
					{
						_state = E_MOVE;
					}
				}
			}
		}
		else
		{
			if (frameX != 0)
			{
				_x += 2.0f;
			}
			frameY = 1;
			if (_count % 3 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 0;
					if (_count % 50 == 0)
					{
						_state = E_MOVE;
					}
				}
			}
		}
		break;
	case E_HIT2:
		_count++;
		if (!_isLeft)
		{
			if (frameX != 11)
			{
				_x -= 4.0f;
			}
			frameY = 0;
			if (_count % 3 == 0)
			{
				frameX++;
				if (frameX > 11)
				{
					frameX = 11;
					if (_count % 100 == 0)
					{
						_state = E_MOVE;
					}
				}
			}
		}
		else
		{
			if (frameX != 0)
			{
				_x += 4.0f;
			}
			frameY = 1;
			if (_count % 3 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 0;
					if (_count % 100 == 0)
					{
						_state = E_MOVE;
					}
				}
			}
		}
		break;
	case E_DEAD:
		_count++;
		frameY = 0;
		if (_count % 2 == 0)
		{
			frameX++;
			if (frameX > 9)
			{
				frameX = 9;
			}
		}
		break;
	}
}

bool enemy::bulletCountFire()
{
	_fireCount++;
	if (_fireCount % _rndFireConut == 0)
	{
		_rndFireConut = RANDOM->Range(1, 1000);
		_fireCount = 0;

		return true;
	}
	return false;
}

HRESULT boss::init()
{
	return S_OK;
}

HRESULT boss::init(const char* imageName, POINT position)
{
	//프레임 변수 초기화
	_count = 0;
	_currentFrameX = _currentFrameY = 0;
	frameX = frameY = 0;
	_gravity = 0.5f;
	_rcAtt = RectMake(0, 0, 0, 0);
	_dmg = 3;
	_maxHp = _hp = 30;
	_life = true;
	_hit = false;

	for (int i = 0; i < 12; i++)
	{
		_exploFrameX[i] = 0;
		_randomX[i] = RANDOM->Range(100, 300);
		_randomY[i] = RANDOM->Range(50, 500);
	}

	//이미지, 이미지렉트 초기화
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());

	_x = position.x;
	_y = position.y;
	_state = E_MOVE;
	_isLeft = true;
	_found = false;
	//랜덤으로 총알 쿨타임 주는 변수 초기화
	_fireCount = 0;
	_rndFireConut = RANDOM->Range(1, 1000);

	_hpBar = new progressBar;
	_hpBar->init("boss(hp)", "boss(maxhp)");

	return S_OK;
}

void boss::release()
{
	//체력바 클래스 해제
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void boss::update()
{
	this->move();
	this->animation();
	for (int i = 0; i < _enemy.size(); i++)
	{
		_enemy[i]->update();
	}

	//체력바 업데이트
	_hpBar->update();
	//체력바 위치, 피통도 업데이트 해줘야 한다
	_hpBar->setPos(50, 800);
	_hpBar->setGauge(_maxHp, _hp);
}

void boss::render()
{
	this->draw();
	for (int i = 0; i < _enemy.size(); i++)
	{
		_enemy[i]->render();
	}
}

//알아서 만들면 된다
void boss::move()
{
	_gravity = 0.5f;
	_y += _gravity;

	_okay = RectMake(_probeR, _probeD, 10, 10);
	
	if (_count % 1500 == 0)
	{
		if (!_isLeft) frameX = 0;
		else frameX = 9;
		_state = E_SUMMON;
	}

	if (_hp < 0)
	{
		_hp = 0;
		frameX = 0;
		_life = false;
	}
	if (_hit)
	{
		_rcAtt = RectMake(0, 0, 0, 0);
	}
	if (_hit && _count % 30 == 0)
	{
		_hit = false;
	}

	if (_isLeft) frameY = 1;
	else frameY = 0;
	if (_life)
	{
		_rc = RectMakeCenter(_x + 256, _y + 320, 160, 400);
		if (!_found)
		{
			if (_isLeft)
			{
				if (_count % 100 == 0 && _state == E_IDLE)
				{
					_state = E_MOVE;
					_count = RANDOM->Range(0, 50);
				}
				if (_count % 300 == 0 && _state == E_MOVE)
				{
					_isLeft = false;
				}
				if (_x - PLAYERDATA->getX() > 0 && _x - PLAYERDATA->getX() < 1000 && _y + 500 > PLAYERDATA->getY() && _y - 150 < PLAYERDATA->getY() && !_found)
				{
					_found = true;
				}
			}
			else
			{
				if (_count % 100 == 0 && _state == E_IDLE)
				{
					_state = E_MOVE;
					_count = RANDOM->Range(0, 50);
				}
				if (_count % 300 == 0 && _state == E_MOVE)
				{
					_isLeft = true;
				}
				if (PLAYERDATA->getX() - _x > 0 && PLAYERDATA->getX() - _x < 1000 && _y + 500 > PLAYERDATA->getY() && _y - 150 < PLAYERDATA->getY() && !_found)
				{
					_found = true;
				}
			}
		}
		else
		{
			if (PLAYERDATA->getX() + 35 < _x + 256)
			{
				_isLeft = true;
			}
			else if (PLAYERDATA->getX() + 35 > _x + 256)
			{
				_isLeft = false;
			}
			if (!_isLeft && PLAYERDATA->getX() - _x < 470 && _y + 500 > PLAYERDATA->getY() && _y - 50 < PLAYERDATA->getY() && _state != E_ATT && _state != E_SUMMON)
			{
				frameX = 0;
				_state = E_ATT;
			}
			else if (_isLeft && _x - PLAYERDATA->getX() < 30 && _y + 500 > PLAYERDATA->getY() && _y - 50 < PLAYERDATA->getY() && _state != E_ATT && _state != E_SUMMON)
			{
				frameX = 9;
				_state = E_ATT;
			}
		}
		_probeD = _y + _image->getHeight() / 2;
		_probeR = _x + _image->getWidth() / 2;

		for (int i = _probeD - 10; i < _probeD; i++)
		{
			COLORREF color = GetPixel(CAMERADATA->getImage()->getMemDC(), _x + 35 - CAMERADATA->get_X(), i - CAMERADATA->get_Y());
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				_y = i - _image->getHeight() / 2;
				_gravity = 0;
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
				_x = i + 512;
				break;
			}
		}
	}
	else
	{
		_rc = RectMakeCenter(0, 0, 0, 0);
		_state = E_DEAD;
	}

	

	
}

void boss::draw()
{
	//_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);

	if (_state == E_MOVE) IMAGEMANAGER->frameRender("boss(move)", getMemDC(), _x, _y + 32, frameX, frameY);
	else if (_state == E_ATT) IMAGEMANAGER->frameRender("boss(att)", getMemDC(), _x, _y + 32, frameX, frameY);
	else if (_state == E_SUMMON) IMAGEMANAGER->frameRender("boss(summon)", getMemDC(), _x, _y + 32, frameX, frameY);
	else if (_state == E_DEAD)
	{
		IMAGEMANAGER->frameRender("boss(summon)", getMemDC(), _x, _y + 32, frameX, frameY);
		
		for (int i = 0; i < 12; i++)
		{
			IMAGEMANAGER->frameRender("explosion", getMemDC(), _x + _randomX[i], _y + _randomY[i], _exploFrameX[i], 0);
		}
		
	}
	if (_count % 5 == 0)
	{
		for (int i = 0; i < 12; i++)
		{
			_exploFrameX[i] += RANDOM->Range(1,2);
			if (_exploFrameX[i] > 15)
			{
				_exploFrameX[i] = RANDOM->Range(0, 4);
				_randomX[i] = RANDOM->Range(100, 300);
				_randomY[i] = RANDOM->Range(50, 500);
			}
		}
	}
	Rectangle(getMemDC(), _okay);

	_hpBar->render();
}

void boss::animation()
{
	//_count++;
	//if (_count % 5 == 0)
	//{
	//	_image->setFrameX(_image->getFrameX());
	//	_currentFrameX++;
	//	if (_currentFrameX >= _image->getMaxFrameX() + 1)
	//	{
	//		_currentFrameX = 0;
	//		_count = 0;
	//	}
	//}
	switch (_state)
	{
	case E_MOVE:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			_x += 2;
			if (_count % 10 == 0)
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
			_x -= 2;
			if (_count % 10 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 9;
				}
			}
		}
		break;
	case E_ATT:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			if (_count % 8 == 0)
			{
				frameX++;
				if (frameX > 9)
				{
					frameX = 9;

					if (_count % 30 == 0)
					{
						_state = E_MOVE;
					}
				}
				if (frameX >= 9 && !_hit)
				{
					_rcAtt = RectMake(_x + 512, _y + 460, 70, 70);
				}
			}
		}
		else
		{
			frameY = 1;
			if (_count % 8 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 0;
					if (_count % 30 == 0)
					{
						_state = E_MOVE;
					}
				}
				if (frameX <= 0 && !_hit)
				{
					_rcAtt = RectMake(_x, _y + 460, 70, 70);
				}
			}
		}
		break;
	case E_SUMMON:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			if (_count % 8 == 0)
			{
				frameX++;
				if (frameX > 9)
				{
					frameX = 9;
					if (_count % 30 == 0)
					{
						enemy* summon = new enemy;
						summon->init("skeleton(idle)", PointMake(_x, _y + 400));
						_enemy.push_back(summon);
						enemy* summon2 = new enemy;
						summon2->init("skeleton(idle)", PointMake(_x + 400, _y + 400));
						_enemy.push_back(summon2);
						_state = E_MOVE;
					}
				}
			}
		}
		else
		{
			frameY = 1;
			if (_count % 8 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 0;
					if (_count % 30 == 0)
					{
						enemy* summon = new enemy;
						summon->init("skeleton(idle)", PointMake(_x, _y + 400));
						_enemy.push_back(summon);
						enemy* summon2 = new enemy;
						summon2->init("skeleton(idle)", PointMake(_x + 400, _y + 400));
						_enemy.push_back(summon2);
						_state = E_MOVE;
					}
				}
			}
		}
		break;
	case E_DEAD:
		_count++;
		if (!_isLeft)
		{
			frameY = 0;
			if (_count % 20 == 0)
			{
				frameX++;
				if (frameX > 9)
				{
					frameX = 5;
				}
			}
		}
		else
		{
			frameY = 1;
			if (_count % 20 == 0)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 4;
				}
			}
		}
		break;
	}
}

bool boss::bulletCountFire()
{
	_fireCount++;
	if (_fireCount % _rndFireConut == 0)
	{
		_rndFireConut = RANDOM->Range(1, 1000);
		_fireCount = 0;

		return true;
	}
	return false;
}

#include "stdafx.h"
#include "inven.h"

HRESULT inven::init()
{
	//PLAYERDATA->getInven();

	_inventory = drag = _equip = false;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_inven[i * 6 + j] = RectMake(44 + j * 100, 400 + i * 100, 92, 92);
			_invenBg[i * 6 + j] = RectMake(44 + j * 100, 400 + i * 100, 92, 92);
			_click[i * 6 + j] = false;
		}
	}
	_weapon = RectMake(56, 259, 92, 92);
	_weaponBg = RectMake(56, 259, 92, 92);
	_acce = RectMake(157, 259, 92, 92);
	_acceBg = RectMake(157, 259, 92, 92);
	_shield = RectMake(257, 259, 92, 92);
	_shieldBg = RectMake(257, 259, 92, 92);
	_out = RectMake(232, 832, 204, 47);

	for (int i = 0; i < 3; i++)
	{
		_unMount[i] = false;
	}

	_money = PLAYERDATA->getGold();
	_store = false;


	_item = new item;
	_item->init();

	
	_vWeapon.clear();
	if (PLAYERDATA->getWeapon() != -1)
	{
		_vWeapon.push_back(_item->getItem()[PLAYERDATA->getWeapon()]);
	}
	_vAcce.clear();
	if (PLAYERDATA->getAcce() != -1)
	{
		_vAcce.push_back(_item->getItem()[PLAYERDATA->getAcce()]);
	}
	_vShield.clear();
	if (PLAYERDATA->getShield() != -1)
	{
		_vShield.push_back(_item->getItem()[PLAYERDATA->getShield()]);
	}
	_vInven.clear();
	for (int i = 0; i < PLAYERDATA->getSerial().size(); i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (PLAYERDATA->getSerial()[i] == j)
			{
				_vInven.push_back(_item->getItem()[j]);
			}
		}
	}
	return S_OK;
}

void inven::release()
{
	_item->release();
	SAFE_DELETE(_item);
}

void inven::update()
{
	if (INPUT->GetKeyDown('I'))
	{
		if (_inventory) _inventory = false;
		else _inventory = true;
	}
	
	if (_inventory)
	{
		
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < _vInven.size(); i++)
			{
				if (PtInRect(&_inven[i], _ptMouse))
				{
					_click[i] = true;
				}
			}
			if (PtInRect(&_out, _ptMouse))
			{
				_inventory = false;
			}
			//장착 해제
			if (!_vWeapon.empty() && PtInRect(&_weapon, _ptMouse))
			{
				_unMount[0] = true;
			}
			else if (!_vAcce.empty() && PtInRect(&_acce, _ptMouse))
			{
				_unMount[1] = true;
			}
			else if (!_vShield.empty() && PtInRect(&_shield, _ptMouse))
			{
				_unMount[2] = true;
			}
		}

		//아이템 장착 & 아이템 판매
		for (int i = 0; i < _vInven.size(); i++)
		{
			if (_click[i])
			{
				_inven[i].left = _ptMouse.x - 20;
				_inven[i].right = _inven[i].left + 37;
				_inven[i].top = _ptMouse.y - 20;
				_inven[i].bottom = _inven[i].top + 35;
				if (INPUT->GetKeyUp(VK_LBUTTON))
				{
					_click[i] = false;
					_unMount[0] = _unMount[1] = _unMount[2] = false;
					_weapon = RectMake(56, 259, 92, 92);
					_acce = RectMake(157, 259, 92, 92);
					_shield = RectMake(257, 259, 92, 92);

					// 무기 장착
					if (PtInRect(&_weapon, _ptMouse) && _vInven[i]._itemKind == ITEM_WEAPON && _vWeapon.empty())
					{
						_vWeapon.push_back(_vInven[i]);
						_vInven.erase(_vInven.begin() + i);
					}
					else if (PtInRect(&_weapon, _ptMouse) && _vInven[i]._itemKind == ITEM_WEAPON && !_vWeapon.empty())
					{
						_vInven.insert(_vInven.begin() + i, _vWeapon[0]);
						_vWeapon.clear();
						_vWeapon.push_back(_vInven[i + 1]);
						_vInven.erase(_vInven.begin() + i + 1);
					}
					else if (PtInRect(&_weapon, _ptMouse) && _vInven[i]._itemKind == ITEM_TWOHAND && _vWeapon.empty())
					{
						_vWeapon.push_back(_vInven[i]);
						_vInven.erase(_vInven.begin() + i);
					}
					else if (PtInRect(&_weapon, _ptMouse) && _vInven[i]._itemKind == ITEM_TWOHAND && !_vWeapon.empty())
					{
						_vInven.insert(_vInven.begin() + i, _vWeapon[0]);
						_vWeapon.clear();
						_vWeapon.push_back(_vInven[i + 1]);
						_vInven.erase(_vInven.begin() + i + 1);
					}
					// 장신구 장착
					if (PtInRect(&_acce, _ptMouse) && _vInven[i]._itemKind == ITEM_ACCE && _vAcce.empty())
					{
						_vAcce.push_back(_vInven[i]);
						_vInven.erase(_vInven.begin() + i);
					}
					else if (PtInRect(&_acce, _ptMouse) && _vInven[i]._itemKind == ITEM_ACCE && !_vAcce.empty())
					{
						_vInven.insert(_vInven.begin() + i, _vAcce[0]);
						_vAcce.clear();
						_vAcce.push_back(_vInven[i + 1]);
						_vInven.erase(_vInven.begin() + i + 1);
					}
					// 방패 장착
					if (PtInRect(&_shield, _ptMouse) && _vInven[i]._itemKind == ITEM_SHIELD && _vShield.empty())
					{
						_vShield.push_back(_vInven[i]);
						_vInven.erase(_vInven.begin() + i);
					}
					else if (PtInRect(&_shield, _ptMouse) && _vInven[i]._itemKind == ITEM_SHIELD && !_vShield.empty())
					{
						_vInven.insert(_vInven.begin() + i, _vShield[0]);
						_vShield.clear();
						_vShield.push_back(_vInven[i + 1]);
						_vInven.erase(_vInven.begin() + i + 1);
					}
					// 신발 장착
					
					// 그외 장착
					
					for (int j = 0; j < _vInven.size(); j++)
					{
						if (PtInRect(&_inven[j], _ptMouse))
						{
							if (i > j)
							{
								setTemp(getInven()[i]);
								_vInven.erase(_vInven.begin() + i);
								_vInven.insert(_vInven.begin() + i, getInven()[j]);
								_vInven.erase(_vInven.begin() + j);
								_vInven.insert(_vInven.begin() + j, getTemp()[0]);
								_vTemp.pop_back();
							}
							else if (i < j)
							{
								setTemp(getInven()[j]);
								_vInven.erase(_vInven.begin() + j);
								_vInven.insert(_vInven.begin() + j, getInven()[i]);
								_vInven.erase(_vInven.begin() + i);
								_vInven.insert(_vInven.begin() + i, getTemp()[0]);
								_vTemp.pop_back();
							}
						}
					}
					
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							_inven[i * 6 + j] = RectMake(44 + j * 100, 400 + i * 100, 92, 92);
						}
					}
				}
			}
			else
			{
				
			}
		}

		//무기해제
		if (_unMount[0])
		{
			_weapon.left = _ptMouse.x - 20;
			_weapon.right = _weapon.left + 37;
			_weapon.top = _ptMouse.y - 20;
			_weapon.bottom = _weapon.top + 35;
			if (INPUT->GetKeyUp(VK_LBUTTON))
			{
				_unMount[0] = false;
				for (int i = 0; i < 24; i++)
				{
					if (PtInRect(&_inven[i], _ptMouse) && i < _vInven.size())
					{
						_vInven.insert(_vInven.begin() + i, _vWeapon[0]);
						_vWeapon.clear();
					}
					else if (PtInRect(&_inven[i], _ptMouse) && i >= _vInven.size())
					{
						_vInven.push_back(_vWeapon[0]);
						_vWeapon.clear();
					}
				}
				_weapon = RectMake(56, 259, 92, 92);
			}
		}
		//장신구해제
		if (_unMount[1])
		{
			_acce.left = _ptMouse.x - 20;
			_acce.right = _acce.left + 37;
			_acce.top = _ptMouse.y - 20;
			_acce.bottom = _acce.top + 35;
			if (INPUT->GetKeyUp(VK_LBUTTON))
			{
				_unMount[1] = false;
				for (int i = 0; i < 24; i++)
				{
					if (PtInRect(&_inven[i], _ptMouse) && i < _vInven.size())
					{
						_vInven.insert(_vInven.begin() + i, _vAcce[0]);
						_vAcce.clear();
					}
					else if (PtInRect(&_inven[i], _ptMouse) && i >= _vInven.size())
					{
						_vInven.push_back(_vAcce[0]);
						_vAcce.clear();
					}
				}
				_acce = RectMake(157, 259, 92, 92);
			}
		}
		//방패해제
		if (_unMount[2])
		{
			_shield.left = _ptMouse.x - 20;
			_shield.right = _shield.left + 37;
			_shield.top = _ptMouse.y - 20;
			_shield.bottom = _shield.top + 35;
			if (INPUT->GetKeyUp(VK_LBUTTON))
			{
				_unMount[2] = false;
				for (int i = 0; i < 24; i++)
				{
					if (PtInRect(&_inven[i], _ptMouse) && i < _vInven.size())
					{
						_vInven.insert(_vInven.begin() + i, _vShield[0]);
						_vShield.clear();
					}
					else if (PtInRect(&_inven[i], _ptMouse) && i >= _vInven.size())
					{
						_vInven.push_back(_vShield[0]);
						_vShield.clear();
					}
				}
				_shield = RectMake(257, 259, 92, 92);
			}
		}
		//신발해제
		
		//그외해제

	}

	_item->update();
	
}

void inven::render()
{
	if (_inventory)
	{
		IMAGEMANAGER->render("inven", getMemDC(), 10, 10);
		if (!_vWeapon.empty())
		{
			IMAGEMANAGER->render("invenbg(weapon)", getMemDC(), _weaponBg.left, _weaponBg.top);
			_vWeapon[0]._itemIcon->render(getMemDC(), _weapon.left, _weapon.top - 2);
		}
		if (!_vAcce.empty())
		{
			IMAGEMANAGER->render("invenbg(acce)", getMemDC(), _acceBg.left, _acceBg.top);
			_vAcce[0]._itemIcon->render(getMemDC(), _acce.left, _acce.top - 2);
		}
		if (!_vShield.empty())
		{
			IMAGEMANAGER->render("invenbg(shield)", getMemDC(), _shieldBg.left, _shieldBg.top);
			_vShield[0]._itemIcon->render(getMemDC(), _shield.left, _shield.top - 2);
		}
		for (int i = 0; i < _vInven.size(); i++)
		{
			{
				if (_vInven[i]._itemKind == ITEM_WEAPON || _vInven[i]._itemKind == ITEM_TWOHAND)
				{
					IMAGEMANAGER->render("invenbg(weapon)", getMemDC(), _invenBg[i].left, _invenBg[i].top);
				}
				else if (_vInven[i]._itemKind == ITEM_ACCE)
				{
					IMAGEMANAGER->render("invenbg(acce)", getMemDC(), _invenBg[i].left, _invenBg[i].top);
				}
				else if (_vInven[i]._itemKind == ITEM_SHIELD)
				{
					IMAGEMANAGER->render("invenbg(shield)", getMemDC(), _invenBg[i].left, _invenBg[i].top);
				}
				_vInven[i]._itemIcon->render(getMemDC(), _inven[i].left, _inven[i].top - 2);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (_money % 10 == i)
			{
				IMAGEMANAGER->frameRender("gold(num)", getMemDC(), 470, 135, i, 0);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (_money / 10 % 10 == i && _money > 9)
			{
				IMAGEMANAGER->frameRender("gold(num)", getMemDC(), 440, 135, i, 0);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (_money / 100 % 10 == i && _money > 99)
			{
				IMAGEMANAGER->frameRender("gold(num)", getMemDC(), 410, 135, i, 0);
			}
		}

		for (int i = 0; i < 10; i++)
		{
			if (!_vWeapon.empty())
			{
				if (_vWeapon[0]._dmg % 10 == i)
				{
					IMAGEMANAGER->frameRender("blue(num)", getMemDC(), 300, 135, i, 0);
				}
			}
			else
			{
				IMAGEMANAGER->frameRender("blue(num)", getMemDC(), 270, 135, 1, 0);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (!_vWeapon.empty())
			{
				if (_vWeapon[0]._dmg / 10 % 10 == i && _vWeapon[0]._dmg > 9)
				{
					IMAGEMANAGER->frameRender("blue(num)", getMemDC(), 270, 135, i, 0);
				}
			}
			
		}
	}

	_item->render();
}

void inven::setInven(tagItem item)
{
	_vInven.push_back(item);
}

void inven::setErase(int index)
{
	_vInven.erase(_vInven.begin() + index);
}

void inven::setTemp(tagItem item)
{
	_vTemp.push_back(item);
}

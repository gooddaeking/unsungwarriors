#include "stdafx.h"
#include "shop.h"
#include "inven.h"

HRESULT shop::init()
{
	//����
	//IMAGEMANAGER->addImage("�������", "Images/����/����-���.bmp", 508, 507);

	//����â ī�װ�
	_buy = RectMake(47, 146, 126, 63);
	buy = true;
	_sell = RectMake(187, 146, 126, 63);
	sell = false;
	_shopOut = RectMake(327, 151, 126, 57);
	//����â ���ù�ư
	_shop1 = RectMake(109, 225, 245, 39);
	//����â & �Ǹ�â
	_equip[0] = true;
	_equip[1] = false;
	_equip[2] = false;
	_buyPage = _sellPage = 1;
	//���� ������ ��� �ȱ�

	for (int i = 0; i < 5; i++)
	{
		_choice[i] = RectMake(63, 227 + i * 116, 575, 110);
	}

	
	
	_left = RectMake(159, 804, 128, 64);
	_right = RectMake(415, 804, 128, 64);

	_store = false;
	shop1 = false;

	_item = new item;
	_item->init();

	return S_OK;
}

void shop::release()
{
	_item->release();
	SAFE_DELETE(_item);
}

void shop::update()
{
	//����
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (!_store)
		{
			shop1 = false;
			_buyPage = _sellPage = 1;
		}
		if (_store)
		{
			//������ ī�װ� ����
			if (PtInRect(&_buy, _ptMouse))
			{
				buy = true;
				sell = false;
			}
			if (PtInRect(&_sell, _ptMouse))
			{
				buy = false;
				sell = true;
			}
			if (PtInRect(&_shopOut, _ptMouse))
			{
				_store = false;
			}
			if (buy)
			{
				for (int i = 0; i < 5; i++)
				{
					if (PtInRect(&_choice[i], _ptMouse) && (_buyPage - 1) * 5 + i < _item->getItem().size())
					{
						_inven->setInven(_item->getItem()[(_buyPage - 1) * 5 + i]);
						_inven->setMoney(_inven->getMoney() - _item->getItem()[(_buyPage - 1) * 5 + i]._price);
					}
				}
				if (PtInRect(&_left, _ptMouse))
				{
					if (_buyPage > 1)
					{
						_buyPage--;
					}
				}
				else if (PtInRect(&_right, _ptMouse))
				{
					if (_item->getItem().size() > _buyPage * 5)
					{
						_buyPage++;
					}
				}
			}
			if (sell)
			{
				for (int i = 0; i < 5; i++)
				{
					if (PtInRect(&_choice[i], _ptMouse) && (_sellPage - 1) * 5 + i < _inven->getInven().size())
					{
						_inven->setMoney(_inven->getMoney() + _inven->getInven()[(_sellPage - 1) * 5 + i]._price / 2);
						_inven->setErase((_sellPage - 1) * 5 + i);
					}
				}
				if (PtInRect(&_left, _ptMouse))
				{
					if (_sellPage > 1)
					{
						_sellPage--;
					}
				}
				else if (PtInRect(&_right, _ptMouse))
				{
					if (_inven->getInven().size() > _sellPage * 5)
					{
						_sellPage++;
					}
				}
			}
			//if (shop1 && buy && PtInRect(&_buying, _ptMouse))
			{
				//_inven->setInven(_item->getItem()[0]);
				//_inven->setMoney(_inven->getMoney() - _item->getItem()[0]._price);
				shop1 = false;
			}
			//������ ����
			if (PtInRect(&_shop1, _ptMouse))
			{
				shop1 = true;
			}

		}
	}

	//������ ����
	if (INPUT->GetKey(VK_LBUTTON))
	{
		//if (shop1 && buy && PtInRect(&_buying, _ptMouse))
		{
			//_inven->setInven(_item->getItem()[0]);
			//_inven->setMoney(_inven->getMoney() - _item->getItem()[0]._price);
			//shop1 = false;
		}
	}

}

void shop::render()
{
	if (_store)
	{
		IMAGEMANAGER->render("shop", getMemDC(), 20, 200);
		IMAGEMANAGER->render("right", getMemDC(), 415, 804);
		IMAGEMANAGER->render("left", getMemDC(), 159, 804);
		if (buy)
		{
			IMAGEMANAGER->render("shop(buy)", getMemDC(), 25, 140);
			for (int j = 0; j < 5; j++)
			{
				if ((_buyPage - 1) * 5 + j < _item->getItem().size())
				{
					_item->getItem()[(_buyPage - 1) * 5 + j]._itemImage->render(getMemDC(), 63, 227 + j * 116);
				}
			}
		}
		else if (sell)
		{
			IMAGEMANAGER->render("shop(sell)", getMemDC(), 25, 140);
			for (int j = 0; j < 5; j++)
			{
				if ((_sellPage - 1) * 5 + j < _inven->getInven().size())
				{
					_inven->getInven()[(_sellPage - 1) * 5 + j]._itemImage->render(getMemDC(), 63, 227 + j * 116);
				}
			}
		}
		IMAGEMANAGER->render("shop(gold)", getMemDC(), 480, 140);
		IMAGEMANAGER->render("goldicon", getMemDC(), 500, 158);
		//if (_inven->getMoney() % 10 == 0)
		//{
		//	IMAGEMANAGER->frameRender("gold(num)", getMemDC(), 520, 165,0,0);
		//}

		for (int i = 0; i < 10; i++)
		{
			if (_inven->getMoney() % 10 == i)
			{
				IMAGEMANAGER->frameRender("gold(num)", getMemDC(), 600, 157, i, 0);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (_inven->getMoney() / 10 % 10 == i && _inven->getMoney() > 9)
			{
				IMAGEMANAGER->frameRender("gold(num)", getMemDC(), 570, 157, i, 0);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (_inven->getMoney() / 100 % 10 == i && _inven->getMoney() > 99)
			{
				IMAGEMANAGER->frameRender("gold(num)", getMemDC(), 540, 157, i, 0);
			}
		}
	}
}

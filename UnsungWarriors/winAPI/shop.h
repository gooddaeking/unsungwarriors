#pragma once
#include "item.h"

class inven;

class shop : public gameNode
{
private:
	inven* _inven;
	item* _item;
	
	image* _money[10];
	bool _store;
	RECT _buy;
	RECT _sell;
	bool buy;
	bool sell;

	RECT _choice[5];

	RECT _left, _right;
	bool _equip[3];
	int _buyPage;
	int _sellPage;

	RECT _shop1;
	bool shop1;


	RECT _shopOut;

	

	char str[100];

public:
	bool getShop() { return _store; }
	void setShop(bool store) { _store = store; }

	item* getItem() { return _item; }

	void setInvenLink(inven* inven) { _inven = inven; }

	HRESULT init();
	void release();
	void update();
	void render();


	shop() {}
	~shop() {}
};
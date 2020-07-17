#pragma once
#include "gameNode.h"

using namespace std;

enum ITEM
{
	ITEM_WEAPON = 1,
	ITEM_TWOHAND,
	ITEM_ACCE,
	ITEM_SHIELD
};

struct tagItem
{
	image* _itemImage;
	image* _itemIcon;
	string _itemName;
	ITEM _itemKind;
	int _dmg;
	int _heal;
	int _mana;
	int _price;
	int _serial;
};

class item : public gameNode
{
private:
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;


public:
	vector<tagItem> getItem() { return _vItem; }
	void setItem(vector<tagItem> item) { _vItem = item; }

	HRESULT init();
	void release();
	void update();
	void render();

	item() {}
	~item() {}
};


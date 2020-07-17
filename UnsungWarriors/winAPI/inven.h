#pragma once
#include "gameNode.h"
#include "item.h"

class shop;

class inven : public gameNode
{
private:
	shop* _shop;
	item* _item;

	vector<tagItem> _vInven;
	vector<tagItem>::iterator _viInven;
	vector<tagItem> _vTemp;
	vector<tagItem> _vWeapon;
	vector<tagItem> _vAcce;
	vector<tagItem> _vShield;

	RECT _inven[24];
	RECT _invenBg[24];
	RECT _weapon;
	RECT _weaponBg;
	RECT _acce;
	RECT _acceBg;
	RECT _shield;
	RECT _shieldBg;
	RECT _out;

	int _money;

	bool _inventory;
	bool _equip;
	bool _click[24];
	bool drag;
	bool _unMount[3];
	bool _store;

	char str[100];
public:
	// æ∆¿Ã≈€ ¿Â¬¯

	int getMoney() { return _money; }
	void setMoney(int money) { _money = money; }
	void setStore(bool store) { _store = store; }

	vector<tagItem> getInven() { return _vInven; }
	vector<tagItem> getWeapon() { return _vWeapon; }
	vector<tagItem> getAcce() { return _vAcce; }
	vector<tagItem> getShield() { return _vShield; }
	//vector<tagItem> getInven(int index) { return _vInven.begin() + index; }
	vector<tagItem> getTemp() { return _vTemp; }
	void setInven(tagItem item);
	void setErase(int index);
	void setTemp(tagItem item);
	void setInventory(bool inven) { _inventory = inven; }
	void setEquip(bool equip) { _equip = equip; }

	item* getItem() { return _item; }
	void setSHOPLink(shop* shop) { _shop = shop; }

	HRESULT init();
	void release();
	void update();
	void render();

	inven() {}
	~inven() {}
};
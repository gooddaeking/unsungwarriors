#pragma once
#include "singletonBase.h"

class playerData : public singletonBase <playerData>
{
private:
	vector<int> _serial;
	int _weapon = -1;
	int _acce = -1;
	int _shield = -1;

	int _hp = 30;
	int _mp = 100;
	int _gold = 999;
	float _x, _y;
	bool _comeback = false;

public:
	HRESULT init();
	void release();

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }
	int getMp() { return _mp; }
	void setMp(int mp) { _mp = mp; }
	int getGold() { return _gold; }
	void setGold(int gold) { _gold = gold; }
	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

	vector<int> getSerial() { return _serial; }
	void setSerial(int index);
	void clearSeiral() { return _serial.clear(); }
	int getWeapon() { return _weapon; }
	void setWeapon(int weapon) { _weapon = weapon; }
	int getAcce() { return _acce; }
	void setAcce(int acce) { _acce = acce; }
	int getShield() { return _shield; }
	void setShield(int shield) { _shield = shield; }
	bool getComeback() { return _comeback; }
	void setComeback(bool comeback) { _comeback = comeback; }

	playerData() {}
	~playerData() {}
};


#include "stdafx.h"
#include "item.h"

HRESULT item::init()
{
	//아이템 생성
	{
		tagItem weapon1;
		weapon1._itemImage = IMAGEMANAGER->findImage("fryingpan");
		weapon1._itemIcon = IMAGEMANAGER->findImage("inven(fryingpan)");
		weapon1._itemName = "pan";
		weapon1._itemKind = ITEM_WEAPON;
		weapon1._dmg = 1;
		weapon1._heal = 0;
		weapon1._mana = 0;
		weapon1._price = 5;
		weapon1._serial = 0;
		_vItem.push_back(weapon1);

		tagItem weapon2;
		weapon2._itemImage = IMAGEMANAGER->findImage("crude");
		weapon2._itemIcon = IMAGEMANAGER->findImage("inven(crude)");
		weapon2._itemName = "crude";
		weapon2._itemKind = ITEM_WEAPON;
		weapon2._dmg = 2;
		weapon2._heal = 0;
		weapon2._mana = 0;
		weapon2._price = 10;
		weapon2._serial = 1;
		_vItem.push_back(weapon2);

		tagItem weapon3;
		weapon3._itemImage = IMAGEMANAGER->findImage("scimitar");
		weapon3._itemIcon = IMAGEMANAGER->findImage("inven(scimitar)");
		weapon3._itemName = "scimitar";
		weapon3._itemKind = ITEM_WEAPON;
		weapon3._dmg = 3;
		weapon3._heal = 0;
		weapon3._mana = 0;
		weapon3._price = 20;
		weapon3._serial = 2;
		_vItem.push_back(weapon3);

		tagItem weapon4;
		weapon4._itemImage = IMAGEMANAGER->findImage("axe");
		weapon4._itemIcon = IMAGEMANAGER->findImage("inven(axe)");
		weapon4._itemName = "axe";
		weapon4._itemKind = ITEM_WEAPON;
		weapon4._dmg = 4;
		weapon4._heal = 0;
		weapon4._mana = 0;
		weapon4._price = 40;
		weapon4._serial = 3;
		_vItem.push_back(weapon4);

		tagItem weapon5;
		weapon5._itemImage = IMAGEMANAGER->findImage("mace");
		weapon5._itemIcon = IMAGEMANAGER->findImage("inven(mace)");
		weapon5._itemName = "mace";
		weapon5._itemKind = ITEM_TWOHAND;
		weapon5._dmg = 6;
		weapon5._heal = 0;
		weapon5._mana = 0;
		weapon5._price = 60;
		weapon5._serial = 4;
		_vItem.push_back(weapon5);

		tagItem weapon6;
		weapon6._itemImage = IMAGEMANAGER->findImage("warhammer");
		weapon6._itemIcon = IMAGEMANAGER->findImage("inven(warhammer)");
		weapon6._itemName = "hammer";
		weapon6._itemKind = ITEM_TWOHAND;
		weapon6._dmg = 6;
		weapon6._heal = 0;
		weapon6._mana = 0;
		weapon6._price = 85;
		weapon6._serial = 5;
		_vItem.push_back(weapon6);

		tagItem weapon7;
		weapon7._itemImage = IMAGEMANAGER->findImage("greatsword");
		weapon7._itemIcon = IMAGEMANAGER->findImage("inven(greatsword)");
		weapon7._itemName = "sword";
		weapon7._itemKind = ITEM_TWOHAND;
		weapon7._dmg = 7;
		weapon7._heal = 0;
		weapon7._mana = 0;
		weapon7._price = 90;
		weapon7._serial = 6;
		_vItem.push_back(weapon7);

		tagItem weapon8;
		weapon8._itemImage = IMAGEMANAGER->findImage("witchblade");
		weapon8._itemIcon = IMAGEMANAGER->findImage("inven(witchblade)");
		weapon8._itemName = "witch";
		weapon8._itemKind = ITEM_TWOHAND;
		weapon8._dmg = 8;
		weapon8._heal = 0;
		weapon8._mana = 0;
		weapon8._price = 103;
		weapon8._serial = 7;
		_vItem.push_back(weapon8);

		tagItem magic1;
		magic1._itemImage = IMAGEMANAGER->findImage("heart");
		magic1._itemIcon = IMAGEMANAGER->findImage("inven(heart)");
		magic1._itemName = "heart";
		magic1._itemKind = ITEM_ACCE;
		magic1._dmg = 8;
		magic1._heal = 0;
		magic1._mana = 20;
		magic1._price = 25;
		magic1._serial = 8;
		_vItem.push_back(magic1);

		tagItem magic2;
		magic2._itemImage = IMAGEMANAGER->findImage("taranis");
		magic2._itemIcon = IMAGEMANAGER->findImage("inven(taranis)");
		magic2._itemName = "taranis";
		magic2._itemKind = ITEM_ACCE;
		magic2._dmg = 5;
		magic2._heal = 0;
		magic2._mana = 20;
		magic2._price = 25;
		magic2._serial = 9;
		_vItem.push_back(magic2);

		tagItem magic3;
		magic3._itemImage = IMAGEMANAGER->findImage("dubnos");
		magic3._itemIcon = IMAGEMANAGER->findImage("inven(dubnos)");
		magic3._itemName = "dubnos";
		magic3._itemKind = ITEM_ACCE;
		magic3._dmg = 2;
		magic3._heal = 2;
		magic3._mana = 25;
		magic3._price = 25;
		magic3._serial = 10;
		_vItem.push_back(magic3);

		tagItem magic4;
		magic4._itemImage = IMAGEMANAGER->findImage("bark");
		magic4._itemIcon = IMAGEMANAGER->findImage("inven(bark)");
		magic4._itemName = "bark";
		magic4._itemKind = ITEM_ACCE;
		magic4._dmg = 0;
		magic4._heal = 2;
		magic4._mana = 50;
		magic4._price = 25;
		magic4._serial = 11;
		_vItem.push_back(magic4);

		tagItem magic5;
		magic5._itemImage = IMAGEMANAGER->findImage("bow");
		magic5._itemIcon = IMAGEMANAGER->findImage("inven(bow)");
		magic5._itemName = "bow";
		magic5._itemKind = ITEM_ACCE;
		magic5._dmg = 4;
		magic5._heal = 0;
		magic5._mana = 20;
		magic5._price = 10;
		magic5._serial = 12;
		_vItem.push_back(magic5);

		tagItem shield1;
		shield1._itemImage = IMAGEMANAGER->findImage("shield");
		shield1._itemIcon = IMAGEMANAGER->findImage("inven(shield)");
		shield1._itemName = "shield";
		shield1._itemKind = ITEM_SHIELD;
		shield1._dmg = 4;
		shield1._heal = 0;
		shield1._mana = 0;
		shield1._price = 10;
		shield1._serial = 13;
		_vItem.push_back(shield1);

	}
	//아이템 생성

	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{
}

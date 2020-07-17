#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�ε� �̹��� �� ���� �ʱ�ȭ
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ�� ����
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("����ȭ��");
	}
}

void loadingScene::render()
{
	//�ε�Ŭ���� ����
	_loading->render();
}


//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//���ȭ�� (��� & ��)
	_loading->loadImage("��׶���", "Images/background.bmp", 9152, 2048);
	_loading->loadImage("�ʵ�����", "Images/�ʵ�����.bmp", 7150, 1600);
	_loading->loadImage("�ʵ��浹", "Images/�ʵ�����(�浹).bmp", 7150, 1600);
	_loading->loadImage("����1", "Images/����1.bmp", 16384, 3072);
	_loading->loadImage("����1�浹", "Images/����1(�浹).bmp", 16384, 3072);
	_loading->loadImage("����2", "Images/����2.bmp", 4608, 1536);
	_loading->loadImage("����2�浹", "Images/����2(�浹).bmp", 4608, 1536);
	_loading->loadImage("����3", "Images/����3.bmp", 7680, 3584);
	_loading->loadImage("����3�浹", "Images/����3(�浹).bmp", 7680, 3584);
	_loading->loadImage("������", "Images/������.bmp", 7392, 1536);
	_loading->loadImage("������(�浹)", "Images/������(�浹).bmp", 7392, 1536);

	//���� ������Ʈ
	_loading->loadFrameImage("torch", "Images/torch.bmp", 672, 143, 12, 1);
	_loading->loadFrameImage("spring", "Images/spring.bmp", 320, 64, 5, 1);


	//�÷��̾�
	_loading->loadFrameImage("idle", "Images/ĳ����(idle).bmp", WINSIZEX / 2, WINSIZEY - 100, 700, 204, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("move", "Images/ĳ����(�̵�).bmp", 980, 204, 14, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("jump", "Images/ĳ����(����).bmp", 490, 204, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("fall", "Images/ĳ����(����).bmp", 280, 204, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("att1", "Images/����1.bmp", 560, 204, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("att2", "Images/����2.bmp", 560, 204, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("att3", "Images/����3.bmp", 560, 204, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("dash", "Images/ĳ����(dash).bmp", 2048, 128, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�ܻ�1", "Images/att1.bmp", 1680, 510, 7, 2);
	_loading->loadFrameImage("�ܻ�2", "Images/att2.bmp", 1680, 510, 7, 2);
	_loading->loadFrameImage("�ܻ�3", "Images/att3.bmp", 1680, 510, 7, 2);
	_loading->loadImage("death", "Images/death.bmp", 128, 128);

	//UI ���� �̹���
	_loading->loadImage("start", "Images/start.bmp", 400, 150);
	_loading->loadImage("goldicon", "Images/goldicon.bmp", 45, 48);
	_loading->loadImage("inven", "Images/inventory.bmp", 662, 880);
	_loading->loadImage("shop", "Images/shop.bmp", 662, 700);
	_loading->loadImage("shop(buy)", "Images/shop(buy).bmp", 450, 70);
	_loading->loadImage("shop(sell)", "Images/shop(sell).bmp", 450, 70);
	_loading->loadImage("shop(gold)", "Images/shop(gold).bmp", 160, 80);
	_loading->loadImage("notice", "Images/notice.bmp", 300, 50);
	_loading->loadImage("openshop", "Images/openshop.bmp", 300, 50);
	_loading->loadImage("enter", "Images/enter.bmp", 300, 50);
	_loading->loadImage("exit", "Images/exit.bmp", 300, 50);
	_loading->loadImage("right", "Images/right.bmp", 128, 64);
	_loading->loadImage("left", "Images/left.bmp", 128, 64);
	_loading->loadImage("invenbg(acce)", "Images/item/invenbg(acce).bmp", 92, 92);
	_loading->loadImage("invenbg(shield)", "Images/item/invenbg(shield).bmp", 92, 92);
	_loading->loadImage("invenbg(weapon)", "Images/item/invenbg(weapon).bmp", 92, 92);
	_loading->loadImage("inven(icon)", "Images/inven(icon).bmp", 90, 74);

	//���� ������ �̹���(����)
	_loading->loadImage("axe", "Images/item/axe.bmp", 575, 110);
	_loading->loadImage("bark", "Images/item/bark.bmp", 575, 110);
	_loading->loadImage("bow", "Images/item/bow.bmp", 575, 110);
	_loading->loadImage("crude", "Images/item/crude.bmp", 575, 110);
	_loading->loadImage("dubnos", "Images/item/dubnos.bmp", 575, 110);
	_loading->loadImage("fryingpan", "Images/item/fryingpan.bmp", 575, 110);
	_loading->loadImage("greatsword", "Images/item/greatsword.bmp", 575, 110);
	_loading->loadImage("heart", "Images/item/heart.bmp", 575, 110);
	_loading->loadImage("mace", "Images/item/mace.bmp", 575, 110);
	_loading->loadImage("scimitar", "Images/item/scimitar.bmp", 575, 110);
	_loading->loadImage("shield", "Images/item/shield.bmp", 575, 110);
	_loading->loadImage("taranis", "Images/item/taranis.bmp", 575, 110);
	_loading->loadImage("warhammer", "Images/item/warhammer.bmp", 575, 110);
	_loading->loadImage("witchblade", "Images/item/witchblade.bmp", 575, 110);
	_loading->loadImage("inven(axe)", "Images/item/inven(axe).bmp", 92, 96);
	_loading->loadImage("inven(bark)", "Images/item/inven(bark).bmp", 92, 96);
	_loading->loadImage("inven(bow)", "Images/item/inven(bow).bmp", 92, 96);
	_loading->loadImage("inven(crude)", "Images/item/inven(crude).bmp", 92, 96);
	_loading->loadImage("inven(dubnos)", "Images/item/inven(dubnos).bmp", 92, 96);
	_loading->loadImage("inven(fryingpan)", "Images/item/inven(fryingpan).bmp", 92, 96);
	_loading->loadImage("inven(greatsword)", "Images/item/inven(greatsword).bmp", 92, 96);
	_loading->loadImage("inven(heart)", "Images/item/inven(heart).bmp", 92, 96);
	_loading->loadImage("inven(mace)", "Images/item/inven(mace).bmp", 92, 96);
	_loading->loadImage("inven(scimitar)", "Images/item/inven(scimitar).bmp", 92, 96);
	_loading->loadImage("inven(shield)", "Images/item/inven(shield).bmp", 92, 96);
	_loading->loadImage("inven(taranis)", "Images/item/inven(taranis).bmp", 92, 96);
	_loading->loadImage("inven(warhammer)", "Images/item/inven(warhammer).bmp", 92, 96);
	_loading->loadImage("inven(witchblade)", "Images/item/inven(witchblade).bmp", 92, 96);
	_loading->loadFrameImage("electric", "Images/electric.bmp", 2048, 128, 8, 2);
	_loading->loadImage("heal", "Images/heal.bmp", 128, 128);

	_loading->loadImage("CharPortrait", "Images/CharPortrait.bmp", 150, 150);
	_loading->loadImage("bgHp", "Images/bgBar.bmp", 214, 29);
	_loading->loadImage("frontHp", "Images/frontBar.bmp", 214, 29);
	_loading->loadImage("bgMp", "Images/bgBar.bmp", 214, 15);
	_loading->loadImage("frontMp", "Images/manaBar.bmp", 214, 15);

	//����
	_loading->loadFrameImage("crude(idle)", "Images/crude(idle).bmp", 800, 96, 10, 2);
	_loading->loadFrameImage("crude(move)", "Images/crude(move).bmp", 2240, 320, 14, 2);
	_loading->loadFrameImage("crude(jump)", "Images/crude(jump).bmp", 560, 96, 7, 2);
	_loading->loadFrameImage("crude(fall)", "Images/crude(fall).bmp", 384, 128, 4, 2);
	_loading->loadFrameImage("crude(att1)", "Images/crude(att1).bmp", 1232, 320, 7, 2);
	_loading->loadFrameImage("crude(att2)", "Images/crude(att2).bmp", 560, 224, 7, 2);
	_loading->loadFrameImage("crude(att3)", "Images/crude(att3).bmp", 896, 320, 7, 2);

	//���ʹ�
	_loading->loadFrameImage("skeleton(idle)", "Images/skeleton(idle).bmp", 1440, 288, 10, 2);
	_loading->loadFrameImage("skeleton(move)", "Images/skeleton(move).bmp", 1440, 288, 10, 2);
	_loading->loadFrameImage("skeleton(att)", "Images/skeleton(att).bmp", 1456, 352, 7, 2);
	_loading->loadFrameImage("skeleton(found)", "Images/skeleton(found).bmp", 1440, 288, 10, 2);
	_loading->loadFrameImage("skeleton(hit)", "Images/skeleton(hit).bmp", 1440, 288, 10, 2);
	_loading->loadFrameImage("skeleton(hit2)", "Images/skeleton(hit2).bmp", 2592, 432, 12, 2);
	_loading->loadFrameImage("skeleton(dead)", "Images/skeleton(dead).bmp", 640, 128, 10, 1);
	_loading->loadFrameImage("explosion", "Images/explosion.bmp", 2000, 128, 16, 1);
	_loading->loadImage("found", "Images/found.bmp", 64, 64);


	//����
	_loading->loadFrameImage("boss(move)", "Images/boss(move).bmp", 5120, 1024, 10, 2);
	_loading->loadFrameImage("boss(att)", "Images/boss(att).bmp", 5120, 1024, 10, 2);
	_loading->loadFrameImage("boss(summon)", "Images/boss(summon).bmp", 5120, 1024, 10, 2);
	_loading->loadImage("boss(maxhp)", "Images/boss(maxhp).bmp", 1500, 33);
	_loading->loadImage("boss(hp)", "Images/boss(hp).bmp", 1500, 33);

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	//for (int i = 0; i < 100; i++)
	//{
	//	_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	//}

	_loading->loadFrameImage("ufo", "Images/ĳ����(idle).bmp", 700, 204, 10, 2);
	_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("ball", "ball.bmp", 60, 60);

	//�÷� ����
	_loading->loadFrameImage("gold(num)", "Images/number/gold(num).bmp", 300, 48, 10,1);
	_loading->loadFrameImage("red(num)", "Images/number/red(num).bmp", 300, 48, 10, 1);
	_loading->loadFrameImage("blue(num)", "Images/number/blue(num).bmp", 300, 48, 10, 1);
	//_loading->loadImage("gold0", "Images/number/gold(0).bmp", 30, 48);
	//_loading->loadImage("gold1", "Images/number/gold(1).bmp", 30, 48);
	//_loading->loadImage("gold2", "Images/number/gold(2).bmp", 30, 48);
	//_loading->loadImage("gold3", "Images/number/gold(3).bmp", 30, 48);
	//_loading->loadImage("gold4", "Images/number/gold(4).bmp", 30, 48);
	//_loading->loadImage("gold5", "Images/number/gold(5).bmp", 30, 48);
	//_loading->loadImage("gold6", "Images/number/gold(6).bmp", 30, 48);
	//_loading->loadImage("gold7", "Images/number/gold(7).bmp", 30, 48);
	//_loading->loadImage("gold8", "Images/number/gold(8).bmp", 30, 48);
	//_loading->loadImage("gold9", "Images/number/gold(9).bmp", 30, 48);
	//_loading->loadImage("red0", "Images/number/red(0).bmp", 30, 48);
	//_loading->loadImage("red1", "Images/number/red(1).bmp", 30, 48);
	//_loading->loadImage("red2", "Images/number/red(2).bmp", 30, 48);
	//_loading->loadImage("red3", "Images/number/red(3).bmp", 30, 48);
	//_loading->loadImage("red4", "Images/number/red(4).bmp", 30, 48);
	//_loading->loadImage("red5", "Images/number/red(5).bmp", 30, 48);
	//_loading->loadImage("red6", "Images/number/red(6).bmp", 30, 48);
	//_loading->loadImage("red7", "Images/number/red(7).bmp", 30, 48);
	//_loading->loadImage("red8", "Images/number/red(8).bmp", 30, 48);
	//_loading->loadImage("red9", "Images/number/red(9).bmp", 30, 48);
	//_loading->loadImage("blue0", "Images/number/blue(0).bmp", 30, 48);
	//_loading->loadImage("blue1", "Images/number/blue(1).bmp", 30, 48);
	//_loading->loadImage("blue2", "Images/number/blue(2).bmp", 30, 48);
	//_loading->loadImage("blue3", "Images/number/blue(3).bmp", 30, 48);
	//_loading->loadImage("blue4", "Images/number/blue(4).bmp", 30, 48); 
	//_loading->loadImage("blue5", "Images/number/blue(5).bmp", 30, 48);
	//_loading->loadImage("blue6", "Images/number/blue(6).bmp", 30, 48);
	//_loading->loadImage("blue7", "Images/number/blue(7).bmp", 30, 48);
	//_loading->loadImage("blue8", "Images/number/blue(8).bmp", 30, 48);
	//_loading->loadImage("blue9", "Images/number/blue(9).bmp", 30, 48);
}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound()
{
	_loading->loadSound("����", "Sounds/ken_KOmake.wav", false, false);
	_loading->loadSound("Ÿ��1", "Sounds/ken_kiai_4.wav", false, false);
	_loading->loadSound("Ÿ��2", "Sounds/ken_kiai_1.wav", false, false);
	_loading->loadSound("Ÿ��3", "Sounds/ken_kiai_3.wav", false, false);
	_loading->loadSound("jumping", "Sounds/jumping.wav", false, false);


	_loading->loadSound("fieldbgm", "Sounds/field.mp3", false, true);
	_loading->loadSound("cavebgm", "Sounds/GoKing-d.mp3", false, true);
	_loading->loadSound("cave2bgm", "Sounds/shopping.mp3", false, true);
	_loading->loadSound("bossbgm", "Sounds/3kingdom_normal.mp3",false,true);
}

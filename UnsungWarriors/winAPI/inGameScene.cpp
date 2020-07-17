#include "stdafx.h"
#include "inGameScene.h"

HRESULT inGameScene::init()
{
	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = new player;
	_player->init();

	//���Ŵ��� Ŭ���� �ʱ�ȭ
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//��ȣ����
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void inGameScene::release()
{
	//�÷��̾� Ŭ���� ����
	_player->release();
	SAFE_DELETE(_player);

	//���Ŵ��� Ŭ���� ����
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void inGameScene::update()
{
	//�÷��̾� Ŭ���� ������Ʈ
	_player->update();

	//���Ŵ��� ������Ʈ
	_enemyManager->update();

	if (INPUT->GetKeyDown(VK_RETURN))
	{
		SCENEMANAGER->loadScene("����ȭ��");
	}
}

void inGameScene::render()
{
	//��׶��� ����
	IMAGEMANAGER->render("��׶���", getMemDC());

	//�÷��̾� Ŭ���� ����
	_player->render();

	//���Ŵ��� Ŭ���� ����
	_enemyManager->render();

}
